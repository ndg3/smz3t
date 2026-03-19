project('SMZ3 Tracker', 'cpp', 'c',
  version: '2.2',
  default_options: ['buildtype=release',
                    'warning_level=3',
                    'cpp_std=c++20'])

gtkmm_dep = dependency('gtkmm-3.0', version: '>= 3.24.0')
json_dep = dependency('nlohmann_json')

sources = [
  'src/main.cc',
  'src/itembox.cc',
  'src/hyrulegrid.cc',
  'src/zebesgrid.cc',
  'src/rewardbox.cc',
  'src/items.c',
  'src/state.cc',
]

exe = executable('smz3t', sources, c_args: '-Wno-overlength-strings',
                 dependencies: [gtkmm_dep, json_dep], install: true)
