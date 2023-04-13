#include "game.hpp"
#include "player.hpp"
#include "card.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace ariel;

Game::Game(Player &player1, Player &player2)
    : player1(player1), player2(player2)
{

    if (player1.isPlaying == true)
    {
        throw invalid_argument(player1.name + "is in another game");
    }
    if (player2.isPlaying == true)
    {
        throw invalid_argument(player2.name + "is in another game");
    }

    player1.isPlaying = true;
    player2.isPlaying = true;

    // create a packet of 52 cards in their order and push it into the vector
    Card card;
    vector<Card> deck;
    for (int shape = 0; shape < 4; shape++)
    {
        for (int num = 0; num < 13; num++)
        {
            card.shape = Shape(shape);
            card.num = Num(num);
            deck.push_back(card);
        }
    }

    srand(time(NULL));
    // shuffle the deck
    while (!deck.empty())
    {
        size_t rand_index = (unsigned long)rand() % deck.size();
        packetOfCard.push_back(deck[rand_index]);
        deck.erase(deck.begin() + (int)rand_index);
    }

    // divide the packet of cards to the players, 26 cards each one.
    for (int index = 0; index < 26; index++)
    {
        player1.packetOfCards.push_back(packetOfCard[0]);
        packetOfCard.erase(packetOfCard.begin());
        player2.packetOfCards.push_back(packetOfCard[0]);
        packetOfCard.erase(packetOfCard.begin());
    }
}

void ariel::Game::printPacketOfCards()
{
    std::cout << "--------------------------------------------------" << endl;
    std::cout << "player1: " << player1.packetOfCards.size() << endl;
    for (Card c : player1.packetOfCards)
    {
        std::cout << "Num: " << c.num << "   "
                  << "Shape: " << c.shape << endl;
    }

    std::cout << "player2: " << player2.packetOfCards.size() << endl;
    for (Card c : player2.packetOfCards)
    {
        std::cout << "Num: " << c.num << "   "
                  << "Shape: " << c.shape << endl;
    }
}

