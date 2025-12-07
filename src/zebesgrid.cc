#include "zebesgrid.h"

#include <format>

namespace Smz3t {

ZebesRow::ZebesRow() {}

ZebesRow::ZebesRow(std::string area_abbr, bool has_reward, bool has_2_keys)
    : m_map_station({"zebes/map_station"}),
      m_key_1({"zebes/key_1"}),
      m_boss_key({"zebes/boss_key"}) {
  m_area.set_markup(std::format("<span weight=\"bold\">{}</span>", area_abbr));

  m_dummy_box.set_size_request(32, 32);

  if (has_reward) m_reward = std::make_unique<RewardBox>();

  if (has_2_keys)
    m_key_2 = std::unique_ptr<ItemBox>(new ItemBox({"zebes/key_2"}));
}

ZebesRow::~ZebesRow() {}

ZebesRowBuilder::ZebesRowBuilder() {}

ZebesRowBuilder::~ZebesRowBuilder() {}

ZebesRowBuilder& ZebesRowBuilder::init(std::string area_abbr) {
  m_area = area_abbr;
  m_has_reward = false;
  m_has_key_2 = false;
  return *this;
}

ZebesRowBuilder& ZebesRowBuilder::reward() {
  m_has_reward = true;
  return *this;
}

ZebesRowBuilder& ZebesRowBuilder::key_2() {
  m_has_key_2 = true;
  return *this;
}

ZebesRow* ZebesRowBuilder::build() {
  return new ZebesRow(m_area, m_has_reward, m_has_key_2);
}

ZebesGrid::ZebesGrid() {}

ZebesGrid::~ZebesGrid() {}

void ZebesGrid::add_row(ZebesRow* row) {
  m_rows.emplace_back(row);

  const int r = 0;
  const int c = m_rows.size() - 1;

  attach(row->m_area, r, c);
  if (row->m_reward) attach(*row->m_reward, r + 1, c);
  attach(row->m_map_station, r + 2, c);
  attach(row->m_dummy_box, r + 3, c);
  attach(row->m_key_1, r + 4, c);
  if (row->m_key_2) attach(*row->m_key_2, r + 5, c);
  attach(row->m_boss_key, r + 6, c);
}

}  // namespace Smz3t
