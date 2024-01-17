// SPDX-FileCopyrightText: 2024 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <QQmlExtensionPlugin>
#include <QtQml>

#include "../sessionlocksurface.h"
#include "../layersurface.h"

QML_DECLARE_TYPEINFO(Liri::QtShellIntegration::LayerSurface, QML_HAS_ATTACHED_PROPERTIES)

class Plugin : public QQmlExtensionPlugin
{
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface/1.0")
    Q_OBJECT
public:
    void registerTypes(const char *uri) override {
        Q_ASSERT(QLatin1String(uri) == QLatin1String("Liri.QtShellIntegration"));

        qmlRegisterType<Liri::QtShellIntegration::SessionLockSurface>(uri, 1, 0, "SessionLockSurface");
        qmlRegisterType<Liri::QtShellIntegration::LayerSurface>(uri, 1, 0, "LayerSurface");
    }
};

#include "qtshellintegrationplugin.moc"
