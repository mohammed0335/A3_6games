#ifndef GAME5_MISERE_H
#define GAME5_MISERE_H

#include "BoardGame_Classes.h"
using namespace std;

template <typename T>
class Misere_Board : public Board<T> {
public:
    Misere_Board() : Board<T>(3, 3) {
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
            if (this->board[i][0] != ' ' &&
                this->board[i][0] == this->board[i][1] &&
                this->board[i][1] == this->board[i][2]) {
                return true;
            }
        }

        // Check columns
        for (int j = 0; j < this->columns; j++) {
            if (this->board[0][j] != ' ' &&
                this->board[0][j] == this->board[1][j] &&
                this->board[1][j] == this->board[2][j]) {
                return true;
            }
        }

        // Check diagonals
        if (this->board[0][0] != ' ' &&
            this->board[0][0] == this->board[1][1] &&
            this->board[1][1] == this->board[2][2]) {
            return true;
        }

        if (this->board[0][2] != ' ' &&
            this->board[0][2] == this->board[1][1] &&
            this->board[1][1] == this->board[2][0]) {
            return true;
        }

        return false;
    }

    bool is_draw() override {
        return this->n_moves == this->rows * this->columns && !is_win();
    }

    bool game_is_over() override {
        return is_win() || is_draw();
    }
};

template <typename T>
class Misere_Player : public Player<T> {
public:
    Misere_Player(string name, T symbol) : Player<T>(name, symbol) {}

    void get_move(int& x, int& y) override {
        cout << this->get_name() << ", enter row and column (0-2): ";
        cin >> x >> y;
    }
};

void runMisereGame() {
    cout << "\n=== Misère Tic Tac Toe ===" << endl;
    cout << "Warning: The player who makes 3 in a row LOSES!" << endl;

    Misere_Board<char>* board = new Misere_Board<char>();

    string name1, name2;
    cout << "Enter Player 1 name: ";
    cin >> name1;
    cout << "Enter Player 2 name: ";
    cin >> name2;

    Misere_Player<char> player1(name1, 'X');
    Misere_Player<char> player2(name2, 'O');

    GameManager<char> game(board, &player1, &player2);
    game.run();

    // In Misere, the winner is the one who didn't make 3 in a row
    if (board->is_win()) {
        // The last player to move lost
        cout << "The last player lost! The other player wins!" << endl;
    }

    delete board;
}

#endif