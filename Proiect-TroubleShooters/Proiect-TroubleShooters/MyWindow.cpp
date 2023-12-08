#include "MyWindow.h"
#include <QPainter>
#include <QMouseEvent>

#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>



CustomGraphicsScene::CustomGraphicsScene(QObject* parent) : QGraphicsScene(parent)
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

}


void CustomGraphicsScene::showCoordinates(qreal x, qreal y)
{
    int X = static_cast<int>(x);
    int Y = static_cast<int>(y);

    qDebug() << "x= " << X << " y=: " << Y;
}

void CustomGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    // Tratarea evenimentului de click pe un cerc
    QGraphicsItem* item = itemAt(event->scenePos(), QTransform());
    if (item)
    {
        qDebug() << "Tipul obiectului: " << item->type();

        if (item->type() == QGraphicsEllipseItem::Type)
        {
            // Schimbare culoare cerc
            QGraphicsEllipseItem* ellipseItem = qgraphicsitem_cast<QGraphicsEllipseItem*>(item);
            if (ellipseItem)
            {
                ellipseItem->setBrush(QBrush(Qt::red)); // Schimba?i culoarea la cea dorit?
            }

            qreal centerX = event->scenePos().x();
            qreal centerY = event->scenePos().y();

            // Afi?a?i coordonatele cercului ap?sat
            showCoordinates(centerX, centerY);
        }
    }
    else
    {
        qDebug() << "Nu s-a gasit niciun cerc la pozitia data.";
    }

    QGraphicsScene::mousePressEvent(event);
}