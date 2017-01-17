#ifndef QUICKUNIONUNIONFIND_H
#define QUICKUNIONUNIONFIND_H
#include <vector>
using namespace std;

class QuickUnionUnionFind
{
private:
    vector<int> id;//array of indexes
    vector<int> sz;//only used to count number of elements in tree(prevent tall trees)
    int Qroot(int i);
public:
    bool Qconnected(int p, int q);//are p and q in the same set?
    void Qunion(int p, int q);//merge sets containing p and q
    QuickUnionUnionFind(int N);
    void disconnectCell(int p);

};

#endif // QUICKUNIONUNIONFIND_H
