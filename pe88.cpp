#include <iostream>
#include <map>
#include <vector>
#include <set>

using namespace std;

typedef struct Prod_sum {
    int sum, cnt;
    Prod_sum(int sum, int cnt):sum(sum), cnt(cnt)   {}
} prod_sum;

const long INF = 30000;
const int max_n = 12000 + 16;
int res[max_n];
map<int, vector<prod_sum>> m;
set<int> s;

void
solve()
{
    int i, j, prod, sum, cnt;
    vector<prod_sum> vec;

    for (i = 1; i < INF; ++i) {
        m[i].push_back(Prod_sum(i, 1));
    }

    for (i = 2; i < INF; ++i) {
        for (j = 2; j * i < INF; ++j) {
            prod = i * j;
            auto find = m.find(j);
            vec = find->second;
            for (auto v = vec.begin(); v != vec.end(); ++v) {
                m[prod].push_back(Prod_sum(v->sum + i, v->cnt+1));
            }
        }
    }
}

int
main(int argc, char **argv)
{
    ios::sync_with_stdio(false);
    for (int i = 0; i < max_n; ++i) {
        res[i] = INF;
    }
    solve();
    long sum = 0;
    vector<prod_sum> vec;
    for (auto v = m.begin(); v != m.end(); ++v) {
        vec = v->second;
        for (auto u = vec.begin(); u != vec.end(); ++u) {
            int ind = v->first - u->sum + u->cnt;
            if (ind < max_n && ind > 0) {
                res[ind] = min(res[ind], v->first);
            }
        }
    }

    for (int i = 2; i <= 12000; ++i) {
        if (res[i] != INF && s.find(res[i]) == s.end()) {
            s.insert(res[i]);
            sum += res[i];
        }
    }
    cout << sum << endl;
}