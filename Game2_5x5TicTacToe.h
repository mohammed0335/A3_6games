#ifndef GAME2_5X5TICTACTOE_H
#define GAME2_5X5TICTACTOE_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cctype>
using namespace std;

template <typename T>
class FiveXFive_Board : public Board<T> {
public:
    FiveXFive_Board() : Board<T>(5, 5) {
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                this->board[i][j] = ' ';
            }
        }
    }

    bool update_board(int x, int y, T symbol) override {
        if (x < 0 || x >= this->rows || y < 0 || y >= this->columns || this->board[x][y] != ' ') {
            return false;
        }
        this->board[x][y] = symbol;
        this->n_moves++;
        return true;
    }

    void display_board() override {
        cout << "\n  ";
        for (int j = 0; j < this->columns; j++) {
            cout << " " << j << " ";
        }
        cout << "\n";

        for (int i = 0; i < this->rows; i++) {
            cout << i << " ";
            for (int j = 0; j < this->columns; j++) {
                cout << " " << this->board[i][j] << " ";
            }
            cout << "\n";
        }
        cout << endl;
    }

    bool is_win() override {
        // Check rows
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns - 2; j++) {
                if (this->board[i][j] != ' ' &&
                    this->board[i][j] == this->board[i][j+1] &&
                    this->board[i][j] == this->board[i][j+2]) {
                    return true;
                }
            }
        }

        // Check columns
        for (int j = 0; j < this->columns; j++) {
            for (int i = 0; i < this->rows - 2; i++) {
                if (this->board[i][j] != ' ' &&
                    this->board[i][j] == this->board[i+1][j] &&
                    this->board[i][j] == this->board[i+2][j]) {
                    return true;
                }
            }
        }

        // Check diagonals
        for (int i = 0; i < this->rows - 2; i++) {
            for (int j = 0; j < this->columns - 2; j++) {
                if (this->board[i][j] != ' ' &&
                    this->board[i][j] == this->board[i+1][j+1] &&
                    this->board[i][j] == this->board[i+2][j+2]) {
                    return true;
                }
            }
        }

        for (int i = 0; i < this->rows - 2; i++) {
            for (int j = 2; j < this->columns; j++) {
                if (this->board[i][j] != ' ' &&
                    this->board[i][j] == this->board[i+1][j-1] &&
                    this->board[i][j] == this->board[i+2][j-2]) {
                    return true;
                }
            }
        }

        return false;
    }

    bool is_draw() override {
        return this->n_moves == this->rows * this->columns;
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }
};

template <typename T>
class FiveXFive_Player : public Player<T> {
public:
    FiveXFive_Player(string name, T symbol) : Player<T>(name, symbol) {}

    void get_move(int& x, int& y) override {
        cout << this->get_name() << ", enter row and column (0-4): ";
        cin >> x >> y;
    }
};

void run5x5Game() {
    cout << "\n=== 5x5 Tic Tac Toe ===" << endl;

    FiveXFive_Board<char>* board = new FiveXFive_Board<char>();

    string name1, name2;
    cout << "Enter Player 1 name: ";
    cin >> name1;
    cout << "Enter Player 2 name: ";
    cin >> name2;

    FiveXFive_Player<char> player1(name1, 'X');
    FiveXFive_Player<char> player2(name2, 'O');

    GameManager<char> game(board, &player1, &player2);
    game.run();

    delete board;
}

#endif