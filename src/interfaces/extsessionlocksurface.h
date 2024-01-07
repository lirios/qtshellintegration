// SPDX-FileCopyrightText: 2022 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QWindow>
#include <QtQmlIntegration>

#include <LiriQtShellIntegration/liriqtshellintegrationglobal.h>

namespace Liri {

namespace QtShellIntegration {

class ExtSessionLockSurfacePrivate;

class LIRIQTSHELLINTEGRATION_EXPORT ExtSessionLockSurface : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_DECLARE_PRIVATE(ExtSessionLockSurface)
    Q_PROPERTY(QWindow *window READ window WRITE setWindow NOTIFY windowChanged)
public:
    ExtSessionLockSurface(QObject *parent = nullptr);
    ~ExtSessionLockSurface();

    bool isInitialized() const;

    void initialize();

    QWindow *window() const;
    void setWindow(QWindow *window);

    static ExtSessionLockSurface *get(QWindow *window);

Q_SIGNALS:
    void windowChanged(QWindow *window);
    void unlockRequested();

private:
    QScopedPointer<ExtSessionLockSurfacePrivate> const d_ptr;
};

} // QtShellIntegration

} // Liri
