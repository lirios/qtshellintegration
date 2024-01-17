// SPDX-FileCopyrightText: 2024 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <QQmlExtensionPlugin>
#include <QtQml>

#include "../layersurface.h"
#include "../sessionlocksurface.h"

QML_DECLARE_TYPEINFO(Liri::QtShellIntegration::LayerSurface, QML_HAS_ATTACHED_PROPERTIES)
QML_DECLARE_TYPEINFO(Liri::QtShellIntegration::SessionLockSurface, QML_HAS_ATTACHED_PROPERTIES)

class Plugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)
public:
    void registerTypes(const char *uri) override {
        Q_ASSERT(QLatin1String(uri) == QLatin1String("Liri.QtShellIntegration"));

        qmlRegisterType<Liri::QtShellIntegration::LayerSurface>(uri, 1, 0, "LayerSurface");
        qmlRegisterType<Liri::QtShellIntegration::SessionLockSurface>(uri, 1, 0, "SessionLockSurface");
    }
};

#include "qtshellintegrationplugin.moc"
