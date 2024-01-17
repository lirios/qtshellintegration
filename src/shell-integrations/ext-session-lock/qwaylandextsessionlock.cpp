// SPDX-FileCopyrightText: 2022 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <QtWaylandClient/private/qwaylandscreen_p.h>
#include <QtWaylandClient/private/qwaylandwindow_p.h>
#include <qpa/qplatformwindow.h>

#include <LiriQtShellIntegration/ExtSessionLockSurface>

#include "qwaylandextsessionlock_p.h"

namespace QtWaylandClient {

/*
 * QWaylandExtSessionLockSurface
 */

QWaylandExtSessionLockSurface::QWaylandExtSessionLockSurface(QWaylandExtSessionLock *lock, QWaylandWindow *window)
    : QWaylandShellSurface(window)
    , QtWayland::ext_session_lock_surface_v1()
    , m_lock(lock)
{
    auto *interface = Liri::QtShellIntegration::SessionLockSurface::get(window->window());
    if (!interface) {
        qCWarning(lcQpaWayland) << "Cannot find LockSurface interface on window" << window->window();
        return;
    }

    init(lock->get_lock_surface(window->wlSurface(), window->waylandScreen()->output()));

    connect(interface, &Liri::QtShellIntegration::SessionLockSurface::unlockRequested,
            this, &QWaylandExtSessionLockSurface::handleUnlock);
}

QWaylandExtSessionLockSurface::~QWaylandExtSessionLockSurface()
{
    destroy();
}

bool QWaylandExtSessionLockSurface::isExposed() const
{
    return m_configured || m_pendingConfigureSerial;
}

void QWaylandExtSessionLockSurface::applyConfigure()
{
    Q_ASSERT(m_pendingConfigureSerial != 0);

    if (!m_pendingSize.isEmpty())
        window()->resizeFromApplyConfigure(m_pendingSize);

    m_configured = true;
    ack_configure(m_pendingConfigureSerial);

    m_pendingConfigureSerial = 0;
}

void QWaylandExtSessionLockSurface::ext_session_lock_surface_v1_configure(uint32_t serial, uint32_t width, uint32_t height)
{
    m_pendingConfigureSerial = serial;
    m_pendingSize = QSize(width, height);

    if (!m_configured) {
        // First time configuration
        applyConfigure();
    } else {
        // All configures after the initial one are for resizing the window,
        // let the QWaylandWindow machinery handle them when not painting
        window()->applyConfigureWhenPossible();
    }

    window()->handleExpose(QRect(QPoint(), m_pendingSize));
}

void QWaylandExtSessionLockSurface::handleUnlock()
{
    m_lock->unlock_and_destroy();
    window()->close();
}

/*
 * QWaylandExtSessionLock
 */

QWaylandExtSessionLock::QWaylandExtSessionLock(struct ::ext_session_lock_v1 *object)
    : QtWayland::ext_session_lock_v1(object)
{
}

QWaylandExtSessionLock::~QWaylandExtSessionLock()
{
    destroy();
}

QWaylandExtSessionLockSurface *QWaylandExtSessionLock::createLockSurface(QWaylandWindow *window)
{
    return new QWaylandExtSessionLockSurface(this, window);
}

void QWaylandExtSessionLock::ext_session_lock_v1_locked()
{
    Q_EMIT locked();
}

void QWaylandExtSessionLock::ext_session_lock_v1_finished()
{
    Q_EMIT finished();
}

} // namespace QtWaylandClient
