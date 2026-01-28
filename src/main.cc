#include <gtkmm/application.h>
#include <gtkmm/grid.h>
#include <gtkmm/notebook.h>
#include <gtkmm/window.h>
#include <gtkmm/cssprovider.h>
#include <gtkmm/stylecontext.h>

#include <memory>
#include <utility>

#include "hyrulegrid.h"
#include "itembox.h"
#include "zebesgrid.h"

namespace Smz3t {

class MainWindow : public Gtk::Window {
 public:
  MainWindow() {
    set_title("SMZ3 Tracker");

    std::vector<std::pair<std::vector<std::string>, std::vector<unsigned int>>>
        h_items{
            {{"hyrule/bow"}, {}},
            {{"hyrule/blue_boomerang"}, {}},
            {{"hyrule/hookshot"}, {}},
            {{"hyrule/bomb"}, {}},
            {{"hyrule/mushroom"}, {}},
            {{"hyrule/bottle", "hyrule/bottle_life_medicine",
              "hyrule/bottle_magic_medicine", "hyrule/bottle_cure-all_medicine",
              "hyrule/bottle_bee", "hyrule/bottle_faerie"},
             {}},
            {{"hyrule/fire_rod"}, {}},
            {{"hyrule/ice_rod"}, {}},
            {{"hyrule/bombos"}, {}},
            {{"hyrule/ether"}, {}},
            {{"hyrule/quake"}, {}},
            {{"hyrule/bottle", "hyrule/bottle_life_medicine",
              "hyrule/bottle_magic_medicine", "hyrule/bottle_cure-all_medicine",
              "hyrule/bottle_bee", "hyrule/bottle_faerie"},
             {}},
            {{"hyrule/lamp"}, {}},
            {{"hyrule/magic_hammer"}, {}},
            {{"hyrule/shovel"}, {}},
            {{"hyrule/bug-catching_net"}, {}},
            {{"hyrule/book_of_mudora"}, {}},
            {{"hyrule/bottle", "hyrule/bottle_life_medicine",
              "hyrule/bottle_magic_medicine", "hyrule/bottle_cure-all_medicine",
              "hyrule/bottle_bee", "hyrule/bottle_faerie"},
             {}},
            {{"hyrule/cane_of_somaria"}, {}},
            {{"hyrule/cane_of_byrna"}, {}},
            {{"hyrule/magic_cape"}, {}},
            {{"hyrule/magic_mirror"}, {}},
            {{"hyrule/silver_arrow"}, {}},
            {{"hyrule/bottle", "hyrule/bottle_life_medicine",
              "hyrule/bottle_magic_medicine", "hyrule/bottle_cure-all_medicine",
              "hyrule/bottle_bee", "hyrule/bottle_faerie"},
             {}},
            {{"hyrule/red_boomerang"}, {}},
            {{"hyrule/magic_powder"}, {}},
            {{"hyrule/flute"}, {}},
            {{"hyrule/fighters_sword", "hyrule/master_sword",
              "hyrule/tempered_sword", "hyrule/gold_sword"},
             {}},
            {{"hyrule/fighters_shield", "hyrule/red_shield",
              "hyrule/mirror_shield"},
             {}},
            {{"hyrule/green_jerkin", "hyrule/blue_mail", "hyrule/red_mail"},
             {}},
            {{"hyrule/arrow_upgrade"}, {1, 4, 1}},
            {{"hyrule/pegasus_boots"}, {}},
            {{"hyrule/power_glove", "hyrule/titans_mitt"}, {}},
            {{"hyrule/zoras_flippers"}, {}},
            {{"hyrule/moon_pearl"}, {}},
            {{"hyrule/bomb_upgrade"}, {1, 4, 1}}};

    std::vector<std::pair<std::vector<std::string>, std::vector<unsigned int>>>
        rewards{{{"hyrule/piece_of_heart"}, {1, 24, 1}},
                {{"hyrule/heart_container"}, {1, 10, 1}},
                {{"hyrule/half_magic"}, {}},
                {{"zebes/energy_tank"}, {1, 14, 1}},
                {{"zebes/reserve_tank"}, {1, 4, 1}}};

    std::vector<std::pair<std::vector<std::string>, std::vector<unsigned int>>>
        z_items{{{"zebes/missile"}, {5, 200, 5}},
                {{"zebes/super_missile"}, {5, 80, 5}},
                {{"zebes/power_bomb"}, {5, 50, 5}},
                {{"zebes/grapple_beam"}, {}},
                {{"zebes/x-ray_scope"}, {}},
                {{"zebes/morphing_ball"}, {}},
                {{"zebes/charge_beam"}, {}},
                {{"zebes/ice_beam"}, {}},
                {{"zebes/wave_beam"}, {}},
                {{"zebes/spazer"}, {}},
                {{"zebes/plasma_beam"}, {}},
                {{"zebes/bomb"}, {}},
                {{"zebes/varia_suit", "zebes/gravity_suit"}, {}},
                {{"zebes/hi-jump_boots"}, {}},
                {{"zebes/space_jump"}, {}},
                {{"zebes/speed_booster"}, {}},
                {{"zebes/screw_attack"}, {}},
                {{"zebes/spring_ball"}, {}}};

    // Build items for A Link to the Past
    std::size_t i = 0;
    for (auto& [item, text] : h_items) {
      std::unique_ptr<Smz3t::ItemBox> box;
      if (text.size() == 0)
        box = std::make_unique<Smz3t::ItemBox>(item);
      else
        box = std::make_unique<Smz3t::ItemBox>(item, text[0], text[1], text[2]);
      m_h_item_grid.attach(*box, i % 6, i / 6);
      m_h_items.push_back(std::move(box));
      ++i;
    }

    // Build health and magic upgrades for both games
    i = 0;
    for (auto& [item, text] : rewards) {
      std::unique_ptr<Smz3t::ItemBox> box;
      if (text.size() == 0)
        box = std::make_unique<Smz3t::ItemBox>(item);
      else
        box = std::make_unique<Smz3t::ItemBox>(item, text[0], text[1], text[2]);
      m_health_magic_grid.attach(*box, i % 5, i / 5);
      m_health_magic_items.push_back(std::move(box));
      ++i;
    }

    // Build items for Super Metroid
    i = 0;
    for (auto& [item, text] : z_items) {
      std::unique_ptr<Smz3t::ItemBox> box;
      if (text.size() == 0)
        box = std::make_unique<Smz3t::ItemBox>(item);
      else
        box = std::make_unique<Smz3t::ItemBox>(item, text[0], text[1], text[2]);
      m_z_item_grid.attach(*box, i % 6, i / 6);
      m_z_items.push_back(std::move(box));
      ++i;
    }

    // Build the HyruleGrid
    Smz3t::HyruleRowBuilder rb;
    m_h_area_grid.add_row(rb.init("HC").box_keys(1).drop_keys(2).build());
    m_h_area_grid.add_row(rb.init("AT").box_keys(2).drop_keys(3).build());
    m_h_area_grid.add_row(rb.init("EP").reward().drop_keys(2).build());
    m_h_area_grid.add_row(
        rb.init("DP").reward().box_keys(1).drop_keys(3).build());
    m_h_area_grid.add_row(rb.init("TH").reward().box_keys(1).build());
    m_h_area_grid.add_row(rb.init("PD").reward().box_keys(6).build());
    m_h_area_grid.add_row(
        rb.init("SP").reward().box_keys(1).drop_keys(5).build());
    m_h_area_grid.add_row(
        rb.init("SW").reward().box_keys(3).drop_keys(2).build());
    m_h_area_grid.add_row(
        rb.init("TT").reward().box_keys(1).drop_keys(2).build());
    m_h_area_grid.add_row(
        rb.init("IP").reward().box_keys(2).drop_keys(4).build());
    m_h_area_grid.add_row(
        rb.init("MM").reward().box_keys(3).drop_keys(3).build());
    m_h_area_grid.add_row(
        rb.init("TR").reward().box_keys(4).drop_keys(2).build());
    m_h_area_grid.add_row(rb.init("GT").box_keys(4).drop_keys(4).build());

    // Build the ZebesGrid
    Smz3t::ZebesRowBuilder zb;
    m_z_area_grid.add_row(zb.init("CR").key_2().build());
    m_z_area_grid.add_row(zb.init("BR").reward().key_2().build());
    m_z_area_grid.add_row(zb.init("NF").key_2().build());
    m_z_area_grid.add_row(zb.init("MA").reward().key_2().build());
    m_z_area_grid.add_row(zb.init("WS").reward().build());
    m_z_area_grid.add_row(zb.init("LN").reward().build());

    // Center the grids
    m_h_item_grid.set_halign(Gtk::ALIGN_CENTER);
    m_health_magic_grid.set_halign(Gtk::ALIGN_CENTER);
    m_z_item_grid.set_halign(Gtk::ALIGN_CENTER);
    m_h_area_grid.set_halign(Gtk::ALIGN_CENTER);
    m_z_area_grid.set_halign(Gtk::ALIGN_CENTER);

    // Add item grids to first page, center
    m_page_1_grid.attach(m_h_item_grid, 0, 0);
    m_page_1_grid.attach(m_health_magic_grid, 0, 1);
    m_page_1_grid.attach(m_z_item_grid, 0, 2);
    m_page_1_grid.set_halign(Gtk::ALIGN_CENTER);

    // Add area grids to second page, center
    m_page_2_grid.attach(m_h_area_grid, 0, 0);
    m_page_2_grid.attach(m_z_area_grid, 0, 1);
    m_page_2_grid.set_halign(Gtk::ALIGN_CENTER);

    // Add pages to main window
    m_main_notebook.append_page(m_page_1_grid, "Items");
    m_main_notebook.append_page(m_page_2_grid, "Areas");
    add(m_main_notebook);

    // Set foreground and background color (avoids theming issues with icons)
    auto provider = Gtk::CssProvider::create();
    provider->load_from_data("* { color: white; background-color: black; }");
    Gtk::StyleContext::add_provider_for_screen(get_screen(), provider, GTK_STYLE_PROVIDER_PRIORITY_USER);

    show_all_children();
  }
  virtual ~MainWindow() {}

 protected:
  std::vector<std::unique_ptr<Smz3t::ItemBox>> m_h_items;
  std::vector<std::unique_ptr<Smz3t::ItemBox>> m_health_magic_items;
  std::vector<std::unique_ptr<Smz3t::ItemBox>> m_z_items;
  Gtk::Grid m_page_1_grid;
  Gtk::Grid m_page_2_grid;
  Gtk::Grid m_h_item_grid;
  Gtk::Grid m_health_magic_grid;
  Gtk::Grid m_z_item_grid;
  Smz3t::HyruleGrid m_h_area_grid;
  Smz3t::ZebesGrid m_z_area_grid;
  Gtk::Notebook m_main_notebook;
};

} // namespace Smz3t

int main(int argc, char* argv[]) {
  auto app = Gtk::Application::create(argc, argv, "org.smz3t");

  Smz3t::MainWindow main_window;

  return app->run(main_window);
}
