
#ifndef MENUSCENE_H
#define MENUSCENE_H

#include <QGraphicsScene>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsProxyWidget>
#include "GameButton.h"


class MenuScene : public QGraphicsScene
{
    Q_OBJECT

public:
    MenuScene(QObject* parent = nullptr, int initialWidth = 0, int initialHeight = 0);
    QPushButton* getPlayButton() const;
    QPushButton* getloadButton() const;
signals:
    void playClicked();
    void loadClicked();
    void exitClicked();
    void settingsClicked();
    void loadGame();
private slots:
    void onPlayClicked();
    void onLoadClicked();
    void onExitClicked();
private:
    QPushButton* createButton(const QString& text, qreal buttonWidth, qreal buttonHeight, qreal buttonX, qreal buttonY);
    void addBackground(int Width, int Height);
    void resizeBackground(int width, int height);
    QPixmap originalBackgroundImage;
    QGraphicsPixmapItem* backgroundItem;
    QPushButton* playButton;
    QPushButton* loadButton;
    QPushButton* exitButton;
    int Width;
    int Height;
};

#endif // MENUSCENE_H
