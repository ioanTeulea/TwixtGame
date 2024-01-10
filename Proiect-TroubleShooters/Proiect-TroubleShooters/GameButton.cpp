#include "GameButton.h"
#include <QGraphicsScene>

GameButton::GameButton(const QString& text, QGraphicsScene* scene, qreal x, qreal y, qreal width, qreal height, QObject* parent)
    : QPushButton(text, nullptr)
{
    this->move(x, y);
    setFixedSize(width, height);
    scene->addWidget(this);

}

GameButton::~GameButton()
{
}
