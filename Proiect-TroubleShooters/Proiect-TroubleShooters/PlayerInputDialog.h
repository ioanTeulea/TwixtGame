#pragma once
#include <QDialog>
#include <QString>
#include <QLineEdit>
#include<QLabel>
#include <QPushButton>
#include <QSpinBox>

class PlayerInputDialog : public QDialog {
    Q_OBJECT

public:
    PlayerInputDialog(QWidget* parent = nullptr);

private slots:
    void validateForm();
    void focusNextLineEdit();
signals:
    void acceptedWithNames(const QString& player1Name, const QString& player2Name);

private:
    QLineEdit* m_player1NameEdit;
    QLineEdit* m_player2NameEdit;
    QSpinBox* m_boardSizeSpinBox;

    QString buttonStyle; // Variabila pentru stilul butoanelor
};