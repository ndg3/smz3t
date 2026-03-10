#ifndef SMZ3T_HYRULEGRID_H_
#define SMZ3T_HYRULEGRID_H_

#include <gtkmm/grid.h>
#include <gtkmm/label.h>

#include <memory>
#include <string>
#include <vector>

#include "src/itembox.h"
#include "src/rewardbox.h"

namespace Smz3t {

/**
 * The HyruleRow struct contains the items used for a row in a HyruleGrid.
 *
 * A HyruleRow can be constructed directly, but it may be easier and more
 * legible to use a HyruleRowBuilder instead.
 */
struct HyruleRow {
  HyruleRow();
  HyruleRow(std::string area_abbr, bool has_reward, bool has_dungeon_map,
            bool has_compass, unsigned int box_keys, unsigned int drop_keys,
            bool has_big_key);
  virtual ~HyruleRow();

  /**
   * Updates the state of each item or reward in this row. Each element is set
   * to its value in the JSON in the State namespace.
   */
  void update_state_from_json();

  Gtk::Label m_area;
  std::unique_ptr<RewardBox> m_reward;
  std::unique_ptr<ItemBox> m_dungeon_map;
  std::unique_ptr<ItemBox> m_compass;
  std::unique_ptr<ItemBox> m_box_keys;
  std::unique_ptr<ItemBox> m_drop_keys;
  std::unique_ptr<ItemBox> m_big_key;
};

/**
 * The HyruleRowBuilder class generates a new HyruleRow based on the methods
 * called thereon.
 *
 * To use a HyruleRowBuilder, construct a new instance and then call `init()`
 * with the abbreviation for a given area.
 *
 * Next, call any of these functions in any order
 * - `reward()` to indicate that a reward can be collected from this area.
 * - `dungeon_map()` to indicate that this area has a dungeon map.
 * - `compass()` to indicate that this area has a compass.
 * - `box_keys()` to indicate that this area has a given number of keys
 *   collected from chests.
 * - `drop_keys()` to indicate that this area has a given number of keys dropped
 *   from pots or enemies.
 * - `big_key()` to indicate that this area has a big key.
 *
 * A distinction is made between "box" keys and "drop" keys due to the current
 * Keysanity logic, as box keys are shuffled and drop keys are not. This
 * distinction is less important for non-Keysanity seeds.
 *
 * There are also presets for common dungeon types, including
 * - `p_no_reward()` for dungeons with everything but a reward.
 * - `p_dungeon_all()` for dungeons with everything.
 * - `p_dungeon_box()` for dungeons with box keys and no drop keys.
 * - `p_dungeon_drop()` for dungeons with drop keys and no box keys.
 *
 * Finally, call `build()` to create a new HyruleRow based on the previously
 * called methods. The memory associated with this HyruleRow is owned by the
 * caller.
 *
 * To reset a HyruleRowBuilder, call `init()` again with the abbreviation for
 * another area.
 *
 * All of these methods except `build()` return a reference to the current
 * HyruleRowBuilder, so they can be chained.
 */
class HyruleRowBuilder {
 public:
  HyruleRowBuilder();
  virtual ~HyruleRowBuilder();

  /**
   * Begins building a new HyruleRow.
   *
   * @param area_abbr The abbreviation for this area. Although any string could
   * be given, try to stick to one with 2 characters.
   * @returns The current HyruleRowBuilder.
   */
  HyruleRowBuilder& init(std::string area_abbr);

  /**
   * Sets the `has_reward` property for this HyruleRowBuilder, indicating that
   * the generated HyruleRow will have a RewardBox.
   *
   * @returns The current HyruleRowBuilder.
   */
  HyruleRowBuilder& reward();

  /**
   * Sets the `has_dungeon_map` property for this HyruleRowBuilder, indicating that
   * the generated HyruleRow will have a dungeon map.
   *
   * @returns The current HyruleRowBuilder.
   */
  HyruleRowBuilder& dungeon_map();

  /**
   * Sets the `has_compass` property for this HyruleRowBuilder, indicating that
   * the generated HyruleRow will have a compass.
   *
   * @returns The current HyruleRowBuilder.
   */
  HyruleRowBuilder& compass();

