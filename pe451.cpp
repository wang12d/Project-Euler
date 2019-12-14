#include <map>
using std::map;
#include "toolbox.h"
#include <iostream>
using std::cout;
using std::endl;
#define max(x, y) ((x) > (y) ? (x) : (y))

map<int, vector<vector<int>>> bitMap;
int n = 20000000;

void
findAllBit()
{
    for (int i = 1; i <= 8; ++i) {
        bitMap[i] = Toolbox::findSubset(i);
    }
}

int
solve(const int& n, const vector<int>& factors)
{
    int fsz = factors.size();
    if (fsz < 1)   return 1;
    bool flag = false;
    int twoP = 0;
    int p = 2;
    while (factors[0] % p == 0) {
        twoP++;
        p *= 2;
    }
    if (twoP > 2)   flag = true;
    vector<vector<int>> allModuli(fsz, vector<int>(2));
    vector<vector<int>> bits = bitMap[fsz];
    for (int i = 0; i < fsz; ++i) {
        allModuli[i][0] = factors[i] - 1;
        allModuli[i][1] = 1;
    }
    int res = -1;
    vector<int> moduli(fsz, 0);
    for (int i = 0; i < bits.size(); ++i) {
        for (int j = 0; j < fsz; ++j) {
            moduli[j] = allModuli[j][bits[i][j]];
        }
        int val = Toolbox::CRT(factors, moduli);
        if (val < n - 1) {
            res = max(val, res);
        }
        if (flag) {
            moduli[0] = p / 4 - 1;
            val = Toolbox::CRT(factors, moduli);
            if (val < n - 1) res = max(val, res);
            moduli[0] = p / 4 + 1;
            val = Toolbox::CRT(factors, moduli);
            if (val < n - 1) res = max(val, res);

        }
    }
    return res;
}

int
main(int argc, char** argv)
{
    findAllBit();
    vector<vector<int>> primesFact = Toolbox::findPrimeFactors(n);
    long long ans = 0;
    for (int i = 3; i <= n; ++i) {
        ans += solve(i, primesFact[i]);
    }
    cout << ans << endl;
}