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

    Board tempboard(board.getSize());
    board = std::move(tempboard);
    consoleDisplay.displayBoard(board);
    uint16_t maxPieces = (board.getSize() * board.getSize() / 2);
    if (difficulty == "Medium")
        maxPieces *= 0.8;
    else
        if (difficulty == "Hard")
            maxPieces *= 0.6;
    player1.setInitialValues(maxPieces);
    player2.setInitialValues(maxPieces);
    if (difficulty == "Hard")
    {
        consoleDisplay.displayMessage("Type in the number of mines: ");
        uint16_t nr_mines;
        std::cin >> nr_mines;
        while (nr_mines > board.getSize() / 3) {
            consoleDisplay.displayMessage(("Too many mines. Type in a smaller number: "));
            std::cin >> nr_mines;
        }
        board.generateMines(nr_mines);
    }
}

void Game::action_placeBridge()
{
    uint16_t x1, y1, x2, y2;
    bool bridge_placed = false;
    consoleDisplay.displayMessage(("Choose the coordinates of the pillar1: "));
    std::cin >> x1 >> y1;
    consoleDisplay.displayMessage(("\nChoose the coordinates of the pillar2: "));
    std::cin >> x2 >> y2;
    while (!board.isOccupied(x1, y1) || !board.isOccupied(x2, y2))
    {
        consoleDisplay.displayMessage("Invalid location\n");
        if (!board.isOccupied(x1, y1))
        {
            consoleDisplay.displayMessage("Choose the coordinates of the pillar1:");
            std::cin >> x1 >> y1;
        }
        if (!board.isOccupied(x2, y2))
        {
            consoleDisplay.displayMessage("\nChoose the coordinates of the pillar2: ");
            std::cin >> x2 >> y2;

        }
    }
    while (board(x1, y1).getColor() != currentPlayer->getColor() || board(x2, y2).getColor() != currentPlayer->getColor())
    {
        if (board(x1, y1).getColor() != currentPlayer->getColor())
        {
            consoleDisplay.displayMessage("Different colors\n");
            consoleDisplay.displayMessage("Choose the coordinates of the pillar1:");
            std::cin >> x1 >> y1;
        }
        if (board(x2, y2).getColor() != currentPlayer->getColor())
        {
            consoleDisplay.displayMessage("Different colors\n");
            consoleDisplay.displayMessage("Choose the coordinates of the pillar2:");
            std::cin >> x2 >> y2;
        }
    }
    if (board.placeBridge(board(x1, y1), board(x2, y2)))
    {
        currentPlayer->setRemainingBridges(currentPlayer->getRemainingBridges() - 1);
    }
    else
    {
        consoleDisplay.displayMessage("The bridge can't be placed.");
    }
}

void Game::action_addPawn()
{
    uint16_t x, y;
    bool piece_placed = false;
    while (!piece_placed) {
        consoleDisplay.displayMessage("Choose the coordinates of the pillar: ");
        std::cin >> x >> y;
        if (currentPlayer->getColor() == Red && (y == 0 || y == board.getSize() - 1)) {
            consoleDisplay.displayMessage("Can't do that!\n");
        }
        else if (currentPlayer->getColor() == Black && (x == 0 || x == board.getSize() - 1)) {
            consoleDisplay.displayMessage("Can't do that!\n");
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
                consoleDisplay.displayMessage("Can't do that!\n");
        }
    }
    currentPlayer->setRemainingPieces(currentPlayer->getRemainingPieces() - 1);
}

void Game::action_deleteBridge()
{
    uint16_t x1, y1, x2, y2;
    while (board(x1, y1).getColor() != currentPlayer->getColor() || board(x2, y2).getColor() != currentPlayer->getColor())
    {
        if (board(x1, y1).getColor() != currentPlayer->getColor())
        {
            consoleDisplay.displayMessage("Different colors\n");
            consoleDisplay.displayMessage("Choose the coordinates of the pillar1:");
            std::cin >> x1 >> y1;
        }
        if (board(x2, y2).getColor() != currentPlayer->getColor())
        {
            consoleDisplay.displayMessage("Different colors\n");
            consoleDisplay.displayMessage("Choose the coordinates of the pillar2:");
            std::cin >> x2 >> y2;
        }
    }
    Piece p1(currentPlayer->getColor(), x1, y1);
    Piece p2(currentPlayer->getColor(), x2, y2);
    board.deleteBridge(p1, p2);
    currentPlayer->setRemainingBridges(currentPlayer->getRemainingBridges() + 1);
}

