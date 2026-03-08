#include <gtkmm/application.h>
#include <gtkmm/button.h>
#include <gtkmm/cssprovider.h>
#include <gtkmm/grid.h>
#include <gtkmm/notebook.h>
#include <gtkmm/stylecontext.h>
#include <gtkmm/window.h>

#include <memory>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include "src/hyrulegrid.h"
#include "src/itembox.h"
#include "src/state.h"
#include "src/zebesgrid.h"

namespace Smz3t {

class MainWindow : public Gtk::Window {
 public:
  MainWindow() {
    set_title("SMZ3 Tracker");

    std::vector<std::pair<std::vector<std::string>, std::vector<unsigned int>>>
        h_items{
            {{"bow"}, {}},
            {{"blue_boomerang"}, {}},
            {{"hookshot"}, {}},
            {{"bomb"}, {}},
            {{"mushroom"}, {}},
            {{"bottle:0", "bottle_life_medicine", "bottle_magic_medicine",
              "bottle_cure-all_medicine", "bottle_bee", "bottle_faerie"},
             {}},
            {{"fire_rod"}, {}},
            {{"ice_rod"}, {}},
            {{"bombos"}, {}},
            {{"ether"}, {}},
            {{"quake"}, {}},
            {{"bottle:1", "bottle_life_medicine", "bottle_magic_medicine",
              "bottle_cure-all_medicine", "bottle_bee", "bottle_faerie"},
             {}},
            {{"lamp"}, {}},
            {{"magic_hammer"}, {}},
            {{"shovel"}, {}},
            {{"bug-catching_net"}, {}},
            {{"book_of_mudora"}, {}},
            {{"bottle:2", "bottle_life_medicine", "bottle_magic_medicine",
              "bottle_cure-all_medicine", "bottle_bee", "bottle_faerie"},
             {}},
            {{"cane_of_somaria"}, {}},
            {{"cane_of_byrna"}, {}},
            {{"magic_cape"}, {}},
            {{"magic_mirror"}, {}},
            {{"silver_arrow"}, {}},
            {{"bottle:3", "bottle_life_medicine", "bottle_magic_medicine",
              "bottle_cure-all_medicine", "bottle_bee", "bottle_faerie"},
             {}},
            {{"red_boomerang"}, {}},
            {{"magic_powder"}, {}},
            {{"flute"}, {}},
            {{"fighters_sword", "master_sword", "tempered_sword", "gold_sword"},
             {}},
            {{"fighters_shield", "red_shield", "mirror_shield"}, {}},
            {{"green_jerkin", "blue_mail", "red_mail"}, {}},
            {{"arrow_upgrade"}, {1, 4, 1}},
            {{"pegasus_boots"}, {}},
            {{"power_glove", "titans_mitt"}, {}},
            {{"zoras_flippers"}, {}},
            {{"moon_pearl"}, {}},
            {{"bomb_upgrade"}, {1, 4, 1}}};

    std::vector<std::tuple<std::string, std::vector<std::string>,
                           std::vector<unsigned int>>>
        rewards{{"hyrule", {"piece_of_heart"}, {1, 24, 1}},
                {"hyrule", {"heart_container"}, {1, 10, 1}},
                {"hyrule", {"half_magic"}, {}},
                {"zebes", {"energy_tank"}, {1, 14, 1}},
                {"zebes", {"reserve_tank"}, {1, 4, 1}}};

    std::vector<std::pair<std::vector<std::string>, std::vector<unsigned int>>>
        z_items{{{"missile"}, {5, 200, 5}},
                {{"super_missile"}, {5, 80, 5}},
                {{"power_bomb"}, {5, 50, 5}},
                {{"grapple_beam"}, {}},
                {{"x-ray_scope"}, {}},
                {{"morphing_ball"}, {}},
                {{"charge_beam"}, {}},
                {{"ice_beam"}, {}},
                {{"wave_beam"}, {}},
                {{"spazer"}, {}},
                {{"plasma_beam"}, {}},
                {{"bomb"}, {}},
                {{"varia_suit", "gravity_suit"}, {}},
                {{"hi-jump_boots"}, {}},
                {{"space_jump"}, {}},
                {{"speed_booster"}, {}},
                {{"screw_attack"}, {}},
                {{"spring_ball"}, {}}};

    // Build items for _A Link to the Past_
    std::size_t i = 0;
    for (auto& [item, text] : h_items) {
      std::unique_ptr<Smz3t::ItemBox> box;
      if (text.size() == 0) {
        box = std::make_unique<Smz3t::ItemBox>("hyrule", item);
      } else {
        box = std::make_unique<Smz3t::ItemBox>("hyrule", item, text[0], text[1],
                                               text[2]);
      }
      m_h_item_grid.attach(*box, i % 6, i / 6);
      m_h_items.push_back(std::move(box));
      ++i;
    }

    // Build health and magic upgrades for both games
    i = 0;
    for (auto& [world, item, text] : rewards) {
      std::unique_ptr<Smz3t::ItemBox> box;
      if (text.size() == 0) {
        box = std::make_unique<Smz3t::ItemBox>(world, item);
      } else {
        box = std::make_unique<Smz3t::ItemBox>(world, item, text[0], text[1],
                                               text[2]);
      }
      m_health_magic_grid.attach(*box, i % 5, i / 5);
      m_health_magic_items.push_back(std::move(box));
      ++i;
    }

    // Build items for _Super Metroid_
    i = 0;
    for (auto& [item, text] : z_items) {
      std::unique_ptr<Smz3t::ItemBox> box;
      if (text.size() == 0) {
        box = std::make_unique<Smz3t::ItemBox>("zebes", item);
      } else {
        box = std::make_unique<Smz3t::ItemBox>("zebes", item, text[0], text[1],
                                               text[2]);
      }
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
    m_z_area_grid.add_row(zb.init("NO").key_2().build());
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

    // Add Save and Open buttons to third page, center
    m_save_button.set_label("Save");
    m_save_button.signal_clicked().connect(sigc::ptr_fun(State::save_file));
    m_load_button.set_label("Open");  // change to Load
    m_load_button.signal_clicked().connect(
        sigc::mem_fun(*this, &MainWindow::update_after_open));
    m_page_3_grid.attach(m_save_button, 0, 0);
    m_page_3_grid.attach(m_load_button, 0, 1);
    m_page_3_grid.set_halign(Gtk::ALIGN_CENTER);

    // Add pages to main window
    m_main_notebook.append_page(m_page_1_grid, "Items");
    m_main_notebook.append_page(m_page_2_grid, "Areas");
    m_main_notebook.append_page(m_page_3_grid, "Save");
    add(m_main_notebook);

    // Set foreground and background color (avoids theming issues with icons)
    auto provider = Gtk::CssProvider::create();
    provider->load_from_data(
        "notebook > stack { color: white; background-color: black; }");
    Gtk::StyleContext::add_provider_for_screen(
        get_screen(), provider, GTK_STYLE_PROVIDER_PRIORITY_USER);

    show_all_children();
  }
  virtual ~MainWindow() {}

 protected:
  void update_after_open() {
    if (!State::open_file()) {
      return;
    }
    auto update_item = [&](std::unique_ptr<Smz3t::ItemBox>& item) {
      item->update_state_from_json();
    };
    std::ranges::for_each(m_h_items, update_item);
    std::ranges::for_each(m_health_magic_items, update_item);
    std::ranges::for_each(m_z_items, update_item);
    m_h_area_grid.update_state_from_json();
    m_z_area_grid.update_state_from_json();
  }

  std::vector<std::unique_ptr<Smz3t::ItemBox>> m_h_items;
  std::vector<std::unique_ptr<Smz3t::ItemBox>> m_health_magic_items;
  std::vector<std::unique_ptr<Smz3t::ItemBox>> m_z_items;
  Gtk::Button m_save_button;
  Gtk::Button m_load_button;
  Gtk::Grid m_page_1_grid;
  Gtk::Grid m_page_2_grid;
  Gtk::Grid m_page_3_grid;
  Gtk::Grid m_h_item_grid;
  Gtk::Grid m_health_magic_grid;
  Gtk::Grid m_z_item_grid;
  Smz3t::HyruleGrid m_h_area_grid;
  Smz3t::ZebesGrid m_z_area_grid;
  Gtk::Notebook m_main_notebook;
};

}  // namespace Smz3t

int main(int argc, char* argv[]) {
  auto app = Gtk::Application::create(argc, argv, "org.smz3t");

  Smz3t::MainWindow main_window;

  return app->run(main_window);
}
