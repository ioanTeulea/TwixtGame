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
    std::cout << "Type in the board size: ";
    uint16_t b_size;
    std::cin >> b_size;
    Board tempboard(b_size);
    board = std::move(tempboard);
    board.displayBoard();
    std::cout << "Type in the maximum number of pieces for each player: ";
    uint16_t maxPieces;
    std::cin >> maxPieces;
    player1.setInitialValues(maxPieces);
    player2.setInitialValues(maxPieces);
    std::cout << "Type in the number of mines: ";
    uint16_t nr_mines;
    std::cin >> nr_mines;
    while (nr_mines > b_size / 3) {
        std::cout << "Too many mines. Type in a smaller number: ";
        std::cin >> nr_mines;
    }
    board.generateMines(nr_mines);
}

void Game::action_placeBridge()
{
    uint16_t x1, y1, x2, y2;
    bool bridge_placed = false;
    std::cout << "Choose the coordinates of the pilon: ";
    std::cin >> x1 >> y1;
    std::cout << "\nChoose the coordinates of the pilon: ";
    std::cin >> x2 >> y2;
    while (!board.isOccupied(x1, y1) || !board.isOccupied(x2, y2))
    {
        std::cout << "Invalid location\n";
        if (!board.isOccupied(x1, y1))
        {
            std::cout << "Choose the coordinates of the pilon:";
            std::cin >> x1 >> y1;
        }
        if (!board.isOccupied(x2, y2))
        {
            std::cout << "\nChoose the coordinates of the pilon: ";
            std::cin >> x2 >> y2;

        }
    }
    while (board(x1, y1).getColor()!=currentPlayer->getColor()|| board(x2, y2).getColor() != currentPlayer->getColor())
    {
        if(board(x1, y1).getColor() != currentPlayer->getColor())
        { 
            std::cout << "Different colors\n";
            std::cout << "Choose the coordinates of the pilon:";
            std::cin >> x1 >> y1;
        }
        if (board(x2, y2).getColor() != currentPlayer->getColor())
        {
            std::cout << "Different colors\n";
            std::cout << "Choose the coordinates of the pilon:";
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
        std::cout << "Choose the coordinates of the pilon: ";
        std::cin >> x >> y;
        if (currentPlayer->getColor() == Red && (y == 0 || y == board.getSize() - 1)) {
            std::cout << "Can't do that!\n";
        }
        else if (currentPlayer->getColor() == Black && (x == 0 || x == board.getSize() - 1)) {
            std::cout << "Can't do that!\n";
        }
        else {
            Piece newPiece(currentPlayer->getColor(), x, y);
            if (board.placePiece(newPiece))
            {
                piece_placed = true;
                if (board(x, y).getColor() == None)
                    currentPlayer->advantage = true;
            }
            else
                std::cout << "Can't do that!\n";
        }
    }
    currentPlayer->setRemainingPieces(currentPlayer->getRemainingPieces() - 1);
}

void Game::action_deleteBridge()
{
    uint16_t x, y;
    std::cout << "Choose the coordinates of the pillars between which the bridge is:\n";
    std::cout << "pilon1: ";
    std::cin >> x >> y;
    Piece p1(currentPlayer->getColor(), x, y);
    std::cout << "pilon2: ";
    std::cin >> x >> y;
    Piece p2(currentPlayer->getColor(), x, y);
    board.deleteBridge(p1, p2);
    currentPlayer->setRemainingBridges(currentPlayer->getRemainingBridges() + 1);
}

void Game::display_changingBridges()
{
   
    std::cout << "Add or delete a bridge.\n";
    std::cout << "1 - Add a bridge, 2 - Delete a bridge\n";
    uint16_t action1;
    std::cin >> action1;
   switch (action1)
   {
        case 1:
            action_placeBridge();
            break;
        case 2:
            if (board.getBridges().empty())
            {
                std::cout << "No bridges to modify!";
                return;
            }
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
    currentPlayer = &player1;
}


bool Game::checkWin(Color color)
{
    //if (player.getNumberBridges() < board.getSize() / 2 - (1 - board.getSize() % 2)) {
    //    return false;
   // }

    std::queue<Piece> road;
    std::vector<Piece> visited_pieces;
    std::vector<Piece> start_pieces;


    for (const Piece& x : board.getPieces()) {
        if (color == Red && (x.getX() == 0 || x.getX() == 1)) {
            start_pieces.push_back(x);
        }
        if (color == Black && (x.getY() == 0 || x.getY() == 1)) {
            start_pieces.push_back(x);
        }
    }

    while (!start_pieces.empty()) {
        if (std::find(visited_pieces.begin(), visited_pieces.end(), start_pieces.back()) == visited_pieces.end()) {
            road.push(start_pieces.back());
        }
        start_pieces.pop_back();
        while (!road.empty()) {
            bool isBridge = false;
            for (const Bridge& x : board.getBridges()) {
                if (x.getPiece1().getColor() == color)
                {
                    if (x.getPiece1() == road.front() && std::find(visited_pieces.begin(), visited_pieces.end(), x.getPiece2()) == visited_pieces.end()) {
                        road.push(x.getPiece2());
                        isBridge = true;
                    }
                    else if (x.getPiece2() == road.front() && std::find(visited_pieces.begin(), visited_pieces.end(), x.getPiece1()) == visited_pieces.end()) {
                        road.push(x.getPiece1());
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
    /*if (player1.getRemainingPieces() ==0 && player2.getRemainingPieces() ==0)
    {
        std::cout << "It' s a draw! Both players are out of pieces!" << "\n";
        return true;
    }
    else
        if (checkWinCondition(*currentPlayer))
        {
            std::cout << "Player " << currentPlayer->getName() << " has won!" << "\n";
            return true;
        }*/
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
        bool placed_piece = false;
        bool moveOn = false;
        std::cout << '\n' << currentPlayer->getName()<< "'s turn\n";
        currentPlayer->displayPlayerNumberPieces();
        while (!moveOn)
        {
            std::cout << "Choose an action (1 - place pawn, 2 - modify bridge, ";
            if (currentPlayer == &player2 && firstTurn == true) {
                std::cout << "3 - take over the first piece, ";
            }
            std::cout << "4 - forfeit, ";
            std::cout << "5 - next player): ";
            uint16_t action;
            std::cin >> action;
            switch (action) {
            case 1:

                if (!placed_piece)
                {
                    if (currentPlayer->advantage)
                    {
                        action_addPawn();
                        currentPlayer->advantage = false;
                    }
                    action_addPawn();
                    if (currentPlayer == &player2 && firstTurn == true)
                        firstTurn = false;
                    std::cout << '\n';
                    board.displayBoard();
                    Piece& random_piece=board.dozerTurn();
                    placed_piece = true;
                    if (random_piece.getColor() == Red)
                    {
                        player1.setRemainingPieces(player1.getRemainingPieces() + 1);
                        player1.setRemainingBridges(player1.getRemainingBridges() + board.delete_DozerBridges(random_piece));
                    }
                    if (random_piece.getColor() == Black)
                        {
                            player2.setRemainingPieces(player2.getRemainingPieces() + 1);
                            player2.setRemainingBridges(player2.getRemainingBridges() + board.delete_DozerBridges(random_piece));
                        }
                    if (random_piece.getColor() == None)
                            break;
                    currentPlayer->displayPlayerNumberPieces();
                }
                else
                    std::cout << "The piece is already added for this time.\n";
                break;

            case 2:
                display_changingBridges();
                std::cout << '\n';
                board.displayBoard();
                currentPlayer->displayPlayerNumberPieces();
                break;
            case 3:
                if (currentPlayer == &player2 && firstTurn == true) {
                    switchPlayerColors();
                    firstTurn = false;
                    std::cout << '\n';
                    board.displayBoard();
                    board.dozerTurn();
                }
                break;
            case 4:
                forfeitGame();
                switchPlayer();
                std::cout << "Player " << currentPlayer->getName() << " has won!" << "\n";
                return;
                break;
            case 5:
                if (placed_piece)
                {
                    moveOn = true;
                    switchPlayer();
                }
                else
                    std::cout << "You must place a piece.\n";
                break;
            default:
                std::cout << "Action not available. Choose 1, 2,";
                std::cout << "3\n";
                continue; // Continua bucla pentru a alege o actiune valida
            }
        }
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
        Setup();
        Play_menu();
        Restart_menu(exit);
    }
}

