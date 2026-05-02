#pragma once
#include <iostream>
#include <string>
using namespace std;

enum PieceType
{
    X,
    O
};

class Piece
{
public:
    PieceType piece;
    Piece(PieceType p) : piece(p) {};
    PieceType getPiece()
    {
        return piece;
    }
    string getPieceString()
    {
        switch (piece)
        {
        case X:
            return "X";
        case O:
            return "O";
        default:
            return "?";
        }
    }
};