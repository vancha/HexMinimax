#include <iostream>
#include "board.h"
#include "vector"
#include <random>
#include <ctime>
#include "quickfindunionfind.h"
#include <limits>
#include "quickunionunionfind.h"


using namespace std;


/**

0   1   2   3   4   5   6   7   8

  9   10  11  12  13  14  15  16  17

    18  19  20  21  22  23  24  25  26

      27  28  29  30  31  32  33  34  35

        36  37  38  39  40  41  42  43  44

          45  46  47  48  49  50  51  52  53

            54  55  56  57  58  59  60  61  62

              63  64  65  66  67  68  69  70  71

                72  73  74  75  76  77  78  79  80

**/

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
        if(b.hasWinner() == 3 || b.hasWinner() == 4)
        {
            std::cout << "game over"<<std::endl;
            break;
        }
        int x = 0;
        std::cout << "place your move(row first, column will be asked for next"<<std::endl;
        cin >> x;
        int y = 0;
        std::cout << "place your move(column now"<<std::endl;
        cin >> y;
        std::cout << "current value is : "<< b.getCell(x*SIZE+y);
        if(b.getCell(x*SIZE+y) != 0)
        {
            std::cout << "field not empty, try again. row:" <<std::endl;
            continue;
        }
        b.placeMove(x,y,3);
        b.nextPlayerTurn();
        b.placeMove(MiniMax(b),4);
        b.Print();
        b.nextPlayerTurn();
       // b.Print();
    }
    std::cout << b.hasWinner() << std::endl;

    //std::cout << "result:" << monteCarlo(b,3) << std::endl;
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
    std::cout << "minmove" << std::endl;
    if(b.hasWinner() != -1)
    {
        std::cout << "win" << std::endl;
        return EvalueateStaticPosition(b);
    }
    std::cout << "make move list" << std::endl;
    vector<int> movelists = b.getEmptyCells();


    int nMoves = movelists.size();
    std::cout << "moves: " << nMoves << std::endl;
    int v = std::numeric_limits<int>::max();
    std::cout << "before for" << std::endl;
    for(int i = 0; i < nMoves;i++)
    {
        int move = movelists.at(i);
        b.placeMove(move, 4);
        //int opponentsBestMove = 0;
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
    std:cout << "maxmove" << std::endl;
    if(b.hasWinner() != -1)//als er een winnaar is
    {
        return EvalueateStaticPosition(b);//return -10 if minimizing player wins, 10 for maximizing player
    }

    vector<int> movelists = b.getEmptyCells();
    int nMoves = movelists.size();
    std::cout << "moves: " << nMoves << std::endl;
    int v = std::numeric_limits<int>::min();
    for(int i = 0; i < nMoves;i++)
    {
        int move = movelists.at(i);
        b.placeMove(move, 3);
        //int opponentsBestMove = 0;
        b.nextPlayerTurn();
        int curRating = minMove(b, bestMove);
        if(curRating > v)
        {
            v = curRating;
            *bestMove = move;
        }
        retractMove(b,move);//zet de ingevulde waarde van het bord weer op 0;
    }
    //delete movelists;
    return v;
}
/* MiniMax(Board)
best.mv= [not yet defined]
best.score= -9999
For each legal move m
{
    make move m.mv on Board
    m.score = MIN
    if (m.score>best.score)then best=m
    retract move m.mv
    on Board
}
Make move best.mv
*/

int MiniMax(Board b)
{
    int bestMove = 0;
    int bestScore = std::numeric_limits<int>::min();
    /*for(int m : b.getEmptyCells())
    {
        b.placeMove(m, 4);
        bestScore = minMove(b,&bestMove);
        //if(bestScore )
    }*/
    if(b.GetPlayerTurn() == MaximizingPlayer)
        bestScore = maxMove(b, &bestMove);
    if(b.GetPlayerTurn() == MinimazingPlayer)
        bestScore = minMove(b, &bestMove);
    std:cout << "bestScore is " << bestScore << std::endl;
    return bestMove;
}

///
/// \brief monteCarlo
/// \param b
/// \return aantal gewonnen gesimuleerde matches van speler die aan beurt is min die van de tegenstander gedeeld door aantal gesimuleerde matches.
///
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
}





