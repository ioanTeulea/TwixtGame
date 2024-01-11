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
#include <QGraphicsDropShadowEffect>

#include"Board.h"


class GameScene : public QGraphicsScene
{
    Q_OBJECT

public:
    GameScene(QObject* parent = nullptr, int initialWidth = 0, int initialHeight = 0);
    void showCoordinates(qreal x, qreal y);
    QPushButton* getNextPlayerButton() const;
    void drawGameBoard();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
   
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
    QString  player1Name;
    QString  player2Name;
    QGraphicsTextItem* turnInfo;
    QColor currentColor;
    bool piecePlaced;
signals:
    void circleClicked(QColor color, const uint16_t i, const uint16_t j, bool& isOk);
    void bridgeClicked(const uint16_t x1, const uint16_t y1, const uint16_t x2, const uint16_t y2, bool& isOk);
    void deleteBridgeClicked(const uint16_t x1, const uint16_t y1, const uint16_t x2, const uint16_t y2);
public slots:
    void setBoardSize(int newSize);
    void PlayersInfo(const std::string& player1Name, QColor color1, const std::string& player2Name, QColor color2);
    void onBoardLoaded(const Board& loadedBoard);
};

#endif // GAMESCENE_H