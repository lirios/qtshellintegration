// SPDX-FileCopyrightText: 2022 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QtWaylandClient/private/qwayland-wayland.h>
#include <QtWaylandClient/private/qwaylandshellintegration_p.h>

#include "qwaylandextsessionlock_p.h"

#include <wayland-client.h>

#include "qwayland-ext-session-lock-v1.h"

namespace QtWaylandClient {

class Q_WAYLANDCLIENT_EXPORT QWaylandLockscreenIntegration
        : public QWaylandShellIntegrationTemplate<QWaylandLockscreenIntegration>
        , public QtWayland::ext_session_lock_manager_v1
{
    Q_OBJECT
    Q_PROPERTY(State state READ state WRITE setState NOTIFY stateChanged)
public:
    enum State {
        Initializing,
        Locking,
        Locked,
        Exiting
    };
    Q_ENUM(State)

    QWaylandLockscreenIntegration();
    ~QWaylandLockscreenIntegration() override;

    State state() const;
    void setState(State state);

    QWaylandShellSurface *createShellSurface(QWaylandWindow *window) override;

Q_SIGNALS:
    void stateChanged(QWaylandLockscreenIntegration::State state);

private:
    QScopedPointer<QWaylandExtSessionLock> m_lock;
    State m_state = Initializing;

    void waitForLock();
};

} // namespace QtWaylandClient

