#ifndef SMZ3T_REWARDGRID_H
#define SMZ3T_REWARDGRID_H

#include <gtkmm/eventbox.h>
#include <gtkmm/label.h>

#include <string>
#include <vector>

class LabelBox : public Gtk::EventBox {
 public:
  LabelBox(std::vector<std::string> labels);
  virtual ~LabelBox();

 protected:
  bool on_button_release(GdkEventButton* event);
  Gtk::Label m_label;
  std::vector<std::string> m_text;
  unsigned int m_state;
};

#include <gtkmm/grid.h>

#include "itembox.h"

class RewardGrid : public Gtk::Grid {
 public:
  RewardGrid(std::vector<std::string> reward);
  virtual ~RewardGrid();

 protected:
  const std::vector<std::string> m_dungeons{"EP", "DP", "TH", "PD", "SP",
                                            "SW", "TT", "IP", "MM", "TR",
                                            "BR", "MA", "WS", "LN"};
  std::size_t m_state;
  ItemBox m_item;
  LabelBox m_label;
};

#endif  // SMZ3T_REWARDGRID_H
