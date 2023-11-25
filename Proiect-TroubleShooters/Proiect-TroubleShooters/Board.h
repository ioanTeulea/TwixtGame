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
    Board(uint16_t boardSize);
    Board(const Board& other);
    Board& operator=(const Board& other);
    std::uint16_t getSize() const;
    const std::vector<std::vector<int>>& getBoard() const;
    bool isValidLocation(uint16_t x, uint16_t y) const;
    bool isOccupied(uint16_t x, uint16_t y) const;

    // Plaseaz? o pies? pe tabla de joc pentru un juc?tor dat
    bool placePiece(Player& player, uint16_t x, uint16_t y);

    // Afi?eaz? tabla de joc
    void displayBoard() const;

    // Plaseaz? o punte între piese existente
    void placeBridge(const Piece& newPiece, const std::vector<Piece>& existingPieces);

    // ?terge o punte între dou? piese
    void deleteBridge(const Piece& p1, const Piece& p2);

    // Verific? dac? exist? o punte între dou? pozi?ii pentru un juc?tor dat
    bool isBridgeBetween(const uint16_t& x1, const uint16_t& y1, const uint16_t& x2, const uint16_t& y2, Player& owner);

    // Verifica daca exista poduri care s-ar intersecta cu cel care pleaca din (x,y)
    bool availableWay(const uint16_t& x, const uint16_t& y, const uint16_t& sign, const bool& vertical, Player& owner);
};



