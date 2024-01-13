#include "ConsoleDisplay.h"
ConsoleDisplay::ConsoleDisplay()
{
}

void ConsoleDisplay::displayPlayerInfo(const Player & player) const
{
    std::cout << "Remaining pieces for " << player.getName() << '\n';
    std::cout << "Pieces: " << player.getRemainingPieces() << '\n';
    std::cout << "Bridges: " << player.getRemainingBridges() << '\n';
}

void ConsoleDisplay::displayBoard(Board& board) const
{
    for (uint16_t row = 0; row < board.getSize(); row++) {
        if (row == 0 || row == board.getSize() - 1) {
            std::cout << "  ";
        }
        for (uint16_t col = 0; col < board.getSize(); col++) {
            if (!((row == board.getSize() - 1 || row == 0) && (col == board.getSize() - 1 || col == 0))) {
                if (board(row,col).getColor() ==Qt::red) {
                    std::cout << "R ";
                }
                else if (board(row,col).getColor() ==Qt::black) {
                    std::cout << "B ";
                }
                else if (row == board.dozer.first && col == board.dozer.second)
                    std::cout << "D ";
                else {
                    std::cout << "O ";
                }
            }
        }
        std::cout << '\n';
    }
}

void ConsoleDisplay::displayMessage(const std::string& message) const
{
    std::cout << message;
}