void Game::display_changingBridges()
{

    consoleDisplay.displayMessage("Add or delete a bridge.\n");
    consoleDisplay.displayMessage("1 - Add a bridge, 2 - Delete a bridge\n");
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
            consoleDisplay.displayMessage("No bridges to modify!");
            return;
        }
        action_deleteBridge();
        break;
    default:
        break;
    }
}

void Game::setGameDifficulty()
{
    if (difficulty == "Easy")
        percentage = 10;
    else
        if (difficulty == "Medium")
            percentage = 30;
        else
            percentage = 50;
}

void Game::actionRandomPiece(Piece random_piece)
{
    if (random_piece.getColor() == Color::Red)
    {
        player1.setRemainingPieces(player1.getRemainingPieces() + 1);
        player1.setRemainingBridges(player1.getRemainingBridges() + board.delete_DozerBridges(random_piece));
        board.deletePiece(random_piece);
        //un mesaj
        consoleDisplay.displayMessage("The dozer had destroyed the pillar from coordinates " + std::to_string(random_piece.getX()) + " " + std::to_string(random_piece.getY()) + "\n");
        consoleDisplay.displayBoard(board);
    }
    else
        if (random_piece.getColor() == Color::Black)
        {
            player2.setRemainingPieces(player2.getRemainingPieces() + 1);
            player2.setRemainingBridges(player2.getRemainingBridges() + board.delete_DozerBridges(random_piece));
            board.deletePiece(random_piece);
            //un mesaj
            consoleDisplay.displayMessage("The dozer had destroyed the pillar from coordinates " + std::to_string(random_piece.getX()) + " " + std::to_string(random_piece.getY()) + "\n");
            consoleDisplay.displayBoard(board);
        }
}

void Game::reset()
{
    board.reset();
    board.deleteBridges();
    currentPlayer = &player1;
}

void Game::Load(const std::string& filename)
{
    std::ifstream in(filename);
    Player p1, p2;
    in >> p1;
    this->player1 = p1;
    in >> p2;
    this->player2 = p2;
    Board board;
    in >> board;
    this->board = board;
    uint16_t color;
    in >> color;
    if (static_cast<Color>(color) == p1.getColor())
        this->currentPlayer = &p1;
    else
        this->currentPlayer = &p2;
}

void Game::Save(const std::string& filename)
{
    std::ofstream out(filename);
    out << this;
}


