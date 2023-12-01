#pragma once
#include "Player.h"
#include <iostream>
#include <vector>
#include<unordered_set>
class Board
{
    std::uint16_t size; // Dimensiunea tablei
    std::vector<std::vector<Piece>> board; // Vector de vector de întregi pentru reprezentarea tablei
    std::vector<Piece> pieces;
    std::vector<Bridge> bridges;
public:
    Board(uint16_t boardSize = 0);
    Board(const Board& other);
    Board& operator=(const Board& other);

    // Move constructor
    Board(Board&& other) noexcept;
    // Move assignment operator
    Board& operator=(Board&& other) noexcept;

    std::uint16_t getSize() const;
    const std::vector<std::vector<Piece>>& getBoard() const;
    std::vector<Piece>& getPieces();
    std::vector<Bridge>& getBridges();


    const Piece& operator()(uint16_t x, uint16_t y) const; // Operatorul () pentru accesul la piese


    void deletePieces();
    void deleteBridges();

    bool isValidLocation(uint16_t x, uint16_t y) const;
    bool isOccupied(uint16_t x, uint16_t y) const;

    bool placePiece(const Piece& newPiece);

    void displayBoard() const;
    bool placeBridge(const Piece& piece1,const Piece& piece2);
    void deleteBridge(const Piece& p1, const Piece& p2);
    bool isBridgeBetween(const uint16_t& x1, const uint16_t& y1, const uint16_t& x2, const uint16_t& y2);
    bool availableWay(const uint16_t& x, const uint16_t& y, const uint16_t& sign, const bool& vertical);
    bool canPlaceBridge(const Piece& piece1, const Piece& piece2);
    void reset();
};



