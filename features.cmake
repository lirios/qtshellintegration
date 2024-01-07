# SPDX-FileCopyrightText: 2024 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
# SPDX-License-Identifier: BSD-3-Clause

## Find wayland-protocols:
find_package(WaylandProtocols 1.25)
set_package_properties(WaylandProtocols PROPERTIES TYPE REQUIRED)

## Find Qt:
find_package(Qt6 "6.6.0"
    REQUIRED
    COMPONENTS
        Core
        Qml
        QmlIntegration
        Gui
        Widgets
        QuickControls2
        WaylandClient
)

#### Features

## Features summary:
if(NOT LIRI_SUPERBUILD)
    feature_summary(WHAT ENABLED_FEATURES DISABLED_FEATURES)
endif()
