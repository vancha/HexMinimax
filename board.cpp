
#include "board.h"
#include <stdlib.h>     /* exit, EXIT_FAILURE */

Board::Board()
{
    for (int q = 0; q < SIZE; q++)
    {
        for (int t = 0; t < SIZE; t++)
        {
            board[q * SIZE + t] = 0;
        }
    }
}
void Board::clear()
{
    for(int i = 0; i < SIZE*SIZE;i++)
    {
        board[i] = 0;
    }
}

void Board::Print()
{
    std::cout << std::endl <<  "        3"<<std::endl;
    for (int q = 0; q < SIZE; q++)
    {
        for(int i = 0; i < q;i++)
        {
            //if(q != SIZE / 2)
            std::cout << " ";

        }
        //if(q == SIZE / 2)
          //  cout << " " << 4 << "  ";
        for (int t = 0; t < SIZE; t++)
        {
            std::cout << board[q * SIZE + t] << " " ;
            if((((q * SIZE + t)+1) % SIZE) == 0)
            {
                std::cout << std::endl;
            }
        }
    }
    std::cout << "              3"<<std::endl <<std::endl;
}

int Board::GetPlayerTurn()
{
    return this->PlayerTurn;

}
void Board::nextPlayerTurn()
{
    if(this->PlayerTurn == MaximizingPlayer)
        this->PlayerTurn = MinimazingPlayer;
    else
        this->PlayerTurn = MaximizingPlayer;


}

void Board::placeMove(int x, int player)
{
    board[x] = player;
}

void Board::placeMove(int x, int y, int player)
{
    board[x*SIZE + y] = player;
}
void Board::undoMove(int i)
{
    board[i] = 0;
}

void Board::undoMove(int i, int j)
{
    board[i*SIZE+j] = 0;
}

vector<int> Board::getEmptyCells()
{
    std::vector<int> emptyCells;
    for(int i = 0; i < SIZE*SIZE;i++)
    {
        if(this->getCell(i) == 0)
            emptyCells.push_back(i);
    }
    return emptyCells;
}

bool Board::hasEmptyCells()
{
    for(int i = 0; i < SIZE*SIZE;i++)
    {
        if(board[i]==0)
            return true;
        return false;
    }
}

