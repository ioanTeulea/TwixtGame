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
    Board(uint16_t boardSize=0);
    Board(const Board& other);
    Board& operator=(const Board& other);
    // Move constructor
    Board(Board&& other) noexcept;

    // Move assignment operator
    Board& operator=(Board&& other) noexcept;
    std::uint16_t getSize() const;
    const std::vector<std::vector<int>>& getBoard() const;
   
    bool isValidLocation(uint16_t x, uint16_t y) const;
   
    bool isOccupied(uint16_t x, uint16_t y) const;

   
    bool placePiece(Player& player, uint16_t x, uint16_t y);

    
    void displayBoard() const;

   
    void placeBridge(Piece& newPiece, std::vector<Piece>& existingPieces);

   
    void deleteBridge(const Piece& p1, const Piece& p2);

    
    bool isBridgeBetween(const uint16_t& x1, const uint16_t& y1, const uint16_t& x2, const uint16_t& y2, Player& owner);

   
    bool availableWay(const uint16_t& x, const uint16_t& y, const uint16_t& sign, const bool& vertical, Player& owner);

    
    bool canPlaceBridge(const Piece& piece1, const Piece& piece2);

    void reset();
};