  /**
   * Sets the `box_keys` property for this HyruleRowBuilder, indicating that the
   * generated HyruleRow will have the given number of box keys.
   *
   * @param box_keys The number of keys in this area that are collected from
   * chests (box keys).
   * @returns The current HyruleRowBuilder.
   */
  HyruleRowBuilder& box_keys(unsigned int box_keys);

  /**
   * Sets the `drop_keys` property for this HyruleRowBuilder, indicating that
   * the generated HyruleRow will have the given number of drop keys.
   *
   * @param drop_keys The number of keys in this area that are dropped from pots
   * or enemies (drop keys).
   * @returns The current HyruleRowBuilder.
   */
  HyruleRowBuilder& drop_keys(unsigned int drop_keys);

  /**
   * Sets the `big_key` property for this HyruleRowBuilder, indicating that the
   * generated HyruleRow will have a big key.
   *
   * @returns The current HyruleRowBuilder.
   */
  HyruleRowBuilder& big_key();

  /**
   * Preset for a dungeon that has everything but a reward (e.g., Hyrule Castle
   * and Ganon's Tower).
   *
   * @param box_keys The number of keys in this area that are collected from
   * chests (box keys).
   * @param drop_keys The number of keys in this area that are dropped from pots
   * or enemies (drop keys).
   * @returns The current HyruleRowBuilder.
   */
  HyruleRowBuilder& p_no_reward(unsigned int box_keys, unsigned int drop_keys);

  /**
   * Preset for a dungeon that has everything (e.g. Desert Palace).
   *
   * @param box_keys The number of keys in this area that are collected from
   * chests (box keys).
   * @param drop_keys The number of keys in this area that are dropped from pots
   * or enemies (drop keys).
   * @returns The current HyruleRowBuilder.
   */
  HyruleRowBuilder& p_dungeon_all(unsigned int box_keys, unsigned int drop_keys);

  /**
   * Preset for a dungeon that has box keys and no drop keys (e.g. Tower of
   * Hera).
   *
   * @param box_keys The number of keys in this area that are collected from
   * chests (box keys).
   * @returns The current HyruleRowBuilder.
   */
  HyruleRowBuilder& p_dungeon_box(unsigned int box_keys);

  /**
   * Preset for a dungeon that has drop keys and no box keys (e.g. Eastern
   * Palace).
   *
   * @param drop_keys The number of keys in this area that are dropped from pots
   * or enemies (drop keys).
   * @returns The current HyruleRowBuilder.
   */
  HyruleRowBuilder& p_dungeon_drop(unsigned int drop_keys);

  /**
   * Builds a new HyruleRow based on the methods called on this
   * HyruleRowBuilder.
   *
   * @returns A new HyruleRow that is managed by the caller.
   */
  HyruleRow* build();

 protected:
  std::string m_area;
  bool m_has_reward;
  bool m_has_dungeon_map;
  bool m_has_compass;
  unsigned int m_box_keys;
  unsigned int m_drop_keys;
  bool m_has_big_key;
};

/**
 * The HyruleGrid widget is a collection of dungeon items and rewards for
 * _A Link to the Past_.
 *
 * Every row in this grid is generated from a HyruleRow, which has the following
 * components
 * - A Label for the abbreviation for the dungeon.
 * - An optional RewardBox if a reward can be collected from this dungeon.
 * - An ItemBox for the Dungeon Map.
 * - An ItemBox for the Compass.
 * - An optional ItemBox for any keys that can be collected from chests.
 * - An optional ItemBox for any keys that can be dropped from pots or enemies.
 * - An ItemBox for the Big Key.
 *
 * A HyruleRow can be built with its constructor or with a HyruleRowBuilder.
 */
class HyruleGrid : public Gtk::Grid {
 public:
  HyruleGrid();
  virtual ~HyruleGrid();

  /**
   * Adds the given HyruleRow to this HyruleGrid. Ownership of the HyruleRow
   * will be transferred from the caller to this HyruleGrid.
   *
   * @param row The HyruleRow to add.
   */
  void add_row(HyruleRow* row);

  /**
   * Updates the state of each row in this grid. Each element is set to its
   * value in the JSON in the State namespace.
   */
  void update_state_from_json();

 protected:
  std::vector<std::unique_ptr<HyruleRow>> m_rows;
};

}  // namespace Smz3t

#endif  // SMZ3T_HYRULEGRID_H_