int Board::maximizerWon()
{
    QuickUnionUnionFind* quuf = new QuickUnionUnionFind(SIZE * SIZE);
    for(int i = 0; i < SIZE*SIZE;i++)
    {
        int oneDimensionalPosition = i;

        if(oneDimensionalPosition % SIZE != 0)//west neighbour
        {
            int westNeighbour = oneDimensionalPosition-1;
            //if(board[oneDimensionalPosition] == board[westNeighbour] && board[oneDimensionalPosition] != 0)
            if(board[oneDimensionalPosition] == MaximizingPlayer && board[westNeighbour] == MaximizingPlayer)
            {

                quuf->Qunion(oneDimensionalPosition, westNeighbour);
            }
        }
        if((oneDimensionalPosition+1)%SIZE != 0)//east neighbour
        {
            int EastNeighbour = oneDimensionalPosition+1;
            //if(board[oneDimensionalPosition] == board[EastNeighbour] && board[oneDimensionalPosition] != 0)
            if(board[oneDimensionalPosition] == MaximizingPlayer && board[EastNeighbour]  == MaximizingPlayer)
            {
                quuf->Qunion(oneDimensionalPosition, EastNeighbour);
            }
        }
        if(oneDimensionalPosition < (SIZE*SIZE)-SIZE)//south east neighbour
        {
            int southEastNeighbour = oneDimensionalPosition+SIZE;
            //if(board[oneDimensionalPosition] == board[southEastNeighbour] && board[oneDimensionalPosition] != 0)
            if(board[oneDimensionalPosition] == MaximizingPlayer && board[southEastNeighbour] == MaximizingPlayer)
            {
                //cout << oneDimensionalPosition << "'s southEastNeighbour is " << southEastNeighbour << endl;
                quuf->Qunion(oneDimensionalPosition, southEastNeighbour);
            }
        }
        if(oneDimensionalPosition < (SIZE* SIZE)-SIZE && oneDimensionalPosition % SIZE != 0)//south west neighbour
        {
            int southWestNeighbour = oneDimensionalPosition+(SIZE-1);
            //if(board[oneDimensionalPosition] == board[southWestNeighbour] && board[oneDimensionalPosition] != 0)
            if(board[oneDimensionalPosition] == MaximizingPlayer && board[southWestNeighbour] == MaximizingPlayer)
            {
                //cout << oneDimensionalPosition << "'s southWestNeighbour is " << southWestNeighbour << endl;
                quuf->Qunion(oneDimensionalPosition, southWestNeighbour);
            }

        }
        if(oneDimensionalPosition > (SIZE-1) && (oneDimensionalPosition+1) % SIZE != 0)//north east neighbour
        {
            int northEastNeighbour = (oneDimensionalPosition-(SIZE))+1;
            //if(board[oneDimensionalPosition] == board[northEastNeighbour] && board[oneDimensionalPosition] != 0)
            if(board[oneDimensionalPosition] == MaximizingPlayer && board[northEastNeighbour] == MaximizingPlayer)
            {
                //cout << oneDimensionalPosition << "'s northEastNeighbour is " << northEastNeighbour << endl;
                quuf->Qunion(oneDimensionalPosition, northEastNeighbour);
            }

        }
        if(oneDimensionalPosition > (SIZE-1) && oneDimensionalPosition % SIZE != 0)//north west neighbour
        {
            int northWestNeighbour = (oneDimensionalPosition-SIZE);
            //if(board[oneDimensionalPosition] == board[northWestNeighbour] && board[oneDimensionalPosition] != 0)
            if(board[oneDimensionalPosition] == MaximizingPlayer && board[northWestNeighbour] == MaximizingPlayer)
            {
                //cout << oneDimensionalPosition << "'s northWestNeighbour is " << northWestNeighbour << endl;
                quuf->Qunion(oneDimensionalPosition, northWestNeighbour);
            }
        }
    }


    for(int i = 0; i < SIZE; i++)
    {
        for(int j = (SIZE*SIZE)-SIZE; j < SIZE*SIZE;j++)
        {
            if(quuf->Qconnected(i,j))
            {
                delete quuf;
                //std::cout << "de verbonden getallen zijn  " << i << " en " << j << " verticaal" << std::endl;
                if(this->getCell(i) == MaximizingPlayer)//3 is the player who should play from top to bottom
                {
                    return MaximizingPlayer;
                }
            }
        }
    }
    delete quuf;
    return -1;
}

