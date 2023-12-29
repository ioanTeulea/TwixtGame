#include "MenuScene.h"
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include<QPushButton>
// Defineste dimensiunile initiale
#define INITIAL_WIDTH 800
#define INITIAL_HEIGHT 600
#define BUTTON_STYLE "QPushButton { \
    background-color: #7B7B7B; \
    color: white; \
    border: 2px solid #343434; \
    border-radius: 8px; \
    padding: 4px 8px; \
} \
QPushButton:hover { \
    background-color: #555555; \
} \
QPushButton:pressed { \
    background-color: #3F3F3F; \
    color: white; \
}"
MenuScene::MenuScene(QObject* parent) : QGraphicsScene(parent)
{
    // Adaug? imaginea de fundal
    addBackground();
    // Adaug? butoanele
    addButton("Play", 100, SLOT(playClicked()), QPixmap("../assets/Play.png"));
    // addButton("Load", 200, SLOT(loadClicked()));
     //addButton("Exit", 300, SLOT(exitClicked()));
     //addButton("Settings", 400, SLOT(settingsClicked()));
}

void MenuScene::settingsClicked()
{
    // Implementare pentru settingsClicked

}

void MenuScene::loadClicked()
{
    // Implementare pentru loadClicked

}

void MenuScene::exitClicked()
{
    // Implementare pentru exitClicked

}
void MenuScene::addButton(const QString& text, qreal yPos, const char* signal, const QPixmap& buttonImage)
{
    ClickableButton* button = new ClickableButton(buttonImage.scaled(50, 50), 0, 0);
    button->setPos(50, yPos);


    QGraphicsTextItem* buttonText = new QGraphicsTextItem(text, button);
    buttonText->setDefaultTextColor(Qt::white);
    buttonText->setPos(button->boundingRect().center().x() - buttonText->boundingRect().width() / 2,
        button->boundingRect().center().y() - buttonText->boundingRect().height() / 2);

    addItem(button);

    if (strcmp(signal, SLOT(playClicked())) == 0)
    {
        connect(button, &ClickableButton::clicked, this, &MenuScene::playClicked);
    }
}

void MenuScene::resizeBackground(int width, int height)
{
    if (backgroundItem) {
        // Redimensioneaz? imaginea pentru a se potrivi cu noile dimensiuni
        QPixmap resizedImage = originalBackgroundImage.scaled(width, height);

        // Afi?eaz? dimensiunile redimensionate ale imaginii
        qDebug() << "Dimensiuni redimensionate:" << resizedImage.width() << "x" << resizedImage.height();

        // Seteaz? noua imagine redimensionat? la obiectul QGraphicsPixmapItem
        backgroundItem->setPixmap(resizedImage);
    }
}

void MenuScene::addBackground()
{
    originalBackgroundImage.load("../assets/hatz.png");
    // Creaz? un obiect QGraphicsPixmapItem cu imaginea de fundal
    backgroundItem = new QGraphicsPixmapItem(originalBackgroundImage);

    // Seteaz? pozi?ia pentru a acoperi întreaga scen?
    backgroundItem->setPos(0, 0);
    resizeBackground(INITIAL_WIDTH, INITIAL_HEIGHT);
    // Adaug? imaginea de fundal la scen?
    addItem(backgroundItem);
}
