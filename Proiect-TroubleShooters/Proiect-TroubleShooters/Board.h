#pragma once
#include "Player.h"
#include <iostream>
class Board
{
    int size; // Dimensiunea tablei
    int** board; // Matrice de întregi pentru reprezentarea tablei
public:
    // Constructor
    Board(int boardSize);
    ~Board();
    Board(const Board& other);
    Board& operator=(const Board& other);
    const int& getSize() const;
    int** getBoard() const;
    bool isValidLocation(int x, int y, int boardSize);
    bool isOccupied(int x, int y, int** board);
    bool placePiece(const Player& player, int x, int y);
    void displayBoard();
};



