#pragma once

#include <QPushButton>
#include <QGraphicsScene>

class GameButton : public QPushButton {
    Q_OBJECT

public:
    GameButton(const QString& text, QGraphicsScene* scene, qreal x, qreal y, qreal width, qreal height, QObject* parent = nullptr);
    ~GameButton();
};