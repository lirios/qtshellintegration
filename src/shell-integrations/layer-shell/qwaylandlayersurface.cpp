// SPDX-FileCopyrightText: 2021 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <QtWaylandClient/private/qwaylandscreen_p.h>
#include <QtWaylandClient/private/qwaylandsurface_p.h>

#include "qwaylandlayersurface_p.h"

namespace QtWaylandClient {

QWaylandLayerSurface::QWaylandLayerSurface(QWaylandLayerShellIntegration *shell, QWaylandWindow *window)
    : QWaylandShellSurface(window)
    , QtWayland::zwlr_layer_surface_v1()
    , m_shell(shell)
{
    // Let's find the interface object associated with this window,
    // or bail out if we cannot find it
    auto *interface = Liri::QtShellIntegration::LayerSurface::get(window->window());
    if (!interface) {
        qCWarning(lcQpaWayland) << "Cannot find LayerSurface interface on window" << window->window();
        return;
    }
    qCDebug(lcQpaWayland) << "Creating layer surface with scope" << interface->scope();

    // Initialize layer surface
    auto *wlSurface = window->waylandSurface()->object();
    auto *wlOutput = !window->waylandScreen() || window->waylandScreen()->isPlaceholder()
            ? nullptr : window->waylandScreen()->output();
    auto layer = static_cast<uint32_t>(interface->layer());
    init(shell->get_layer_surface(wlSurface, wlOutput, layer, interface->scope()));

    // Enable changing the layer after initialization
    interface->setLayerEnabled(zwlr_layer_surface_v1_get_version(object()) >= ZWLR_LAYER_SURFACE_V1_SET_LAYER_SINCE_VERSION);

    // Set initial attributes, don't worry the surface will be committed automatically
    setAnchors(interface->anchors());
    setExclusiveZone(interface->exclusiveZone());
    setMargins(interface->margins());
    setKeyboardInteractivity(interface->keyboardInteractivity());

    // React to changes to the interface object
    connect(interface, &Liri::QtShellIntegration::LayerSurface::layerChanged,
            this, &QWaylandLayerSurface::setLayer);
    connect(interface, &Liri::QtShellIntegration::LayerSurface::anchorsChanged,
            this, &QWaylandLayerSurface::setAnchors);
    connect(interface, &Liri::QtShellIntegration::LayerSurface::exclusiveZoneChanged,
            this, &QWaylandLayerSurface::setExclusiveZone);
    connect(interface, &Liri::QtShellIntegration::LayerSurface::marginsChanged,
            this, &QWaylandLayerSurface::setMargins);
    connect(interface, &Liri::QtShellIntegration::LayerSurface::keyboardInteractivityChanged,
            this, &QWaylandLayerSurface::setKeyboardInteractivity);
}

QWaylandLayerSurface::~QWaylandLayerSurface()
{
    destroy();
}

bool QWaylandLayerSurface::isExposed() const
{
    return m_configured;
}

void QWaylandLayerSurface::applyConfigure()
{
    window()->resizeFromApplyConfigure(m_pendingSize);
}

void QWaylandLayerSurface::setWindowGeometry(const QRect &rect)
{
    setSize(rect.size());
}

void QWaylandLayerSurface::attachPopup(QWaylandShellSurface *popup)
{
    std::any anyRole = popup->surfaceRole();

    if (auto role = std::any_cast<::xdg_popup *>(&anyRole))
        get_popup(*role);
    else
        qCWarning(lcQpaWayland, "Cannot attach popup of unknown state");
}

void QWaylandLayerSurface::setLayer(Liri::QtShellIntegration::LayerSurface::Layer layer)
{
    // This slot shouldn't even be called if the compositor supports an older version
    // because in this case the interface won't allow changing the layer after initialization,
    // however better safe than sorry
    auto version = zwlr_layer_surface_v1_get_version(object());
    if (version >= ZWLR_LAYER_SURFACE_V1_SET_LAYER_SINCE_VERSION)
        set_layer(static_cast<uint32_t>(layer));
    else
        qCWarning(lcQpaWayland, "Do not set layer after initialization: need at least version %d instead of %d",
                  ZWLR_LAYER_SURFACE_V1_SET_LAYER_SINCE_VERSION, version);
}

void QWaylandLayerSurface::setAnchors(Liri::QtShellIntegration::LayerSurface::Anchors anchors)
{
    m_anchors = anchors;
    set_anchor(static_cast<uint32_t>(anchors));
    setSize(window()->surfaceSize());
}

void QWaylandLayerSurface::setSize(const QSize &surfaceSize)
{
    // Start with the surface size
    QSize size = surfaceSize;

    // Let the compositor set the width based on the output available width
    if (m_anchors.testFlag(Liri::QtShellIntegration::LayerSurface::LeftAnchor) &&
            m_anchors.testFlag(Liri::QtShellIntegration::LayerSurface::RightAnchor))
        size.setWidth(0);
    // Let the compositor set the width based on the output available width
    if (m_anchors.testFlag(Liri::QtShellIntegration::LayerSurface::TopAnchor) &&
            m_anchors.testFlag(Liri::QtShellIntegration::LayerSurface::BottomAnchor))
        size.setHeight(0);

    // Set size only if it's valid
    if (size.isValid()) {
        set_size(size.width(), size.height());

        // During the initialization process, we will apply all settings at once,
        // but after that we need to apply each setting as it's set by the application
        if (m_configured)
            window()->commit();
    }
}

void QWaylandLayerSurface::setExclusiveZone(qint32 exclusiveZone)
{
    set_exclusive_zone(exclusiveZone);

    // During the initialization process, we will apply all settings at once,
    // but after that we need to apply each setting as it's set by the application
    if (m_configured)
        window()->commit();
}

void QWaylandLayerSurface::setMargins(const QMargins &margins)
{
    set_margin(margins.top(), margins.right(), margins.bottom(), margins.left());

    // During the initialization process, we will apply all settings at once,
    // but after that we need to apply each setting as it's set by the application
    if (m_configured)
        window()->commit();
}

void QWaylandLayerSurface::setKeyboardInteractivity(Liri::QtShellIntegration::LayerSurface::KeyboardInteractivity keyboardInteractivity)
{
    auto version = zwlr_layer_surface_v1_get_version(object());
    if (keyboardInteractivity == Liri::QtShellIntegration::LayerSurface::OnDemandKeyboardInteractivity &&
            version < ZWLR_LAYER_SURFACE_V1_KEYBOARD_INTERACTIVITY_ON_DEMAND_SINCE_VERSION) {
        qCWarning(lcQpaWayland, "Ignoring on_demand keyboard interactivity: need at least version %d instead of %d",
                  ZWLR_LAYER_SURFACE_V1_KEYBOARD_INTERACTIVITY_ON_DEMAND_SINCE_VERSION, version);
        return;
    } else {
        set_keyboard_interactivity(static_cast<uint32_t>(keyboardInteractivity));

        // During the initialization process, we will apply all settings at once,
        // but after that we need to apply each setting as it's set by the application
        if (m_configured)
            window()->commit();
    }
}

void QWaylandLayerSurface::zwlr_layer_surface_v1_configure(uint32_t serial, uint32_t width, uint32_t height)
{
    ack_configure(serial);

    auto surfaceSize = window()->surfaceSize();
    m_pendingSize.setWidth(width > 0 ? width : surfaceSize.width());
    m_pendingSize.setHeight(height > 0 ? height : surfaceSize.height());

    if (m_configured) {
        // All configures after the initial one are for resizing the window,
        // let the QWaylandWindow machinery handle them when not painting
        window()->applyConfigureWhenPossible();
    } else {
        // First time configuration
        m_configured = true;
        window()->resizeFromApplyConfigure(m_pendingSize);
        window()->handleExpose(QRect(QPoint(), m_pendingSize));
    }
}

void QWaylandLayerSurface::zwlr_layer_surface_v1_closed()
{
    window()->window()->close();
}

} // namespace QtWaylandClient
