#include "card.hpp"
#include <string.h>
#include <string>
#include <iostream>

Card::Card() {}

Card::Card(Num num, Shape shape)
{
    num = num;
    shape = shape;
}

void Card::printCard()
{
    string numString;
    string shapeString;

    switch (this->num)
    {
    case two:
        numString = "two";
        break;
    case three:
        numString = "three";
        break;
    case four:
        numString = "four";
        break;
    case five:
        numString = "five";
        break;
    case six:
        numString = "six";
        break;
    case seven:
        numString = "seven";
        break;
    case eight:
        numString = "eight";
        break;
    case nine:
        numString = "nine";
        break;
    case ten:
        numString = "ten";
        break;
    case jack:
        numString = "jack";
        break;
    case queen:
        numString = "queen";
        break;
    case king:
        numString = "king";
        break;
    case ace:
        numString = "ace";
        break;
    }

    switch (this->shape) {
        case spaders:
            shapeString = "spaders";
            break;
        case hearts:
            shapeString = "hearts";
            break;
        case diamonds:
            shapeString = "diamonds";
            break;
        case clubs:
            shapeString = "clubs";
            break;
    }

    // Print the card
    std::cout << numString << " of " << shapeString << endl;
}