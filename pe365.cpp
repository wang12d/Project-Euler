/*
 * @Author: WangHeng 
 * @Date: 2018-12-29 18:33:26 
 * @Last Modified by: WangHeng
 * @Last Modified time: 2018-12-29 19:07:39
 */


#include <iostream>
#include "pe_algs.h"
#include <map>

const long N = 1E18;
const long M = 1E9;
const long BASE =  N - M;

std::map<long, long> basePow;    // 素数的指数形式
bool notPrime[M+1];
std::vector<int> allPrime;
std::vector<int> primeNeeded;
// 采用二分搜索的办法，找到大于10^18-10^9的
// 能够被p整除的最小的数
bool
binSearch(int p)
{
    long lo = 1, hi = BASE / p;
    long mid, tmp;
    while (hi >= lo) {
        mid = lo + (hi - lo) / 2;
        tmp = mid * p;
        // 此时说明太大了
        if (tmp >= hi || tmp < 0) {
            hi = mid - 1;
        }
        else {
            lo = mid + 1;
        }
    }

    return lo * p - BASE;
}

// n的阶乘的p的指数位数
long
pot(long n, long p)
{
    long res = 0;
    long tmp = p;
    while (tmp <= n && tmp > 0) {
        res += n / p;
        tmp *= p;
    }
    return res;
}

long
fastMod(long base, long expt, long mod)
{
    long res = 1;
    while (expt) {
        if (expt & 1) {
            res = res * base % mod;
        }
        base = base * base % mod;
        expt >>= 1;
    }

    return res;
}

void
findPrime()
{
    allPrime = sieve(M+1);
    long v;

    std::cout << "sieve done." << std::endl;
    for (auto i = allPrime.begin(); i != allPrime.end(); ++i) {
        if (1000 < *i < 5000) {
            primeNeeded.push_back(*i);
        }
        basePow[*i] = pot(N, *i) - pot(M, *i) - pot(BASE, *i);
        v = binSearch(*i);
        for (; v <= M; v += *i) {
            notPrime[v] = true;
        }
    }
    
    std::cout << "loop done." << std::endl;
    for (int i = 0; i <= M; ++i) {
        if (!notPrime[i]) {
            basePow[i+BASE] = 1;
        }
    }
}

long
findMod(long p)
{
    long res = 1;
    for (auto i = basePow.begin(); i != basePow.end(); ++i) {
        res = res * fastMod(i->first, i->second, p) % p;
    }

    return res;
}

int
main(int argc, char **argv)
{
    findPrime();
    std::cout << "find prime done." << std::endl;
    std::cout << "prime pair size = " << basePow.size() << std::endl;
    long res = 0;
    int i, j, k, sz;
    long p, q, r;

    /**
    sz = primeNeeded.size();
    for (i = 0; i < sz; ++i) {
        p = primeNeeded[i];
        for (j = i + 1; j < sz; ++j) {
            q = primeNeeded[j];
            for (k = j + 1; k < sz; ++k) {
                r = primeNeeded[k];
                res += findMod(p*q*r);
            }
        }
    }
    **/
    std::cout << "the answer of problem 365 is: " << res << std::endl;
    return 0;
}
