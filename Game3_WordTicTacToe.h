#ifndef GAME3_WORDTICTACTOE_H
#define GAME3_WORDTICTACTOE_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

vector<string> dictionary;

void loadDictionary() {
    ifstream file("dic.txt");
    string word;
    while (file >> word) {
        dictionary.push_back(word);
    }
    file.close();
}

template <typename T>
class WordTicTacToe_Board : public Board<T> {
public:
    WordTicTacToe_Board() : Board<T>(3, 3) {
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
            string word = "";
            for (int j = 0; j < this->columns; j++) {
                word += this->board[i][j];
            }
            if (find(dictionary.begin(), dictionary.end(), word) != dictionary.end() && word != "   ") {
                return true;
            }
        }

        // Check columns
        for (int j = 0; j < this->columns; j++) {
            string word = "";
            for (int i = 0; i < this->rows; i++) {
                word += this->board[i][j];
            }
            if (find(dictionary.begin(), dictionary.end(), word) != dictionary.end() && word != "   ") {
                return true;
            }
        }

        // Check diagonals
        string diag1 = "";
        diag1 += this->board[0][0];
        diag1 += this->board[1][1];
        diag1 += this->board[2][2];
        if (find(dictionary.begin(), dictionary.end(), diag1) != dictionary.end() && diag1 != "   ") {
            return true;
        }

        string diag2 = "";
        diag2 += this->board[0][2];
        diag2 += this->board[1][1];
        diag2 += this->board[2][0];
        if (find(dictionary.begin(), dictionary.end(), diag2) != dictionary.end() && diag2 != "   ") {
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
class WordTicTacToe_Player : public Player<T> {
public:
    WordTicTacToe_Player(string name, T symbol) : Player<T>(name, symbol) {}

    void get_move(int& x, int& y) override {
        char letter;
        cout << this->get_name() << ", enter row (0-2), column (0-2) and letter: ";
        cin >> x >> y >> letter;
        this->symbol = letter;
    }
};

void runWordGame() {
    cout << "\n=== Word Tic-tac-toe ===" << endl;
    loadDictionary();

    WordTicTacToe_Board<char>* board = new WordTicTacToe_Board<char>();

    string name1, name2;
    cout << "Enter Player 1 name: ";
    cin >> name1;
    cout << "Enter Player 2 name: ";
    cin >> name2;

    WordTicTacToe_Player<char> player1(name1, ' ');
    WordTicTacToe_Player<char> player2(name2, ' ');

    GameManager<char> game(board, &player1, &player2);
    game.run();

    delete board;
}

#endif