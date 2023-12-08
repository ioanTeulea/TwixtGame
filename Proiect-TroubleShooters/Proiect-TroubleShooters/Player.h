#pragma once
#include<string>
#include<vector>
#include"Piece.h"
#include"Bridge.h"


class Player
{
    std::string name;
    Color color;
    uint16_t remainingPieces;
    uint16_t remainingBridges;
public:
    bool advantage = false;
    // Constructor
    Player(const std::string& playerName = "", Color playerColor = None);
    std::string getName() const;
    void setName(const std::string& newName);
    const Color& getColor() const;
    void displayPlayerNumberPieces();
    const uint16_t& getRemainingPieces()const;
    const uint16_t& getRemainingBridges()const;
    
    void setRemainingPieces(uint16_t pieces);
    void setRemainingBridges(uint16_t bridges);
    void setColor(Color c);
    void setInitialValues(uint16_t max);
    bool operator==(const Player& other);
   // void transferFirstPiece(Player& otherPlayer);
};
