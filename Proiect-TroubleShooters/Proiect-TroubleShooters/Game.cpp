#include "Game.h"
#include<algorithm>
#include<queue>


Game::Game(Board& gameBoard) : board{ gameBoard }, player1{}, player2{}, currentPlayer{ &player1 } {
    // Restul logicii de ini?ializare pentru joc
}

void Game::setPlayerNames(const QString& namePlayer1, const QString& namePlayer2) {
    player1.setName(namePlayer1.toStdString());
    player1.setColor(Qt::red);
    player2.setName(namePlayer2.toStdString());
    player2.setColor(Qt::black);

    emit PlayersInfo(player1.getName(),player1.getColor(),player2.getName(),player2.getColor(),player1.getColor());
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
    if (difficulty == "Medium")
    {
        std::pair<uint16_t, uint16_t> current_dozer = board.dozerTurn(30);
        actionRandomPiece(current_dozer);
    }
    else if (difficulty == "Hard")
    {
        std::pair<uint16_t, uint16_t> current_dozer = board.dozerTurn(40);
        actionRandomPiece(current_dozer);
    }
}

void Game::switchPlayerColors()
{
    QColor temp = player1.getColor();
    player1.setColor(player2.getColor());
    player2.setColor(temp);
}

void Game::Setup()
{

    Board tempboard(board.getSize());
    board = std::move(tempboard);
    //consoleDisplay.displayBoard(board);
    uint16_t maxPieces;
    if (difficulty == "Easy") {
        maxPieces = (board.getSize() * 2.0);
    }
    else {
        maxPieces = (board.getSize() * 1.7);
    }

    player1.setInitialValues(maxPieces);
    player2.setInitialValues(maxPieces);
    if (difficulty == "Hard")
    {
        // consoleDisplay.displayMessage("Type in the number of mines: ");
        uint16_t nr_mines;
        //std::cin >> nr_mines;
        nr_mines = board.getSize() / 3;
        board.generateMines(nr_mines);
        const auto& mines = board.getMines();
        consoleDisplay.displayMessage("Generated Mines:\n");
        for (const auto& mine : mines) {
            consoleDisplay.displayMessage("Mine at coordinates: " + std::to_string(std::get<0>(mine)) + ", " + std::to_string(std::get<1>(mine)) + std::to_string(std::get<2>(mine))+ "\n");
        }
    }
}

void Game::action_placeBridge(const uint16_t x1, const uint16_t y1, const uint16_t x2, const uint16_t y2, bool& isOk)
{
    isOk = false;
    if (!board.isOccupied(x1, y1) || !board.isOccupied(x2, y2))
    {
        consoleDisplay.displayMessage("Invalid location\n");
        isOk = false;
        return;
    }
    if (board(x1, y1).getColor() != currentPlayer->getColor() || board(x2, y2).getColor() != currentPlayer->getColor())
    {
        consoleDisplay.displayMessage((board(x1, y1).getColor().name().toStdString()) + "\n");
        consoleDisplay.displayMessage((board(x2, y2).getColor().name().toStdString()) + "\n");
        consoleDisplay.displayMessage("Invalid location!\n");
        isOk = false;
        return;
    }
    if (board.placeBridge(board(x1, y1), board(x2, y2)))
    {
        isOk = true;
        currentPlayer->setRemainingBridges(currentPlayer->getRemainingBridges() - 1);
    }
    else
    {
        isOk = false;
        consoleDisplay.displayMessage("The bridge can't be placed.");
    }
    Play();
}

