cmake_minimum_required(VERSION 4.0)
project(untitled12)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled12 main.cpp
        BoardGame_Classes.h
        Game1_FourInRow.h
        Game2_5x5TicTacToe.h
        Game3_WordTicTacToe.h
        Game4_Numerical.h
        Game5_Misere.h
        Game6_4x4TicTacToe.h)
