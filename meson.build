project('SMZ3 Tracker', 'cpp', 'c',
  version: '1.1',
  default_options: ['buildtype=release',
                    'warning_level=3',
                    'cpp_std=c++20'])

gtkmm_dep = dependency('gtkmm-3.0', version: '>= 3.24.0')

sources = [
  'src/main.cc',
  'src/itembox.cc',
  'src/hyrulegrid.cc',
  'src/zebesgrid.cc',
  'src/rewardbox.cc',
  'src/items.c'
]

exe = executable('smz3t', sources, c_args: '-Wno-overlength-strings',
                 dependencies: gtkmm_dep, install: true)
