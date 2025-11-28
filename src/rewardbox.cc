#include "rewardbox.h"

#include <cairomm/context.h>
#include <gdkmm/general.h>
#include <glibmm/fileutils.h>

#include <format>
#include <iostream>

RewardBox::RewardArea::RewardArea() : m_state(0), m_enabled(false) {
  for (auto r : m_rewards) {
    Glib::RefPtr<Gdk::Pixbuf> img =
        Gdk::Pixbuf::create_from_resource(std::format("/org/smz3t/{}.png", r));
    m_reward_images.push_back(img);
  }
  set_size_request(m_reward_images[0]->get_width(),
                   m_reward_images[0]->get_height());
  m_max_state = m_reward_images.size() - 1;
}

RewardBox::RewardArea::~RewardArea() {}

void RewardBox::RewardArea::draw_next_state() {
  if (m_state >= m_max_state) {
    m_state = -1;
  }
  m_state++;
  queue_draw();
}

void RewardBox::RewardArea::draw_init_state() {
  m_enabled = false;
  m_state = 0;
  queue_draw();
}

bool RewardBox::RewardArea::get_enabled() { return m_enabled; }

void RewardBox::RewardArea::set_enabled(bool is_enabled) {
  m_enabled = is_enabled;
  queue_draw();
}

bool RewardBox::RewardArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
  if (!m_enabled) {
    set_opacity(0.4);
  } else {
    set_opacity(1.0);
  }

  Gtk::Allocation allocation = get_allocation();
  const int width = allocation.get_width();
  const int height = allocation.get_height();

  Glib::RefPtr<Gdk::Pixbuf> img = m_reward_images[m_state];
  const int img_width = img->get_width();
  const int img_height = img->get_height();
  Gdk::Cairo::set_source_pixbuf(cr, img, (width - img_width) / 2,
                                (height - img_height) / 2);
  cr->paint();

  return true;
}

RewardBox::RewardBox() {
  add(m_item);
  add_events(Gdk::EventMask::BUTTON_RELEASE_MASK);
  signal_button_release_event().connect(
      sigc::mem_fun(*this, &RewardBox::on_button_release));
}

RewardBox::~RewardBox() {}

bool RewardBox::on_button_release(GdkEventButton* event) {
  if (event->type == GDK_BUTTON_RELEASE) {
    switch (event->button) {
      case 1:  // Left click
        m_item.set_enabled(!m_item.get_enabled());
        break;
      case 2:  // Middle click
        m_item.draw_init_state();
        break;
      case 3:  // Right click
        m_item.draw_next_state();
        break;
      default:
        break;
    }
    return true;
  }
  return false;
}