void ariel::Game::playTurn()
{
    if (&player1 == &player2)
    {
        throw invalid_argument("You have to choose two diffrent players");
    }

    if (player1.packetOfCards.size())
    {
        if (!isDraw)
        {
            numOfTurns++;
            while (thisTurnPlayer1.size())
            {
                thisTurnPlayer1.erase(thisTurnPlayer1.begin());
                thisTurnPlayer2.erase(thisTurnPlayer2.begin());
            }
        }

        lastCardOfPlayer1 = player1.packetOfCards[0];
        player1.packetOfCards.erase(player1.packetOfCards.begin());
        lastCardOfPlayer2 = player2.packetOfCards[0];
        player2.packetOfCards.erase(player2.packetOfCards.begin());

        packetOfLog.push_back(lastCardOfPlayer1);
        packetOfLog.push_back(lastCardOfPlayer2);

        // std::cout << "lastCardOfPlayer1: " << lastCardOfPlayer1.num << ", " << lastCardOfPlayer1.shape << endl;
        // std::cout << "lastCardOfPlayer2: " << lastCardOfPlayer2.num << ", " << lastCardOfPlayer2.shape << endl;

        if ((lastCardOfPlayer1.num > lastCardOfPlayer2.num) || (lastCardOfPlayer1.num == 0 && lastCardOfPlayer2.num == 12))
        {
            // player 1 won
            player1Won = true;
            player2Won = false;
            player1.numOfWinning++;

            if (isDraw)
            {
                emptyPacketOfDraw(player1.packetOfWonsCards);
                isDraw = false;
            }
            player1.packetOfWonsCards.push_back(lastCardOfPlayer1);
            player1.packetOfWonsCards.push_back(lastCardOfPlayer2);
            thisTurnPlayer1.push_back(lastCardOfPlayer1);
            thisTurnPlayer2.push_back(lastCardOfPlayer2);
        }

        else if ((lastCardOfPlayer1.num < lastCardOfPlayer2.num) || (lastCardOfPlayer1.num == 12 && lastCardOfPlayer2.num == 0))
        {
            // player 2 won
            player2Won = true;
            player1Won = false;
            player2.numOfWinning++;

            if (isDraw)
            {
                emptyPacketOfDraw(player2.packetOfWonsCards);
                isDraw = false;
            }
            player2.packetOfWonsCards.push_back(lastCardOfPlayer1);
            player2.packetOfWonsCards.push_back(lastCardOfPlayer2);
            thisTurnPlayer1.push_back(lastCardOfPlayer1);
            thisTurnPlayer2.push_back(lastCardOfPlayer2);
        }

        if (lastCardOfPlayer1.num == lastCardOfPlayer2.num)
        {
            // draw
            isDraw = true;
            numOfDraw++;
            player1Won = false;
            player2Won = false;
            thisTurnPlayer1.push_back(lastCardOfPlayer1);
            thisTurnPlayer2.push_back(lastCardOfPlayer2);
            if (player1.packetOfCards.size())
            {
                unknownOfDraw1 = player1.packetOfCards[0];
                player1.packetOfCards.erase(player1.packetOfCards.begin());
                unknownOfDraw2 = player2.packetOfCards[0];
                player2.packetOfCards.erase(player2.packetOfCards.begin());

                // std::cout << "unknownOfDraw1: " << unknownOfDraw1.num << ", " << unknownOfDraw1.shape << endl;
                // std::cout << "unknownOfDraw2: " << unknownOfDraw2.num << ", " << unknownOfDraw2.shape << endl;

                packetOfDraw.push_back(lastCardOfPlayer1);
                packetOfDraw.push_back(lastCardOfPlayer2);
                packetOfDraw.push_back(unknownOfDraw1);
                packetOfDraw.push_back(unknownOfDraw2);
                playTurn();
            }
            else
            {
                while (packetOfDraw.size())
                {
                    player1.packetOfWonsCards.push_back(packetOfDraw[0]);
                    packetOfDraw.erase(packetOfDraw.begin());
                    player2.packetOfWonsCards.push_back(packetOfDraw[0]);
                    packetOfDraw.erase(packetOfDraw.begin());
                }
            }
        }
    }

    else if (isDraw)
    {
        std::cout << "*** TEST is draw ***" << endl;
        while (packetOfDraw.size())
        {
            player1.packetOfWonsCards.push_back(packetOfDraw[0]);
            packetOfDraw.erase(packetOfDraw.begin());
            player2.packetOfWonsCards.push_back(packetOfDraw[0]);
            packetOfDraw.erase(packetOfDraw.begin());
        }
        isDraw = false;
    }

    else
    {
        throw invalid_argument("There is no more cards");
    }
}

void ariel::Game::emptyPacketOfDraw(vector<Card> &deck)
{
    for (Card c : packetOfDraw)
    {
        deck.push_back(packetOfDraw[0]);
        packetOfDraw.erase(packetOfDraw.begin());
    }
}

void ariel::Game::printLastTurn()
{
    std::cout << "--------------------------------------------------" << endl;
    while (thisTurnPlayer2.size())
    {
        // std::cout << player1.name << " played " << thisTurnPlayer1[0].num << " of " << thisTurnPlayer1[0].shape << endl;
        // std::cout << player2.name << " played " << thisTurnPlayer2[0].num << " of " << thisTurnPlayer2[0].shape << endl;
        std::cout << player1.name << " played ";
        thisTurnPlayer1[0].printCard();
        std::cout << endl;
        std::cout << player2.name << " played ";
        thisTurnPlayer2[0].printCard();
        std::cout << endl;

        if (thisTurnPlayer1[0].num == thisTurnPlayer2[0].num)
        {
            std::cout << "Draw " << endl;
        }
        thisTurnPlayer1.erase(thisTurnPlayer1.begin());
        thisTurnPlayer2.erase(thisTurnPlayer2.begin());
    }
    if (player1Won)
    {
        std::cout << player1.name << " win." << endl;
    }
    if (player2Won)
    {
        std::cout << player2.name << " win." << endl;
    }
}

