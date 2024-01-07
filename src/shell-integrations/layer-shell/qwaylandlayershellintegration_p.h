// SPDX-FileCopyrightText: 2021 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QtWaylandClient/private/qwayland-wayland.h>
#include <QtWaylandClient/private/qwaylandshellintegration_p.h>

#include "qwayland-wlr-layer-shell-unstable-v1.h"

namespace QtWaylandClient {

class Q_WAYLANDCLIENT_EXPORT QWaylandLayerShellIntegration
        : public QtWaylandClient::QWaylandShellIntegrationTemplate<QWaylandLayerShellIntegration>
        , public QtWayland::zwlr_layer_shell_v1
{
public:
    QWaylandLayerShellIntegration();
    ~QWaylandLayerShellIntegration() override;

    QWaylandShellSurface *createShellSurface(QWaylandWindow *window) override;
};

} // namespace QtWaylandClient

