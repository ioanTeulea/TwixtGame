#pragma once
#include "Player.h"
#include <iostream>
#include <vector>
class Board
{
    std::uint16_t size; // Dimensiunea tablei
    std::vector<std::vector<int>> board; // Vector de vector de întregi pentru reprezentarea tablei
public:
    // Constructor
    Board(int boardSize);
    Board(const Board& other);
    Board& operator=(const Board& other);
    std::uint16_t getSize() const;
    const std::vector<std::vector<int>>& getBoard() const;
    bool isValidLocation(int x, int y) const;
    bool isOccupied(int x, int y) const;

    // Plaseaz? o pies? pe tabla de joc pentru un juc?tor dat
    bool placePiece(Player& player, int x, int y);

    // Afi?eaz? tabla de joc
    void displayBoard() const;

    // Plaseaz? o punte între piese existente
    void placeBridge(const Piece& newPiece, const std::vector<Piece>& existingPieces);

    // ?terge o punte între dou? piese
    void deleteBridge(const Piece& p1, const Piece& p2);

    // Verific? dac? exist? o punte între dou? pozi?ii pentru un juc?tor dat
    bool isBridgeBetween(const int& x1, const int& y1, const int& x2, const int& y2, Player& owner);
};



