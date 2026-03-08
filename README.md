# Super Metroid + A Link to the Past Randomizer Tracker (SMZ3T)
SMZ3T is a tracker for the [_Super Metroid_ and _The Legend of Zelda: A Link to
the Past_ combo randomizer](https://samus.link).

- Features
  - Simple and condensed layout
  - Keysanity support
  - Save and restore in JSON format
- Upcoming but may take a while
  - Location tracker to show whether a location can be reached with the current
  items collected

## Build
This program requires
- [Meson](https://mesonbuild.com/index.html)
- [gtkmm 3](https://gtkmm.gnome.org/en/index.html)
- [nlohmann/json](https://github.com/nlohmann/json)
- A C/C++ compiler (tested with [gcc](https://gcc.gnu.org/) and
[clang](https://clang.llvm.org/))

All of these dependencies should be available in most Linux distributions.
Windows is not currently supported but may be in the future.

To build, navigate to the top level of the project's directory and execute the
following:

```bash
meson setup build/ # you can use another directory instead of build if you want
meson compile -C build/
```

## Usage
To run, execute `./build/smz3t` in the terminal or double-click on the program
in your file browser.

Most items have these controls:
- Left-click to mark an item as collected or, if already collected, mark it as
upgraded.
- Right-click to unmark upgrades or, if only the base item is collected, unmark
the item.
- Middle-click to unmark an item whether it has been upgraded or not.

The only exception is with rewards (pendants, crystals, and boss rewards):
- Left-click to toggle an item as marked or unmarked.
- Right-click to cycle through rewards (green pendant, blue/red pendant, blue
crystal, red crystal, Kraid reward, Phantoon reward, Draygon reward, and Ridley
reward). The item does not have to be marked to do this.
- Middle-click to reset to an unmarked green pendant.

To save your progress, click on the "Save" tab and click the "Save" button. The
state will be saved in JSON format. You can also load a previous save by
clicking on the "Open" button.
