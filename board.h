#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <iostream>     // std::cout
#include <algorithm>    // std::merge, std::sort
#include <set>
#include <vector>
#include <quickunionunionfind.h>
#define SIZE 4
#define MaximizingPlayer 3
#define MinimazingPlayer 4

using namespace std;

class Board
{

private:
    QuickUnionUnionFind *quuf = new QuickUnionUnionFind(SIZE*SIZE);
    int board[SIZE*SIZE];
    int PlayerTurn = MaximizingPlayer;

public:
    Board();
    void clear();
    int GetPlayerTurn();
    vector<int> getEmptyCells();
    void nextPlayerTurn();
    void undoMove(int i);
    int threeWon();
    int fourWon();
    void undoMove(int i, int j);
    bool hasEmptyCells();
    int getCell(int x, int y);
    int getCell(int x);
    int hasWinner();
    void Print();
    void placeMove(int x, int y, int player);
    void placeMove(int x, int player);
};

#endif // BOARD_H
