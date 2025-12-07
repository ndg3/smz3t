#ifndef SMZ3T_ITEMBOX_H
#define SMZ3T_ITEMBOX_H

#include <gdkmm/pixbuf.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/eventbox.h>

#include <string>
#include <vector>

namespace Smz3t {

/**
 * The ItemBox widget represents a trackable item.
 *
 * Each ItemBox has a list of images that represents the item and its
 * progressive upgrades and a range of values for displaying how many of an
 * item has been collected. Usually an ItemBox with a range has only one image
 * in its list. The ItemBox also has a black background to provide better
 * contrast with light GTK themes.
 *
 * When an ItemBox is initially drawn, it shows its first image and has an
 * opacity of 40% and does not show any range values.
 *
 * When the ItemBox is left-clicked, its opacity changes to 100% and the range's
 * start value is drawn (if the range has been specified). The ItemBox can
 * continue to be left-clicked to draw its next state, whether that is the next
 * image or the next value in the range. Once there are no more images to draw
 * or the range has reached its end, further left clicks are ignored.
 *
 * When the ItemBox is right-clicked, its previous state is drawn instead. When
 * the ItemBox reaches its initial state, its opacity reverts to 40% and omits
 * the range value. Right clicks are ignored when the ItemBox is in its initial
 * state.
 *
 * When the ItemBox is middle-clicked, it reverts to its initial state, and
 * further middle clicks are ignored.
 */
class ItemBox : public Gtk::EventBox {
 public:
  ItemBox();
  ItemBox(std::vector<std::string> images, unsigned int range_start = 0,
          unsigned int range_end = 0, unsigned int range_step = 0);
  virtual ~ItemBox();

 protected:
  /**
   * Signal that redraws the ItemBox with the new state according to the button
   * clicked.
   *
   * @param event The event that triggered this signal.
   * @returns True to stop other handlers from being invoked for the event.
   * False to propagate the event further.
   */
  virtual bool on_button_release(GdkEventButton* event);

  /**
   * Signal handler for drawing the current image onto the given Cairo context.
   *
   * The image according to the current state is centered on a black background,
   * and any text is drawn at the bottom-right corner. If the state is maxed
   * out, then the text is green, otherwise it is white. If the state is zero,
   * then no text is drawn and the area has 40% opacity.
   *
   * @param cr The context to draw on.
   * @returns True to stop other handlers from being invoked for the event.
   * False to propagate the event further.
   */
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

  std::vector<Glib::RefPtr<Gdk::Pixbuf>> m_imgs;
  unsigned int m_r_start;
  unsigned int m_r_end;
  unsigned int m_r_step;
  unsigned int m_state;
  unsigned int m_max_state;
};

}  // namespace Smz3t

#endif  // SMZ3T_ITEMBOX_H
