#pragma once
#include <string>
using namespace std;

enum Num {two, three, four, five, six, seven, eight, nine, ten, jack, queen, king, ace};
enum Shape {spaders, hearts, diamonds, clubs}; 

class Card{

public:
    Num num;
    Shape shape;

    Card();
    Card(Num num, Shape shape);

};