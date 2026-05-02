#pragma once
#include <string>
#include "Piece.h"
using namespace std;

class Player
{
public:
    string name;
    Piece *piece;
    Player(string n, Piece *p) : name(n), piece(p) {};
};