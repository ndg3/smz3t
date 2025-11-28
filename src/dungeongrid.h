#ifndef SMZ3T_DUNGEONGRID_H
#define SMZ3T_DUNGEONGRID_H

#include <gdkmm/pixbuf.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/eventbox.h>

class SmallKeyBox : public Gtk::EventBox {
 public:
  SmallKeyBox();
  SmallKeyBox(unsigned int keys, bool is_box);
  virtual ~SmallKeyBox();

 protected:
  class SmallKeyArea : public Gtk::DrawingArea {
   public:
    SmallKeyArea();
    SmallKeyArea(unsigned int keys, bool is_box);
    virtual ~SmallKeyArea();

    void draw_next_state();
    void draw_init_state();
    void draw_prev_state();

   protected:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
    Glib::RefPtr<Gdk::Pixbuf> m_key_image;
    unsigned int m_state;
    unsigned int m_count;
  };
  bool on_button_release(GdkEventButton* event);
  SmallKeyArea m_keys;
};

#include <gtkmm/grid.h>
#include <gtkmm/label.h>

#include <memory>
#include <string>
#include <vector>

#include "itembox.h"
#include "rewardbox.h"

struct DungeonRow {
  DungeonRow();
  DungeonRow(std::string dungeon_abbr, bool has_reward, unsigned box_keys = 0,
             unsigned drop_keys = 0);
  virtual ~DungeonRow();

  Gtk::Label m_name;
  std::unique_ptr<RewardBox> m_reward;
  ItemBox m_dungeon_map;
  ItemBox m_compass;
  std::unique_ptr<SmallKeyBox> m_box_keys;
  std::unique_ptr<SmallKeyBox> m_drop_keys;
  ItemBox m_big_key;
};

class DungeonGrid : public Gtk::Grid {
 public:
  DungeonGrid();
  virtual ~DungeonGrid();

  void add_row(DungeonRow* row);

 protected:
  std::vector<std::unique_ptr<DungeonRow>> m_rows;
};

#endif  // SMZ3T_DUNGEONGRID_H
