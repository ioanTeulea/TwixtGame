#pragma once
#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QMouseEvent>

#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <qcoreapplication.h>

#include "EscapeMenuDialog.h"


class GameScene : public QGraphicsScene
{
    Q_OBJECT

public:
    GameScene(QObject* parent = nullptr, int initialWidth = 0, int initialHeight = 0);
    void showCoordinates(qreal x, qreal y);
    QPushButton* getNextPlayerButton() const;
    EscapeMenuDialog* getEscapeMenu() const;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void drawGameBoard();
    void switchColor();
    int Width;
    int Height;

private:
    qreal cellSize = 50;
    int boardSize;
    QGraphicsEllipseItem* startEllipse;
    QList<QGraphicsLineItem*> lines;
    QPushButton* nextPlayerButton = nullptr;
    QColor player1Color;
    QColor player2Color;
    QColor currentColor;
    bool piecePlaced;
    EscapeMenuDialog* escapeMenu = new EscapeMenuDialog(qobject_cast<QWidget*>(QCoreApplication::instance()));
signals:
    void circleClicked(QColor color, const uint16_t i, const uint16_t j, bool& isOk);
    void bridgeClicked(const uint16_t x1, const uint16_t y1, const uint16_t x2, const uint16_t y2, bool& isOk);
    void deleteBridgeClicked(const uint16_t x1, const uint16_t y1, const uint16_t x2, const uint16_t y2);
public slots:
    void setBoardSize(int newSize);
    void PlayerColors(QColor color1, QColor color2);
};

#endif // GAMESCENE_H