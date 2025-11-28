#ifndef SMZ3T_REWARDBOX_H
#define SMZ3T_REWARDBOX_H

#include <gtkmm/drawingarea.h>
#include <gtkmm/eventbox.h>

#include <string>
#include <vector>

class RewardBox : public Gtk::EventBox {
 public:
  RewardBox();
  virtual ~RewardBox();

 protected:
  class RewardArea : public Gtk::DrawingArea {
   public:
    RewardArea();
    virtual ~RewardArea();

    void draw_next_state();
    void draw_init_state();

    bool get_enabled();
    void set_enabled(bool is_enabled);

   protected:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
    const std::vector<std::string> m_rewards{
        "zelda/green_pendant",    "zelda/blue_red_pendant",
        "zelda/blue_crystal",     "zelda/red_crystal",
        "metroid/kraid_reward",   "metroid/phantoon_reward",
        "metroid/draygon_reward", "metroid/ridley_reward"};
    std::vector<Glib::RefPtr<Gdk::Pixbuf>> m_reward_images;
    unsigned int m_state;
    unsigned int m_max_state;
    bool m_enabled;
  };
  bool on_button_release(GdkEventButton* event);
  RewardArea m_item;
};

#endif  // SMZ3T_REWARDBOX_H
