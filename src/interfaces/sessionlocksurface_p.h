// SPDX-FileCopyrightText: 2022-2024 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <LiriQtShellIntegration/SessionLockSurface>

namespace Liri {

namespace QtShellIntegration {

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

class SessionLockSurfacePrivate
{
public:
    SessionLockSurfacePrivate() = default;

    bool initialized = false;
    QWindow *window = nullptr;
};

} // namespace QtShellIntegration

} // namespace Liri
