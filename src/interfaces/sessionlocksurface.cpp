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

SessionLockSurface::SessionLockSurface(QWindow *window, QObject *parent)
    : QObject(parent)
    , d_ptr(new SessionLockSurfacePrivate())
{
    Q_D(SessionLockSurface);
    d->window = window;
    globalLockSurfaces->insert(window, this);
}

SessionLockSurface::~SessionLockSurface()
{
    Q_D(SessionLockSurface);
    globalLockSurfaces->remove(d->window);
}

QWindow *SessionLockSurface::window() const
{
    Q_D(const SessionLockSurface);
    return d->window;
}

bool SessionLockSurface::isEnabled() const
{
    Q_D(const SessionLockSurface);
    return d->enabled;
}

void SessionLockSurface::setEnabled(bool enabled)
{
    Q_D(SessionLockSurface);
    
    if (!d->initialized) {
        if (d->enabled == enabled)
            return;

        d->initialized = true;
        d->enabled = enabled;
        Q_EMIT enabledChanged(enabled);
    }
}

SessionLockSurface *SessionLockSurface::get(QWindow *window)
{
    if (globalLockSurfaces->contains(window))
        return globalLockSurfaces->value(window);
    else
        return new SessionLockSurface(window);
}

SessionLockSurface *SessionLockSurface::qmlAttachedProperties(QObject *object)
{
    return get(qobject_cast<QWindow *>(object));
}

} // QtShellIntegration

} // Liri
