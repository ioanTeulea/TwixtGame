#include "PlayerInputDialog.h"
#include <QFormLayout>
#include <QPixmap>
PlayerInputDialog::PlayerInputDialog(QWidget* parent) : QDialog(parent) {
    setWindowTitle("Completati formularul pentru a incepe jocul:");

    // Creeaza casetele de text pentru nume
    m_player1NameEdit = new QLineEdit;
    m_player2NameEdit = new QLineEdit;
    m_boardSizeSpinBox = new QSpinBox;
    m_boardSizeSpinBox->setRange(5, 25);

    m_difficultyComboBox = new QComboBox;
    m_difficultyComboBox->addItem("Easy");
    m_difficultyComboBox->addItem("Medium");
    m_difficultyComboBox->addItem("Hard");

    m_difficultyComboBox->setItemData(0, "Plenty of pieces, no Dozer, no Mines", Qt::ToolTipRole);
    m_difficultyComboBox->setItemData(1, "Fewer pieces, Dozer enabled, no Mines", Qt::ToolTipRole);
    m_difficultyComboBox->setItemData(2, "Fewer pieces, higher chances for Dozer, Mines enabled", Qt::ToolTipRole);

    // Creeaza butoanele OK si Anulare
    QPushButton* okButton = new QPushButton("OK", this);
    QPushButton* cancelButton = new QPushButton("Anulare", this);

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

    // Aplic? stilul pentru butonul OK si cancel
    okButton->setStyleSheet(buttonStyle);
    cancelButton->setStyleSheet(buttonStyle);

    // Adauga casetele de text si butoanele la layout 
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(new QLabel("Player 1 Name:"));
    layout->addWidget(m_player1NameEdit);
    layout->addWidget(new QLabel("Player 2 Name:"));
    layout->addWidget(m_player2NameEdit);
    layout->addWidget(new QLabel("Board Size:"));
    layout->addWidget(m_boardSizeSpinBox);
    layout->addWidget(new QLabel("Difficulty:"));
    layout->addWidget(m_difficultyComboBox);
    layout->addWidget(okButton);
    layout->addWidget(cancelButton);

    setLayout(layout);


    // Conecteaza butonul OK la slot-ul custom validateForm
    connect(okButton, &QPushButton::clicked, this, &PlayerInputDialog::validateForm);

    // Conecteaza butonul Anulare la închiderea ferestrei
    connect(cancelButton, &QPushButton::clicked, this, &PlayerInputDialog::reject);

    // Conecteaza un slot pentru a trata evenimentul de ap?sare a tastei Enter
    connect(m_player1NameEdit, &QLineEdit::returnPressed, this, &PlayerInputDialog::focusNextLineEdit);
    connect(m_player2NameEdit, &QLineEdit::returnPressed, this, &PlayerInputDialog::focusNextLineEdit);


    setMinimumSize(120, 30);
}

void PlayerInputDialog::validateForm() {
    if (m_player1NameEdit->text().isEmpty() || m_player2NameEdit->text().isEmpty()) {

        return;
    }

    // Emite semnalul acceptedWithNames cu numele jucatorilor
    emit acceptedWithNames(m_player1NameEdit->text(), m_player2NameEdit->text());
    emit acceptedWithBoardSize(m_boardSizeSpinBox->value());
    emit acceptedWithDifficulty(m_difficultyComboBox->currentText());
    accept();
}
void PlayerInputDialog::focusNextLineEdit() {
    // Afl? care este obiectul care a emis semnalul ?i d? focus pe cel?lalt
    QObject* senderObject = sender();
    if (senderObject == m_player1NameEdit) {
        m_player2NameEdit->setFocus();
    }
    else if (senderObject == m_player2NameEdit) {
        m_boardSizeSpinBox->setFocus();
    }
}

 