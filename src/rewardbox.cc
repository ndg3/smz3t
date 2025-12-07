#include "rewardbox.h"

#include <cairomm/context.h>
#include <gdkmm/general.h>
#include <glibmm/fileutils.h>

#include <format>
#include <string>

namespace Smz3t {

RewardBox::RewardBox() : m_state(0), m_enabled(false) {
  const std::vector<std::string> rewards{
      "hyrule/green_pendant", "hyrule/blue_red_pendant",
      "hyrule/blue_crystal",  "hyrule/red_crystal",
      "zebes/kraid_reward",   "zebes/phantoon_reward",
      "zebes/draygon_reward", "zebes/ridley_reward"};

  for (auto& r : rewards) {
    auto img =
        Gdk::Pixbuf::create_from_resource(std::format("/org/smz3t/{}.png", r));
    m_reward_imgs.push_back(img);
  }

  set_size_request(m_reward_imgs[0]->get_width(),
                   m_reward_imgs[0]->get_height());

  m_max_state = m_reward_imgs.size() - 1;

  add_events(Gdk::EventMask::BUTTON_RELEASE_MASK);
  signal_button_release_event().connect(
      sigc::mem_fun(*this, &RewardBox::on_button_release));
}

RewardBox::~RewardBox() {}

bool RewardBox::on_button_release(GdkEventButton* event) {
  // Stop if the user did something other than a click
  if (event->type != GDK_BUTTON_RELEASE) return false;

  switch (event->button) {
    case 1:  // Left click
      m_enabled = !m_enabled;
      break;
    case 2:  // Middle click
      m_enabled = false;
      m_state = 0;
      break;
    case 3:  // Right click
      if (m_state >= m_max_state) m_state = -1;
      ++m_state;
      break;
  }

  queue_draw();
  return true;
}

bool RewardBox::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
  // Set opacity to 100% if enabled, 40% otherwise
  set_opacity(m_enabled ? 1.0 : 0.4);

  // Start with black background
  cr->set_source_rgb(0, 0, 0);
  cr->fill();
  cr->paint();

  // Draw current image in the center of the drawing area
  const int alloc_w = get_allocated_width();
  const int alloc_h = get_allocated_height();
  auto& img = m_reward_imgs[m_state];
  const int img_w = img->get_width();
  const int img_h = img->get_height();
  Gdk::Cairo::set_source_pixbuf(cr, img, (alloc_w - img_w) / 2,
                                (alloc_h - img_h) / 2);
  cr->paint();

  return true;
}

}  // namespace Smz3t
