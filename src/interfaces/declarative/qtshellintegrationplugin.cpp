// SPDX-FileCopyrightText: 2024 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <QQmlExtensionPlugin>
#include <QtQml>

#include "../extsessionlocksurface.h"
#include "../wlrlayersurface.h"

QML_DECLARE_TYPEINFO(Liri::QtShellIntegration::WlrLayerSurface, QML_HAS_ATTACHED_PROPERTIES)

class Plugin : public QQmlExtensionPlugin
{
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface/1.0")
    Q_OBJECT
public:
    void registerTypes(const char *uri) override {
        Q_ASSERT(QLatin1String(uri) == QLatin1String("Liri.QtShellIntegration"));

        qmlRegisterType<Liri::QtShellIntegration::ExtSessionLockSurface>(uri, 1, 0, "ExtSessionLockSurface");
        qmlRegisterType<Liri::QtShellIntegration::WlrLayerSurface>(uri, 1, 0, "WlrLayerSurface");
    }
};

#include "qtshellintegrationplugin.moc"
