#include "MyWindow.h"

MyWindow::MyWindow(QWidget* parent) : QMainWindow(parent) {
    // Ini?ializarea ferestrei aici
    setWindowTitle("Fereastra Mea");
    resize(400, 300);
}

MyWindow::~MyWindow() {
    // Distrugerea resurselor aici, dac? este cazul
}
