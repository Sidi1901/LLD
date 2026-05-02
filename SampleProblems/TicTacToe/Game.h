#include <bits/stdc++.h>
#include "Player.h"
#include "Board.h"
using namespace std;

class Game
{
public:
    queue<Player *> players;
    Board *board;

    Game()
    {
        board = new Board(3);

        Player *p1 = new Player("Player1", new Piece(PieceType::X));
        Player *p2 = new Player("Player2", new Piece(PieceType::O));

        players.push(p1);
        players.push(p2);
    }

    string startGame()
    {
        string result = "";
        while (result == "")
        {
            Player *cur = players.front();
            players.pop();

            board->printBoard();

            if (board->isFull())
            {
                result = "draw";
                cout << "\n--Game is a draw--\n";
                return result;
            }
            cout << "--- " << cur->name << "'s turn ---" << endl;
            bool isValidMove = false;
            while (!isValidMove)
            {
                cout << "Enter row: ";
                int row;
                cin >> row;
                cout << "Enter col: ";
                int col;
                cin >> col;

                if (!board->addPiece(row, col, cur->piece->getPiece()))
                {
                    cout << "Invalid move. Try again.\n";
                }
                else
                {
                    isValidMove = true;
                    if (board->checkWin())
                    {
                        result = cur->name + " wins!";
                        cout << "\n--" << result << "--\n";
                        return result;
                    }

                    players.push(cur);
                }
            }
        }

        return result;
    }
};