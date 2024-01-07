// SPDX-FileCopyrightText: 2021-2024 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#include <QHash>

#include "wlrlayersurface_p.h"
#include "qtshellintegrationlogging.h"
#include "wlrlayersurface.h"

namespace Liri {

namespace QtShellIntegration {

// Both shell integration and QML plugins will share this global
// since the interface is in a dynamic library
typedef QHash<QWindow *, WlrLayerSurface *> WlrLayerSurfaceMap;
Q_GLOBAL_STATIC(WlrLayerSurfaceMap, globalLayerSurfaces)

WlrLayerSurface::WlrLayerSurface(QObject *parent)
    : QObject(parent)
    , d_ptr(new WlrLayerSurfacePrivate())
{
}

WlrLayerSurface::~WlrLayerSurface()
{
    Q_D(WlrLayerSurface);
    globalLayerSurfaces->remove(d->window);
}

bool WlrLayerSurface::isInitialized() const
{
    Q_D(const WlrLayerSurface);
    return d->initialized;
}

QWindow *WlrLayerSurface::window() const
{
    Q_D(const WlrLayerSurface);
    return d->window;
}

void WlrLayerSurface::setWindow(QWindow *window)
{
    Q_D(WlrLayerSurface);

    if (d->window == window)
        return;

    if (d->initialized) {
        qCWarning(lcQtShellIntegration, "Unable to change WlrLayerSurface::window after initialization");
        return;
    }

    d->window = window;
    Q_EMIT windowChanged(d->window);

    if (!globalLayerSurfaces->contains(d->window))
        globalLayerSurfaces->insert(d->window, this);
}

WlrLayerSurface::Layer WlrLayerSurface::layer() const
{
    Q_D(const WlrLayerSurface);
    return d->layer;
}

void WlrLayerSurface::setLayer(WlrLayerSurface::Layer layer)
{
    Q_D(WlrLayerSurface);

    if (d->layer == layer)
        return;

    if (d->initialized && !d->setLayerEnabled) {
        qCWarning(lcQtShellIntegration, "Unable to change WlrLayerSurface::layer after initialization");
        return;
    }

    d->layer = layer;
    Q_EMIT layerChanged(d->layer);
}

QString WlrLayerSurface::role() const
{
    Q_D(const WlrLayerSurface);
    return d->role;
}

void WlrLayerSurface::setRole(const QString &role)
{
    Q_D(WlrLayerSurface);

    if (d->role == role)
        return;

    if (d->initialized) {
        qCWarning(lcQtShellIntegration, "Unable to change WlrLayerSurface::role after initialization");
        return;
    }

    d->role = role;
    Q_EMIT roleChanged(d->role);
}

WlrLayerSurface::Anchors WlrLayerSurface::anchors() const
{
    Q_D(const WlrLayerSurface);
    return d->anchors;
}

void WlrLayerSurface::setAnchors(WlrLayerSurface::Anchors anchors)
{
    Q_D(WlrLayerSurface);

    if (d->anchors == anchors)
        return;

    d->anchors = anchors;
    Q_EMIT anchorsChanged(d->anchors);
}

qint32 WlrLayerSurface::exclusiveZone() const
{
    Q_D(const WlrLayerSurface);
    return d->exclusiveZone;
}

void WlrLayerSurface::setExclusiveZone(qint32 zone)
{
    Q_D(WlrLayerSurface);

    if (d->exclusiveZone == zone)
        return;

    d->exclusiveZone = zone;
    Q_EMIT exclusiveZoneChanged(d->exclusiveZone);
}

QMargins WlrLayerSurface::margins() const
{
    Q_D(const WlrLayerSurface);
    return d->margins;
}

qint32 WlrLayerSurface::leftMargin() const
{
    Q_D(const WlrLayerSurface);
    return d->margins.left();
}

void WlrLayerSurface::setLeftMargin(qint32 margin)
{
    Q_D(WlrLayerSurface);

    if (d->margins.left() == margin)
        return;

    d->margins.setLeft(margin);
    Q_EMIT leftMarginChanged(margin);
    Q_EMIT marginsChanged(d->margins);
}

qint32 WlrLayerSurface::rightMargin() const
{
    Q_D(const WlrLayerSurface);
    return d->margins.right();
}

void WlrLayerSurface::setRightMargin(qint32 margin)
{
    Q_D(WlrLayerSurface);

    if (d->margins.right() == margin)
        return;

    d->margins.setRight(margin);
    Q_EMIT rightMarginChanged(margin);
    Q_EMIT marginsChanged(d->margins);
}

qint32 WlrLayerSurface::topMargin() const
{
    Q_D(const WlrLayerSurface);
    return d->margins.top();
}

void WlrLayerSurface::setTopMargin(qint32 margin)
{
    Q_D(WlrLayerSurface);

    if (d->margins.top() == margin)
        return;

    d->margins.setTop(margin);
    Q_EMIT topMarginChanged(margin);
    Q_EMIT marginsChanged(d->margins);
}

qint32 WlrLayerSurface::bottomMargin() const
{
    Q_D(const WlrLayerSurface);
    return d->margins.bottom();
}

void WlrLayerSurface::setBottomMargin(qint32 margin)
{
    Q_D(WlrLayerSurface);

    if (d->margins.bottom() == margin)
        return;

    d->margins.setBottom(margin);
    Q_EMIT bottomMarginChanged(margin);
    Q_EMIT marginsChanged(d->margins);
}

WlrLayerSurface::KeyboardInteractivity WlrLayerSurface::keyboardInteractivity() const
{
    Q_D(const WlrLayerSurface);
    return d->keyboardInteractivity;
}

void WlrLayerSurface::setKeyboardInteractivity(WlrLayerSurface::KeyboardInteractivity keyboardInteractivity)
{
    Q_D(WlrLayerSurface);

    if (d->keyboardInteractivity == keyboardInteractivity)
        return;

    d->keyboardInteractivity = keyboardInteractivity;
    Q_EMIT keyboardInteractivityChanged(d->keyboardInteractivity);
}

void WlrLayerSurface::initialize()
{
    Q_D(WlrLayerSurface);

    if (d->initialized)
        return;

    if (!d->window) {
        qCWarning(lcQtShellIntegration, "Window not assigned to WlrLayerSurface, failed to initialize");
        return;
    }

    d->initialized = true;
}

void WlrLayerSurface::setLayerEnabled(bool enabled)
{
    Q_D(WlrLayerSurface);
    d->setLayerEnabled = enabled;
}

WlrLayerSurface *WlrLayerSurface::get(QWindow *window)
{
    return globalLayerSurfaces->value(window, nullptr);
}

WlrLayerSurface *WlrLayerSurface::qmlAttachedProperties(QObject *object)
{
    return get(qobject_cast<QWindow *>(object));
}

} // namespace QtShellIntegration

} // namespace Liri
