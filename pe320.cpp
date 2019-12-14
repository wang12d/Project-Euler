#include <iostream>
#include "pe_algs.h"
#include <string.h>
#define max(x, y) ((x) > (y)) ? (x) : (y)

const long neg = 1L << 63;
const long m = (~0 ^ neg);
const int n = 1000000;
const long mod = 1000000000000000000L;
long res [1+n];
std::vector<int> primes;
long cons = 1234567890L;

long pot(long n, int p)
{
    long res = 0;
    long tmp = p;
    while (tmp > 0 && n > tmp) {
        res += n / tmp;
        tmp *= p;
    }
    if (tmp > 0) res += n / tmp;
    return res;
}

long bin_search(long lo, long hi, int p, long val)
{
    long mid, tmp;
    while (hi - lo > 1) {
        tmp = hi - lo;
        mid = lo + (tmp / 2);

        long expt = pot(mid, p);
        // std::cout << expt << std::endl;
        if (expt >= val) {
            hi = mid;
        }
        else {
            lo = mid;
        }
        // std::cout << mid << std::endl;
    }
    return hi;
}

void get_factor(int n, long *ans)
{
    std::vector<int>::iterator end = primes.end();

    long prev_ans = *ans;   // 存储这之前最大的值
    for (std::vector<int>::iterator it = primes.begin(); it != end; ++it) {
        int p = *it;
        int cnt = 0;
        if (p > n) {
            break;
        }
        while (n % p == 0) {
            ++cnt;
            n /= p;
        }
        if (cnt > 0) {
            long v = cnt * cons;
            if (v < 0) {
                std::cout << "Error detected" << std::endl;
            }
            res[p] = res[p] + v;
            prev_ans = max(prev_ans, bin_search(0, m, p, res[p]));
        }
    }
    
    *ans = prev_ans;
}

int main(void)
{
    primes = sieve(n);
    res[2] = pot(10, 2) * cons; res[3] = pot(10, 3) * cons; res[5] = pot(10, 5) * cons; res[7] = pot(10, 7) * cons;

    long ans = bin_search(0, m, 2, res[2]);
    ans = max(ans, bin_search(0, m, 3, res[3]));
    ans = max(ans, bin_search(0, m, 5, res[5]));
    ans = max(ans, bin_search(0, m, 7, res[7]));

    long fin_ans = ans;
    for (int i = 11; i <= n; ++i) {
        get_factor(i, &ans);
        fin_ans = (fin_ans + ans) % mod;
    }
    for (int i = 0; i <= 10; ++i) {
        std::cout << primes[i] << " " << res[primes[i]] << std::endl;
    }
    std::cout << fin_ans << std::endl;
}