void ariel::Game::playAll()
{
    while (player1.packetOfCards.size())
    {
        playTurn();
    }
}
void ariel::Game::printWiner()
{
    std::cout << "--------------------------------------------------" << endl;
    if (player1.packetOfWonsCards.size() > player2.packetOfWonsCards.size())
    {
        std::cout << player1.name << " Won." << endl;
    }
    if (player1.packetOfWonsCards.size() < player2.packetOfWonsCards.size())
    {
        std::cout << player2.name << " Won." << endl;
    }
    if (player1.packetOfWonsCards.size() == player2.packetOfWonsCards.size())
    {
        std::cout << "Draw." << endl;
    }
}
void ariel::Game::printLog()
{
    std::cout << "--------------------------------------------------" << endl;
    bool draw = false;
    std::cout << "numOfTurns: " << numOfTurns << endl;

    Card cardOfPlayer1;
    Card cardOfPlayer2;

    for (int i = 1; i <= numOfTurns; i++)
    {
        if (!draw)
        {
            // i--;
            std::cout << "Turn " << i << ": " << endl;
        }

        Card cardOfPlayer1 = packetOfLog[0];
        Card cardOfPlayer2 = packetOfLog[1];

        std::cout << player1.name << " played with " << cardOfPlayer1.num << ", " << cardOfPlayer1.shape << endl;
        std::cout << player2.name << " played with " << cardOfPlayer2.num << ", " << cardOfPlayer2.shape << endl;
        if (cardOfPlayer1.num > cardOfPlayer2.num || (cardOfPlayer1.num == 0 && cardOfPlayer2.num == 13))
        {
            draw = false;
            std::cout << player1.name << " is winning." << endl;
            packetOfLog.erase(packetOfLog.begin());
            packetOfLog.erase(packetOfLog.begin());
        }
        else if (cardOfPlayer1.num < cardOfPlayer2.num || (cardOfPlayer1.num == 13 && cardOfPlayer2.num == 0))
        {
            draw = false;
            std::cout << player2.name << " is winning." << endl;
            packetOfLog.erase(packetOfLog.begin());
            packetOfLog.erase(packetOfLog.begin());
        }
        while (packetOfLog.size() && (packetOfLog[0].num == packetOfLog[1].num))
        {
            if (!draw)
            {
                i++;
                std::cout << "Turn " << i << ": " << endl;
                std::cout << player1.name << " played with " << packetOfLog[0].num << ", " << packetOfLog[0].shape << endl;
                std::cout << player2.name << " played with " << packetOfLog[1].num << ", " << packetOfLog[1].shape << endl;
            }
            std::cout << "Draw." << endl;
            packetOfLog.erase(packetOfLog.begin());
            packetOfLog.erase(packetOfLog.begin());
            if (draw)
            {
                std::cout << player1.name << " played with " << packetOfLog[0].num << ", " << packetOfLog[0].shape << endl;
                std::cout << player2.name << " played with " << packetOfLog[1].num << ", " << packetOfLog[1].shape << endl;
            }
            draw = true;
            i--;
        }
    }
}
void ariel::Game::printStats()
{
    std::cout << "--------------------------------------------------" << endl;
    std::cout << player1.name << " Won " << (double)player1.numOfWinning / (double)numOfTurns << endl;
    std::cout << player2.name << " Won " << (double)player2.numOfWinning / (double)numOfTurns << endl;
    std::cout << "The cards which " << player1.name << " won: " << endl;
    for (Card c : player1.packetOfWonsCards)
    {
        std::cout << "Num: " << c.num << " "
                  << "Shape: " << c.shape << endl;
    }
    std::cout << "The cards which " << player2.name << " won: " << endl;
    for (Card c : player2.packetOfWonsCards)
    {
        std::cout << "Num: " << c.num << " "
                  << "Shape: " << c.shape << endl;
    }
    std::cout << "Rate of draw: " << (double)numOfDraw / (double)numOfTurns << endl;
}
