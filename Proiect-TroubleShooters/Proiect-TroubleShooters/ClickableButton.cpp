#include "ClickableButton.h"
#include <QDebug>

ClickableButton::ClickableButton(const QPixmap& pixmap, qreal xPos, qreal yPos, QObject* parent)
    : QObject(parent), QGraphicsPixmapItem(pixmap)
{
    setPos(xPos, yPos);
}

void ClickableButton::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    qDebug() << "Button clicked!";
    emit clicked(); // Emite semnalul clicked()
}

