
#include "player.hpp"

Player::Player(){}

Player::Player(std::string name)
{
    this->name = name;
}

int Player::stacksize()
{
    return packetOfCards.size();
}

int Player::cardesTaken()
{
    return packetOfWonsCards.size();
}
