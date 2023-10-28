#include "Board.h"

Board::Board(int boardSize) : size(boardSize) {
    // Alocare dinamic? pentru tabla de joc
    board = new int* [size];
    for (int i = 0; i < size; ++i) {
        board[i] = new int[size];
        for (int j = 0; j < size; ++j) {
            board[i][j] = 0; // Ini?ializare cu valori implicite (0 = niciun juc?tor)
        }
    }
}

Board::~Board()
{
    for (int i = 0; i < size; ++i) {
        delete[] board[i];
    }
    delete[] board;

}

Board::Board(const Board& other)
{
    size = other.size;

    // Alocare memorie pentru matricea nou?
    board = new int* [size];
    for (int i = 0; i < size; i++) {
        board[i] = new int[size];
        for (int j = 0; j < size; j++) {
            board[i][j] = other.board[i][j];
        }
    }
}

Board& Board::operator=(const Board& other)
{
    if (this == &other) {
        // Evit?m auto-atribuirea
        return *this;
    }

    // Dealoc?m memoria pentru matricea curent?
    for (int i = 0; i < size; i++) {
        delete[] board[i];
    }
    delete[] board;

    // Copiem dimensiunea
    size = other.size;

    // Alocare memorie pentru matricea nou?
    board = new int* [size];
    for (int i = 0; i < size; i++) {
        board[i] = new int[size];
        for (int j = 0; j < size; j++) {
            board[i][j] = other.board[i][j];
        }
    }

    return *this;
}


