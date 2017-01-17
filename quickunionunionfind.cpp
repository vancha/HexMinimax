#include "quickunionunionfind.h"
#include "iostream"
#include "vector"

int QuickUnionUnionFind::Qroot(int i)
{
    while(i != id.at(i))
    {
        id.at(i) = id.at(id.at(i));
        i = id[i];
    }
    return i;
}

QuickUnionUnionFind::QuickUnionUnionFind(int N)
{
    id.resize(N);
    sz.resize(N);
    for(int i = 0; i< id.size();i++)
    {
        id.at(i) = i;
        sz.at(i) = 1;
    }
}
bool QuickUnionUnionFind::Qconnected(int p, int q)
{
    return Qroot(p) == Qroot(q);
}

void QuickUnionUnionFind::disconnectCell(int p)
{
    std::vector<int> otherConnectedCells;
    int newroot = 0;
    bool rerouted = false;
    for(int i = 0; i < id.size();i++)
    {
        if(Qroot(i) == Qroot(p) && i != p)
        {
            otherConnectedCells.push_back(i);
            if(id.at(i) == p && !rerouted)
            {
                id.at(i) == i;
                newroot = i;
                rerouted = true;
            }
            if(id.at(i) == p && rerouted)
            {
                id.at(i) = newroot;
            }

        }
    }
    std::cout << p << "is connected to " << otherConnectedCells.size() << " other cells" << std::endl;

}

void QuickUnionUnionFind::Qunion(int p, int q)
{
    int i = Qroot(p);
    int j = Qroot(q);
    if(i == j)//p and q are already connected, root is the same
    {
        return;
    }

    if(sz.at(i) < sz.at(j))//is the size of the tree at size(0) smaller then size at the root of q?
    {
        id.at(i) = j;
        sz.at(j) += sz.at(i);
    }
    else
    {
        id.at(j) = i;
        sz.at(i) += sz.at(j);
    }
//    std::cout << "all indexes in id:"<<std::endl;
//    for(int i = 0;i < id.size();i++)
//    {
//        std::cout << id.at(i) << " ";
//        if(i % 9 == 0)
//            std::cout << std::endl;
//    }
}
