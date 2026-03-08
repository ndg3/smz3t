#ifndef SMZ3T_STATE_H_
#define SMZ3T_STATE_H_

#include <gtkmm/window.h>

#include <string>

#include <nlohmann/json.hpp>

/**
 * The State namespace contains utility functions for saving and restoring the
 * state of the tracker in JSON format.
 */
namespace Smz3t::State {

using json = nlohmann::json;

/**
 * Sets the state of the item in the given area for the JSON state.
 *
 * An area is a string containing either "hyrule" or "zebes" (indicating that
 * the item comes from _A Link to the Past_ or _Super Metroid_, respectively)
 * optionally followed by a colon and a dungeon or subarea.
 *
 * The allowed dungeons for Hyrule are
 * - "HC" (Hyrule Castle)
 * - "AT" (Agahnim's Tower)
 * - "EP" (Eastern Palace)
 * - "DP" (Desert Palace)
 * - "TH" (Tower of Hera)
 * - "PD" (Palace of Darkness)
 * - "SP" (Swamp Palace)
 * - "SW" (Skull Woods)
 * - "TT" (Thieves' Town)
 * - "IP" (Ice Palace)
 * - "MM" (Misery Mire)
 * - "TR" (Turtle Rock)
 * - "GT" (Ganon's Tower)
 *
 * The allowed subareas for Zebes are
 * - "CR" (Crateria)
 * - "BR" (Brinstar)
 * - "NO" (Norfair)
 * - "MA" (Maridia)
 * - "WS" (Wrecked Ship)
 * - "LN" (Lower Norfair)
 *
 * Note that the dungeon and subarea designations are for dungeon items like
 * maps, compasses, chests, keys, and rewards.
 *
 * An item is the name of an item optionally followed by a colon and a number
 * indicating the ID of an item (primarily used for bottles, of which there are
 * 4). Item IDs are zero-indexed.
 *
 * For example:
 * - To set the Hookshot to its enabled state, set area to "hyrule",
 *   item to "hookshot", and state to 1.
 * - To set the Boss Keycard of Brinstar to its enabled state, set area to
 *   "zebes:BR", item to "boss_key", and state to 1.
 * - To set the 3rd Bottle to be a Bee, set area to "hyrule", item to
 *   "bottle:2", and state to 4.
 *
 * @param area The area that the item belongs to, optionally indicating its
 * dungeon or subarea.
 * @param item The item itself, optionally indicating the index of that item if
 * there are multiple.
 * @param state The new state of the item.
 */
void set_item_state(std::string area, std::string item, unsigned int state);

/**
 * Gets the state of the item in the given area of the JSON state.
 *
 * An area is a string containing either "hyrule" or "zebes" (indicating that
 * the item comes from _A Link to the Past_ or _Super Metroid_, respectively)
 * optionally followed by a colon and a dungeon or subarea. See `set_item_state`
 * for a list of valid dungeons and subareas.
 *
 * An item is the name of an item optionally followed by a colon and a number
 * indicating the ID of an item (primarily used for bottles, of which there are
 * 4). Item IDs are zero-indexed.
 *
 * @param area The area that the item belongs to, optionally indicating its
 * dungeon or subarea.
 * @param item The item itself, optionally indicating the index of that item if
 * there are multiple.
 * @returns The current state of the item.
 */
unsigned int get_item_state(std::string area, std::string item);

/**
 * Saves the current JSON state to a file, as determined by a file chooser.
 * Intended to be used as a signal handler.
 */
void save_file();

/**
 * Opens a file to replace the current JSON state, as determined by a file
 * chooser. Intended to be used as a signal handler.
 *
 * @returns True if the state was actually updated (i.e. if the file loaded
 * correctly), false otherwise.
 */
bool open_file();

}  // namespace Smz3t::State

#endif  // SMZ3T_STATE_H_
