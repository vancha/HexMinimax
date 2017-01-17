#include "quickfindunionfind.h"
#include "iostream"
QuickFindUnionFind::QuickFindUnionFind(int N)
{

    id.resize(9*9);
    for(int i = 0; i < id.size();i++)
    {
        id.at(i) = i;
        std::cout << id.at(i) << std::endl;
    }


}

bool QuickFindUnionFind::Qconnected(int p, int q)
{
    //std::cout << "is " << id.at(p) << " equal to " << id.at(q) << "?" << std::endl;
    return id.at(p) == id.at(q);
}

void QuickFindUnionFind::Qunion(int p, int q)
{
    int pid = id.at(p);
    int qid = id.at(q);

    for(int i = 0; i < id.size();i++)
    {
        if(id.at(i) == pid)
        {
            id[i] = qid;
        }
    }
}

