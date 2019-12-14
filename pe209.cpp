#include <iostream>
using std::cout;
using std::endl;
#include <cassert>
#include <vector>
using std::vector;
#include <stack>
using std::stack;
#include "Toolbox.h"
typedef unsigned long long ull;

// 根据比特之间的位移关系，可以得出其真值表的特点
// 目前初步判断其应该是一个动态规划或者图搜索的问题
// 现在卡住的地方就是如何来建立这样的一个图
// 目前感觉其应该是一个有向图
inline bool
getNthBit(ull v, int n)
{
    return (v & (1ULL << (n-1))) >> (n-1);
}

inline void
printAllBits(int m, int n)
{
    for (int i = n; i >= 1; --i) {
        cout << getNthBit(m, i);
    }
}

inline int
getComplement(ull v, int n)
{
    int lastBit = getNthBit(v, n) ^ (getNthBit(v, n-1) & getNthBit(v, n-2));
    return ((v << 1) & ((1ULL << n) - 1)) | lastBit;
}

ull
findTable(int bit, vector<int>::iterator cur, vector<vector<vector<ull>>>& cache, const int firstBit, const vector<int>::iterator end)
{
    if (cache[*cur][bit][firstBit]) {
        return cache[*cur][bit][firstBit];
    }
    if (cur == end) {
        return (bit & firstBit) == 0 ? 1 : 0;
    }
    int v = (bit == 0 ? 1 : 0);
    ull result = 0;
    for (int i = 0; i <= v; ++i) {
        result += findTable(i, cur+1, cache, firstBit, end);
    }
    cache[*cur][bit][firstBit] = result;
    return result;
}

void
dfs(int v, vector<bool>& flag, const vector<vector<int>>& edge, int mark, vector<int>& loopMark)
{
    loopMark.push_back(v);
    flag[v] = true;
    for (auto i = edge[v].begin(); i != edge[v].end(); ++i) {
        if (!flag[*i]) {
            dfs(*i, flag, edge, mark, loopMark);
        }
    }
}

int
main(int argc, char** argv)
{
    Toolbox::timer();
    int n = 6;
    if (argc > 1) {
       sscanf(argv[1], "%d", &n);
    }
    assert(n > 0);
    int V = 1 << n;
    vector<int> loop(V, 0);
    vector<vector<int>> edge(V, vector<int>());
    vector<bool> flag(V, false);
    for (int i = 0; i < V; ++i) {
        loop[i] = getComplement(i, n);
    }
    for (int i = 0; i < V; ++i) {
        edge[i].push_back(loop[i]);
    }
    int mark = 0;
    vector<vector<int>> vertexByMark;
    for (int i = 0; i < V; ++i) {
        if (!flag[i]) {
            vector<int> loopMark;
            dfs(i, flag, edge, mark, loopMark);
            vertexByMark.push_back(loopMark);
            ++mark;
        }
    }
    vector<vector<vector<ull>>> cache(V, vector<vector<ull>>(2, vector<ull>(2, 0)));
    ull result = 1;
    for (auto i = vertexByMark.begin(); i != vertexByMark.end(); ++i) {
        auto end = i->end() - 1;
        ull tmp = 0;
        tmp += findTable(0, i->begin(), cache, 0, end);
        tmp += findTable(1, i->begin(), cache, 1, end);
        result *= tmp;
    }

    cout << result << endl;
    Toolbox::timeCost();
}
