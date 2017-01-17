#include <iostream>
#include "board.h"
#include "vector"
#include <random>
#include <ctime>
#include "quickfindunionfind.h"
#include <limits>
#include "quickunionunionfind.h"


using namespace std;


/* if the boar is 9 x 9, it looks like this:


0   1   2   3   4   5   6   7   8

  9   10  11  12  13  14  15  16  17

    18  19  20  21  22  23  24  25  26

      27  28  29  30  31  32  33  34  35

        36  37  38  39  40  41  42  43  44

          45  46  47  48  49  50  51  52  53

            54  55  56  57  58  59  60  61  62

              63  64  65  66  67  68  69  70  71

                72  73  74  75  76  77  78  79  80

*/

Board b;
int MiniMax(Board b);
int playerTurn = MaximizingPlayer;
double monteCarlo(Board b, int playerTurn);
int minMove(Board b, int* Move);
int maxMove(Board b, int* Move);


int main()
{
    while(true)
    {
        b.Print();
        if(b.hasWinner() == 3 || b.hasWinner() == 4)
        {
            std::cout << "game over"<<std::endl;
            break;
        }
        int x = 0;
        std::cout << "input row: "<<std::endl;
        cin >> x;
        int y = 0;
        std::cout << "input column: "<<std::endl;
        cin >> y;
        if(b.getCell(x*SIZE+y) != 0)
        {
            std::cout << "field not empty, try again." <<std::endl;
            continue;
        }
        b.placeMove(x,y,3);
        b.nextPlayerTurn();
        if(b.hasWinner() == -1)
        {
            std::cout << "LOADING..."<< std::endl;

            b.placeMove(MiniMax(b),4);
            b.Print();
            b.nextPlayerTurn();
        }
        else
        {
            cout << "congrats, you won!" << endl;
        }
    }
}

int EvalueateStaticPosition(Board b)
{
    if(b.hasWinner() == MaximizingPlayer)
        return 10;
    if(b.hasWinner() == MinimazingPlayer)
        return -10;
}

void retractMove(Board b, int move)
{
    b.undoMove(move);
}

int minMove(Board b, int* bestMove)
{
    if(b.hasWinner() != -1)
    {
        return EvalueateStaticPosition(b);
    }
    vector<int> movelists = b.getEmptyCells();


    int nMoves = movelists.size();
    int v = std::numeric_limits<int>::max();
    for(int i = 0; i < nMoves;i++)
    {
        int move = movelists.at(i);
        b.placeMove(move, 4);
        b.nextPlayerTurn();
        int curRating = maxMove(b, bestMove);
        if(curRating < v)
        {
            v = curRating;
            *bestMove = move;
        }
        retractMove(b,move);
    }
    return v;
}

int maxMove(Board b, int* bestMove)
{
    if(b.hasWinner() != -1)
    {
        return EvalueateStaticPosition(b);
    }

    vector<int> movelists = b.getEmptyCells();
    int nMoves = movelists.size();
    int v = std::numeric_limits<int>::min();
    for(int i = 0; i < nMoves;i++)
    {
        int move = movelists.at(i);
        b.placeMove(move, 3);
        b.nextPlayerTurn();
        int curRating = minMove(b, bestMove);
        if(curRating > v)
        {
            v = curRating;
            *bestMove = move;
        }
        retractMove(b,move);
    }
    return v;
}

int MiniMax(Board b)
{
    int bestMove = 0;
    //int bestScore = std::numeric_limits<int>::min();
    int bestScore = 0;
    if(b.GetPlayerTurn() == MaximizingPlayer)
        bestScore = maxMove(b, &bestMove);
    if(b.GetPlayerTurn() == MinimazingPlayer)
        bestScore = minMove(b, &bestMove);
    //std:cout << "bestScore is " << bestScore << std::endl;
    return bestMove;
}

/*
double monteCarlo(Board board, int player)//vult het bord met willekeurig geplaatste stukken van de maximizing en minimizing speler
{
    std::cout << "carlo begint"<<std::endl;
    //loop inhoud van montecarlo 1000 keer, hou bij hoe vaak elke speler wint.
    int maximizerWins = 0;
    int minimizerWins = 0;
    std::vector<int> emptyCells;

    for(int i = 0; i < 1;i++)
    {
        srand(time(NULL));
        emptyCells = board.getEmptyCells();

        bool alternate;
        if(board.GetPlayerTurn() == 3)
            alternate = false;
        else
            alternate = true;

        cout << "voor check in mont"<<endl;
        while(board.hasWinner() == -1)
        {
            int x = rand() % emptyCells.size();
            if(alternate)
                board.placeMove(emptyCells.at(x),3);
            else
                board.placeMove(emptyCells.at(x),4);
            alternate = !alternate;
            emptyCells.erase(emptyCells.begin() + (x));//haalt de gevulde index uit de vector met lege indexes

        }
        cout << "na check" << endl;
        cout << "check twee" << endl;
        if(board.hasWinner() != -1)
        {
            std::cout << "pff"<<std::endl;
            std::cout << "de winnaar is " << board.hasWinner() << "."<<std::endl;
            board.Print();

            if(EvalueateStaticPosition(board) == 3)
            {
                cout << "max";
                maximizerWins++;
            }
            else if(EvalueateStaticPosition(board) == 4)
            {
                cout << "min";
                minimizerWins++;
            }
        }
        cout << "na twee"<<endl;
        board.clear();
    }
    std::cout << "carlo eindigt"<<std::endl;
    return maximizerWins / minimizerWins ;
}*/





