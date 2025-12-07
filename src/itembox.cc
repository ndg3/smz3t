#include "itembox.h"

#include <cairomm/context.h>
#include <gdkmm/general.h>
#include <glibmm/fileutils.h>

#include <algorithm>
#include <format>
#include <string>

namespace Smz3t {

ItemBox::ItemBox() {}

ItemBox::ItemBox(std::vector<std::string> images, unsigned int r_start,
                 unsigned int r_end, unsigned int r_step)
    : m_r_start(r_start), m_r_end(r_end), m_r_step(r_step), m_state(0) {
  for (auto& i : images) {
    auto img =
        Gdk::Pixbuf::create_from_resource(std::format("/org/smz3t/{}.png", i));
    m_imgs.push_back(img);
  }

  set_size_request(m_imgs[0]->get_width(), m_imgs[0]->get_height());

  m_max_state = r_step > 0 ? (r_end - r_start) / r_step + 1 : 1;
  m_max_state = std::max<unsigned int>(m_max_state, m_imgs.size());

  add_events(Gdk::EventMask::BUTTON_RELEASE_MASK);
  signal_button_release_event().connect(
      sigc::mem_fun(*this, &ItemBox::on_button_release));
}

ItemBox::~ItemBox() {}

bool ItemBox::on_button_release(GdkEventButton* event) {
  // Stop if the user did something other than a click
  if (event->type != GDK_BUTTON_RELEASE) return false;

  switch (event->button) {
    case 1:  // Left click
      if (m_state < m_max_state) ++m_state;
      break;
    case 2:  // Middle click
      m_state = 0;
      break;
    case 3:  // Right click
      if (m_state > 0) --m_state;
      break;
  }

  queue_draw();
  return true;
}

bool ItemBox::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
  // Set opacity to 40% if in initial state
  set_opacity(m_state == 0 ? 0.4 : 1.0);

  // Start with black background
  cr->set_source_rgb(0, 0, 0);
  cr->fill();
  cr->paint();

  // Draw current image in the center of the drawing area
  const int alloc_w = get_allocated_width();
  const int alloc_h = get_allocated_height();
  auto& img = m_imgs[std::clamp<unsigned int>(m_state, 1, m_imgs.size()) - 1];
  const int img_w = img->get_width();
  const int img_h = img->get_height();
  Gdk::Cairo::set_source_pixbuf(cr, img, (alloc_w - img_w) / 2,
                                (alloc_h - img_h) / 2);
  cr->paint();

  // Stop if there is no range to draw or if in the initial state
  if (m_r_step == 0 || m_state == 0) return true;

  // Draw current range value in bold text with a faint black background for
  // contrast
  unsigned int count = m_r_start + (m_state - 1) * m_r_step;
  std::string markup = std::format(
      "<span background=\"#0000003F\" weight=\"bold\">{}</span>", count);

  // Draw the range value in green if at the end, otherwise draw in white
  if (count == m_r_end)
    cr->set_source_rgb(0, 1, 0);
  else
    cr->set_source_rgb(1, 1, 1);

  // Draw the range value in the bottom-right corner of the drawing area
  auto layout = create_pango_layout("");
  layout->set_markup(markup);
  int markup_w, markup_h;
  layout->get_pixel_size(markup_w, markup_h);
  cr->move_to((alloc_w + img_w) / 2 - markup_w,
              (alloc_h + img_h) / 2 - markup_h);
  layout->show_in_cairo_context(cr);

  return true;
}

}  // namespace Smz3t
