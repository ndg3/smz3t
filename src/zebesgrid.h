#ifndef SMZ3T_ZEBESGRID_H
#define SMZ3T_ZEBESGRID_H

#include <gtkmm/box.h>
#include <gtkmm/grid.h>
#include <gtkmm/label.h>

#include <memory>
#include <string>
#include <vector>

#include "itembox.h"
#include "rewardbox.h"

namespace Smz3t {

/**
 * The ZebesRow struct contains the items used for a row in a ZebesGrid.
 *
 * A ZebesRow can be constructed directly, but it may be easier and more legible
 * to use a ZebesRowBuilder instead.
 */
struct ZebesRow {
  ZebesRow();
  ZebesRow(std::string area_abbr, bool has_reward, bool has_2_keys);
  virtual ~ZebesRow();

  Gtk::Label m_area;
  std::unique_ptr<RewardBox> m_reward;
  ItemBox m_map_station;
  Gtk::Box m_dummy_box;
  ItemBox m_key_1;
  std::unique_ptr<ItemBox> m_key_2;
  ItemBox m_boss_key;
};

/**
 * The ZebesRowBuilder class generates a new ZebesRow based on the methods
 * called thereon.
 *
 * To use a ZebesRowBuilder, construct a new instance and then call `init()`
 * with the abbreviation for a given area.
 *
 * Next, call any of these functions in any order
 * - `reward()` to indicate that a reward can be collected from this area.
 * - `key_2()` to indicate that this area has a Level 2 Keycard.
 *
 * Finally, call `build()` to create a new ZebesRow based on the previously
 * called methods. The memory associated with this ZebesRow is owned by the
 * caller.
 *
 * To reset a ZebesRowBuilder, call `init()` again with the abbreviation for
 * another area.
 *
 * All of these methods except `build()` return a reference to the current
 * ZebesRowBuilder, so they can be chained.
 */
class ZebesRowBuilder {
 public:
  ZebesRowBuilder();
  virtual ~ZebesRowBuilder();

  /**
   * Begins building a new ZebesRow.
   *
   * @param area_abbr The abbreviation for this area. Although any string could
   * be given, try to stick to one with 2 characters.
   * @returns The current ZebesRowBuilder.
   */
  ZebesRowBuilder& init(std::string area_abbr);

  /**
   * Sets the `has_reward` property for this ZebesRowBuilder, indicating that
   * the generated ZebesRow will have a RewardBox.
   *
   * @returns The current ZebesRowBuilder.
   */
  ZebesRowBuilder& reward();

  /**
   * Sets the `has_key_2` property for this ZebesRowBuilder, indicating that the
   * generated ZebesRow will have an ItemBox for a Level 2 Keycard.
   *
   * @returns The current ZebesRowBuilder.
   */
  ZebesRowBuilder& key_2();

  /**
   * Builds a new ZebesRow based on the methods called on this ZebesRowBuilder.
   *
   * @returns A new ZebesRow that is managed by the caller.
   */
  ZebesRow* build();

 protected:
  std::string m_area;
  bool m_has_reward;
  bool m_has_key_2;
};

/**
 * The ZebesGrid widget is a collection of items and rewards for
 * _Super Metroid_.
 *
 * Every row in this grid is generated from a ZebesRow, which has the following
 * components
 * - A Label for the abbreviation for the area.
 * - An optional RewardBox if a reward can be collected from this area.
 * - An ItemBox for the Area Map.
 * - An ItemBox for the Level 1 Keycard.
 * - An optional ItemBox if there is a Level 2 Keycard.
 * - An ItemBox for the Boss Keycard.
 *
 * A ZebesRow can be built with its constructor or with a ZebesRowBuilder.
 */
class ZebesGrid : public Gtk::Grid {
 public:
  ZebesGrid();
  virtual ~ZebesGrid();

  /**
   * Adds the given ZebesRow to this ZebesGrid. Ownership of the ZebesRow will
   * be transferred from the caller to this ZebesGrid.
   *
   * @param row The ZebesRow to add.
   */
  void add_row(ZebesRow* row);

 protected:
  std::vector<std::unique_ptr<ZebesRow>> m_rows;
};

}  // namespace Smz3t

#endif  // SMZ3T_ZEBESGRID_H
