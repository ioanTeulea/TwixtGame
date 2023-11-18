#include "Game.h"
#include<algorithm>
#include<stack>
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
    if (isConnected(player) == true)
    {
        currentPlayer->increaseScore();
        displayScore();
        return true;
    }
    return false;
}

bool Game::isConnected(Player player)
{
    if (player.getNumberBridges() == 0)
    {
        return false;
    }
        std::stack<Bridge> connected_bridges;
        std::vector<bool>visited(player.getNumberBridges(), false);
        std::vector<Bridge>bridges_connected;
        Piece start1 = player.getBridges()[0].getPiece1();
        Piece start2 = player.getBridges()[0].getPiece2();
        if (player.getColor() == 1)
        {
            if (start1.getX() >1)
                return false;
        }
        else
        {
            if (start1.getY() >1)
                return false;
        }
        connected_bridges.push(player.getBridges()[0]);
        visited[0] = true;
        while (std::any_of(visited.begin(), visited.end(), [](bool value) { return !value; }))
        {
            while (!connected_bridges.empty())
            {
                bool found = false;

                for (int i = 1; i < player.getNumberBridges()&&!found; i++)
                {
                    if (!visited[i] && player.getBridges()[i].getPiece1() == start2)
                    {
                        found = true;
                        visited[i] = true;
                        connected_bridges.push(player.getBridges()[i]);
                        start2 = player.getBridges()[i].getPiece2();
                    }
                }
                if (!found)
                {
                    bridges_connected.push_back(connected_bridges.top());
                    connected_bridges.pop();
                }
            }
            if (bridges_connected[0].getPiece2().getX() == board.getSize()-1 || bridges_connected[0].getPiece2().getX() == board.getSize()-2 && player.getColor()==1)
                return true;
            if (bridges_connected[0].getPiece2().getY() == board.getSize() - 1 || bridges_connected[0].getPiece2().getY() == board.getSize() - 2 && player.getColor() == 2)
                return true;
            bridges_connected.clear();
            for (int i = 1; i < player.getNumberBridges(); i++)
                if (!visited[i])
                {
                    visited[i] = true;
                    connected_bridges.push(player.getBridges()[i]);
                }
        }
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
            std::cout << "Player " << currentPlayer->getName() << " has won!" << "\n";
            return true;
        }
    return false;
}

bool Game::forfeitGame()
{
    std::cout << "Player " << currentPlayer->getName() << " has forfeited!" << "\n";
    return false;
}

void Game::displayScore() const
{
    std::cout << "Player 1 Score: " << player1.getScore() << "\n" << "Player 2 Score: " << player2.getScore() << "\n";
}


void Game::Play()
{
    std::cout << "Introduceti numarul maxim de piloni/jucator: ";
    int maxPieces;
    std::cin >> maxPieces;
    player1.setMaxPieces(maxPieces);
    player2.setMaxPieces(maxPieces);
    bool firstTurn = true;
    while (currentPlayer->getNumberPieces() <= maxPieces && !checkGameResult(*this)) {
        int x, y;
        std::cout << '\n' << currentPlayer->getName()<< "'s turn\n";
        currentPlayer->displayPlayerNumberPieces();
        if (currentPlayer->getNumberPieces() == 0 && currentPlayer == &player2 && firstTurn == true) {
            std::cout << "Alege actiunea (1 - plaseaza pion, 2 - elimina poduri, 3 - preia prima piesa, 4 - renunta la joc): ";
            int action;
            std::cin >> action;

            switch (action) {
            case 1:
            {
                bool piece_placed = false;
                while (!piece_placed) {
                    std::cout << "Alege coordonatele pilonului: ";
                    std::cin >> x >> y;
                    if (*currentPlayer == player2 && (x == 0 || x == board.getSize() - 1)) {
                        std::cout << "Mutare nepermisa!\n";
                    }
                    else {
                        if (board.placePiece(*currentPlayer, x, y))
                        {
                            piece_placed = true;
                            firstTurn = false;
                        }
                        else
                            std::cout << "Mutare nepermisa!\n";
                    }
                }
                sortBridges();

                switchPlayer();
                break;
            }
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
                firstTurn = false;
                sortBridges();
                break;
            }
            case 3:
                player2.transferFirstPiece(player1);
                firstTurn=false;
                switchPlayer();
                break;
            case 4:
                forfeitGame();
                switchPlayer();
                std::cout << "Player " << currentPlayer->getName() << " has won!" << "\n";
                return;
            default:
                std::cout << "Actiune invalida. Alege 1, 2, 3, 4.\n";
                continue; // Continua bucla pentru a alege o actiune valida
            }
        }
        else {
            std::cout << "Alege actiunea (1 - plaseaza pion, 2 - elimina poduri, 3 - renunta la joc): ";
            int action;
            std::cin >> action;

            switch (action) {
            case 1:
            {
                bool piece_placed = false;
                while (!piece_placed) {
                    std::cout << "Alege coordonatele pilonului: ";
                    std::cin >> x >> y;
                    if ((*currentPlayer == player1 && (y == 0 || y == board.getSize() - 1)) || (*currentPlayer == player2 && (x == 0 || x == board.getSize() - 1))) {
                        std::cout << "Mutare nepermisa!\n";
                    }
                    else {
                        if (board.placePiece(*currentPlayer, x, y))
                            piece_placed = true;
                        else
                            std::cout << "Mutare nepermisa!\n";
                    }
                }
                sortBridges();
                if (checkGameResult(*this))
                {
                    return;
                }
                switchPlayer();
                break;
            }
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
                sortBridges();
                break;
            }
            case 3:
                forfeitGame();
                switchPlayer();
                std::cout << "Player" << currentPlayer->getName() << " has won!" << "\n";
                currentPlayer->increaseScore();
                displayScore();
                return;
            default:
                std::cout << "Actiune invalida. Alege 1, 2 sau 3.\n";
                continue; // Continua bucla pentru a alege o actiune valida
            }
        }

        std::cout << '\n';
        board.displayBoard();
    }
}


