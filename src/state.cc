#include "src/state.h"

#include <gtkmm/dialog.h>
#include <gtkmm/filechoosernative.h>
#include <gtkmm/window.h>

#include <format>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <optional>
#include <string>

namespace Smz3t::State {

using json = nlohmann::json;

// The current state of the tracker in JSON format.
json current_state = {{"hyrule",
                       {
                           {"bow", 0},
                           {"blue_boomerang", 0},
                           {"hookshot", 0},
                           {"bomb", 0},
                           {"mushroom", 0},
                           {"bottle", {0, 0, 0, 0}},
                           {"fire_rod", 0},
                           {"ice_rod", 0},
                           {"bombos", 0},
                           {"ether", 0},
                           {"quake", 0},
                           {"lamp", 0},
                           {"magic_hammer", 0},
                           {"shovel", 0},
                           {"bug-catching_net", 0},
                           {"book_of_mudora", 0},
                           {"cane_of_somaria", 0},
                           {"cane_of_byrna", 0},
                           {"magic_cape", 0},
                           {"magic_mirror", 0},
                           {"silver_arrow", 0},
                           {"red_boomerang", 0},
                           {"magic_powder", 0},
                           {"flute", 0},
                           {"fighters_sword", 0},
                           {"fighters_shield", 0},
                           {"green_jerkin", 0},
                           {"arrow_upgrade", 0},
                           {"pegasus_boots", 0},
                           {"power_glove", 0},
                           {"zoras_flippers", 0},
                           {"moon_pearl", 0},
                           {"bomb_upgrade", 0},
                           {"piece_of_heart", 0},
                           {"heart_container", 0},
                           {"half_magic", 0},
                           {"HC",
                            {
                                {"dungeon_map", 0},
                                {"compass", 0},
                                {"box_key", 0},
                                {"drop_key", 0},
                                {"big_key", 0},
                            }},
                           {"CT",
                            {
                                {"box_key", 0},
                                {"drop_key", 0},
                            }},
                           {"EP",
                            {
                                {"reward_type", 0},
                                {"reward", 0},
                                {"dungeon_map", 0},
                                {"compass", 0},
                                {"drop_key", 0},
                                {"big_key", 0},
                            }},
                           {"DP",
                            {
                                {"reward_type", 0},
                                {"reward", 0},
                                {"dungeon_map", 0},
                                {"compass", 0},
                                {"box_key", 0},
                                {"drop_key", 0},
                                {"big_key", 0},
                            }},
                           {"TH",
                            {
                                {"reward_type", 0},
                                {"reward", 0},
                                {"dungeon_map", 0},
                                {"compass", 0},
                                {"box_key", 0},
                                {"big_key", 0},
                            }},
                           {"PD",
                            {
                                {"reward_type", 0},
                                {"reward", 0},
                                {"dungeon_map", 0},
                                {"compass", 0},
                                {"box_key", 0},
                                {"big_key", 0},
                            }},
                           {"SP",
                            {
                                {"reward_type", 0},
                                {"reward", 0},
                                {"dungeon_map", 0},
                                {"compass", 0},
                                {"box_key", 0},
                                {"drop_key", 0},
                                {"big_key", 0},
                            }},
                           {"SW",
                            {
                                {"reward_type", 0},
                                {"reward", 0},
                                {"dungeon_map", 0},
                                {"compass", 0},
                                {"box_key", 0},
                                {"drop_key", 0},
                                {"big_key", 0},
                            }},
                           {"TT",
                            {
                                {"reward_type", 0},
                                {"reward", 0},
                                {"dungeon_map", 0},
                                {"compass", 0},
                                {"box_key", 0},
                                {"drop_key", 0},
                                {"big_key", 0},
                            }},
                           {"IP",
                            {
                                {"reward_type", 0},
                                {"reward", 0},
                                {"dungeon_map", 0},
                                {"compass", 0},
                                {"box_key", 0},
                                {"drop_key", 0},
                                {"big_key", 0},
                            }},
                           {"MM",
                            {
                                {"reward_type", 0},
                                {"reward", 0},
                                {"dungeon_map", 0},
                                {"compass", 0},
                                {"box_key", 0},
                                {"drop_key", 0},
                                {"big_key", 0},
                            }},
                           {"TR",
                            {
                                {"reward_type", 0},
                                {"reward", 0},
                                {"dungeon_map", 0},
                                {"compass", 0},
                                {"box_key", 0},
                                {"drop_key", 0},
                                {"big_key", 0},
                            }},
                           {"GT",
                            {
                                {"dungeon_map", 0},
                                {"compass", 0},
                                {"box_key", 0},
                                {"drop_key", 0},
                                {"big_key", 0},
                            }},
                       }},
                      {"zebes",
                       {
                           {"missile", 0},
                           {"super_missile", 0},
                           {"power_bomb", 0},
                           {"grapple_beam", 0},
                           {"x-ray_scope", 0},
                           {"morphing_ball", 0},
                           {"charge_beam", 0},
                           {"ice_beam", 0},
                           {"wave_beam", 0},
                           {"spazer", 0},
                           {"plasma_beam", 0},
                           {"bomb", 0},
                           {"varia_suit", 0},
                           {"hi-jump_boots", 0},
                           {"space_jump", 0},
                           {"speed_booster", 0},
                           {"screw_attack", 0},
                           {"spring_ball", 0},
                           {"energy_tank", 0},
                           {"reserve_tank", 0},
                           {"CR",
                            {
                                {"map_station", 0},
                                {"key_1", 0},
                                {"key_2", 0},
                                {"boss_key", 0},
                            }},
                           {"BR",
                            {
                                {"reward_type", 0},
                                {"reward", 0},
                                {"map_station", 0},
                                {"key_1", 0},
                                {"key_2", 0},
                                {"boss_key", 0},
                            }},
                           {"NO",
                            {
                                {"map_station", 0},
                                {"key_1", 0},
                                {"key_2", 0},
                                {"boss_key", 0},
                            }},
                           {"MA",
                            {
                                {"reward_type", 0},
                                {"reward", 0},
                                {"map_station", 0},
                                {"key_1", 0},
                                {"key_2", 0},
                                {"boss_key", 0},
                            }},
                           {"WS",
                            {
                                {"reward_type", 0},
                                {"reward", 0},
                                {"map_station", 0},
                                {"key_1", 0},
                                {"boss_key", 0},
                            }},
                           {"LN",
                            {
                                {"reward_type", 0},
                                {"reward", 0},
                                {"map_station", 0},
                                {"key_1", 0},
                                {"boss_key", 0},
                            }},
                       }}};

// A helper struct to make validation easier.
struct Indexes {
  std::optional<std::string> world;
  std::optional<std::string> dungeon;
  std::optional<std::string> item_name;
  std::optional<int> item_num;
};

// Ensures that the given combination of area and item exists. If any value in
// the returned Indexes struct is nullopt, then validation failed.
std::unique_ptr<Indexes> validate_item(std::string area, std::string item) {
  auto res = std::make_unique<Indexes>();

  // Validate world
  std::string::size_type a_colon = area.find(':');
  std::string world = area.substr(0, a_colon);

  if (world != "hyrule" && world != "zebes") {
    return res;
  }
  res->world = world;

  // Validate dungeon (if applicable)
  std::string dungeon;
  if (a_colon != std::string::npos) {
    dungeon = area.substr(a_colon + 1);
  }
  if (dungeon.size() > 0 && !current_state[world].contains(dungeon)) {
    return res;
  }
  res->dungeon = dungeon;

  // Move to the right area in the JSON to make further validation easier
  json& area_json =
      dungeon.size() > 0 ? current_state[world][dungeon] : current_state[world];

  // Validate item name
  std::string::size_type i_colon = item.find(':');
  std::string item_name = item.substr(0, i_colon);
  if (!area_json.contains(item_name)) {
    return res;
  }
  res->item_name = item_name;

  // Validate item number (if applicable)
  int item_num = -1;
  if (i_colon != std::string::npos) {
    item_num = std::stoi(item.substr(i_colon + 1));
  }
  if (item_num >= static_cast<int>(area_json[item_name].size())) {
    return res;
  }
  res->item_num = item_num;

  return res;
}

void set_item_state(std::string area, std::string item, unsigned int state) {
  std::unique_ptr<Indexes> idxs = validate_item(area, item);
  if (!(idxs->world && idxs->dungeon && idxs->item_name && idxs->item_num)) {
    return;
  }

  json& area_json = idxs->dungeon->size() > 0
                        ? current_state[*idxs->world][*idxs->dungeon]
                        : current_state[*idxs->world];

  if (*idxs->item_num >= 0) {
    area_json[*idxs->item_name][*idxs->item_num] = state;
  } else {
    area_json[*idxs->item_name] = state;
  }

  return;
}

unsigned int get_item_state(std::string area, std::string item) {
  std::unique_ptr<Indexes> idxs = validate_item(area, item);
  if (!(idxs->world && idxs->dungeon && idxs->item_name && idxs->item_num)) {
    return 0;
  }

  json& area_json = idxs->dungeon->size() > 0
                        ? current_state[*idxs->world][*idxs->dungeon]
                        : current_state[*idxs->world];

  int state = *idxs->item_num >= 0
                  ? area_json[*idxs->item_name][*idxs->item_num]
                  : area_json[*idxs->item_name];

  return state < 0 ? 0 : state;
}

void save_file() {
  auto dialog = Gtk::FileChooserNative::create(
      "Save File", Gtk::FILE_CHOOSER_ACTION_SAVE, "_Save", "_Cancel");
  dialog->set_current_name("smz3t.json");

  auto json_filter = Gtk::FileFilter::create();
  json_filter->set_name("JSON Files");
  json_filter->add_mime_type("application/json");
  dialog->add_filter(json_filter);

  auto any_filter = Gtk::FileFilter::create();
  any_filter->set_name("Any Files");
  any_filter->add_pattern("*");
  dialog->add_filter(any_filter);

  dialog->signal_response().connect([&](int response) {
    if (response == Gtk::RESPONSE_ACCEPT) {
      std::string filename = dialog->get_filename();
      std::fstream file(filename, std::ios::out);
      if (!file.is_open()) {
        std::cout << "WARNING: Failed to open " << filename << ".\n";
      }
      file << std::setw(4) << current_state << '\n';
    }
  });

  dialog->run();
}

// Helper function to compare the structure of two JSON arrays.
bool compare_json_array(const json& a1, const json& a2) {
  auto it1 = a1.begin();
  auto it2 = a2.begin();
  while (it1 != a1.end() || it2 != a2.end()) {
    if (it1->type() != it2->type()) {
      return false;
    }
    ++it1;
    ++it2;
  }
  return it1 == a1.end() && it2 == a2.end();
}

// Helper function to compare the structure of two JSON objects.
// This is not testing if the values are the same, just that everything exists
// and is the correct type.
bool compare_json(const json& j1, const json& j2) {
  auto it1 = j1.begin();
  auto it2 = j2.begin();
  while (it1 != j1.end() || it2 != j2.end()) {
    if (it1.key() != it2.key() || it1.value().type() != it2.value().type()) {
      return false;
    }
    if (it1.value() == json::value_t::array &&
        !compare_json_array(it1.value(), it2.value())) {
      return false;
    }
    if (it1.value() == json::value_t::object &&
        !compare_json(it1.value(), it2.value())) {
      return false;
    }
    ++it1;
    ++it2;
  }
  return it1 == j1.end() && it2 == j2.end();
}

bool open_file() {
  auto dialog = Gtk::FileChooserNative::create(
      "Open File", Gtk::FILE_CHOOSER_ACTION_OPEN, "_Open", "_Cancel");

  auto json_filter = Gtk::FileFilter::create();
  json_filter->set_name("JSON Files");
  json_filter->add_mime_type("application/json");
  dialog->add_filter(json_filter);

  auto any_filter = Gtk::FileFilter::create();
  any_filter->set_name("Any Files");
  any_filter->add_pattern("*");
  dialog->add_filter(any_filter);

  bool updated = false;

  dialog->signal_response().connect([&](int response) {
    if (response == Gtk::RESPONSE_ACCEPT) {
      auto file = dialog->get_file();
      std::size_t data_s = file->query_info()->get_size();
      char* data{new char[data_s]{}};
      file->load_contents(data, data_s);
      json loaded_json = json::parse(data);
      if (compare_json(current_state, loaded_json)) {
        current_state = loaded_json;
        updated = true;
      } else {
        std::cout << "WARNING: Save file has incorrect format. Not loaded.\n";
      }
      delete[] data;
    }
  });

  dialog->run();
  return updated;
}

}  // namespace Smz3t::State
