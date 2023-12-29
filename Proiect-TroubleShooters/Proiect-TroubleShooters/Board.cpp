#include "Board.h"

// Constructor
Board::Board(uint16_t boardSize) : size(boardSize), board(boardSize, std::vector<Piece>(boardSize)), pieces(), bridges(), engine(std::random_device{}()) {
    
}
// Copy constructor
Board::Board(const Board& other) : size(other.size), board(other.board), pieces(other.pieces), bridges(other.bridges), dozer(other.dozer) {
}

// Copy assignment operator
Board& Board::operator=(const Board& other) {
    if (this != &other) {
        size = other.size;
        board = other.board;
        pieces = other.pieces;
        dozer = other.dozer;
       // bridges = other.bridges;
    }
    return *this;
}

Board::Board(Board&& other) noexcept
    : size{ std::move(other.size) }, board{ std::move(other.board) }, dozer{ std::move(other.dozer) }
{
    // Dup? mutarea resurselor, cel?lalt obiect trebuie s? fie într-o stare valid?
    other.size = 0;
    other.board.clear();
}

Board& Board::operator=(Board&& other) noexcept
{
    if (this != &other)
    {
        size = other.size;
        board = std::move(other.board);
        dozer = other.dozer;

        // Dup? mutarea resurselor, cel?lalt obiect trebuie s? fie într-o stare valid?
        other.size = 0;
        other.board.clear();
    }
    return *this;
}

// Getter pentru dimensiune
uint16_t Board::getSize() const {
    return size;
}

void Board::setSize(std::uint16_t newSize)
{
    if (newSize != size) {
        size = newSize;

        // Reset?m ?i ajust?m structurile de date în consecin??
        board.clear();
        board.resize(size, std::vector<Piece>(size, Piece())); // Reinitializ?m tabla cu dimensiunea nou?

        
    }
}

// Getter pentru tabla de joc
const std::vector<std::vector<Piece>>& Board::getBoard() const {
    return board;
}
std::vector<Piece>& Board::getPieces()
{
    return pieces;
}
std::vector<Bridge>& Board::getBridges()
{
    return bridges;
}

 Piece& Board::operator()(uint16_t x, uint16_t y)
{
    // Presupunând c? x ?i y sunt indici valizi
    return board[x][y];
}

void Board::deletePieces()
{
    pieces.clear();
}

void Board::deleteBridges()
{
    bridges.clear();
}

bool Board::isValidLocation(uint16_t x, uint16_t y) const
{
    if ((x == size - 1 || x == 0) && (y == size - 1 || y == 0))
        return false;
    return x >= 0 && x <= size - 1 && y>=0 && y <= size - 1;
}

bool Board::isOccupied(uint16_t x, uint16_t y) const {
    return board[x][y].getColor() != Color::None || (x == dozer.first && y == dozer.second);
}

