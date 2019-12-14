/**
 * Project Euler 153 Investiage Guass Integer
 * @author: Wang
 * @date: 2018/8/24
 **/

#include <iostream>
#include <set>

#define M 100000000 + 16

long num[M];
std::set<std::pair<int, int>> s;  // using to store <i, j>
long N;  // input

void init()
{
    long i_sq, j_sq;
    for (long i = 1; 2 * i * i <= N; ++i) {
        i_sq = i * i;
        num[i_sq*2] += 2*i;
        for (long j = i+1; i_sq + j * j <= N; ++j) {
            num[i_sq + j * j] +=  2*(i + j);
        }
    }
}

long helper(long n)
{
    if (n == 1) return 1;
    long res = n;
    for (long i = 2; i <= n/2; ++i) {
        res += n / i * i;
    }
    long v = n/2 + 1;
    res += (n - v + 1) * (n + v) / 2;
    return res;
}

long solver(long n)
{
    long res = 0;
    long tmp_val = 0;
    for (long i = 1; i <= n; ++i) {
        long v = n / i;
        tmp_val += i * v;
        res += i*v + (num[i] != 0 ? helper(v) * num[i] : 0);
    }

    for (long i = 1; i <= n; ++i) {
        for (long j = i; j <= n; ++j) {
            long a = i * i + j * j;
            if (a > n) break;
            long cnt = 2, tmp = cnt * cnt * a;
            long val = (i == j ? 2 * i : 2*(i+j));
            // using a set to store the (i, j) pair,then subtract from the result
            while (tmp <= n) {
                if (s.find(std::make_pair(cnt*i, cnt*j)) == s.end()) {
                    res -= helper(n / tmp) * cnt * val;
                    s.insert(std::make_pair(cnt*i, cnt*j));
                }
                ++cnt;
                tmp = (cnt*cnt) * a;
            }
        }
    }

    return res;
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        std::cout << "Input error." << std::endl;
        return 1;
    }

    sscanf(argv[1], "%ld", &N);
    init();

    long res = solver(N);

    std::cout << res << std::endl;
}
