Qt shell integration
====================

[![License](https://img.shields.io/badge/license-GPLv3.0-blue.svg)](https://www.gnu.org/licenses/gpl-3.0.html)
[![GitHub release](https://img.shields.io/github/release/lirios/qtshellintegration.svg)](https://github.com/lirios/qtshellintegration)
[![GitHub issues](https://img.shields.io/github/issues/lirios/qtshellintegration.svg)](https://github.com/lirios/qtshellintegration/issues)
[![CI](https://github.com/lirios/qtshellintegration/workflows/CI/badge.svg?branch=develop)](https://github.com/lirios/qtshellintegration/actions?query=workflow%3ACI)

Integration between Wayland shell protocols and Qt applications.

Contains support for the following Wayland protocols:

  * layer-shell
  * ext-session-lock

## Dependencies

Qt >= 6.6.0 with at least the following modules is required:

 * [qtbase](http://code.qt.io/cgit/qt/qtbase.git)
 * [qtwayland](http://code.qt.io/cgit/qt/qtwayland.git)

And the following modules:

 * [cmake](https://gitlab.kitware.com/cmake/cmake) >= 3.19.0
 * [extra-cmake-modules](https://invent.kde.org/frameworks/extra-cmake-modules) >= 5.245.0
 * [wayland-protocols](https://gitlab.freedesktop.org/wayland/wayland-protocols) >= 1.25
 * [xkbcommon](https://github.com/xkbcommon/libxkbcommon)

## Installation

```sh
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=/path/to/prefix ..
make
make install # use sudo if necessary
```

Replace `/path/to/prefix` to your installation prefix.
Default is `/usr/local`.

## Licensing

Licensed under the terms of the GNU Lesser General Public License version 3 or,
at your option, any later version.
