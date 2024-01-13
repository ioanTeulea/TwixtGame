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
#include <QGraphicsDropShadowEffect>

#include "EscapeMenuDialog.h"
#include"Board.h"
#include "Bridge.h"


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
   
   
    void switchColor();
    int Width;
    int Height;

private:
    qreal cellSize = 40;
    int boardSize;
    QGraphicsEllipseItem* startEllipse;
    QList<QGraphicsLineItem*> lines;
    QPushButton* nextPlayerButton = nullptr;
    QColor player1Color;
    QColor player2Color;
    QString  player1Name;
    QString  player2Name;
    QGraphicsTextItem* turnInfo, *player1TextItem,* player2TextItem;
    QList<QGraphicsEllipseItem*> circlesList;
    QColor currentColor;
    bool piecePlaced;
    int X_before = -1, Y_before = -1;
    EscapeMenuDialog* escapeMenu = new EscapeMenuDialog(qobject_cast<QWidget*>(QCoreApplication::instance()));
    bool isPointInsideAnyEllipse(const QPointF& point, QList<QGraphicsEllipseItem*>& ellipses);
    bool isPointInsideEllipse(const QPointF& point,  QGraphicsEllipseItem* ellipse);
    void applyGlowEffect(QGraphicsTextItem* textItem, int blurRadius, const QColor& glowColor, int offset);
signals:
    void circleClicked(QColor color, const uint16_t i, const uint16_t j, bool& isOk);
    void bridgeClicked(const uint16_t x1, const uint16_t y1, const uint16_t x2, const uint16_t y2, bool& isOk);
    void deleteBridgeClicked(const uint16_t x1, const uint16_t y1, const uint16_t x2, const uint16_t y2);
    bool isPiecePlaced(bool piecePlaced);

public slots:
    void setBoardSize(int newSize);
    void PlayersInfo(const std::string& player1Name, QColor color1, const std::string& player2Name, QColor color2);
    void onBoardLoaded( Board loadedBoard,int isLastPiecePlaced);
    void onMineExploded(Board board);
    void drawGameBoard();
    void saveButtonClicked();
    void randomPiece(uint16_t X, uint16_t Y);
    void gameFinished();
};

#endif // GAMESCENE_H