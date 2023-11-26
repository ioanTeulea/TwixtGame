#pragma once
#include <QDialog>
#include <QString>
#include <QLineEdit>
#include<QLabel>
#include <QPushButton>

class PlayerInputDialog : public QDialog {
    Q_OBJECT

public:
    PlayerInputDialog(QWidget* parent = nullptr);

private slots:
    void validateForm();

signals:
    void acceptedWithNames(const QString& player1Name, const QString& player2Name);

private:
    QLineEdit* player1Edit;
    QLineEdit* player2Edit;
};


