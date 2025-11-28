#include <gtkmm/application.h>
#include <gtkmm/grid.h>
#include <gtkmm/notebook.h>
#include <gtkmm/window.h>

#include <memory>
#include <utility>

// #include "doubleitembox.h"
#include "dungeongrid.h"
#include "itembox.h"
#include "rewardgrid.h"
#include "zebesgrid.h"

class MainWindow : public Gtk::Window {
 public:
  MainWindow() {
    set_title("SMZ3 GtkTracker");
    std::vector<std::pair<std::vector<std::string>, std::vector<unsigned int>>>
        z_items{
            {{"zelda/bow"}, {}},
            {{"zelda/blue_boomerang"}, {}},
            {{"zelda/hookshot"}, {}},
            {{"zelda/bomb"}, {}},
            {{"zelda/mushroom"}, {}},
            {{"zelda/bottle", "zelda/bottle_life_medicine",
              "zelda/bottle_magic_medicine", "zelda/bottle_cure-all_medicine",
              "zelda/bottle_bee", "zelda/bottle_faerie"},
             {}},
            {{"zelda/fire_rod"}, {}},
            {{"zelda/ice_rod"}, {}},
            {{"zelda/bombos"}, {}},
            {{"zelda/ether"}, {}},
            {{"zelda/quake"}, {}},
            {{"zelda/bottle", "zelda/bottle_life_medicine",
              "zelda/bottle_magic_medicine", "zelda/bottle_cure-all_medicine",
              "zelda/bottle_bee", "zelda/bottle_faerie"},
             {}},
            {{"zelda/lamp"}, {}},
            {{"zelda/magic_hammer"}, {}},
            {{"zelda/shovel"}, {}},
            {{"zelda/bug-catching_net"}, {}},
            {{"zelda/book_of_mudora"}, {}},
            {{"zelda/bottle", "zelda/bottle_life_medicine",
              "zelda/bottle_magic_medicine", "zelda/bottle_cure-all_medicine",
              "zelda/bottle_bee", "zelda/bottle_faerie"},
             {}},
            {{"zelda/cane_of_somaria"}, {}},
            {{"zelda/cane_of_byrna"}, {}},
            {{"zelda/magic_cape"}, {}},
            {{"zelda/magic_mirror"}, {}},
            {{"zelda/silver_arrow"}, {}},
            {{"zelda/bottle", "zelda/bottle_life_medicine",
              "zelda/bottle_magic_medicine", "zelda/bottle_cure-all_medicine",
              "zelda/bottle_bee", "zelda/bottle_faerie"},
             {}},
            {{"zelda/red_boomerang"}, {}},
            {{"zelda/magic_powder"}, {}},
            {{"zelda/flute"}, {}},
            {{"zelda/fighters_sword", "zelda/master_sword",
              "zelda/tempered_sword", "zelda/gold_sword"},
             {}},
            {{"zelda/fighters_shield", "zelda/red_shield",
              "zelda/mirror_shield"},
             {}},
            {{"zelda/green_jerkin", "zelda/blue_mail", "zelda/red_mail"}, {}},
            {{"zelda/arrow_upgrade"}, {1, 4, 1}},
            {{"zelda/pegasus_boots"}, {}},
            {{"zelda/power_glove", "zelda/titans_mitt"}, {}},
            {{"zelda/zoras_flippers"}, {}},
            {{"zelda/moon_pearl"}, {}},
            {{"zelda/bomb_upgrade"}, {1, 4, 1}}};

    std::vector<std::pair<std::vector<std::string>, std::vector<unsigned int>>>
        rewards{{{"zelda/piece_of_heart"}, {1, 24, 1}},
                {{"zelda/heart_container"}, {1, 10, 1}},
                {{"zelda/half_magic"}, {}},
                {{"metroid/energy_tank"}, {1, 14, 1}},
                {{"metroid/reserve_tank"}, {1, 4, 1}}};

    std::vector<std::pair<std::vector<std::string>, std::vector<unsigned int>>>
        m_items{{{"metroid/missile"}, {5, 200, 5}},
                {{"metroid/super_missile"}, {5, 80, 5}},
                {{"metroid/power_bomb"}, {5, 50, 5}},
                {{"metroid/grapple_beam"}, {}},
                {{"metroid/x-ray_scope"}, {}},
                {{"metroid/morphing_ball"}, {}},
                {{"metroid/charge_beam"}, {}},
                {{"metroid/ice_beam"}, {}},
                {{"metroid/wave_beam"}, {}},
                {{"metroid/spazer"}, {}},
                {{"metroid/plasma_beam"}, {}},
                {{"metroid/bomb"}, {}},
                {{"metroid/varia_suit", "metroid/gravity_suit"}, {}},
                {{"metroid/hi-jump_boots"}, {}},
                {{"metroid/space_jump"}, {}},
                {{"metroid/speed_booster"}, {}},
                {{"metroid/screw_attack"}, {}},
                {{"metroid/spring_ball"}, {}}};

    for (auto [item, text] : z_items) {
      std::unique_ptr<ItemBox> box;
      if (!text.size()) {
        box = std::make_unique<ItemBox>(item);
      } else {
        box = std::make_unique<ItemBox>(item, text[0], text[1], text[2]);
      }
      m_z_items.push_back(std::move(box));
    }

    std::size_t i = 0;
    for (; i < m_z_items.size(); i++) {
      if (!i) {
        m_z_item_grid.add(*m_z_items[0]);
      } else if (i % 6 == 0) {
        m_z_item_grid.attach_next_to(
            *m_z_items[i], *m_z_item_grid.get_child_at(0, (i - 1) / 6),
            Gtk::POS_BOTTOM);
      } else {
        m_z_item_grid.attach(*m_z_items[i], i % 6, i / 6);
      }
    }

    for (auto [item, text] : rewards) {
      std::unique_ptr<ItemBox> box;
      if (text.size()) {
        box = std::make_unique<ItemBox>(item, text[0], text[1], text[2]);
      } else {
        box = std::make_unique<ItemBox>(item);
      }
      m_health_magic_items.push_back(std::move(box));
    }

    i = 0;
    for (; i < m_health_magic_items.size(); i++) {
      if (!i) {
        m_health_magic_grid.add(*m_health_magic_items[0]);
      } else if (i % 5 == 0) {
        m_health_magic_grid.attach_next_to(
            *m_health_magic_items[i],
            *m_health_magic_grid.get_child_at(0, (i - 1) / 5), Gtk::POS_BOTTOM);
      } else {
        m_health_magic_grid.attach(*m_health_magic_items[i], i % 5, i / 5);
      }
    }

    for (auto [item, text] : m_items) {
      std::unique_ptr<ItemBox> box;
      if (!text.size()) {
        box = std::make_unique<ItemBox>(item);
      } else {
        box = std::make_unique<ItemBox>(item, text[0], text[1], text[2]);
      }
      m_m_items.push_back(std::move(box));
    }

    i = 0;
    for (; i < m_m_items.size(); i++) {
      if (!i) {
        m_m_item_grid.add(*m_m_items[i]);
      } else if (i % 6 == 0) {
        m_m_item_grid.attach_next_to(
            *m_m_items[i], *m_m_item_grid.get_child_at(0, (i - 1) / 6),
            Gtk::POS_BOTTOM);
      } else {
        m_m_item_grid.attach(*m_m_items[i], i % 6, i / 6);
      }
    }

    m_dungeon_grid.add_row(new DungeonRow("HC", false, 1, 2));
    m_dungeon_grid.add_row(new DungeonRow("AT", false, 2, 3));
    m_dungeon_grid.add_row(new DungeonRow("EP", true, 0, 2));
    m_dungeon_grid.add_row(new DungeonRow("DP", true, 1, 3));
    m_dungeon_grid.add_row(new DungeonRow("TH", true, 1, 0));
    m_dungeon_grid.add_row(new DungeonRow("PD", true, 6, 0));
    m_dungeon_grid.add_row(new DungeonRow("SP", true, 1, 5));
    m_dungeon_grid.add_row(new DungeonRow("SW", true, 3, 2));
    m_dungeon_grid.add_row(new DungeonRow("TT", true, 1, 2));
    m_dungeon_grid.add_row(new DungeonRow("IP", true, 2, 4));
    m_dungeon_grid.add_row(new DungeonRow("MM", true, 3, 3));
    m_dungeon_grid.add_row(new DungeonRow("TR", true, 4, 2));
    m_dungeon_grid.add_row(new DungeonRow("GT", false, 4, 4));

    m_zebes_grid.add_row(new ZebesRow("CR", false, true));
    m_zebes_grid.add_row(new ZebesRow("BR", true, true));
    m_zebes_grid.add_row(new ZebesRow("NF", false, true));
    m_zebes_grid.add_row(new ZebesRow("MA", true, true));
    m_zebes_grid.add_row(new ZebesRow("WS", true, false));
    m_zebes_grid.add_row(new ZebesRow("LN", true, false));

    m_z_item_grid.set_halign(Gtk::ALIGN_CENTER);
    m_z_item_grid.set_row_spacing(2);
    m_z_item_grid.set_column_spacing(2);
    m_health_magic_grid.set_halign(Gtk::ALIGN_CENTER);
    m_health_magic_grid.set_row_spacing(2);
    m_health_magic_grid.set_column_spacing(2);
    m_m_item_grid.set_halign(Gtk::ALIGN_CENTER);
    m_m_item_grid.set_row_spacing(2);
    m_m_item_grid.set_column_spacing(2);
    m_dungeon_grid.set_halign(Gtk::ALIGN_CENTER);
    m_dungeon_grid.set_row_spacing(2);
    m_dungeon_grid.set_column_spacing(2);
    m_zebes_grid.set_halign(Gtk::ALIGN_CENTER);
    m_zebes_grid.set_row_spacing(2);
    m_zebes_grid.set_column_spacing(2);

    m_page_1_grid.add(m_z_item_grid);
    m_page_1_grid.attach(m_health_magic_grid, 0, 1);
    m_page_1_grid.attach(m_m_item_grid, 0, 2);
    m_page_1_grid.set_halign(Gtk::ALIGN_CENTER);

    m_page_2_grid.add(m_dungeon_grid);
    m_page_2_grid.attach(m_zebes_grid, 0, 1);
    m_page_2_grid.set_halign(Gtk::ALIGN_CENTER);

    m_main_notebook.append_page(m_page_1_grid, "Items");
    m_main_notebook.append_page(m_page_2_grid, "Dungeons");

    add(m_main_notebook);
    show_all_children();
  }
  virtual ~MainWindow() {}

 protected:
  std::vector<std::unique_ptr<ItemBox>> m_z_items;
  std::vector<std::unique_ptr<ItemBox>> m_health_magic_items;
  std::vector<std::unique_ptr<ItemBox>> m_m_items;
  std::vector<std::unique_ptr<RewardGrid>> m_rewards;
  Gtk::Grid m_page_1_grid;
  Gtk::Grid m_page_2_grid;
  Gtk::Grid m_z_item_grid;
  Gtk::Grid m_health_magic_grid;
  Gtk::Grid m_m_item_grid;
  DungeonGrid m_dungeon_grid;
  ZebesGrid m_zebes_grid;
  Gtk::Notebook m_main_notebook;
};

int main(int argc, char *argv[]) {
  auto app = Gtk::Application::create(argc, argv, "org.smz3.tracker");

  MainWindow main_window;

  return app->run(main_window);
}
