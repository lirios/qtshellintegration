// SPDX-FileCopyrightText: 2022 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <QtCore/QEventLoop>
#include <QtCore/QTimer>
#include <QtGui/QGuiApplication>

#include "qwaylandlockscreenintegration_p.h"

namespace QtWaylandClient {

QWaylandLockscreenIntegration::QWaylandLockscreenIntegration()
    : QWaylandShellIntegrationTemplate(1)
    , QtWayland::ext_session_lock_manager_v1()
{
    connect(this, &QWaylandShellIntegrationTemplate::activeChanged, this, [this] {
        if (isActive() && m_lock.isNull()) {
            // Ask the compositor to lock the session and wait for it, otherwise
            // createShellSurface() would fail since the lock is not yet acquired
            // when it's invoked
            setState(Locking);
            
            m_lock.reset(new QWaylandExtSessionLock(QtWayland::ext_session_lock_manager_v1::lock()));

            connect(m_lock.data(), &QWaylandExtSessionLock::locked, [this] {
                qCInfo(lcQpaWayland, "Lock screen engaged");
                setState(Locked);
            });
            connect(m_lock.data(), &QWaylandExtSessionLock::finished, [this] {
                qCInfo(lcQpaWayland, "Exiting lock screen...");

                switch (m_state) {
                case Locking:
                    qCWarning(lcQpaWayland, "The Wayland compositor has denied the attempt to lock the session: maybe another client is running, exiting...");
                    setState(Exiting);
                    break;
                case Locked:
                    qCWarning(lcQpaWayland, "The Wayland compositor has unlocked the session, exiting...");
                    setState(Exiting);
                    break;
                default:
                    break;
                };
            });

            waitForLock();
        }
    });
}

QWaylandLockscreenIntegration::~QWaylandLockscreenIntegration()
{
    if (isActive())
        QtWayland::ext_session_lock_manager_v1::destroy();
}

QWaylandLockscreenIntegration::State QWaylandLockscreenIntegration::state() const
{
    return m_state;
}

void QWaylandLockscreenIntegration::setState(State state)
{
    if (m_state == state)
        return;

    m_state = state;
    Q_EMIT stateChanged(state);

    if (state == Exiting)
        QGuiApplication::quit();
}

QWaylandShellSurface *QWaylandLockscreenIntegration::createShellSurface(QWaylandWindow *window)
{
    if (window->window()->type() != Qt::Window) {
        qCWarning(lcQpaWayland) << "Only toplevel windows are supported by liri-lockscreen";
        return nullptr;
    }

    if (m_state != QWaylandLockscreenIntegration::Locked) {
        qCWarning(lcQpaWayland) << "A lock was not acquired: cannot create a lock surface";
        return nullptr;
    }

    return m_lock->createLockSurface(window);
}

void QWaylandLockscreenIntegration::waitForLock()
{
    QEventLoop loop;

    // We don't want to wait for ever: at some point we will give up
    QTimer timer;
    timer.setSingleShot(true);
    connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);

    connect(m_lock.data(), &QWaylandExtSessionLock::locked,
            &loop, &QEventLoop::quit);

    timer.start(5000);
    loop.exec();

    disconnect(m_lock.data(), nullptr, this, nullptr);
}

} // namespace QtWaylandClient
