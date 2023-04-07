#pragma once
#include "player.hpp"
#include "card.hpp"
#include <string.h>
#include <vector>

namespace ariel
{

    class Game
    {

    public:
        Player& player1;
        Player& player2;
        vector<Card> packetOfCard;
        Card lastCardOfPlayer1;
        Card lastCardOfPlayer2;
        vector<Card> thisTurnPlayer1;
        vector<Card> thisTurnPlayer2;
        Card unknownOfDraw1;
        Card unknownOfDraw2;
        vector<Card> packetOfDraw;
        bool isDraw = false;
        bool player1Won = false;
        bool player2Won = false;
        int numOfTurns = 0;
        int numOfDraw = 0;

        Game(Player& player1, Player& player2);

        void playTurn();
        void printLastTurn();
        void playAll();
        void printWiner();
        void printLog();
        void printStats();
        void printPacketOfCards();
        void emptyPacketOfDraw(vector<Card>& deck);
    };
}