bool Board::placeBridge(Piece& piece1,Piece& piece2) 
{
        if ((abs(piece1.getX() - piece2.getX()) == 1 && abs(piece1.getY() - piece2.getY()) == 2) ||
            (abs(piece1.getX() - piece2.getX()) == 2 && abs(piece1.getY() - piece2.getY()) == 1))
        {
            if (canPlaceBridge(piece1, piece2))
            {
                Bridge newBridge(piece1, piece2);
                bridges.push_back(newBridge);
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    
}

void Board::deleteBridge(const Piece& p1,const Piece& p2)
{
    if (p1.getColor() != p2.getColor())
        return;
    else
    {
        for (auto it = bridges.begin(); it !=bridges.end(); ++it) {
            if ((it->getPiece1()==p1 && it->getPiece2()==p2) ||
                (it->getPiece2() == p1 && it->getPiece1() == p2) ){
                bridges.erase(it);
                break;
            }
        }
        board[p1.getX()][p1.getY()] = Piece(p1.getColor(), p1.getX(), p1.getY());
        board[p2.getX()][p2.getY()] = Piece(p2.getColor(), p2.getX(), p2.getY());
    }
}

bool Board::placePiece(const Piece & newPiece)
{

    if (isValidLocation(newPiece.getX(),newPiece.getY()) && !isOccupied(newPiece.getX(), newPiece.getY()))
    {
        for (int i = 0; i < mines.size();i++) {
            if (newPiece.getX() == std::get<0>(mines[i]) && newPiece.getY() == std::get<1>(mines[i])) {
                explode(mines[i]);
                mines.erase(mines.begin() + i);
                return true;
            }
        }
      board[newPiece.getX()][newPiece.getY()] = newPiece;
      pieces.push_back(newPiece);
      return true;
    }
    return false;
}

bool Board::isBridgeBetween(const uint16_t& x1, const uint16_t& y1, const uint16_t& x2, const uint16_t& y2)
{
    Piece piece1, piece2;
    for (const Piece& piece :pieces)
    {
        if (piece.getX() == x1 && piece.getY() == y1) { piece1 = piece; }
        if (piece.getX() == x2 && piece.getY() == y2) { piece2 = piece; }
    }
    if (piece1.getColor()== piece2.getColor())
        for (const auto& bridge : bridges)
        {
            if ((bridge.getPiece1() == piece1 && bridge.getPiece2() == piece2) || (bridge.getPiece2() == piece1 && bridge.getPiece1() == piece2))
                return true;
        }
    return false;
}


bool Board::availableWay(const uint16_t& x, const uint16_t& y, const uint16_t& sign, const bool& vertical)
{
    if(vertical)
    {
        if (isBridgeBetween(x + 1, y, x - 1, y - 1 * sign))
            return false;
        if (isBridgeBetween(x + 1, y, x, y - 2 * sign))
            return false;
        if (isBridgeBetween(x + 1, y, x + 2, y - 2 * sign))
            return false;
        if (isBridgeBetween(x + 1, y - 1 * sign, x, y + 1 * sign))
            return false;
        if (isBridgeBetween(x + 1, y - 1 * sign, x + 2, y + 1 * sign))
            return false;
        if (isBridgeBetween(x + 1, y - 1 * sign, x + 3, y))
            return false;
        if (isBridgeBetween(x + 1, y + 1 * sign, x, y - 1 * sign))
            return false;
        if (isBridgeBetween(x, y - 1 * sign, x + 2, y))
            return false;
        if (isBridgeBetween(x + 2, y, x + 1, y - 2 * sign))
            return false;
    }
    else
    {
        if (isBridgeBetween(x, y + 1 * sign, x + 1, y - 1 * sign))
            return false;
        if (isBridgeBetween(x, y + 1 * sign, x + 2, y))
            return false;
        if (isBridgeBetween(x, y + 1 * sign, x + 2, y + 2 * sign))
            return false;
        if (isBridgeBetween(x + 1, y + 1 * sign, x - 1, y))
            return false;
        if (isBridgeBetween(x + 1, y + 1 * sign, x - 1, y + 2 * sign))
            return false;
        if (isBridgeBetween(x + 1, y + 1 * sign, x, y + 3 * sign))
            return false;
        if (isBridgeBetween(x - 1, y + 1 * sign, x + 1, y))
            return false;
        if (isBridgeBetween(x + 1, y, x, y + 2 * sign))
            return false;
        if (isBridgeBetween(x, y + 2 * sign, x + 2, y + 1 * sign))
            return false;
    }
    return true;
}

bool Board::canPlaceBridge(const Piece& piece1, const Piece& piece2)
{
    bool condX = piece1.getX() > piece2.getX();
    bool condY = piece1.getY() > piece2.getY();
    if (abs(piece1.getX() - piece2.getX()) > abs(piece1.getY() - piece2.getY()))
    {
        uint16_t x, y;
        if (piece1.getX() < piece2.getX())
            x = piece1.getX(), y = piece1.getY();
        else
            x = piece2.getX(), y = piece2.getY();
        if (condX && condY || !condX && !condY)
        {
            if (!availableWay(x, y, -1, true))
                return false;
        }
        else //if (condX && !condY || !condX && condY)
        {
            if (!availableWay(x, y, 1, true))
                return false;
        }
    }
    else //if (abs(piece1.getX() - piece2.getX()) < abs(piece1.getY() - piece2.getY()))
    {
        if (condX && condY || !condX && !condY)
        {
            if (piece1.getY() < piece2.getY())
            {
                if (!availableWay(piece1.getX(), piece1.getY(), 1, false))
                    return false;
            }
            else
            {
                if (!availableWay(piece2.getX(), piece2.getY(), 1, false))
                    return false;
            }
        }
        else //if (condX && !condY || !condX && condY)
        {
            if (piece1.getY() > piece2.getY())
            {
                if (!availableWay(piece1.getX(), piece1.getY(), -1, false))
                    return false;
            }
            else
            {
                if (!availableWay(piece2.getX(), piece2.getY(), -1, false))
                    return false;
            }
        }
    }
    return true;
}

Piece Board::dozerTurn(int& piece_location,const std::uint16_t& percentage)
{
    int dozer_action;
    {
        std::uniform_int_distribution<int> distribution(1, 100);
        dozer_action = distribution(engine);
    }
    if (dozer_action <= percentage)
    {
        std::uniform_int_distribution<int> distribution(0, pieces.size() - 1);
        piece_location = distribution(engine);
        Piece& chosen_piece = pieces[piece_location];
        dozer = { chosen_piece.getX(),chosen_piece.getY() };
        return chosen_piece;
    }
    else
    {
        generateRandomPiece();
        Piece emptyPiece;
        return emptyPiece;
    }
}

uint16_t Board::delete_DozerBridges(Piece random_piece)
{
    uint16_t numberBridges = 0;
    for (int i = 0; i < bridges.size(); i++)
    {
        if (bridges[i].getPiece1() == random_piece || bridges[i].getPiece2() == random_piece)
        {
            if (bridges[i].getPiece1() == random_piece)
            {
                deleteBridge(random_piece, bridges[i].getPiece2());

            }
            else if (bridges[i].getPiece2() == random_piece)
            {
                deleteBridge(bridges[i].getPiece1(), random_piece);
            }
            numberBridges++;
        }
    }
    return numberBridges;
}

std::pair<std::uint16_t, std::uint16_t> Board::generateRandomPiece()
{
    if (getSize() != 0)
    {
        uint16_t x, y;
        do
        {
            std::uniform_int_distribution<int> distribution(1, getSize() - 2);
            x = distribution(engine);
            y = distribution(engine);
        } while (isOccupied(x, y));
        dozer = { x,y };
    }
    return dozer;
}

void Board::deletePiece(Piece chosen_piece,int piece_location)
{
    Piece empty;
    board[dozer.first][dozer.second] = empty;
    pieces.erase(pieces.begin() + piece_location);
   
}

void Board::generateMines(const uint16_t& mines_nr)
{
    for (int i{ 0 }; i < mines_nr; i++) {
        uint16_t x, y, type;
        std::uniform_int_distribution<int> distribution1(1, size - 2);
        x = distribution1(engine);
        y = distribution1(engine);

        std::uniform_int_distribution<int> distribution2(1, 3);
        type = distribution2(engine);

        mines.push_back(std::make_tuple(x, y, type));
    }
}

void Board::explode(const std::tuple<uint16_t, uint16_t, uint16_t>& mine)
{
    switch (std::get<2>(mine))
    {
    case 1:
        for (int i{ std::get<0>(mine) - 1 }; i < std::get<0>(mine) + 1; i++)
            for (int j{ std::get<1>(mine) - 1 }; j < std::get<1>(mine) + 1; j++) {
                if (board[i][j].getColor() != None) {
                    for (int t = 0; t < bridges.size(); t++)
                    {
                        if (bridges[t].getPiece1() == board[i][j] || bridges[t].getPiece2() == board[i][j])
                            bridges.erase(bridges.begin() + t);
                    }
                }
                for (int t = 0; t < pieces.size(); t++)
                    if (pieces[t] == board[i][j])
                        pieces.erase(pieces.begin()+t);
                Piece empty;
                board[i][j] = empty;
            }
        break;
    case 2:
        for (int j{ 0 }; j < size - 1; j++)
        {
            if (board[std::get<0>(mine)][j].getColor() != None) {
                for (int t = 0; t < bridges.size(); t++)
                    if (bridges[t].getPiece1() == board[std::get<0>(mine)][j] || bridges[t].getPiece2() == board[std::get<0>(mine)][j])
                       bridges.erase(bridges.begin() + t);
            }
            for (int t = 0; t < pieces.size(); t++)
                if (pieces[t] == board[std::get<0>(mine)][j])
                    pieces.erase(pieces.begin() + t);
            Piece empty;
            board[std::get<0>(mine)][j] = empty;
        }
        break;
    case 3:
        for (int i{ 0 }; i < size - 1; i++)
        {
            if (board[i][std::get<1>(mine)].getColor() != None) {
                for (int t = 0; t < bridges.size(); t++)
                    if (bridges[t].getPiece1() == board[i][std::get<1>(mine)] || bridges[t].getPiece2() == board[i][std::get<1>(mine)])
                        bridges.erase(bridges.begin() + t);
            }
            for (int t = 0; t < pieces.size(); t++)
                if (pieces[t] == board[i][std::get<1>(mine)])
                    pieces.erase(pieces.begin() + t);
            Piece empty;
            board[i][std::get<1>(mine)] = empty;
        }
        break;
    default:
        break;
    }
}

void Board::reset()
{
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            board[row][col] = Color::None;
        }
    }
}

