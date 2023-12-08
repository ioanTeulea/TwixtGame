#pragma once
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class CustomGraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    CustomGraphicsScene(QObject* parent = nullptr);
    void showCoordinates(qreal x, qreal y);

protected:
    // void drawBackground(QPainter* painter, const QRectF& rect) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
    qreal cellSize = 50;
    qint32 boardSize = 10;
};