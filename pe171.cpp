#include <cstdint>
using Long=int64_t;
using Int=int32_t;
#include <iostream>
using std::cout;
using std::endl;
#include <vector>
using std::vector;
#include "Toolbox.h"
#include <algorithm>
using std::find;
using std::make_pair;
using std::pair;
#include <ctime>
// Algorithm parperation, find all the squares needed
// into its input
// @params: vector to be filled with squares
void init(vector<Int>&);
Int digitSuqreSum(Int);

Int N = 20;
const Int M = 1000000000;

int
main(int argc, char** argv)
{
    clock_t begin = clock();
    if (argc > 1) {
        sscanf(argv[1], "%d", &N);
    }
    vector<Int> squares;
    vector<vector<pair<Long, Int>>> dp(N+1, vector<pair<Long, Int>>((N+1)*81, make_pair(0, 0)));
    init(squares);
    Int maxValue = (N + 1) * 81;
    for (Int i = 1; i <= N; ++i) {
        for (Int j = 1; j < maxValue; ++j) {
            dp[i][j].first = dp[i-1][j].first;
            dp[i][j].second = dp[i-1][j].second;
            for (Int v = 1; v < 10; ++v) {
                Int sq = v*v;
                if (j == sq) {
                    dp[i][j].first = (dp[i][j].first + v * Toolbox::powerWithMOD(10, i-1, M) % M) % M;
                    dp[i][j].second++;
                }
                else if (j > sq && dp[i-1][j-sq].first){
                    dp[i][j].first = (dp[i][j].first + dp[i-1][j-sq].first + dp[i-1][j-sq].second * v * Toolbox::powerWithMOD(10, i-1, M) % M) % M;
                    dp[i][j].second += dp[i-1][j-sq].second;
                }
            }
        }
    }
    Long res = 0;
    for (Int v: squares) {
        res = (res + dp[N][v].first) % M;
    }
    cout << res << endl;
    cout << "cost " << (double) (clock() - begin) / CLOCKS_PER_SEC << "s" << endl;
}

void
init(vector<Int>& squares)
{
    Int maxValue = N * 81;
    for (Int i = 0; i <= maxValue; ++i) {
        Int sq = i*i;   if (sq > maxValue)   break;
        squares.push_back(sq);
    }
}

Int
digitSuqreSum(Int n)
{
    Int sum = 0;
    while (n) {
        Int v = n % 10;
        sum += v * v;
        n /= 10;
    }
    return sum;
}

