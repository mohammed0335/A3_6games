#ifndef GAME4_NUMERICAL_H
#define GAME4_NUMERICAL_H

#include "BoardGame_Classes.h"
#include <vector>
#include <algorithm>
using namespace std;

vector<int> player1_numbers = {1, 3, 5, 7, 9};
vector<int> player2_numbers = {2, 4, 6, 8};

template <typename T>
class Numerical_Board : public Board<T> {
public:
    Numerical_Board() : Board<T>(3, 3) {
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->columns; j++) {
                this->board[i][j] = 0;
            }
        }
    }

    bool update_board(int x, int y, T symbol) override {
        if (x < 0 || x >= this->rows || y < 0 || y >= this->columns || this->board[x][y] != 0) {
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
                if (this->board[i][j] == 0) {
                    cout << " . ";
                } else {
                    cout << " " << this->board[i][j] << " ";
                }
            }
            cout << "\n";
        }
        cout << endl;
    }

    bool is_win() override {
        // Check rows
        for (int i = 0; i < this->rows; i++) {
            if (this->board[i][0] + this->board[i][1] + this->board[i][2] == 15 &&
                this->board[i][0] != 0 && this->board[i][1] != 0 && this->board[i][2] != 0) {
                return true;
            }
        }

        // Check columns
        for (int j = 0; j < this->columns; j++) {
            if (this->board[0][j] + this->board[1][j] + this->board[2][j] == 15 &&
                this->board[0][j] != 0 && this->board[1][j] != 0 && this->board[2][j] != 0) {
                return true;
            }
        }

        // Check diagonals
        if (this->board[0][0] + this->board[1][1] + this->board[2][2] == 15 &&
            this->board[0][0] != 0 && this->board[1][1] != 0 && this->board[2][2] != 0) {
            return true;
        }

        if (this->board[0][2] + this->board[1][1] + this->board[2][0] == 15 &&
            this->board[0][2] != 0 && this->board[1][1] != 0 && this->board[2][0] != 0) {
            return true;
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
class Numerical_Player : public Player<T> {
private:
    vector<int>& available_numbers;
public:
    Numerical_Player(string name, vector<int>& numbers) : Player<T>(name, 0), available_numbers(numbers) {}

    void get_move(int& x, int& y) override {
        int number;
        cout << this->get_name() << ", enter row (0-2), column (0-2) and number: ";
        cin >> x >> y >> number;

        auto it = find(available_numbers.begin(), available_numbers.end(), number);
        if (it != available_numbers.end()) {
            this->symbol = number;
            available_numbers.erase(it);
        } else {
            cout << "Invalid number! Choose from your available numbers." << endl;
            get_move(x, y);
        }
    }
};

void runNumericalGame() {
    cout << "\n=== Numerical Tic-Tac-Toe ===" << endl;

    Numerical_Board<int>* board = new Numerical_Board<int>();

    string name1, name2;
    cout << "Enter Player 1 (odd numbers) name: ";
    cin >> name1;
    cout << "Enter Player 2 (even numbers) name: ";
    cin >> name2;

    Numerical_Player<int> player1(name1, player1_numbers);
    Numerical_Player<int> player2(name2, player2_numbers);

    GameManager<int> game(board, &player1, &player2);
    game.run();

    delete board;
}

#endif