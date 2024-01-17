// SPDX-FileCopyrightText: 2021-2024 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#include <QHash>

#include "layersurface_p.h"
#include "qtshellintegrationlogging.h"
#include "layersurface.h"

namespace Liri {

namespace QtShellIntegration {

// Both shell integration and QML plugins will share this global
// since the interface is in a dynamic library
typedef QHash<QWindow *, LayerSurface *> LayerSurfaceMap;
Q_GLOBAL_STATIC(LayerSurfaceMap, globalLayerSurfaces)

LayerSurface::LayerSurface(QWindow *window, QObject *parent)
    : QObject(parent)
    , d_ptr(new LayerSurfacePrivate())
{
    Q_D(LayerSurface);
    d->window = window;
    globalLayerSurfaces->insert(window, this);
}

LayerSurface::~LayerSurface()
{
    Q_D(LayerSurface);
    globalLayerSurfaces->remove(d->window);
}

QWindow *LayerSurface::window() const
{
    Q_D(const LayerSurface);
    return d->window;
}

LayerSurface::Layer LayerSurface::layer() const
{
    Q_D(const LayerSurface);
    return d->layer;
}

void LayerSurface::setLayer(LayerSurface::Layer layer)
{
    Q_D(LayerSurface);

    if (d->layer == layer)
        return;

    d->layer = layer;
    Q_EMIT layerChanged(d->layer);
}

QString LayerSurface::scope() const
{
    Q_D(const LayerSurface);
    return d->scope;
}

void LayerSurface::setScope(const QString &scope)
{
    Q_D(LayerSurface);

    if (d->scope == scope)
        return;

    d->scope = scope;
    Q_EMIT scopeChanged(d->scope);
}

LayerSurface::Anchors LayerSurface::anchors() const
{
    Q_D(const LayerSurface);
    return d->anchors;
}

void LayerSurface::setAnchors(LayerSurface::Anchors anchors)
{
    Q_D(LayerSurface);

    if (d->anchors == anchors)
        return;

    d->anchors = anchors;
    Q_EMIT anchorsChanged(d->anchors);
}

qint32 LayerSurface::exclusiveZone() const
{
    Q_D(const LayerSurface);
    return d->exclusiveZone;
}

void LayerSurface::setExclusiveZone(qint32 zone)
{
    Q_D(LayerSurface);

    if (d->exclusiveZone == zone)
        return;

    d->exclusiveZone = zone;
    Q_EMIT exclusiveZoneChanged(d->exclusiveZone);
}

QMargins LayerSurface::margins() const
{
    Q_D(const LayerSurface);
    return d->margins;
}

qint32 LayerSurface::leftMargin() const
{
    Q_D(const LayerSurface);
    return d->margins.left();
}

void LayerSurface::setLeftMargin(qint32 margin)
{
    Q_D(LayerSurface);

    if (d->margins.left() == margin)
        return;

    d->margins.setLeft(margin);
    Q_EMIT leftMarginChanged(margin);
    Q_EMIT marginsChanged(d->margins);
}

qint32 LayerSurface::rightMargin() const
{
    Q_D(const LayerSurface);
    return d->margins.right();
}

void LayerSurface::setRightMargin(qint32 margin)
{
    Q_D(LayerSurface);

    if (d->margins.right() == margin)
        return;

    d->margins.setRight(margin);
    Q_EMIT rightMarginChanged(margin);
    Q_EMIT marginsChanged(d->margins);
}

qint32 LayerSurface::topMargin() const
{
    Q_D(const LayerSurface);
    return d->margins.top();
}

void LayerSurface::setTopMargin(qint32 margin)
{
    Q_D(LayerSurface);

    if (d->margins.top() == margin)
        return;

    d->margins.setTop(margin);
    Q_EMIT topMarginChanged(margin);
    Q_EMIT marginsChanged(d->margins);
}

qint32 LayerSurface::bottomMargin() const
{
    Q_D(const LayerSurface);
    return d->margins.bottom();
}

void LayerSurface::setBottomMargin(qint32 margin)
{
    Q_D(LayerSurface);

    if (d->margins.bottom() == margin)
        return;

    d->margins.setBottom(margin);
    Q_EMIT bottomMarginChanged(margin);
    Q_EMIT marginsChanged(d->margins);
}

LayerSurface::KeyboardInteractivity LayerSurface::keyboardInteractivity() const
{
    Q_D(const LayerSurface);
    return d->keyboardInteractivity;
}

void LayerSurface::setKeyboardInteractivity(LayerSurface::KeyboardInteractivity keyboardInteractivity)
{
    Q_D(LayerSurface);

    if (d->keyboardInteractivity == keyboardInteractivity)
        return;

    d->keyboardInteractivity = keyboardInteractivity;
    Q_EMIT keyboardInteractivityChanged(d->keyboardInteractivity);
}

void LayerSurface::setLayerEnabled(bool enabled)
{
    Q_D(LayerSurface);
    d->setLayerEnabled = enabled;
}

LayerSurface *LayerSurface::get(QWindow *window)
{
    if (globalLayerSurfaces->contains(window))
        return globalLayerSurfaces->value(window);
    else
        return new LayerSurface(window);
}

LayerSurface *LayerSurface::qmlAttachedProperties(QObject *object)
{
    return get(qobject_cast<QWindow *>(object));
}

} // namespace QtShellIntegration

} // namespace Liri
