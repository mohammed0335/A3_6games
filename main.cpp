#include <iostream>
#include <cstdlib>
#include <ctime>
#include "BoardGame_Classes.h"
#include "Game1_FourInRow.h"
#include "Game2_5x5TicTacToe.h"
#include "Game3_WordTicTacToe.h"
#include "Game4_Numerical.h"
#include "Game5_Misere.h"
#include "Game6_4x4TicTacToe.h"

using namespace std;

void displayMenu() {
    cout << "\n==========================================" << endl;
    cout << "    Games " << endl;
    cout << "     Part 2 Submission - 6 Games" << endl;
    cout << "==========================================" << endl;
    cout << "1. Four-in-a-row" << endl;
    cout << "2. 5x5 Tic Tac Toe" << endl;
    cout << "3. Word Tic-tac-toe" << endl;
    cout << "4. Numerical Tic-Tac-Toe" << endl;
    cout << "5. Misère Tic Tac Toe" << endl;
    cout << "6. 4x4 Tic-Tac-Toe" << endl;
    cout << "7. Exit" << endl;
    cout << "==========================================" << endl;
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    int choice;

    cout << "Welcome " << endl;
    cout << "CS213 - Object Oriented Programming" << endl;

    do {
        displayMenu();
        cout << "Enter your choice (1-7): ";
        cin >> choice;

        switch(choice) {
            case 1:
                runFourInRowGame();
                break;
            case 2:
                run5x5Game();
                break;
            case 3:
                runWordGame();
                break;
            case 4:
                runNumericalGame();
                break;
            case 5:
                runMisereGame();
                break;
            case 6:
                run4x4Game();
                break;
            case 7:
                cout << "Thank you for playing!" << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }

        if (choice != 7) {
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
    } while (choice != 7);

    return 0;
}
