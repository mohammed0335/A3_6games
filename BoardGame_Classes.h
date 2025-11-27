#ifndef BOARDGAME_CLASSES_H
#define BOARDGAME_CLASSES_H

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

template <typename T>
class Board {
protected:
    int rows, columns;
    T** board;
    int n_moves = 0;
public:
    Board(int r, int c) : rows(r), columns(c) {
        board = new T*[rows];
        for (int i = 0; i < rows; i++) {
            board[i] = new T[columns];
        }
    }

    virtual ~Board() {
        for (int i = 0; i < rows; i++) {
            delete[] board[i];
        }
        delete[] board;
    }

    virtual bool update_board(int x, int y, T symbol) = 0;
    virtual void display_board() = 0;
    virtual bool is_win() = 0;
    virtual bool is_draw() = 0;
    virtual bool game_is_over() = 0;

    int get_rows() { return rows; }
    int get_columns() { return columns; }
    int get_n_moves() { return n_moves; }
};

template <typename T>
class Player {
protected:
    string name;
    T symbol;
    Board<T>* boardPtr;
public:
    Player(string n, T s) : name(n), symbol(s), boardPtr(nullptr) {}

    virtual void get_move(int& x, int& y) = 0;

    string get_name() { return name; }
    T get_symbol() { return symbol; }
    void set_board(Board<T>* b) { boardPtr = b; }
    Board<T>* get_board() { return boardPtr; }
};

template <typename T>
class RandomPlayer : public Player<T> {
protected:
    int dimension;
public:
    RandomPlayer(string n, T s) : Player<T>(n, s), dimension(3) {}

    void get_move(int& x, int& y) override {
        x = rand() % dimension;
        y = rand() % dimension;
    }
};

template <typename T>
class GameManager {
private:
    Board<T>* boardPtr;
    Player<T>* players[2];
public:
    GameManager(Board<T>* b, Player<T>* p1, Player<T>* p2) : boardPtr(b) {
        players[0] = p1;
        players[1] = p2;
        p1->set_board(b);
        p2->set_board(b);
    }

    void run() {
        boardPtr->display_board();

        while (!boardPtr->game_is_over()) {
            for (int i = 0; i < 2; i++) {
                int x, y;
                players[i]->get_move(x, y);

                while (!boardPtr->update_board(x, y, players[i]->get_symbol())) {
                    cout << "Invalid move! Try again." << endl;
                    players[i]->get_move(x, y);
                }

                boardPtr->display_board();

                if (boardPtr->is_win()) {
                    cout << players[i]->get_name() << " wins!" << endl;
                    return;
                }

                if (boardPtr->is_draw()) {
                    cout << "Draw!" << endl;
                    return;
                }
            }
        }
    }
};

#endif