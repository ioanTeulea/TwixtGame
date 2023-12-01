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

void Game::switchPlayerColors()
{
    Color temp = player1.getColor();
    player1.setColor(player2.getColor());
    player2.setColor(temp);
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
    player1.setInitialValues(maxPieces);
    player2.setInitialValues(maxPieces);
}

void Game::action_placeBridge()
{
    uint16_t x1, y1, x2, y2;
    bool bridge_placed = false;
    std::cout << "Alege coordonatele pilonului: ";
    std::cin >> x1 >> y1;
    std::cout << "\nAlege coordonatele pilonului: ";
    std::cin >> x2 >> y2;
    while (!board.isOccupied(x1, y1) || !board.isOccupied(x2, y2))
    {
        std::cout << "Locatie invalida\n";
        if (!board.isOccupied(x1, y1))
        {
            std::cout << "Alege coordonatele pilonului:";
            std::cin >> x1 >> y1;
        }
        if (!board.isOccupied(x2, y2))
        {
            std::cout << "\nAlege coordonatele pilonului: ";
            std::cin >> x2 >> y2;

        }
    }
    while (board(x1, y1).getColor()!=currentPlayer->getColor()|| board(x2, y2).getColor() != currentPlayer->getColor())
    {
        if(board(x1, y1).getColor() != currentPlayer->getColor())
        { 
            std::cout << "Different colors\n";
            std::cout << "Alege coordonatele pilonului:";
            std::cin >> x1 >> y1;
        }
        if (board(x2, y2).getColor() != currentPlayer->getColor())
        {
            std::cout << "Different colors\n";
            std::cout << "Alege coordonatele pilonului:";
            std::cin >> x2 >> y2;
        }
    }
    if (board.placeBridge(board(x1, y1), board(x2, y2)))
    {
        currentPlayer->setRemainingBridges(currentPlayer->getRemainingBridges() - 1);
    }
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
            Piece newPiece(currentPlayer->getColor(), x, y);
            if (board.placePiece(newPiece))
            {
                piece_placed = true;
            }
            else
                std::cout << "Mutare nepermisa!\n";
        }
    }
    currentPlayer->setRemainingPieces(currentPlayer->getRemainingPieces() - 1);
}

void Game::action_deleteBridge()
{
    uint16_t x, y;
    if (board.getBridges().empty())
    {
        std::cout << "Nu exista poduri";
        return;
    }
    std::cout << "Alege coordonatele pilonilor intre care se afla un pod:\n";
    std::cout << "pilonul1: ";
    std::cin >> x >> y;
    Piece p1(currentPlayer->getColor(), x, y);
    std::cout << "pilonul2: ";
    std::cin >> x >> y;
    Piece p2(currentPlayer->getColor(), x, y);
    board.deleteBridge(p1, p2);
    currentPlayer->setRemainingBridges(currentPlayer->getRemainingBridges() + 1);
}

void Game::display_changingBridges()
{
    std::cout << "Do you want to place a bridge, to delete a bridge or neither of them?\n";
    std::cout << "1 - Place a bridge, 2 - Delete a bridge, 3 - Go ahead\n";
    uint16_t action1;
    std::cin >> action1;
   switch (action1)
   {
        case 1:
            action_placeBridge();
            break;
        case 2:
            action_deleteBridge();
            break;
        default:
            break;
    }
}

void Game::reset()
{
    board.reset();
    board.deleteBridges();
    board.deletePieces();
}


bool Game::checkWinCondition(Player player)
{
    if (isConnected(player.getColor()) == true)
    {
        //currentPlayer->increaseScore();
      //  displayScore();
        return true;
    }
    return false;
}