bool Game::checkWin(Color color)
{
    //if (player.getNumberBridges() < board.getSize() / 2 - (1 - board.getSize() % 2)) {
    //    return false;
   // }

    std::queue<Piece> road;
    std::vector<Piece> visited_pieces;
    std::vector<Piece> start_pieces;

    for (uint16_t i = 0; i < board.getSize(); i++)
    {
        if (board(0,i).getColor() == Color::Red || board(1, i).getColor() == Color::Red)
            start_pieces.push_back(board(0, i));
        if (board(i, 0).getColor() == Color::Black || board(i,1).getColor() == Color::Black)
            start_pieces.push_back(board(i, 0));
    }
    for (Piece p : start_pieces)
    {
        std::cout << p.getColor() << " " << p.getX() << " " << p.getY() << "\n";
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
                        visited_pieces.push_back(x.getPiece1());
                        road.push(x.getPiece2());
                        isBridge = true;
                    }
                    else if (x.getPiece2() == road.front() && std::find(visited_pieces.begin(), visited_pieces.end(), x.getPiece1()) == visited_pieces.end()) {
                        visited_pieces.push_back(x.getPiece2());
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
    if (player1.getRemainingPieces() == 0 && player2.getRemainingPieces() == 0)
    {
        consoleDisplay.displayMessage("It' s a draw! Both players are out of pieces!\n");
        return true;
    }
    else
        if (checkWin(currentPlayer->getColor()))
        {
            consoleDisplay.displayMessage("Player " + currentPlayer->getName() + " has won!" + "\n");
            return true;
        }
    return false;
}

void Game::forfeitGame()
{
    consoleDisplay.displayMessage("Player " + currentPlayer->getName() + " has forfeited!" + "\n");
}

//void Game::displayScore() const
//{
//     consoleDisplay.displayMessage ("Player 1 Score: " << player1.getScore() << "\n" << "Player 2 Score: " << player2.getScore() << "\n";
//}


void Game::Play_menu()
{
    bool firstTurn = true;
    Piece random_piece;
    int location;
    board.generateRandomPiece();
    consoleDisplay.displayBoard(board);
    setGameDifficulty();
    while (currentPlayer->getRemainingPieces() >= 0 && !checkGameResult()) {
        bool placed_piece = false;
        bool moveOn = false;
        consoleDisplay.displayMessage('\n' + currentPlayer->getColor() + "'s turn\n");
        consoleDisplay.displayPlayerInfo(*currentPlayer);
        while (!moveOn)
        {
            consoleDisplay.displayMessage("Choose an action (1 - place pawn, 2 - modify bridge, ");
            if (currentPlayer == &player2 && firstTurn == true) {
                consoleDisplay.displayMessage("3 - take over the first piece, ");
            }
            consoleDisplay.displayMessage("4 - forfeit, 5 - next player): ");
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
                    consoleDisplay.displayMessage("\n");
                    consoleDisplay.displayBoard(board);
                    placed_piece = true;
                    random_piece = board.dozerTurn(percentage);
                    if (random_piece.getColor() != Color::None)
                        actionRandomPiece(random_piece);
                    consoleDisplay.displayPlayerInfo(*currentPlayer);
                }
                else
                    consoleDisplay.displayMessage("The piece is already added for this time.\n");
                break;

            case 2:
                if (placed_piece)
                {
                    display_changingBridges();
                    consoleDisplay.displayMessage("\n");
                    consoleDisplay.displayBoard(board);
                    consoleDisplay.displayPlayerInfo(*currentPlayer);
                    if (checkGameResult())
                        return;
                }
                else
                    consoleDisplay.displayMessage("You must place a piece!\n");
                break;
            case 3:
                if (currentPlayer == &player2 && firstTurn == true) {
                    switchPlayerColors();
                    firstTurn = false;
                    consoleDisplay.displayMessage("\n");
                    consoleDisplay.displayBoard(board);
                    board.dozerTurn(percentage);
                }
                break;
            case 4:
                forfeitGame();
                switchPlayer();
                consoleDisplay.displayMessage("Player " + currentPlayer->getName() + " has won!" + "\n");
                return;
                break;
            case 5:
                if (placed_piece)
                {
                    moveOn = true;
                    switchPlayer();
                }
                else
                    consoleDisplay.displayMessage("You must place a piece.\n");
                break;
            default:
                consoleDisplay.displayMessage("Action not available. Choose 1, 2, 3, 4, 5\n");
                continue; // Continua bucla pentru a alege o actiune valida
            }
        }
    }
}

void Game::Load_menu() {
    consoleDisplay.displayMessage("Choose an action: (1 - Start a new game, 2 - Load an existing one): ");
    while (1) {
        uint16_t action;
        std::cin >> action;
        switch (action)
        {
        case 1:
            return;
        case 2:
            Load("in.txt");
            return;
        default:
            consoleDisplay.displayMessage("Action not available. Choose 1, 2.\n");
            continue;
        }
    }
}

void Game::Restart_menu(bool& exit) {
    consoleDisplay.displayMessage("Choose an action: (1 - Play again, 2 - Exit): ");
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
            consoleDisplay.displayMessage("Action not available. Choose 1, 2.\n");
            continue;
        }
    }
}

void Game::setBoardSize(const int boardSize)
{
    board.setSize(boardSize);
}
void Game::setDifficulty(const QString& diff)
{
    difficulty = diff.toStdString();
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

std::ostream& operator<<(std::ostream& out, const Game& game)
{
    out << game.player1 << '\n';
    out << game.player2 << '\n';
    out << game.board << '\n';
    out << game.currentPlayer->getColor();
    return out;
}

std::istream& operator>>(std::istream& in, Game& game)
{
    in >> game.player1;
    in >> game.player2;
    in >> game.board;
    uint16_t color;
    in >> color;
    if (static_cast<Color>(color) == game.player1.getColor())
        game.currentPlayer = &game.player1;
    else
        game.currentPlayer = &game.player2;
    return in;
}