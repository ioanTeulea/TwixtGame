#include "Game.h"
#include<algorithm>
Game::Game(Board& gameBoard, Player& p1, Player& p2) : board{ gameBoard }, player1{ p1 }, player2{ p2 }, currentPlayer{ &player1 }
{
    // Initialize the game engine
}

void Game::switchPlayer()
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

void Game::sortBridges()
{
    std::sort(currentPlayer->getBridges().begin(), currentPlayer->getBridges().end(), [](const Bridge& bridge1, const Bridge& bridge2) {
        return bridge1.sortBridgesComparator(bridge2);
        });
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
    if (player1.getNumberMaxPieces() == player1.getNumberPieces() && player2.getNumberMaxPieces() == player2.getNumberPieces())
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


void Game::Play()
{
    std::cout << "Introduceti numarul maxim de piloni/jucator: ";
    int maxPieces;
    std::cin >> maxPieces;
    player1.setMaxPieces(maxPieces);
    player2.setMaxPieces(maxPieces);
    int count = 0;
    while (currentPlayer->getNumberPieces() <= maxPieces && !checkGameResult(*this)) {
        int x, y;
        std::cout << '\n' << currentPlayer->getName()<< "'s turn\n";

        if (currentPlayer->getNumberPieces() == 0 && currentPlayer == &player2&& count==0) {
            std::cout << "Alege actiunea (1 - plaseaza pion, 2 - elimina poduri, 3 - preia prima piesa): ";
            int action;
            std::cin >> action;

            switch (action) {
            case 1:
                std::cout << "Alege coordonatele pilonului: ";
                std::cin >> x >> y;
                board.placePiece(*currentPlayer, x, y);
                switchPlayer();
                count++;
                break;
            case 2:
            {
                if (currentPlayer->getBridges().empty())
                {
                    std::cout << "Nu exista poduri";
                    break;
                }
                std::cout << "Alege coordonatele pilonilor intre care se afla un pod:\n";
                std::cout << "pilonul1: ";
                std::cin >> x >> y;
                Piece p1(currentPlayer, x, y);
                std::cout << "pilonul2: ";
                std::cin >> x >> y;
                Piece p2(currentPlayer, x, y);
                board.deleteBridge(p1, p2);
                count++;
                break;
            }
            case 3:
                player2.transferFirstPiece(*currentPlayer);
                count++;
                break;
            default:
                std::cout << "Actiune invalida. Alege 1, 2, 3 sau 4.\n";
                continue; // Continua bucla pentru a alege o actiune valida
            }
        }
        else {
            std::cout << "Alege actiunea (1 - plaseaza pion, 2 -elimina poduri): ";
            int action;
            std::cin >> action;

            switch (action) {
            case 1:
                std::cout << "Alege coordonatele pilonului: ";
                std::cin >> x >> y;
                board.placePiece(*currentPlayer, x, y);
                switchPlayer();
                break;
            case 2:
            {
                if (currentPlayer->getBridges().empty())
                {
                    std::cout << "Nu exista poduri";
                    break;
                }
                std::cout << "Alege coordonatele pilonilor intre care se afla un pod:\n";
                std::cout << "pilonul1: ";
                std::cin >> x >> y;
                Piece p1(currentPlayer, x, y);
                std::cout << "pilonul2: ";
                std::cin >> x >> y;
                Piece p2(currentPlayer, x, y);
                board.deleteBridge(p1, p2);
                break;
            }
            default:
                std::cout << "Actiune invalida. Alege 1 sau 2.\n";
                continue; // Continua bucla pentru a alege o actiune valida
            }
        }

        std::cout << '\n';
        board.displayBoard();
    }
}


