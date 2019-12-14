/**
 * Project Euler 304 Primonacci
 * @author: Heng
 * @Date: 2018/08/27
 * @Modified: 2018/08/27
 * using sieve to find out all primes, then compute the
 * fibonacci in log(O)
 **/

#include "pe_algs.h"
#include <stdio.h>

#define BASE 100000000000000
#define MAX 10000000    // prepare 10^7 cadicate

std::vector<long> primes;   // all the primes larger than 10^14
bool not_prime[MAX];

// find min mutiple of p between low and high
long 
bin_search(int p)
{
    long lo = 1, hi = (BASE + MAX) / p;
    long mid;
    while (hi >= lo) {
        mid = (lo + hi) / 2;
        if (mid * p >= BASE) {
            hi = mid - 1;
        }
        else {
            lo = mid + 1;
        }
    }

    return lo*p - BASE;
}

void 
find_primes()
{
    std::vector<int> ps = sieve(MAX+1);

    int sz = ps.size();
    int ptr = 0;    // use to indicate the base + ptr
    for (int i = 0; i < sz; ++i) {
        int p = ps[i];
        long v = bin_search(p);
        for (; v < MAX; v += p) {
            not_prime[v] = 1;
        }
    }
    
    for (int i = 0; i < MAX; ++i) {
        if (!not_prime[i]) {
            primes.push_back(BASE + i);
            printf("%ld\n", BASE + i);
        }
    }
    
}

int 
main(int argc, char *argv[])
{
    find_primes();
}