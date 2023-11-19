#pragma once
#include "Player.h"
#include <iostream>
#include <vector>
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
    bool placePiece(Player& player, int x, int y);
    void displayBoard();
    void placeBridge(Piece newPiece, const std::vector<Piece>& existingPieces);
    bool isBridgeBetween(const int& x1, const int& y1, const int& x2, const int& y2, Player& owner);
    void deleteBridge(Piece p1,Piece p2);
};



