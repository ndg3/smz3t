#include "itembox.h"

#include <cairomm/context.h>
#include <gdkmm/general.h>
#include <glibmm/fileutils.h>

#include <algorithm>
#include <format>
#include <iostream>

ItemArea::ItemArea() {}

ItemArea::ItemArea(std::vector<std::string> images, unsigned int range_start,
                   unsigned int range_end, unsigned int range_step)
    : m_range_start(range_start),
      m_range_end(range_end),
      m_range_step(range_step),
      m_state(0) {
  for (auto i : images) {
    Glib::RefPtr<Gdk::Pixbuf> img =
        Gdk::Pixbuf::create_from_resource(std::format("/org/smz3t/{}.png", i));
    m_images.push_back(img);
  }
  set_size_request(m_images[0]->get_width(), m_images[0]->get_height());
  if (!m_range_step) {
    m_max_state = m_images.size();
  } else {
    m_max_state = std::max(static_cast<unsigned int>(m_images.size()),
                           (m_range_end - m_range_start) / m_range_step + 1);
  }
}

ItemArea::~ItemArea() {}

void ItemArea::draw_next_state() {
  if (m_state >= m_max_state) {
    return;
  }
  m_state++;
  queue_draw();
}

void ItemArea::draw_init_state() {
  m_state = 0;
  queue_draw();
}

void ItemArea::draw_prev_state() {
  if (!m_state) {
    return;
  }
  m_state--;
  queue_draw();
}

bool ItemArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
  if (!m_state) {
    set_opacity(0.4);
  } else {
    set_opacity(1.0);
  }

  Gtk::Allocation allocation = get_allocation();
  const int width = allocation.get_width();
  const int height = allocation.get_height();

  std::size_t index = m_state;
  if (index >= m_images.size()) {
    index = m_images.size();
  }
  Glib::RefPtr<Gdk::Pixbuf> image = m_state ? m_images[index - 1] : m_images[0];
  const int image_width = image->get_width();
  const int image_height = image->get_height();
  Gdk::Cairo::set_source_pixbuf(cr, image, (width - image_width) / 2,
                                (height - image_height) / 2);
  cr->paint();

  if (!(m_range_step && m_state)) {
    return true;
  }

  unsigned int text = m_range_start + (m_state - 1) * m_range_step;
  std::string color;
  if (text >= m_range_end) {
    text = m_range_end;
    color = "#00FF00FF";
  } else {
    color = "#FFFFFFFF";
  }
  Pango::FontDescription font;
  font.set_weight(Pango::WEIGHT_BOLD);
  auto layout = create_pango_layout("");
  layout->set_markup(g_markup_printf_escaped(
      "<span background=\"#00000077\" foreground=\"%s\">%d</span>",
      color.c_str(), text));
  layout->set_font_description(font);
  int text_width, text_height;
  layout->get_pixel_size(text_width, text_height);
  cr->move_to((width + image_width) / 2 - text_width,
              (height + image_height) / 2 - text_height);
  layout->show_in_cairo_context(cr);

  return true;
}

ItemBox::ItemBox() {}

ItemBox::ItemBox(std::vector<std::string> images, unsigned int range_start,
                 unsigned int range_end, unsigned int range_step)
    : m_item(images, range_start, range_end, range_step) {
  add(m_item);
  add_events(Gdk::EventMask::BUTTON_RELEASE_MASK);
  signal_button_release_event().connect(
      sigc::mem_fun(*this, &ItemBox::on_button_release));
}

ItemBox::~ItemBox() {}

bool ItemBox::on_button_release(GdkEventButton* event) {
  if (event->type == GDK_BUTTON_RELEASE) {
    switch (event->button) {
      case 1:  // Left click
        m_item.draw_next_state();
        break;
      case 2:  // Middle click
        m_item.draw_init_state();
        break;
      case 3:  // Right click
        m_item.draw_prev_state();
        break;
      default:
        break;
    }
    return true;
  }
  return false;
}
