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
            board[i][j]= other.board[i][j];
        }
    }
}

Board& Board::operator=(const Board& other)
{
    if (this == &other) {
        // Evit?m auto-atribuirea
        return *this;
    }

    // Dealoc?m memoria pentru matricea curent?
    for (int i = 0; i < size; i++) {
        delete[] board[i];
    }
    delete[] board;

    // Copiem dimensiunea
    size = other.size;

    // Alocare memorie pentru matricea nou?
    board = new int* [size];
    for (int i = 0; i < size; i++) {
        board[i] = new int[size];
        for (int j = 0; j < size; j++) {
            board[i][j] = other.board[i][j];
        }
    }

    return *this;
}

bool Board::isValidLocation(int x, int y, int boardSize)
{
        return x > 0 && x < boardSize - 1 && y>0 && y < boardSize - 1;
    
}

bool Board::isOccupied(int x, int y,int** board)
{
    return board[x][y] != 0;
}

bool Board::placePiece(const Player& player, int x, int y)
{
    if (isValidLocation(x, y, size) && !isOccupied(x, y, board))
    {
        board[x][y] = player.getColor();
        return true;
    }
    return false;
}

void Board::displayBoard()
{
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
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
        std::cout << '\n';
    }
}