int Board::minimizerWon()
{
    QuickUnionUnionFind* quuf = new QuickUnionUnionFind(SIZE * SIZE);
    for(int i = 0; i < SIZE*SIZE;i++)
    {
        int oneDimensionalPosition = i;

        if(oneDimensionalPosition % SIZE != 0)//west neighbour
        {
            int westNeighbour = oneDimensionalPosition-1;
            //if(board[oneDimensionalPosition] == board[westNeighbour] && board[oneDimensionalPosition] != 0)
            if(board[oneDimensionalPosition] == MinimazingPlayer && board[westNeighbour] == MinimazingPlayer)
            {

                quuf->Qunion(oneDimensionalPosition, westNeighbour);
            }
        }
        if((oneDimensionalPosition+1)%SIZE != 0)//east neighbour
        {
            int EastNeighbour = oneDimensionalPosition+1;
            //if(board[oneDimensionalPosition] == board[EastNeighbour] && board[oneDimensionalPosition] != 0)
            if(board[oneDimensionalPosition] == MinimazingPlayer && board[EastNeighbour]  == MinimazingPlayer)
            {
                quuf->Qunion(oneDimensionalPosition, EastNeighbour);
            }
        }
        if(oneDimensionalPosition < (SIZE*SIZE)-SIZE)//south east neighbour
        {
            int southEastNeighbour = oneDimensionalPosition+SIZE;
            //if(board[oneDimensionalPosition] == board[southEastNeighbour] && board[oneDimensionalPosition] != 0)
            if(board[oneDimensionalPosition] == MinimazingPlayer && board[southEastNeighbour] == MinimazingPlayer)
            {
                //cout << oneDimensionalPosition << "'s southEastNeighbour is " << southEastNeighbour << endl;
                quuf->Qunion(oneDimensionalPosition, southEastNeighbour);
            }
        }
        if(oneDimensionalPosition < (SIZE* SIZE)-SIZE && oneDimensionalPosition % SIZE != 0)//south west neighbour
        {
            int southWestNeighbour = oneDimensionalPosition+(SIZE-1);
            //if(board[oneDimensionalPosition] == board[southWestNeighbour] && board[oneDimensionalPosition] != 0)
            if(board[oneDimensionalPosition] == MinimazingPlayer && board[southWestNeighbour] == MinimazingPlayer)
            {
                //cout << oneDimensionalPosition << "'s southWestNeighbour is " << southWestNeighbour << endl;
                quuf->Qunion(oneDimensionalPosition, southWestNeighbour);
            }

        }
        if(oneDimensionalPosition > (SIZE-1) && (oneDimensionalPosition+1) % SIZE != 0)//north east neighbour
        {
            int northEastNeighbour = (oneDimensionalPosition-(SIZE))+1;
            //if(board[oneDimensionalPosition] == board[northEastNeighbour] && board[oneDimensionalPosition] != 0)
            if(board[oneDimensionalPosition] == MinimazingPlayer && board[northEastNeighbour] == MinimazingPlayer)
            {
                //cout << oneDimensionalPosition << "'s northEastNeighbour is " << northEastNeighbour << endl;
                quuf->Qunion(oneDimensionalPosition, northEastNeighbour);
            }

        }
        if(oneDimensionalPosition > (SIZE-1) && oneDimensionalPosition % SIZE != 0)//north west neighbour
        {
            int northWestNeighbour = (oneDimensionalPosition-SIZE);
            //if(board[oneDimensionalPosition] == board[northWestNeighbour] && board[oneDimensionalPosition] != 0)
            if(board[oneDimensionalPosition] == MinimazingPlayer && board[northWestNeighbour] == MinimazingPlayer)
            {
                //cout << oneDimensionalPosition << "'s northWestNeighbour is " << northWestNeighbour << endl;
                quuf->Qunion(oneDimensionalPosition, northWestNeighbour);
            }
        }
    }


    for(int k = 0;k < SIZE * SIZE;k+=SIZE)
    {

        for(int l = SIZE-1;l < SIZE * SIZE;l+=SIZE)
        {
            if(quuf->Qconnected(k,l))
            {
                delete quuf;
                //std::cout << "de verbonden getallen zijn  " << k << " en " << l <<" horizontaal"<< std::endl;
                if(this->getCell(l) == MinimazingPlayer)//4 should play from left to right.
                {
                    return MinimazingPlayer;
                }
            }
        }
    }
    delete quuf;
    return -1;
}
int Board::hasWinner()
{
    //std::cout << "begin check"<<std::endl;
    if(maximizerWon() == MaximizingPlayer)
    {
        //this->Print();

        //cout << "it's three" << endl;
        //exit(0);
        return MaximizingPlayer;
    }
    if(minimizerWon() == MinimazingPlayer)
    {
        //this->Print();
        //cout << "it's four" << endl;
        //exit(0);
        return MinimazingPlayer;
    }
    return -1;
    //std::cout << "end check" <<std::endl;
}


int Board::getCell(int x, int y)
{
    return board[x * SIZE + y];
}
int Board::getCell(int x)
{
    return board[x];
}



