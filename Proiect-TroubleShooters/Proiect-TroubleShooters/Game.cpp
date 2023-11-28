#include "Game.h"
#include<algorithm>
#include<queue>

Game::Game(Board& gameBoard) : board{ gameBoard }, player1{}, player2{}, currentPlayer{ &player1 } {
    // Restul logicii de ini?ializare pentru joc
}

void Game::setPlayerNames(const QString& namePlayer1, const QString& namePlayer2) {
    player1.setName(namePlayer1.toStdString());
    player1.setColor(Color::Red);
    player2.setName(namePlayer2.toStdString());
    player2.setColor(Color::Black);

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

void Game::Setup()
{
    std::cout << "Introduceti marimea tablei de joc: ";
    uint16_t b_size;
    std::cin >> b_size;
    Board tempboard(b_size);
    board = std::move(tempboard);
    board.displayBoard();
    std::cout << "Introduceti numarul maxim de piloni/jucator: ";
    uint16_t maxPieces;
    std::cin >> maxPieces;
    player1.setMaxPieces(maxPieces);
    player2.setMaxPieces(maxPieces);
}

void Game::action_addPawn()
{
    uint16_t x, y;
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
            }
            else
                std::cout << "Mutare nepermisa!\n";
        }
    }
    switchPlayer();
}

void Game::action_deleteBridge()
{
    uint16_t x, y;
    if (currentPlayer->getBridges().empty())
    {
        std::cout << "Nu exista poduri";
        return;
    }
    std::cout << "Alege coordonatele pilonilor intre care se afla un pod:\n";
    std::cout << "pilonul1: ";
    std::cin >> x >> y;
    Piece p1(currentPlayer, x, y);
    std::cout << "pilonul2: ";
    std::cin >> x >> y;
    Piece p2(currentPlayer, x, y);
    board.deleteBridge(p1, p2);
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

bool Game::checkGameResult()
{
    if (player1.getNumberMaxPieces() == player1.getNumberPieces() && player2.getNumberMaxPieces() == player2.getNumberPieces())
    {
        std::cout << "It' s a draw! Both players are out of pieces!" << "\n";
        return true;
    }
    else
        if (checkWinCondition(*currentPlayer))
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
    bool firstTurn = true;
    while (currentPlayer->getNumberPieces() <= currentPlayer->getNumberMaxPieces() && !checkGameResult()) {
        uint16_t x, y;
        std::cout << '\n' << currentPlayer->getName()<< "'s turn\n";
        currentPlayer->displayPlayerNumberPieces();
        std::cout << "Alege actiunea (1 - plaseaza pion, 2 - elimina poduri,";
        if (currentPlayer == &player2 && firstTurn == true) {
            std::cout << "3 - preia prima piesa,";
        }
        std::cout << "4 - renunta la joc): ";
        uint16_t action;
        std::cin >> action;

        switch (action) {
            case 1:
            {
                action_addPawn();
                if (currentPlayer == &player2 && firstTurn == true)
                    firstTurn = false;
                break;
            }
            case 2:
            {
                action_deleteBridge();
                if (currentPlayer == &player2 && firstTurn == true)
                    firstTurn = false;
                break;
            }
            case 3:
                if (currentPlayer == &player2 && firstTurn == true) {
                    player2.transferFirstPiece(player1);
                    firstTurn = false;
                    switchPlayer();
                }
                break;
            case 4:
                forfeitGame();
                switchPlayer();
                std::cout << "Player " << currentPlayer->getName() << " has won!" << "\n";
                return;
            default:
                std::cout << "Actiune invalida. Alege 1, 2,";
                std::cout << "3,";
                std::cout<<"4.\n";
                continue; // Continua bucla pentru a alege o actiune valida
        }
        
        std::cout << '\n';
        board.displayBoard();
    }
}

