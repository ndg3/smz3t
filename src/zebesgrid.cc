#include "zebesgrid.h"

ZebesRow::ZebesRow() {}

ZebesRow::ZebesRow(std::string area_abbr, bool has_reward, bool has_2_keys)
    : m_name(area_abbr),
      m_map_station({"metroid/map_station"}),
      m_key_1({"metroid/key_1"}),
      m_boss_key({"metroid/boss_key"}) {
  auto context = m_name.get_pango_context();
  auto font = context->get_font_description();
  font.set_weight(Pango::WEIGHT_BOLD);
  context->set_font_description(font);

  m_dummy_box.set_size_request(32, 32);

  if (has_reward) {
    m_reward = std::make_unique<RewardBox>();
  }
  if (has_2_keys) {
    m_key_2 = std::unique_ptr<ItemBox>(new ItemBox({"metroid/key_2"}));
  }
}

ZebesRow::~ZebesRow() {}

ZebesGrid::ZebesGrid() {}

ZebesGrid::~ZebesGrid() {}

void ZebesGrid::add_row(ZebesRow* row) {
  m_rows.emplace_back(row);
  int r = 0;
  int c = m_rows.size() - 1;
  attach(row->m_name, r, c);
  if (row->m_reward) {
    attach(*row->m_reward, r + 1, c);
  }
  attach(row->m_map_station, r + 2, c);
  attach(row->m_dummy_box, r + 3, c);
  attach(row->m_key_1, r + 4, c);
  if (row->m_key_2) {
    attach(*row->m_key_2, r + 5, c);
  }
  attach(row->m_boss_key, r + 6, c);
}
