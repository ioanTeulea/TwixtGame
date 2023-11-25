#pragma once

#include <QMainWindow>
#include <QVector>
#include <QPoint>
#include<iostream>

class MyWindow : public QWidget {
    Q_OBJECT

public:
    MyWindow(QWidget* parent = nullptr);
    ~MyWindow();
    int boardSize = 24;
    int cellSize = 20;
protected:
    void paintEvent(QPaintEvent* event) override;


    //public slots:
};




