#ifndef SMZ3T_ZEBESGRID_H
#define SMZ3T_ZEBESGRID_H

#include <gtkmm/grid.h>
#include <gtkmm/label.h>

#include <memory>
#include <string>
#include <vector>

#include "itembox.h"
#include "rewardbox.h"

struct ZebesRow {
  ZebesRow();
  ZebesRow(std::string area_abbr, bool has_reward, bool has_2_keys);
  virtual ~ZebesRow();

  Gtk::Label m_name;
  std::unique_ptr<RewardBox> m_reward;
  ItemBox m_map_station;
  ItemBox m_dummy_box;
  ItemBox m_key_1;
  std::unique_ptr<ItemBox> m_key_2;
  ItemBox m_boss_key;
};

class ZebesGrid : public Gtk::Grid {
 public:
  ZebesGrid();
  virtual ~ZebesGrid();
  void add_row(ZebesRow* row);

 protected:
  std::vector<std::unique_ptr<ZebesRow>> m_rows;
};

#endif  // SMZ3T_ZEBESGRID_H
