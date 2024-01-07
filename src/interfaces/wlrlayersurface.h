// SPDX-FileCopyrightText: 2021-2024 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QWindow>
#include <QtQmlIntegration>

#include <LiriQtShellIntegration/liriqtshellintegrationglobal.h>

namespace Liri {

namespace QtShellIntegration {

class WlrLayerSurfacePrivate;

class LIRIQTSHELLINTEGRATION_EXPORT WlrLayerSurface : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_DECLARE_PRIVATE(WlrLayerSurface)
    Q_PROPERTY(QWindow *window READ window WRITE setWindow NOTIFY windowChanged)
    Q_PROPERTY(Liri::QtShellIntegration::WlrLayerSurface::Layer layer READ layer WRITE setLayer NOTIFY layerChanged)
    Q_PROPERTY(QString role READ role WRITE setRole NOTIFY roleChanged)
    Q_PROPERTY(Liri::QtShellIntegration::WlrLayerSurface::Anchors anchors READ anchors WRITE setAnchors NOTIFY anchorsChanged)
    Q_PROPERTY(qint32 exclusiveZone READ exclusiveZone WRITE setExclusiveZone NOTIFY exclusiveZoneChanged)
    Q_PROPERTY(QMargins margins READ margins NOTIFY marginsChanged)
    Q_PROPERTY(qint32 leftMargin READ leftMargin WRITE setLeftMargin NOTIFY leftMarginChanged)
    Q_PROPERTY(qint32 rightMargin READ rightMargin WRITE setRightMargin NOTIFY rightMarginChanged)
    Q_PROPERTY(qint32 topMargin READ topMargin WRITE setTopMargin NOTIFY topMarginChanged)
    Q_PROPERTY(qint32 bottomMargin READ bottomMargin WRITE setBottomMargin NOTIFY bottomMarginChanged)
    Q_PROPERTY(Liri::QtShellIntegration::WlrLayerSurface::KeyboardInteractivity keyboardInteractivity READ keyboardInteractivity WRITE setKeyboardInteractivity NOTIFY keyboardInteractivityChanged)
public:
    enum Layer {
        BackgroundLayer = 0,
        BottomLayer = 1,
        TopLayer = 2,
        OverlayLayer = 3
    };
    Q_ENUM(Layer)

    enum Anchor {
        TopAnchor = 1,
        BottomAnchor = 2,
        LeftAnchor = 4,
        RightAnchor = 8
    };
    Q_ENUM(Anchor)
    Q_DECLARE_FLAGS(Anchors, Anchor)
    Q_FLAG(Anchors)

    enum KeyboardInteractivity {
        NoKeyboardInteractivity = 0,
        ExclusiveKeyboardInteractivity = 1,
        OnDemandKeyboardInteractivity
    };
    Q_ENUM(KeyboardInteractivity)

    ~WlrLayerSurface();

    bool isInitialized() const;

    QWindow *window() const;
    void setWindow(QWindow *window);

    WlrLayerSurface::Layer layer() const;
    void setLayer(WlrLayerSurface::Layer layer);

    QString role() const;
    void setRole(const QString &role);

    WlrLayerSurface::Anchors anchors() const;
    void setAnchors(WlrLayerSurface::Anchors anchors);

    qint32 exclusiveZone() const;
    void setExclusiveZone(qint32 zone);

    QMargins margins() const;

    qint32 leftMargin() const;
    void setLeftMargin(qint32 margin);

    qint32 rightMargin() const;
    void setRightMargin(qint32 margin);

    qint32 topMargin() const;
    void setTopMargin(qint32 margin);

    qint32 bottomMargin() const;
    void setBottomMargin(qint32 margin);

    WlrLayerSurface::KeyboardInteractivity keyboardInteractivity() const;
    void setKeyboardInteractivity(WlrLayerSurface::KeyboardInteractivity keyboardInteractivity);

    void initialize();

    void setLayerEnabled(bool enabled);

    static WlrLayerSurface *get(QWindow *window);

    static WlrLayerSurface *qmlAttachedProperties(QObject *object);

Q_SIGNALS:
    void windowChanged(QWindow *window);
    void layerChanged(WlrLayerSurface::Layer layer);
    void roleChanged(const QString &role);
    void anchorsChanged(WlrLayerSurface::Anchors anchors);
    void exclusiveZoneChanged(qint32 exclusiveZone);
    void marginsChanged(const QMargins &margins);
    void leftMarginChanged(qint32 margin);
    void rightMarginChanged(qint32 margin);
    void topMarginChanged(qint32 margin);
    void bottomMarginChanged(qint32 margin);
    void keyboardInteractivityChanged(Liri::QtShellIntegration::WlrLayerSurface::KeyboardInteractivity keyboardInteractivity);

protected:
    explicit WlrLayerSurface(QObject *parent = nullptr);

private:
    QScopedPointer<WlrLayerSurfacePrivate> const d_ptr;
};

} // QtShellIntegration

} // Liri

Q_DECLARE_OPERATORS_FOR_FLAGS(Liri::QtShellIntegration::WlrLayerSurface::Anchors)