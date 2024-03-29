// SPDX-FileCopyrightText: 2021-2024 Pier Luigi Fiorini <pierluigi.fiorini@gmail.com>
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QWindow>
#include <QtQmlIntegration>

#include <LiriQtShellIntegration/liriqtshellintegrationglobal.h>

namespace Liri {

namespace QtShellIntegration {

class LayerSurfacePrivate;

class LIRIQTSHELLINTEGRATION_EXPORT LayerSurface : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("Cannot instantiate LayerSurface")
    QML_ATTACHED(LayerSurface)
    Q_DECLARE_PRIVATE(LayerSurface)
    Q_PROPERTY(QWindow *window READ window CONSTANT)
    Q_PROPERTY(Liri::QtShellIntegration::LayerSurface::Layer layer READ layer WRITE setLayer NOTIFY layerChanged)
    Q_PROPERTY(QString scope READ scope WRITE setScope NOTIFY scopeChanged)
    Q_PROPERTY(Liri::QtShellIntegration::LayerSurface::Anchors anchors READ anchors WRITE setAnchors NOTIFY anchorsChanged)
    Q_PROPERTY(qint32 exclusiveZone READ exclusiveZone WRITE setExclusiveZone NOTIFY exclusiveZoneChanged)
    Q_PROPERTY(QMargins margins READ margins NOTIFY marginsChanged)
    Q_PROPERTY(qint32 leftMargin READ leftMargin WRITE setLeftMargin NOTIFY leftMarginChanged)
    Q_PROPERTY(qint32 rightMargin READ rightMargin WRITE setRightMargin NOTIFY rightMarginChanged)
    Q_PROPERTY(qint32 topMargin READ topMargin WRITE setTopMargin NOTIFY topMarginChanged)
    Q_PROPERTY(qint32 bottomMargin READ bottomMargin WRITE setBottomMargin NOTIFY bottomMarginChanged)
    Q_PROPERTY(Liri::QtShellIntegration::LayerSurface::KeyboardInteractivity keyboardInteractivity READ keyboardInteractivity WRITE setKeyboardInteractivity NOTIFY keyboardInteractivityChanged)
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

    ~LayerSurface();

    QWindow *window() const;

    LayerSurface::Layer layer() const;
    void setLayer(LayerSurface::Layer layer);

    QString scope() const;
    void setScope(const QString &scope);

    LayerSurface::Anchors anchors() const;
    void setAnchors(LayerSurface::Anchors anchors);

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

    LayerSurface::KeyboardInteractivity keyboardInteractivity() const;
    void setKeyboardInteractivity(LayerSurface::KeyboardInteractivity keyboardInteractivity);

    void setLayerEnabled(bool enabled);

    static LayerSurface *get(QWindow *window);

    static LayerSurface *qmlAttachedProperties(QObject *object);

Q_SIGNALS:
    void layerChanged(LayerSurface::Layer layer);
    void scopeChanged(const QString &scope);
    void anchorsChanged(LayerSurface::Anchors anchors);
    void exclusiveZoneChanged(qint32 exclusiveZone);
    void marginsChanged(const QMargins &margins);
    void leftMarginChanged(qint32 margin);
    void rightMarginChanged(qint32 margin);
    void topMarginChanged(qint32 margin);
    void bottomMarginChanged(qint32 margin);
    void keyboardInteractivityChanged(Liri::QtShellIntegration::LayerSurface::KeyboardInteractivity keyboardInteractivity);

protected:
    explicit LayerSurface(QWindow *window, QObject *parent = nullptr);

private:
    QScopedPointer<LayerSurfacePrivate> const d_ptr;
};

} // QtShellIntegration

} // Liri

Q_DECLARE_OPERATORS_FOR_FLAGS(Liri::QtShellIntegration::LayerSurface::Anchors)