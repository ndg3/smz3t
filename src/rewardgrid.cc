#include "rewardgrid.h"

LabelBox::LabelBox(std::vector<std::string> labels)
    : m_label("???"), m_text(labels), m_state(0) {
  add(m_label);
  add_events(Gdk::EventMask::BUTTON_RELEASE_MASK);
  signal_button_release_event().connect(
      sigc::mem_fun(*this, &LabelBox::on_button_release));
}

LabelBox::~LabelBox() {}

bool LabelBox::on_button_release(GdkEventButton* event) {
  if (event->type == GDK_BUTTON_RELEASE) {
    switch (event->button) {
      case 1:  // Left click
        if (m_state >= m_text.size()) {
          m_state = 0;
        }
        m_state++;
        m_label.set_text(m_text[m_state - 1]);
        break;
      case 2:  // Middle click
        m_state = 0;
        m_label.set_text("???");
        break;
      case 3:  // Right click
        if (!m_state) {
          break;
        }
        if (m_state == 1) {
          m_state = m_text.size() + 1;
        }
        m_state--;
        m_label.set_text(m_text[m_state - 1]);
        break;
      default:
        break;
    }
  }
  return false;
}

RewardGrid::RewardGrid(std::vector<std::string> reward)
    : m_state(0), m_item(reward), m_label({m_dungeons}) {
  add(m_item);
  attach_next_to(m_label, m_item, Gtk::POS_BOTTOM);
}

RewardGrid::~RewardGrid() {}
