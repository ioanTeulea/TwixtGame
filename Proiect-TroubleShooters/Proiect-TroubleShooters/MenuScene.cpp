#include "MenuScene.h"
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>

MenuScene::MenuScene(QObject* parent)
{

    QGraphicsRectItem* playButton = new QGraphicsRectItem(0, 0, 100, 50);
    playButton->setPos(100, 100);
    addItem(playButton);
    QGraphicsTextItem* playText = new QGraphicsTextItem("Play", playButton);
    playText->setDefaultTextColor(Qt::blue);  // Set?m culoarea textului
    playText->setPos(playButton->rect().center().x() - playText->boundingRect().width() / 2,
        playButton->rect().center().y() - playText->boundingRect().height() / 2);
}

void MenuScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsItem* item = itemAt(event->scenePos(), QTransform());
    if (item)
    {
        // Dac? a fost ap?sat butonul de "Play"
        if (item->type() == QGraphicsRectItem::Type)
        {
            emit playClicked();
        }
    }

    QGraphicsScene::mousePressEvent(event);
}
