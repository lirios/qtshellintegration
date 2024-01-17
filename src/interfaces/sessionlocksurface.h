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
    Q_DECLARE_PRIVATE(SessionLockSurface)
    Q_PROPERTY(QWindow *window READ window WRITE setWindow NOTIFY windowChanged)
public:
    SessionLockSurface(QObject *parent = nullptr);
    ~SessionLockSurface();

    bool isInitialized() const;

    void initialize();

    QWindow *window() const;
    void setWindow(QWindow *window);

    static SessionLockSurface *get(QWindow *window);

Q_SIGNALS:
    void windowChanged(QWindow *window);
    void unlockRequested();

private:
    QScopedPointer<SessionLockSurfacePrivate> const d_ptr;
};

} // QtShellIntegration

} // Liri
