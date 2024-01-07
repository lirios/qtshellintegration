// SPDX-FileCopyrightText: 2021 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QtWaylandClient/qtwaylandclientglobal.h>
#include <QtWaylandClient/private/qwaylandshellsurface_p.h>
#include <QtWaylandClient/private/qwaylandwindow_p.h>

#include <LiriQtShellIntegration/WlrLayerSurface>

#include "qwaylandlayershellintegration_p.h"
#include "qwayland-wlr-layer-shell-unstable-v1.h"

namespace QtWaylandClient {

class Q_WAYLANDCLIENT_EXPORT QWaylandLayerSurface
        : public QWaylandShellSurface
        , public QtWayland::zwlr_layer_surface_v1
{
    Q_OBJECT
public:
    QWaylandLayerSurface(QWaylandLayerShellIntegration *shell, QWaylandWindow *window);
    virtual ~QWaylandLayerSurface();

    bool isExposed() const override;

    void applyConfigure() override;
    void setWindowGeometry(const QRect &rect) override;
    void attachPopup(QWaylandShellSurface *popup) override;

public Q_SLOTS:
    void setLayer(Liri::QtShellIntegration::WlrLayerSurface::Layer layer);
    void setAnchors(Liri::QtShellIntegration::WlrLayerSurface::Anchors anchors);
    void setSize(const QSize &surfaceSize);
    void setExclusiveZone(qint32 exclusiveZone);
    void setMargins(const QMargins &margins);
    void setKeyboardInteractivity(Liri::QtShellIntegration::WlrLayerSurface::KeyboardInteractivity keyboardInteractivity);

protected:
    void zwlr_layer_surface_v1_configure(uint32_t serial, uint32_t width, uint32_t height) override;
    void zwlr_layer_surface_v1_closed() override;

private:
    QWaylandLayerShellIntegration *m_shell = nullptr;
    Liri::QtShellIntegration::WlrLayerSurface::Anchors m_anchors;
    bool m_configured = false;
    QSize m_pendingSize;
};

} // namespace QtWaylandClient

