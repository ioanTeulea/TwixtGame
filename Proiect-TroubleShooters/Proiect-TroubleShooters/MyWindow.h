#pragma once

#include <QMainWindow>

class MyWindow : public QMainWindow {
    Q_OBJECT

public:
    MyWindow(QWidget* parent = nullptr);
    ~MyWindow();
};



