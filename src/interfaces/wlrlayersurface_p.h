// SPDX-FileCopyrightText: 2021-2024 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <LiriQtShellIntegration/WlrLayerSurface>

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Liri API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

namespace Liri {

namespace QtShellIntegration {

class WlrLayerSurfacePrivate
{
public:
    WlrLayerSurfacePrivate() = default;

    bool initialized = false;
    bool setLayerEnabled = false;
    QWindow *window = nullptr;
    WlrLayerSurface::Layer layer = WlrLayerSurface::TopLayer;
    QString role = QStringLiteral("unknown");
    WlrLayerSurface::Anchors anchors;
    qint32 exclusiveZone = 0;
    QMargins margins;
    WlrLayerSurface::KeyboardInteractivity keyboardInteractivity = WlrLayerSurface::ExclusiveKeyboardInteractivity;
};

} // namespace QtShellIntegration

} // namespace Liri
