// SPDX-FileCopyrightText: 2022 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QWindow>
#include <QtQmlIntegration>

#include <LiriQtShellIntegration/liriqtshellintegrationglobal.h>

namespace Liri {

namespace QtShellIntegration {

class SessionLockSurfacePrivate;

class LIRIQTSHELLINTEGRATION_EXPORT SessionLockSurface : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("Cannot instantiate SessionLockSurface")
    QML_ATTACHED(SessionLockSurface)
    Q_DECLARE_PRIVATE(SessionLockSurface)
    Q_PROPERTY(QWindow *window READ window CONSTANT)
    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled NOTIFY enabledChanged)
public:
    ~SessionLockSurface();

    QWindow *window() const;

    bool isEnabled() const;
    void setEnabled(bool enabled);

    static SessionLockSurface *get(QWindow *window);

    static SessionLockSurface *qmlAttachedProperties(QObject *object);

Q_SIGNALS:
    void enabledChanged(bool enabled);
    void unlockRequested();

protected:
    SessionLockSurface(QWindow *window, QObject *parent = nullptr);

private:
    QScopedPointer<SessionLockSurfacePrivate> const d_ptr;
};

} // QtShellIntegration

} // Liri
