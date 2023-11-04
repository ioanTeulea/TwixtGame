#include "Game.h"

Game::Game(Board& gameBoard, Player& p1, Player& p2) : board{ gameBoard }, player1{ p1 }, player2{ p2 }, currentPlayer{ &player1 }
{
    // Initialize the game engine
}

void Game::switchPLayer()
{
    if (currentPlayer == &player1)
    {
        currentPlayer = &player2;
    }
    else
    {
        currentPlayer = &player1;
    }
}


bool Game::checkWinCondition(Player player)
{
    std::vector<std::vector<bool>> visited(board.getSize(), std::vector<bool>(board.getSize(), false));
    Color playerColor = player.getColor();

    for (int i = 0; i < board.getSize(); i++) {
        if (board.isOccupied(i, 0, board.getBoard()) && board.isOccupied(i, board.getSize() - 1, board.getBoard()) && board.getBoard()[i][0] == playerColor && board.getBoard()[i][board.getSize() - 1] == playerColor) {
            if (isConnected(i, 0, playerColor, visited)) {
                return true;
            }
        }
    }

    return false;
}

bool Game::isConnected(int x, int y, Color playerColor, std::vector<std::vector<bool>>& visited)
{
    return false;
}

bool Game::checkGameResult(Game game)
{
    if (player1.getScore() == player1.getNumberPieces() && player2.getScore() == player2.getNumberPieces())
    {
        std::cout << "It' s a draw! Both players are out of pieces!" << "\n";
        return true;
    }
    else
        if (game.checkWinCondition(*currentPlayer))
        {
            std::cout << "Player" << currentPlayer->getName() << " has won!" << "\n";
            return true;
        }
    return false;
}


