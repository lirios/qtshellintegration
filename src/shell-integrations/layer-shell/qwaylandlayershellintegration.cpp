// SPDX-FileCopyrightText: 2021 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "qwaylandlayershellintegration_p.h"
#include "qwaylandlayersurface_p.h"

namespace QtWaylandClient {

QWaylandLayerShellIntegration::QWaylandLayerShellIntegration()
    : QWaylandShellIntegrationTemplate<QWaylandLayerShellIntegration>(4)
{
}

QWaylandLayerShellIntegration::~QWaylandLayerShellIntegration()
{
    if (object() && zwlr_layer_shell_v1_get_version(object()) >= ZWLR_LAYER_SHELL_V1_DESTROY_SINCE_VERSION)
        zwlr_layer_shell_v1_destroy(object());
}

QWaylandShellSurface *QWaylandLayerShellIntegration::createShellSurface(QWaylandWindow *window)
{
    return new QWaylandLayerSurface(this, window);
}

} // namespace QtWaylandClient
