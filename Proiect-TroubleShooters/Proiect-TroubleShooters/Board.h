#pragma once
#include "Player.h"
#include <vector>
#include <unordered_set>
#include <random>
#include <tuple>
class Board
{
    std::uint16_t size; // Dimensiunea tablei
    std::vector<Bridge> bridges;
    std::mt19937 engine;
    std::vector<std::tuple<uint16_t, uint16_t, uint16_t>> mines; // Vector de mine care detine coordonatele si tipul minei

public:
    std::vector<std::vector<Piece>> board; // Vector de vector de întregi pentru reprezentarea tablei
    std::pair<uint16_t, uint16_t> dozer;
    Board(uint16_t boardSize = 0);
    Board(const Board& other);
    Board& operator=(const Board& other);

    // Move constructor
    Board(Board&& other) noexcept;
    // Move assignment operator
    Board& operator=(Board&& other) noexcept;

    std::uint16_t getSize() const;
    void setSize(std::uint16_t newSize);

    const std::vector<std::vector<Piece>>& getBoard() const;
    std::vector<Bridge>& getBridges();
    

    Piece& operator()(uint16_t x, uint16_t y); // Operatorul () pentru accesul la piese
    const Piece& operator()(uint16_t x, uint16_t y) const;
    void deleteBridges();

    bool isValidLocation(uint16_t x, uint16_t y) const;
    bool isOccupied(uint16_t x, uint16_t y) const;

    bool placePiece(const Piece& newPiece);

    bool placeBridge(Piece& piece1, Piece& piece2);
    void deleteBridge(const Piece& p1, const Piece& p2);
    bool isBridgeBetween(const int16_t& x1, const int16_t& y1, const int16_t& x2, const int16_t& y2);
    bool availableWay(const int16_t& x, const int16_t& y, const int16_t& sign, const bool& vertical);
    bool canPlaceBridge(const Piece& piece1, const Piece& piece2);
    std::pair<std::uint16_t, std::uint16_t> dozerTurn(const std::uint16_t& percentage);
    uint16_t delete_DozerBridges(Piece random_piece);
    std::pair<std::uint16_t, std::uint16_t> generateRandomPiece();
    void deletePiece(Piece chosen_piece);
    void generateMines(const uint16_t& mines_nr);
    void explode(const std::tuple<uint16_t, uint16_t, uint16_t>& mine);
    void reset();
    friend std::ostream& operator<<(std::ostream& out, const Board& B);
    friend std::istream& operator>>(std::istream& in, Board& B);
};