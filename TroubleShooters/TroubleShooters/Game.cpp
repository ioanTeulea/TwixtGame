#include "Game.h"
#include<iostream>
Game::Game(Board& gameBoard, Player& p1, Player& p2) : board(gameBoard), player1(p1), player2(p2), currentPlayer(&player1) 
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

bool Game::isOver()
{
   // return false;
}

bool Game::checkGameResult(Game game)
{
    if (player1.score == player1.pieces.size() && player2.score == player2.pieces.size())
    {
        std::cout << "It' s a draw! Both players are out of pices!" << "\n";
        return true;
    }
    else
        if (game.isOver())
        {
            std::cout << "Player" << currentPlayer->name << " has won!" << "\n";
            return true;
        }
    return false;
}


