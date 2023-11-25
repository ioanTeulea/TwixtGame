#include "MyWindow.h"
#include <QPainter>
#include <QMouseEvent>

MyWindow::MyWindow(QWidget* parent) : QWidget(parent) {
    // Ini?ializeaz? dimensiunile tablei
    boardSize = 24;
    cellSize = 20;  // M?rimea fiec?rei celule în pixeli
    setFixedSize(24 * cellSize, 24 * cellSize);
}
MyWindow::~MyWindow() {
    // Destructorul clasei
}

void MyWindow::paintEvent(QPaintEvent* event) {
    QPainter painter(this);

    painter.setPen(Qt::red);
    // Deseneaz? liniile orizontale ?i verticale
    painter.drawLine(0, cellSize, boardSize * cellSize, cellSize); // Linia între linia 0 ?i 1
    painter.drawLine(0, (boardSize - 1) * cellSize, boardSize * cellSize, (boardSize - 1) * cellSize); // Linia între penultima ?i ultima linie

    painter.setPen(Qt::black);
    // Deseneaz? liniile suplimentare între coloana 0 ?i 1 ?i între penultima ?i ultima coloan?
    painter.drawLine(cellSize, 0, cellSize, boardSize * cellSize); // Linia între coloana 0 ?i 1
    painter.drawLine((boardSize - 1) * cellSize, 0, (boardSize - 1) * cellSize, boardSize * cellSize); // Linia între penultima ?i ultima coloan?

    // Deseneaz? punctele
    painter.setPen(Qt::NoPen);  // Elimin? conturul punctelor
    painter.setBrush(Qt::gray);  // Seteaz? culoarea de umplere a punctelor
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            painter.drawEllipse(i * cellSize + cellSize / 4, j * cellSize + cellSize / 4, cellSize / 2, cellSize / 2);
        }
    }
}

