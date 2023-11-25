#include "Game.h"
#include<algorithm>
#include<queue>
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
    if (player.getNumberBridges() < board.getSize() / 2 - (1 - board.getSize() % 2)) {
        return false;
    }

    std::queue<Piece> road;
    std::vector<Piece> visited_pieces;
    std::vector<Piece> start_pieces;

    if (player.getColor() == 1) {
        for (Piece x : player.getPieces()) {
            if (x.getX() == 0 || x.getX() == 1) {
                start_pieces.push_back(x);
            }
        }
    }
    else {
        for (Piece x : player.getPieces()) {
            if (x.getY() == 0 || x.getY() == 1) {
                start_pieces.push_back(x);
            }
        }
    }

    while (!start_pieces.empty()) {
        if (std::find(visited_pieces.begin(), visited_pieces.end(), start_pieces.back())==visited_pieces.end()) {
            road.push(start_pieces.back());
        }
        start_pieces.pop_back();
        while (!road.empty()) {
            bool isBridge = false;
            for (Bridge x : player.getBridges()) {
                if (x.getPiece1() == road.front() && std::find(visited_pieces.begin(), visited_pieces.end(), x.getPiece2()) == visited_pieces.end()) {
                    road.push(x.getPiece2());
                    isBridge = true;
                }
            }
            if (!isBridge && ((player.getColor() == 1 && road.front().getX() == board.getSize() - 1 || road.front().getX() == board.getSize() - 2) || 
                (player.getColor() == 2 && road.front().getY() == board.getSize() - 1 || road.front().getY() == board.getSize() - 2))) {
                return true;
            }
            road.pop();
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

void Game::forfeitGame()
{
    std::cout << "Player " << currentPlayer->getName() << " has forfeited!" << "\n";
}

void Game::displayScore() const
{
    std::cout << "Player 1 Score: " << player1.getScore() << "\n" << "Player 2 Score: " << player2.getScore() << "\n";
}


void Game::Play()
{
    std::cout << "Introduceti numarul maxim de piloni/jucator: ";
    uint16_t maxPieces;
    std::cin >> maxPieces;
    player1.setMaxPieces(maxPieces);
    player2.setMaxPieces(maxPieces);
    bool firstTurn = true;
    while (currentPlayer->getNumberPieces() <= maxPieces && !checkGameResult(*this)) {
        uint16_t x, y;
        std::cout << '\n' << currentPlayer->getName()<< "'s turn\n";
        currentPlayer->displayPlayerNumberPieces();
        if (currentPlayer->getNumberPieces() == 0 && currentPlayer == &player2 && firstTurn == true) {
            std::cout << "Alege actiunea (1 - plaseaza pion, 2 - elimina poduri, 3 - preia prima piesa, 4 - renunta la joc): ";
            uint16_t action;
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
            uint32_t action;
            std::cin >> action;

            switch (action) {
            case 1:
            {
                bool piece_placed = false;
                while (!piece_placed) {
                    std::cout << "Alege coordonatele pilonului: ";
                    std::cin >> x >> y;
                    if ((currentPlayer->getColor() == 1 && (y == 0 || y == board.getSize() - 1)) || (currentPlayer->getColor() == 2 && (x == 0 || x == board.getSize() - 1))) {
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
                    std::cout << '\n';
                    board.displayBoard();
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


