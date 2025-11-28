#include "dungeongrid.h"

#include <cairomm/context.h>
#include <gdkmm/general.h>
#include <glibmm/fileutils.h>

#include <format>
#include <iostream>

SmallKeyBox::SmallKeyArea::SmallKeyArea() {}

SmallKeyBox::SmallKeyArea::SmallKeyArea(unsigned int keys, bool is_box)
    : m_state(0), m_count(keys) {
  Glib::RefPtr<Gdk::Pixbuf> img = Gdk::Pixbuf::create_from_resource(
      std::format("/org/smz3t/zelda/{}_key.png", is_box ? "box" : "drop"));
  m_key_image = img;
  set_size_request(m_key_image->get_width(), m_key_image->get_height());
}

SmallKeyBox::SmallKeyArea::~SmallKeyArea() {}

void SmallKeyBox::SmallKeyArea::draw_next_state() {
  if (m_state >= m_count) {
    return;
  }
  m_state++;
  queue_draw();
}

void SmallKeyBox::SmallKeyArea::draw_init_state() {
  m_state = 0;
  queue_draw();
}

void SmallKeyBox::SmallKeyArea::draw_prev_state() {
  if (!m_state) {
    return;
  }
  m_state--;
  queue_draw();
}

bool SmallKeyBox::SmallKeyArea::on_draw(
    const Cairo::RefPtr<Cairo::Context>& cr) {
  if (!m_state) {
    set_opacity(0.4);
  } else {
    set_opacity(1.0);
  }

  Gtk::Allocation allocation = get_allocation();
  const int width = allocation.get_width();
  const int height = allocation.get_height();

  const int img_width = m_key_image->get_width();
  const int img_height = m_key_image->get_height();
  Gdk::Cairo::set_source_pixbuf(cr, m_key_image, (width - img_width) / 2,
                                (height - img_height) / 2);
  cr->paint();

  if (!m_count) {
    return true;
  }

  std::string color;
  if (m_state >= m_count) {
    m_state = m_count;
    color = "#00FF00FF";
  } else {
    color = "#FFFFFFFF";
  }
  Pango::FontDescription font;
  font.set_weight(Pango::WEIGHT_BOLD);
  auto layout = create_pango_layout("");
  layout->set_markup(g_markup_printf_escaped(
      "<span background=\"#00000077\" foreground=\"%s\">%d/%d</span>",
      color.c_str(), m_state, m_count));
  layout->set_font_description(font);
  int text_width, text_height;
  layout->get_pixel_size(text_width, text_height);
  cr->move_to((width + img_width) / 2 - text_width,
              (height + img_height) / 2 - text_height);
  layout->show_in_cairo_context(cr);

  return true;
}

SmallKeyBox::SmallKeyBox() {}

SmallKeyBox::SmallKeyBox(unsigned int keys, bool is_box)
    : m_keys(keys, is_box) {
  add(m_keys);
  add_events(Gdk::EventMask::BUTTON_RELEASE_MASK);
  signal_button_release_event().connect(
      sigc::mem_fun(*this, &SmallKeyBox::on_button_release));
}

SmallKeyBox::~SmallKeyBox() {}

bool SmallKeyBox::on_button_release(GdkEventButton* event) {
  if (event->type == GDK_BUTTON_RELEASE) {
    switch (event->button) {
      case 1:  // Left click
        m_keys.draw_next_state();
        break;
      case 2:  // Middle click
        m_keys.draw_init_state();
        break;
      case 3:  // Right click
        m_keys.draw_prev_state();
        break;
      default:
        break;
    }
    return true;
  }
  return false;
}

DungeonRow::DungeonRow() {}

DungeonRow::DungeonRow(std::string dungeon_abbr, bool has_reward,
                       unsigned box_keys, unsigned drop_keys)
    : m_name(dungeon_abbr),
      m_dungeon_map({"zelda/dungeon_map"}),
      m_compass({"zelda/compass"}),
      m_big_key({"zelda/big_key"}) {
  auto context = m_name.get_pango_context();
  auto font = context->get_font_description();
  font.set_weight(Pango::WEIGHT_BOLD);
  context->set_font_description(font);

  if (has_reward) {
    m_reward = std::make_unique<RewardBox>();
  }
  if (box_keys) {
    m_box_keys = std::unique_ptr<SmallKeyBox>(new SmallKeyBox(box_keys, true));
  }
  if (drop_keys) {
    m_drop_keys =
        std::unique_ptr<SmallKeyBox>(new SmallKeyBox(drop_keys, false));
  }
}

DungeonRow::~DungeonRow() {}

DungeonGrid::DungeonGrid() {}

DungeonGrid::~DungeonGrid() {}

void DungeonGrid::add_row(DungeonRow* dungeon_row) {
  m_rows.emplace_back(dungeon_row);
  int r = 0;
  int c = m_rows.size() - 1;
  attach(dungeon_row->m_name, r, c);
  if (dungeon_row->m_reward) {
    attach(*dungeon_row->m_reward, r + 1, c);
  }
  attach(dungeon_row->m_dungeon_map, r + 2, c);
  attach(dungeon_row->m_compass, r + 3, c);
  if (dungeon_row->m_box_keys) {
    attach(*dungeon_row->m_box_keys, r + 4, c);
  }
  if (dungeon_row->m_drop_keys) {
    attach(*dungeon_row->m_drop_keys, r + 5, c);
  }
  attach(dungeon_row->m_big_key, r + 6, c);
}
