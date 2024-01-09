#include "GameScene.h"

GameScene::GameScene(QObject* parent):QGraphicsScene(parent), startEllipse(nullptr)
{
    qreal radius = cellSize / 4.0; // raza cercului
    qreal distance = 1.0 * cellSize; // distan?a între cercuri

    // Ini?ializarea dimensiunilor ?i coordonatelor scenei
    qreal sceneWidth = boardSize * distance;
    qreal sceneHeight = boardSize * distance;
    qreal xOffset = -sceneWidth / 2.0;
    qreal yOffset = -sceneHeight / 2.0;

    // Setarea scenei
    setSceneRect(xOffset, yOffset, sceneWidth, sceneHeight);

    for (qreal i = 0; i < boardSize; ++i) {
        for (qreal j = 0; j < boardSize; ++j) {
            QGraphicsEllipseItem* circle = new QGraphicsEllipseItem(i * distance + xOffset, j * distance + yOffset, radius, radius);
            circle->setPen(QPen(Qt::black));
            circle->setBrush(QBrush(Qt::gray));
            circle->setFlag(QGraphicsItem::ItemIsSelectable);
            addItem(circle);
        }
    }

    qreal lineHeight = 2.0; // Grosimea liniei
    QPen redPen(Qt::red), blackPen(Qt::black);
    redPen.setWidthF(lineHeight);
    blackPen.setWidthF(lineHeight);

    qreal middle = yOffset + distance * 0.6;
    addLine(xOffset, middle, xOffset + sceneWidth, middle, redPen);
    middle = yOffset + sceneHeight - distance * 1.3;
    addLine(xOffset, middle, xOffset + sceneWidth, middle, redPen);
    middle = xOffset + sceneWidth - distance * 1.3;
    addLine(middle, yOffset, middle, yOffset + sceneHeight, blackPen);
    middle = xOffset + distance * 0.6;
    addLine(middle, yOffset, middle, yOffset + sceneHeight, blackPen);

    lines = QList<QGraphicsLineItem*>();
}

void GameScene::showCoordinates(qreal x, qreal y)
{
    int X = static_cast<int>(x);
    int Y = static_cast<int>(y);

    qDebug() << "x= " << X << " y=: " << Y;
}

void GameScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    
        QGraphicsItem* item = itemAt(event->scenePos(), QTransform());
        if (item && item->type() == QGraphicsEllipseItem::Type)
        {
            startEllipse = qgraphicsitem_cast<QGraphicsEllipseItem*>(item);
            startEllipse->setBrush(QBrush(Qt::red));  // Face cercul rosu

            qreal centerX = event->scenePos().x();
            qreal centerY = event->scenePos().y();

            showCoordinates(centerX, centerY);
        }
   

    QGraphicsScene::mousePressEvent(event);
}

//void GameScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
//{
//    if (selectedEllipse)
//    {
//        QPointF start = selectedEllipse->rect().center();
//        QPointF end = event->scenePos();
//
//        if (!draggingLine->scene())
//        {
//            addItem(draggingLine);
//        }
//
//        draggingLine->setLine(start.x(), start.y(), end.x(), end.y());
//    }
//
//    QGraphicsScene::mouseMoveEvent(event);
//}

void GameScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    if (startEllipse)
    {
        QGraphicsItem* item = itemAt(event->scenePos(), QTransform());
        if (item && item->type() == QGraphicsEllipseItem::Type)
        {
            QGraphicsEllipseItem* endEllipse = qgraphicsitem_cast<QGraphicsEllipseItem*>(item);
            if (endEllipse != startEllipse)
            {
                endEllipse->setBrush(QBrush(Qt::red));  // Face cercul rosu
                QGraphicsLineItem* line = new QGraphicsLineItem();
                QPen pen(Qt::red, 2, Qt::SolidLine);  // Linie ro?ie, grosime 2, linie punctat?
                line->setPen(pen);
                line->setLine(startEllipse->rect().center().x(), startEllipse->rect().center().y(),
                    endEllipse->rect().center().x(), endEllipse->rect().center().y());
                addItem(line);
                lines.append(line);
            }
        }

       
        startEllipse = nullptr;
    }

    QGraphicsScene::mouseReleaseEvent(event);
}
