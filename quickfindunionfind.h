#ifndef QUICKFINDUNIONFIND_H
#define QUICKFINDUNIONFIND_H
#include <vector>


class QuickFindUnionFind
{
private:
    std::vector<int> id;
public:
    QuickFindUnionFind(int N);
    bool Qconnected(int p, int q);
    void Qunion(int p, int q);
};

#endif // QUICKFINDUNIONFIND_H
