#include "Board.h"

Board::Board(int boardSize) :
    size{ boardSize }
{
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
        // Evitam auto-atribuirea
        return *this;
    }

    // Dealocam memoria pentru matricea curenta
    for (int i = 0; i < size; i++) {
        delete[] board[i];
    }
    delete[] board;

    // Copiem dimensiunea
    size = other.size;

    // Alocare memorie pentru matricea noua
    board = new int* [size];
    for (int i = 0; i < size; i++) {
        board[i] = new int[size];
        for (int j = 0; j < size; j++) {
            board[i][j] = other.board[i][j];
        }
    }

    return *this;
}

const int& Board::getSize() const
{
    return size;
}

int** Board::getBoard() const
{
    return board;
}

bool Board::isValidLocation(int x, int y, int boardSize)
{
    if ((x == boardSize - 1 || x == 0) && (y == boardSize - 1 || y == 0))
        return false;
    return x >= 0 && x <= boardSize - 1 && y>=0 && y <= boardSize - 1;
}

bool Board::isOccupied(int x, int y, int** board)
{
    return board[x][y] != 0;
}

void Board::displayBoard()
{
    for (int row = 0; row < size; row++) {
        if (row == 0 || row == size - 1) {
            std::cout << "  ";
        }
        for (int col = 0; col < size; col++) {
            if (!((row == size - 1 || row == 0) && (col == size - 1 || col == 0))) {
                    if (board[row][col] == Color::Red) {
                        std::cout << "R ";
                    }
                    else if (board[row][col] == Color::Black) {
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

void Board::placeBridge(Piece newPiece, const std::vector<Piece>& existingPieces) {
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

void Board::deleteBridge(Piece p1, Piece p2)
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

bool Board::placePiece(Player& player, int x, int y)
{
    if (isValidLocation(x, y, size) && !isOccupied(x, y, board))
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



