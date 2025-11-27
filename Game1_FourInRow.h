#ifndef GAME1_FOURINROW_H
#define GAME1_FOURINROW_H

#include "BoardGame_Classes.h"
#include <algorithm>
using namespace std;

template <typename T>
class FourInRow_Board : public Board<T> {
public:
    FourInRow_Board() : Board<T>(6, 7) {
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                this->board[i][j] = ' ';
            }
        }
    }

    bool update_board(int x, int y, T symbol) override {
        if (y < 0 || y >= this->columns) return false;

        for (int i = this->rows - 1; i >= 0; i--) {
            if (this->board[i][y] == ' ') {
                this->board[i][y] = symbol;
                this->n_moves++;
                return true;
            }
        }
        return false;
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
        
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns - 3; j++) {
                if (this->board[i][j] != ' ' &&
                    this->board[i][j] == this->board[i][j+1] &&
                    this->board[i][j] == this->board[i][j+2] &&
                    this->board[i][j] == this->board[i][j+3]) {
                    return true;
                }
            }
        }

        
        for (int i = 0; i < this->rows - 3; i++) {
            for (int j = 0; j < this->columns; j++) {
                if (this->board[i][j] != ' ' &&
                    this->board[i][j] == this->board[i+1][j] &&
                    this->board[i][j] == this->board[i+2][j] &&
                    this->board[i][j] == this->board[i+3][j]) {
                    return true;
                }
            }
        }

        
        for (int i = 0; i < this->rows - 3; i++) {
            for (int j = 0; j < this->columns - 3; j++) {
                if (this->board[i][j] != ' ' &&
                    this->board[i][j] == this->board[i+1][j+1] &&
                    this->board[i][j] == this->board[i+2][j+2] &&
                    this->board[i][j] == this->board[i+3][j+3]) {
                    return true;
                }
            }
        }

        for (int i = 0; i < this->rows - 3; i++) {
            for (int j = 3; j < this->columns; j++) {
                if (this->board[i][j] != ' ' &&
                    this->board[i][j] == this->board[i+1][j-1] &&
                    this->board[i][j] == this->board[i+2][j-2] &&
                    this->board[i][j] == this->board[i+3][j-3]) {
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
class FourInRow_Player : public Player<T> {
public:
    FourInRow_Player(string name, T symbol) : Player<T>(name, symbol) {}

    void get_move(int& x, int& y) override {
        cout << this->get_name() << ", enter column (0-6): ";
        cin >> y;
        x = 0;
    }
};

void runFourInRowGame() {
    cout << "\n= Four-in-a-row Game " << endl;

    FourInRow_Board<char>* board = new FourInRow_Board<char>();

    string name1, name2;
    cout << "Enter Player 1 name: ";
    cin >> name1;
    cout << "Enter Player 2 name: ";
    cin >> name2;

    FourInRow_Player<char> player1(name1, 'X');
    FourInRow_Player<char> player2(name2, 'O');

    GameManager<char> game(board, &player1, &player2);
    game.run();

    delete board;
}

#endif
