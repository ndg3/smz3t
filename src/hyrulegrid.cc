#include "hyrulegrid.h"

#include <format>

namespace Smz3t {

HyruleRow::HyruleRow() {}

HyruleRow::HyruleRow(std::string area_abbr, bool has_reward,
                     unsigned int box_keys, unsigned int drop_keys)
    : m_dungeon_map({"hyrule/dungeon_map"}),
      m_compass({"hyrule/compass"}),
      m_big_key({"hyrule/big_key"}) {
  m_area.set_markup(std::format("<span weight=\"bold\">{}</span>", area_abbr));

  if (has_reward) m_reward = std::make_unique<RewardBox>();

  if (box_keys) {
    m_box_keys = std::unique_ptr<ItemBox>(
        new ItemBox({"hyrule/box_key"}, 1, box_keys, 1));
  }

  if (drop_keys) {
    m_drop_keys = std::unique_ptr<ItemBox>(
        new ItemBox({"hyrule/drop_key"}, 1, drop_keys, 1));
  }
}

HyruleRow::~HyruleRow() {}

HyruleRowBuilder::HyruleRowBuilder() {}

HyruleRowBuilder::~HyruleRowBuilder() {}

HyruleRowBuilder& HyruleRowBuilder::init(std::string area_abbr) {
  m_area = area_abbr;
  m_has_reward = false;
  m_box_keys = 0;
  m_drop_keys = 0;
  return *this;
}

HyruleRowBuilder& HyruleRowBuilder::reward() {
  m_has_reward = true;
  return *this;
}

HyruleRowBuilder& HyruleRowBuilder::box_keys(unsigned int box_keys) {
  m_box_keys = box_keys;
  return *this;
}

HyruleRowBuilder& HyruleRowBuilder::drop_keys(unsigned int drop_keys) {
  m_drop_keys = drop_keys;
  return *this;
}

HyruleRow* HyruleRowBuilder::build() {
  return new HyruleRow(m_area, m_has_reward, m_box_keys, m_drop_keys);
}

HyruleGrid::HyruleGrid() {}

HyruleGrid::~HyruleGrid() {}

void HyruleGrid::add_row(HyruleRow* row) {
  m_rows.emplace_back(row);

  const int r = 0;
  const int c = m_rows.size() - 1;

  attach(row->m_area, r, c);
  if (row->m_reward) attach(*row->m_reward, r + 1, c);
  attach(row->m_dungeon_map, r + 2, c);
  attach(row->m_compass, r + 3, c);
  if (row->m_box_keys) attach(*row->m_box_keys, r + 4, c);
  if (row->m_drop_keys) attach(*row->m_drop_keys, r + 5, c);
  attach(row->m_big_key, r + 6, c);
}

}  // namespace Smz3t
