// SPDX-FileCopyrightText: 2022 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QtWaylandClient/qtwaylandclientglobal.h>
#include <QtWaylandClient/private/qwayland-wayland.h>
#include <QtWaylandClient/private/qwaylandshellsurface_p.h>
#include <QtWaylandClient/private/qwaylandwindow_p.h>

#include "qwayland-ext-session-lock-v1.h"

namespace QtWaylandClient {

class QWaylandExtSessionLock;

class Q_WAYLANDCLIENT_EXPORT QWaylandExtSessionLockSurface
        : public QWaylandShellSurface
        , public QtWayland::ext_session_lock_surface_v1
{
    Q_OBJECT
public:
    QWaylandExtSessionLockSurface(QWaylandExtSessionLock *lock, QWaylandWindow *window);
    virtual ~QWaylandExtSessionLockSurface();

    bool isExposed() const override;
    void applyConfigure() override;

protected:
    void ext_session_lock_surface_v1_configure(uint32_t serial, uint32_t width, uint32_t height) override;

private:
    bool m_configured = false;
    uint32_t m_pendingConfigureSerial = 0;
    QSize m_pendingSize;
    QWaylandExtSessionLock *m_lock = nullptr;

private Q_SLOTS:
    void handleUnlock();
};

class Q_WAYLANDCLIENT_EXPORT QWaylandExtSessionLock
        : public QObject
        , public QtWayland::ext_session_lock_v1
{
    Q_OBJECT
public:
    QWaylandExtSessionLock(struct ::ext_session_lock_v1 *object);
    ~QWaylandExtSessionLock();

    QWaylandExtSessionLockSurface *createLockSurface(QWaylandWindow *window);

Q_SIGNALS:
    void locked();
    void finished();

protected:
    void ext_session_lock_v1_locked() override;
    void ext_session_lock_v1_finished() override;
};

} // namespace QtWaylandClient

