#include "EscapeMenuDialog.h"
#include <qlayout.h>

EscapeMenuDialog::EscapeMenuDialog(QWidget* parent) : QDialog(parent) {
    setWindowTitle("Pause");

    QPushButton* resumeButton = new QPushButton("Resume", this);
    QPushButton* saveButton = new QPushButton("Save", this);
    QPushButton* forfeitButton = new QPushButton("Forfeit", this);

    buttonStyle = "QPushButton {"
        "    background-color: #7B7B7B;"
        "    color: white;"
        "    border: 2px solid #343434;"
        "    border-radius: 8px;"
        "    padding: 4px 8px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #555555;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #3F3F3F;"
        "    color: white;"
        "}";

    resumeButton->setStyleSheet(buttonStyle);
    saveButton->setStyleSheet(buttonStyle);
    forfeitButton->setStyleSheet(buttonStyle);
    setFixedSize(150, 100);
    connect(resumeButton, &QPushButton::clicked, this, &EscapeMenuDialog::resumeGame);
    connect(saveButton, &QPushButton::clicked, this, &EscapeMenuDialog::saveGame);
    connect(forfeitButton, &QPushButton::clicked, this, &EscapeMenuDialog::forfeitGame);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(resumeButton);
    layout->addWidget(saveButton);
    layout->addWidget(forfeitButton);

    setLayout(layout);
}

void EscapeMenuDialog::resumeGame() {
    accept();
}
bool EscapeMenuDialog::isPiecePlaced(bool isPiecePlaced)
{
    isLastPiecePlaced = isPiecePlaced;
    return isLastPiecePlaced;
}
void EscapeMenuDialog::saveGame() {
    emit savedClicked();
    emit save("out_in.txt",isLastPiecePlaced);
    accept();
}

void EscapeMenuDialog::forfeitGame() {
    
    
    emit forfeitClicked();
    accept();
}