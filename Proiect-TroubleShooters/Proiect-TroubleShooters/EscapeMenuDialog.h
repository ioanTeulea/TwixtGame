#pragma once
#ifndef ESCAPEMENUDIALOG_H
#define ESCAPEMENUDIALOG_H

#include <QDialog>
#include <QPushButton>

class EscapeMenuDialog : public QDialog {
    Q_OBJECT

public:
    EscapeMenuDialog(QWidget* parent = nullptr);

private:
    QString buttonStyle;
    bool isLastPiecePlaced;
signals:
    void save(const std::string& filename,bool isPiecePlaced);
    void savedClicked();
    void forfeitClicked();
private slots:
    void resumeGame();
    void saveGame();
    void forfeitGame();
public slots:
    bool isPiecePlaced(bool isPiecePlaced);
};

#endif

