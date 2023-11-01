#pragma once
#include "Player.h"
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
    bool isValidLocation(int x, int y, int boardSize);
    bool isOccupied(int x, int y,const int** board);
    bool placePiece(const Player& player, int x, int y);
};