bool Game::isConnected(Color color)
{
    //if (player.getNumberBridges() < board.getSize() / 2 - (1 - board.getSize() % 2)) {
    //    return false;
   // }

    std::queue<Piece> road;
    std::vector<Piece> visited_pieces;
    std::vector<Piece> start_pieces;

  
    for (Piece x : board.getPieces()) {
       if (x.getX() == 0 || x.getX() == 1) {
              start_pieces.push_back(x);
        }
  }
    
   

    while (!start_pieces.empty()) {
        if (std::find(visited_pieces.begin(), visited_pieces.end(), start_pieces.back())==visited_pieces.end()) {
            road.push(start_pieces.back());
        }
        start_pieces.pop_back();
        while (!road.empty()) {
            bool isBridge = false;
            for (Bridge x : board.getBridges()) {
                if (x.getPiece1().getColor() == color)
                {
                    if (x.getPiece1() == road.front() && std::find(visited_pieces.begin(), visited_pieces.end(), x.getPiece2()) == visited_pieces.end()) {
                        road.push(x.getPiece2());
                        isBridge = true;
                    }
                }
            }
            if (!isBridge && ((color == 1 && road.front().getX() == board.getSize() - 1 || road.front().getX() == board.getSize() - 2) || 
                (color == 2 && road.front().getY() == board.getSize() - 1 || road.front().getY() == board.getSize() - 2))) {
                return true;
            }
            road.pop();
        }
    }
    return false;
}

bool Game::checkGameResult()
{
    if (player1.getRemainingPieces() ==0 && player2.getRemainingPieces() ==0)
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

//void Game::displayScore() const
//{
//    std::cout << "Player 1 Score: " << player1.getScore() << "\n" << "Player 2 Score: " << player2.getScore() << "\n";
//}


void Game::Play_menu()
{
    bool firstTurn = true;
    while (currentPlayer->getRemainingPieces() >=0   && !checkGameResult()) {
        uint16_t x, y;
        std::cout << '\n' << currentPlayer->getName()<< "'s turn\n";
        currentPlayer->displayPlayerNumberPieces();
        std::cout << "Choose an action (1 - place pawn, ";
        if (currentPlayer == &player2 && firstTurn == true) {
            std::cout << "2 - take over the first piece,";
        }
        std::cout << "3 - forfeit): ";
        uint16_t action;
        std::cin >> action;

        switch (action) {
            case 1:
            {
                action_addPawn();
                if (currentPlayer == &player2 && firstTurn == true)
                    firstTurn = false;
                display_changingBridges();
                switchPlayer();
                break;
            }
            case 2:
                if (currentPlayer == &player2 && firstTurn == true) {
                    switchPlayerColors();
                    firstTurn = false;
                    switchPlayer();
                }
                break;
            case 3:
                forfeitGame();
                switchPlayer();
                std::cout << "Player " << currentPlayer->getName() << " has won!" << "\n";
                return;
            default:
                std::cout << "Action not available. Choose 1, 2,";
                std::cout << "3\n";
                continue; // Continua bucla pentru a alege o actiune valida
        }
        
        std::cout << '\n';
        board.displayBoard();
    }
}

void Game::Load_menu() {
    std::cout << "Choose an action: (1 - Start a new game, 2 - Load an existing one): ";
    while (1) {
        uint16_t action;
        std::cin >> action;
        switch (action)
        {
        case 1:
            return;
        case 2:
            //game = saved game
            return;
        default:
            std::cout << "Action not available. Choose 1, 2.\n";
            continue;
        }
    }
}

void Game::Restart_menu(bool& exit) {
    std::cout << "Choose an action: (1 - Play again, 2 - Exit): ";
    while (1) {
        uint16_t action;
        std::cin >> action;

        switch (action)
        {
        case 1:
            reset();
            return;
        case 2:
            exit = true;
            return;
        default:
            std::cout << "Action not available. Choose 1, 2.\n";
            continue;
        }
    }
}

void Game::Play() {
    bool exit = false;
    while (!exit) {
        Load_menu();
        Play_menu();
        Restart_menu(exit);
    }
}