void Game::action_addPawn(QColor color, const  uint16_t i, const  uint16_t j, bool& isOk)
{
    isOk = false;
    consoleDisplay.displayMessage(board(i, j).getColor().name().toStdString()+"\n");
    if (!isOk) {
        consoleDisplay.displayMessage("Choose the coordinates of the pillar: ");
        if (currentPlayer->getColor() == Qt::red && (j == 0 || j == board.getSize() - 1)) {
            consoleDisplay.displayMessage("Can't do that!\n");
        }
        else if (currentPlayer->getColor() == Qt::black && (i == 0 || i == board.getSize() - 1)) {
            consoleDisplay.displayMessage("Can't do that!\n");
        }
        else
            if (board(i, j).getColor() == Qt::blue)
                consoleDisplay.displayMessage("Can't do that!\n");
        else {
            Piece newPiece(currentPlayer->getColor(), i, j);
            bool exploded = false;
            for (int i = 0; i < board.getMines().size(); i++) {
                if (i < board.getMines().size() && newPiece.getX() == std::get<0>(board.getMines()[i]) && newPiece.getY() == std::get<1>(board.getMines()[i])) {
                    board.explode(board.getMines()[i]);
                    board.getMines().erase(board.getMines().begin() + i);
                    exploded = true;
                   
                    break;
                }
            }
            if (exploded)
            {
                consoleDisplay.displayBoard(board);
                emit mineExploded(board);
            }
            else 
            {
                if (board.placePiece(newPiece))
                {
                    isOk = true;
                    currentPlayer->setRemainingPieces(currentPlayer->getRemainingPieces() - 1);
                    if (board(i, j).getColor() == Qt::gray)
                        currentPlayer->advantage = true;
                }
                else
                    consoleDisplay.displayMessage("Can't do that!\n");
            }
        }
    }

}



void Game::action_deleteBridge(const uint16_t x1, const uint16_t y1, const uint16_t x2, const uint16_t y2)
{
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
        // action_placeBridge();
        break;
    case 2:
        if (board.getBridges().empty())
        {
            consoleDisplay.displayMessage("No bridges to modify!");
            return;
        }
        //action_deleteBridge();
        break;
    default:
        break;
    }
}

void Game::setGameDifficulty()
{
    if (difficulty == "Easy")
        percentage = 0;
    else
        if (difficulty == "Medium")
            percentage = 30;
        else
            percentage = 50;
}

void Game::actionRandomPiece(std::pair<uint16_t,uint16_t> random_piece)
{

    //consoleDisplay.displayMessage("Dozer's turn\n");
    if (board(random_piece.first,random_piece.second).getColor()==Qt::red)
    {
        player1.setRemainingPieces(player1.getRemainingPieces() + 1);
        player1.setRemainingBridges(player1.getRemainingBridges() + board.delete_DozerBridges(board(random_piece.first, random_piece.second)));
        board.deletePiece(board(random_piece.first, random_piece.second));
        //un mesaj
        consoleDisplay.displayMessage("The dozer had destroyed the pillar from coordinates " + std::to_string(random_piece.first) + " " + std::to_string(random_piece.second) + "\n");
        //consoleDisplay.displayBoard(board);
    }
    else
        if (board(random_piece.first, random_piece.second).getColor() == Qt::black)
        {
            player2.setRemainingPieces(player2.getRemainingPieces() + 1);
            player2.setRemainingBridges(player2.getRemainingBridges() + board.delete_DozerBridges(board(random_piece.first, random_piece.second)));
            board.deletePiece(board(random_piece.first, random_piece.second));
            //un mesaj
            consoleDisplay.displayMessage("The dozer had destroyed the pillar from coordinates " + std::to_string(random_piece.first) + " " + std::to_string(random_piece.second) + "\n");
            //consoleDisplay.displayBoard(board);
        }
        else
        {
            consoleDisplay.displayMessage("The dozer moved to an empty position.\n");
            consoleDisplay.displayBoard(board);
        }
    emit randomPiece(random_piece.second, random_piece.first);
}

void Game::reset()
{
    board.reset();
    board.deleteBridges();
    currentPlayer = &player1;
}

std::string Game::getDifficulty()
{
    return difficulty;
}

