#pragma once
#include <iostream>
#include <vector>
#include "Piece.h"
using namespace std;

class Board
{
public:
    int size;
    vector<vector<Piece *>> grid;

    Board(int s) : size(s), grid(s, vector<Piece *>(s, nullptr))
    {
    }

    bool addPiece(int row, int col, Piece *p)
    {
        if (grid[row][col] != nullptr)
        {
            return false;
        }
        grid[row][col] = p;
        return true;
    }

    void printBoard()
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (grid[i][j] == nullptr)
                {
                    cout << "   ";
                }
                else
                {
                    cout << " " << (grid[i][j]->getPieceString()) << " ";
                }
                cout << "|";
            }
            cout << endl;
        }
    }

    bool isFull()
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (grid[i][j] == nullptr)
                    return false;
            }
        }
        return true;
    }

    bool addPiece(int row, int col, PieceType p)
    {
        cout << "Adding piece " << p << " at (" << row << ", " << col << ")\n";
        if (grid[row][col] != nullptr)
        {
            return false;
        }
        grid[row][col] = new Piece(p);
        return true;
    }

    bool checkWin()
    {
        // Check rows
        for (int i = 0; i < size; i++)
        {
            if (grid[i][0] != nullptr && grid[i][1] != nullptr && grid[i][2] != nullptr &&
                grid[i][0]->getPiece() == grid[i][1]->getPiece() && grid[i][1]->getPiece() == grid[i][2]->getPiece())
            {
                return true;
            }
        }

        // Check columns
        for (int j = 0; j < size; j++)
        {
            if (grid[0][j] != nullptr && grid[1][j] != nullptr && grid[2][j] != nullptr &&
                grid[0][j]->getPiece() == grid[1][j]->getPiece() && grid[1][j]->getPiece() == grid[2][j]->getPiece())
            {
                return true;
            }
        }

        // Check diagonals
        if (grid[0][0] != nullptr && grid[1][1] != nullptr && grid[2][2] != nullptr &&
            grid[0][0]->getPiece() == grid[1][1]->getPiece() && grid[1][1]->getPiece() == grid[2][2]->getPiece())
        {
            return true;
        }
        if (grid[0][2] != nullptr && grid[1][1] != nullptr && grid[2][0] != nullptr &&
            grid[0][2]->getPiece() == grid[1][1]->getPiece() && grid[1][1]->getPiece() == grid[2][0]->getPiece())
        {
            return true;
        }

        return false;
    }
};
