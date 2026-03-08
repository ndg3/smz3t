#include "src/zebesgrid.h"

#include <format>
#include <memory>
#include <string>

namespace Smz3t {

ZebesRow::ZebesRow() {}

ZebesRow::ZebesRow(std::string area_abbr, bool has_reward, bool has_2_keys)
    : m_map_station("zebes:" + area_abbr, {"map_station"}),
      m_key_1("zebes:" + area_abbr, {"key_1"}),
      m_boss_key("zebes:" + area_abbr, {"boss_key"}) {
  m_area.set_markup(std::format("<span weight=\"bold\">{}</span>", area_abbr));

  m_dummy_box.set_size_request(32, 32);

  if (has_reward)
    m_reward = std::unique_ptr<RewardBox>(new RewardBox("zebes:" + area_abbr));

  if (has_2_keys)
    m_key_2 =
        std::unique_ptr<ItemBox>(new ItemBox("zebes:" + area_abbr, {"key_2"}));
}

ZebesRow::~ZebesRow() {}

void ZebesRow::update_state_from_json() {
  if (m_reward) {
    m_reward->update_state_from_json();
  }
  m_map_station.update_state_from_json();
  m_key_1.update_state_from_json();
  if (m_key_2) {
    m_key_2->update_state_from_json();
  }
  m_boss_key.update_state_from_json();
}

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

void ZebesGrid::update_state_from_json() {
  for (auto& row : m_rows) {
    row->update_state_from_json();
  }
}

}  // namespace Smz3t