std::ostream& operator<<(std::ostream& out, const Board& B)
{
    out << B.size << '\n';
    out << B.pieces.size() << '\n';
    for (int i = 0; i < B.pieces.size(); i++)
        out << B.pieces[i] << '\n';
    out << B.bridges.size() << '\n';
    for (int i = 0; i < B.bridges.size(); i++)
        out << B.bridges[i] << '\n';
    out << B.mines.size()<<'\n';
    for (int i = 0; i < B.mines.size(); i++)
        out << std::get<0>(B.mines[i]) << " " << std::get<1>(B.mines[i]) << " " << std::get<2>(B.mines[i])<<'\n';
    out << B.dozer.first << " " << B.dozer.second;
    return out;
}

std::istream& operator>>(std::istream& in, Board& B)
{
    uint16_t size;
    in >> size;
    Board aux(size);
    uint16_t piecesSize;
    in >> piecesSize;
    for (uint16_t i{ 0 }; i < piecesSize; i++) {
        in >> aux.pieces[i];
        aux(aux.pieces[i].getX(), aux.pieces[i].getY()) = aux.pieces[i];
    }
    uint16_t bridgesSize;
    in >> bridgesSize;
    for (uint16_t i{ 0 }; i < bridgesSize; i++) {
        in >> aux.bridges[i];
    }
    uint16_t minesSize;
    in >> minesSize;
    for (uint16_t i{ 0 }; i < minesSize; i++) {
        uint16_t mineX, mineY, type;
        in >> mineX, mineY, type;
        aux.mines[i] = std::make_tuple(mineX, mineY, type);
    }
    in >> aux.dozer.first >> aux.dozer.second;
    B = aux;

    return in;
}
