// SPDX-FileCopyrightText: 2022-2024 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#include "extsessionlocksurface.h"
#include "extsessionlocksurface_p.h"
#include "qtshellintegrationlogging.h"

namespace Liri {

namespace QtShellIntegration {

// Both shell integration and QML plugins will share this global
// since the interface is in a dynamic library
typedef QHash<QWindow *, ExtSessionLockSurface *> ExtSessionLockSurfaceMap;
Q_GLOBAL_STATIC(ExtSessionLockSurfaceMap, globalLockSurfaces)

ExtSessionLockSurface::ExtSessionLockSurface(QObject *parent)
    : QObject(parent)
    , d_ptr(new ExtSessionLockSurfacePrivate())
{
}

ExtSessionLockSurface::~ExtSessionLockSurface()
{
    Q_D(ExtSessionLockSurface);
    globalLockSurfaces->remove(d->window);
}

bool ExtSessionLockSurface::isInitialized() const
{
    Q_D(const ExtSessionLockSurface);
    return d->initialized;
}

void ExtSessionLockSurface::initialize()
{
    Q_D(ExtSessionLockSurface);

    if (d->initialized)
        return;

    if (!d->window) {
        qCWarning(lcQtShellIntegration, "Window not assigned to ExtSessionLockSurface, failed to initialize");
        return;
    }

    d->initialized = true;
}

QWindow *ExtSessionLockSurface::window() const
{
    Q_D(const ExtSessionLockSurface);
    return d->window;
}

void ExtSessionLockSurface::setWindow(QWindow *window)
{
    Q_D(ExtSessionLockSurface);

    if (d->window == window)
        return;

    if (d->initialized) {
        qCWarning(lcQtShellIntegration, "Unable to change ExtSessionLockSurface::window after initialization");
        return;
    }

    d->window = window;
    Q_EMIT windowChanged(d->window);

    if (!globalLockSurfaces->contains(d->window))
        globalLockSurfaces->insert(d->window, this);
}

ExtSessionLockSurface *ExtSessionLockSurface::get(QWindow *window)
{
    return globalLockSurfaces->value(window, nullptr);
}

} // QtShellIntegration

} // Liri
