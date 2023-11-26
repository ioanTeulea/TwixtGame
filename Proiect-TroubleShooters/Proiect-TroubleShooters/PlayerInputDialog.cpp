#include "PlayerInputDialog.h"
#include <QFormLayout>

PlayerInputDialog::PlayerInputDialog(QWidget* parent) : QDialog(parent) {
    setWindowTitle("Introduceti numele jucatorilor:");

    // Creeaza casetele de text pentru nume
    player1Edit = new QLineEdit(this);
    player2Edit = new QLineEdit(this);

    // Creeaza butoanele OK si Anulare
    QPushButton* okButton = new QPushButton("OK", this);
    QPushButton* cancelButton = new QPushButton("Anulare", this);

    // Adauga casetele de text si butoanele la layout
    QFormLayout* formLayout = new QFormLayout(this);
    formLayout->addRow(new QLabel("Nume jucator 1:"), player1Edit);
    formLayout->addRow(new QLabel("Nume jucator 2:"), player2Edit);
    formLayout->addWidget(okButton);
    formLayout->addWidget(cancelButton);

    // Conecteaza butonul OK la slot-ul custom validateForm
    connect(okButton, &QPushButton::clicked, this, &PlayerInputDialog::validateForm);

    // Conecteaza butonul Anulare la închiderea ferestrei
    connect(cancelButton, &QPushButton::clicked, this, &PlayerInputDialog::reject);

    setMinimumSize(120, 30);
}

void PlayerInputDialog::validateForm() {
    if (!player1Edit->text().isEmpty() && !player2Edit->text().isEmpty()) {
        // Emite semnalul acceptedWithNames cu numele jucatorilor
        emit acceptedWithNames(player1Edit->text(), player2Edit->text());
        accept();
    }
}