void Game::Load()
{
    std::string lastSavedFileName;
    std::ifstream configFile("config.txt");
    if (configFile.is_open()) {
        configFile >> lastSavedFileName;
        configFile.close();
    }
    std::ifstream in(lastSavedFileName);
    Player p1, p2;
    in >> p1;
    this->player1 = p1;
    in >> p2;
    this->player2 = p2;
    Board board;
    in >> board;
    this->board = board;
    std::string colorStr;
    in >> colorStr;
    std::string diff;
    in >> diff;
    difficulty = diff;
    int isLastPiecePlaced;
    in >> isLastPiecePlaced;
    QColor Color(QString::fromStdString(colorStr));
    if (Color == p1.getColor())
    {
        this->currentPlayer = &this->player1;
    }
    else
    {
        this->currentPlayer = &this->player2;
    }
    emit PlayersInfo(p1.getName(),p1.getColor(),p2.getName(), p2.getColor(),Color);
    emit boardLoaded(board,isLastPiecePlaced);
}

void Game::Save(const std::string& filename,bool isPiecePlaced)
{
    std::ofstream out(filename);
    out << *this;
    out << isPiecePlaced;
    std::ofstream configFile("config.txt");
    configFile << filename;
}


bool Game::checkWin(QColor color)
{
    //if (player.getNumberBridges() < board.getSize() / 2 - (1 - board.getSize() % 2)) {
    //    return false;
   // }

    std::queue<Piece> road;
    std::vector<Piece> visited_pieces;
    std::vector<Piece> start_pieces;

    if (color == Qt::red) {
        for (uint16_t i = 0; i < board.getSize(); i++)
        {
            if (board(0, i).getColor() == Qt::red)
                start_pieces.push_back(board(0, i));
            if (board(1, i).getColor() == Qt::red)
                start_pieces.push_back(board(1, i));
        }
    }
    else if (color == Qt::black) {
        for (uint16_t i = 0; i < board.getSize(); i++)
        {
            if (board(i, 0).getColor() == Qt::black)
                start_pieces.push_back(board(i, 0));
            if (board(i, 1).getColor() == Qt::black)
                start_pieces.push_back(board(i, 1));
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
            if (!isBridge && ((color == Qt::red && (road.front().getX() == board.getSize() - 1 || road.front().getX() == board.getSize() - 2)) ||
                (color == Qt::black && (road.front().getY() == board.getSize() - 1 || road.front().getY() == board.getSize() - 2)))) {
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
        //consoleDisplay.displayMessage('\n' + currentPlayer->getColor() + "'s turn\n");
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
                        // action_addPawn();
                        currentPlayer->advantage = false;
                    }
                    //action_addPawn();
                    if (currentPlayer == &player2 && firstTurn == true)
                        firstTurn = false;
                    consoleDisplay.displayMessage("\n");
                    consoleDisplay.displayBoard(board);
                    placed_piece = true;
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
                    //random_piece = board.dozerTurn(percentage);
                    //actionRandomPiece(random_piece);
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
            //Load("in.txt");
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
    emit gameDifficulty(diff);
}

bool Game::Play() {
    if (currentPlayer->getRemainingPieces() >= 0 && !checkGameResult()) {
        return true;
    }
    else
    {
        emit gameFinished();
        return false;
    }
}

std::ostream& operator<<(std::ostream& out, const Game& game)
{
    out << game.player1 << '\n';
    out << game.player2 << '\n';
    out << game.board << '\n';
    out << game.currentPlayer->getColor().name().toStdString() << '\n';
    out << game.difficulty;
    out << '\n';
    return out;
}

std::istream& operator>>(std::istream& in, Game& game)
{
    in >> game.player1;
    in >> game.player2;
    in >> game.board;
    uint16_t color;
    in >> color;
    if (static_cast<QColor>(color) == game.player1.getColor())
        game.currentPlayer = &game.player1;
    else
        game.currentPlayer = &game.player2;
    std::string difficulty;
    in >> difficulty;
    game.difficulty = difficulty;
    return in;
}