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

signals:
    void save(const std::string& filename);

private slots:
    void resumeGame();
    void saveGame();
    void forfeitGame();
};

#endif

