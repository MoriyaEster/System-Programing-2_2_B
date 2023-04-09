#pragma once
#include <string>
#include "card.hpp"
#include <vector>

using namespace std;

class Player{

public:
    std::string name;
    bool isPlaying = false;
    Card cardOfLastTurn;
    vector<Card> packetOfCards;
    vector<Card> packetOfWonsCards;
    int numOfWinning = 0;

    Player();
    Player(std::string name);

    int stacksize();
    int cardesTaken();
};