
#ifndef MENUSCENE_H
#define MENUSCENE_H

#include <QGraphicsScene>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include "ClickableButton.h"

class MenuScene : public QGraphicsScene
{
    Q_OBJECT

public:
    MenuScene(QObject* parent = nullptr);

signals:
    void playClicked();

private slots:
    void loadClicked();
    void exitClicked();
    void settingsClicked();
private:
    void addButton(const QString& text, qreal yPos, const char* signal, const QPixmap& buttonImage);
    void addBackground();
    void resizeBackground(int width, int height);
    QPixmap originalBackgroundImage;
    QGraphicsPixmapItem* backgroundItem;
};

#endif // MENUSCENE_H
