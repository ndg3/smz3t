#ifndef SMZ3T_REWARDBOX_H
#define SMZ3T_REWARDBOX_H

#include <gtkmm/drawingarea.h>
#include <gtkmm/eventbox.h>

#include <vector>

namespace Smz3t {

/**
 * The RewardBox widget represents a reward from either game.
 *
 * Each RewardBox has the same list of images for each possible reward. Some
 * rewards are merged because collecting one or another has the same effect.
 *
 * The images are drawn in this order:
 * - From _A Link to the Past_:
 *   - The Green Pendant (for checking the Master Sword pedestal with Blue and
 *     Red Pendant **and** for checking Sahasrahla)
 *   - The Blue or Red Pendant (for checking Master Sword Pedestal with
 *     Green Pendant)
 *   - The Blue Crystal (Crystals 1-4 and 7, for opening Ganon's Tower with Red
 *     Crystals)
 *   - The Red Crystal (Crystals 5-6, for opening Ganon's Tower with Blue
 *     Crystals **and** for checking Pyramid Fairy)
 * - From _Super Metroid_:
 *   - Kraid's Reward (for entering Tourian)
 *   - Phantoon's Reward ('')
 *   - Draygon's Reward ('')
 *   - Ridley's Reward ('')
 *
 * Like the ItemBox, the RewardBox has a black background and draws its initial
 * state at 40% opacity.
 *
 * When the RewardBox is left-clicked, its opacity is toggled between 40% and
 * 100%.
 *
 * When the RewardBox is right-clicked, it cycles through the available rewards
 * without changing the opacity.
 *
 * When the RewardBox is middle-clicked, it reverts to its initial state, and
 * further middle-clicks are ignored.
 */
class RewardBox : public Gtk::EventBox {
 public:
  RewardBox();
  virtual ~RewardBox();

 protected:
  /**
   * Signal that redraws the ItemBox with the new state according to the button
   * clicked.
   *
   * @param event The event that triggered this signal.
   * @returns True to stop other handlers from being invoked for the event.
   * False to propagate the event further.
   */
  bool on_button_release(GdkEventButton* event);

  /**
   * Signal handler for drawing the current image onto the given Cairo context.
   *
   * The image according to the current state is centered on a black background.
   * If the state is zero, then the area has 40% opacity.
   *
   * @param cr The context to draw on.
   * @returns True to stop other handlers from being invoked for the event.
   * False to propagate the event further.
   */
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

  std::vector<Glib::RefPtr<Gdk::Pixbuf>> m_reward_imgs;
  unsigned int m_state;
  unsigned int m_max_state;
  bool m_enabled;
};

}  // namespace Smz3t

#endif  // SMZ3T_REWARDBOX_H
