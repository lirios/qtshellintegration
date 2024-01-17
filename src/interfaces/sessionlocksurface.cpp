// SPDX-FileCopyrightText: 2022-2024 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#include "sessionlocksurface.h"
#include "sessionlocksurface_p.h"
#include "qtshellintegrationlogging.h"

namespace Liri {

namespace QtShellIntegration {

// Both shell integration and QML plugins will share this global
// since the interface is in a dynamic library
typedef QHash<QWindow *, SessionLockSurface *> SessionLockSurfaceMap;
Q_GLOBAL_STATIC(SessionLockSurfaceMap, globalLockSurfaces)

SessionLockSurface::SessionLockSurface(QObject *parent)
    : QObject(parent)
    , d_ptr(new SessionLockSurfacePrivate())
{
}

SessionLockSurface::~SessionLockSurface()
{
    Q_D(SessionLockSurface);
    globalLockSurfaces->remove(d->window);
}

bool SessionLockSurface::isInitialized() const
{
    Q_D(const SessionLockSurface);
    return d->initialized;
}

void SessionLockSurface::initialize()
{
    Q_D(SessionLockSurface);

    if (d->initialized)
        return;

    if (!d->window) {
        qCWarning(lcQtShellIntegration, "Window not assigned to SessionLockSurface, failed to initialize");
        return;
    }

    d->initialized = true;
}

QWindow *SessionLockSurface::window() const
{
    Q_D(const SessionLockSurface);
    return d->window;
}

void SessionLockSurface::setWindow(QWindow *window)
{
    Q_D(SessionLockSurface);

    if (d->window == window)
        return;

    if (d->initialized) {
        qCWarning(lcQtShellIntegration, "Unable to change SessionLockSurface::window after initialization");
        return;
    }

    d->window = window;
    Q_EMIT windowChanged(d->window);

    if (!globalLockSurfaces->contains(d->window))
        globalLockSurfaces->insert(d->window, this);
}

SessionLockSurface *SessionLockSurface::get(QWindow *window)
{
    return globalLockSurfaces->value(window, nullptr);
}

} // QtShellIntegration

} // Liri
