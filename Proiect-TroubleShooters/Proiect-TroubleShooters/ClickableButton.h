#ifndef CLICKABLEBUTTON_H
#define CLICKABLEBUTTON_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsSceneMouseEvent>

class ClickableButton : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    ClickableButton(const QPixmap& pixmap, qreal xPos, qreal yPos, QObject* parent = nullptr);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

signals:
    void clicked();
};

#endif // CLICKABLEBUTTON_H

