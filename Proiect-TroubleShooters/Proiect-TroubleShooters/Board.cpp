#include "Board.h"

// Constructor
Board::Board(uint16_t boardSize) : size(boardSize), board(boardSize, std::vector<int>(boardSize, 0)) {}

// Copy constructor
Board::Board(const Board& other) : size(other.size), board(other.board) {}

// Copy assignment operator
Board& Board::operator=(const Board& other) {
    if (this != &other) {
        size = other.size;
        board = other.board;
    }
    return *this;
}

// Getter pentru dimensiune
uint16_t Board::getSize() const {
    return size;
}

// Getter pentru tabla de joc
const std::vector<std::vector<int>>& Board::getBoard() const {
    return board;
}

bool Board::isValidLocation(uint16_t x, uint16_t y) const
{
    if ((x == size - 1 || x == 0) && (y == size - 1 || y == 0))
        return false;
    return x >= 0 && x <= size - 1 && y>=0 && y <= size - 1;
}

bool Board::isOccupied(uint16_t x, uint16_t y) const {
    return board[x][y] != 0;
}

void Board::displayBoard() const {
    for (uint16_t row = 0; row < size; row++) {
        if (row == 0 || row == size - 1) {
            std::cout << "  ";
        }
        for (uint16_t col = 0; col < size; col++) {
            if (!((row == size - 1 || row == 0) && (col == size - 1 || col == 0))) {
                if (board[row][col] == static_cast<int>(Color::Red)) {
                    std::cout << "R ";
                }
                else if (board[row][col] == static_cast<int>(Color::Black)) {
                    std::cout << "B ";
                }
                else {
                    std::cout << "O ";
                }
            }
        }
        std::cout << '\n';
    }
}

void Board::placeBridge(const Piece& newPiece, const std::vector<Piece>& existingPieces) {
    for (const Piece& existingPiece : existingPieces) 
    {
        if ((abs(newPiece.getX() - existingPiece.getX()) == 1 && abs(newPiece.getY() - existingPiece.getY()) == 2) ||
            (abs(newPiece.getX() - existingPiece.getX()) == 2 && abs(newPiece.getY() - existingPiece.getY()) == 1)) 
        {
            Bridge newBridge(existingPiece,newPiece);
            newPiece.getOwner()->addBridge(newBridge);
        }
    }
}

void Board::deleteBridge(const Piece& p1, const Piece& p2)
{
    if (p1.getOwner() != p2.getOwner())
        return;
    else
    {
        for (auto it = p1.getOwner()->getBridges().begin(); it != p1.getOwner()->getBridges().end(); ++it) {
            if ((it->getPiece1()==p1 && it->getPiece2()==p2) ||
                (it->getPiece2() == p2 && it->getPiece1() == p1) ){
                p1.getOwner()->getBridges().erase(it);
                break;
            }
        }
    }
}

bool Board::placePiece(Player& player, uint16_t x, uint16_t y)
{
    if (isValidLocation(x, y) && !isOccupied(x, y))
    {
      board[x][y] = player.getColor();
      Piece newPiece(&player, x, y);
      player.addPiece(newPiece);
      placeBridge(newPiece, player.getPieces());
      return true;
    }
    return false;
}

bool Board::isBridgeBetween(const int& x1, const int& y1, const int& x2, const int& y2, Player& owner)
{
    Piece piece1, piece2;
    for (Piece piece : owner.getPieces())
    {
        if (piece.getX() == x1 && piece.getY() == y1) { piece1 = piece; }
        if (piece.getX() == x2 && piece.getY() == y2) { piece2 = piece; }
    }
    if (piece1.getOwner() && piece2.getOwner())
        for (auto bridge : owner.getBridges())
        {
            if ((bridge.getPiece1() == piece1 || bridge.getPiece1() == piece2) && (bridge.getPiece2() == piece1 || bridge.getPiece2() == piece2))
                return true;
        }
    return false;
}



