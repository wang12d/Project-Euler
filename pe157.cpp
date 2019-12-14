#include "Toolbox.h"
#include <iostream>
using std::cout;
using std::endl;
#ifndef VECTOR_H
#define VECTOR_H
#endif
using std::vector;
typedef long long ll;

const ll MAXN = 2000000000LL;
vector<ll> primes;

void
findPrimes(const ll& n)
{
      ll i, j;  // use long in case overflow
      std::vector<bool> is_prime(n+1, true);
      is_prime[0] = is_prime[1] = false;
      for (i = 2; i*i <= n; ++i) {
            if (is_prime[i]) {
                  // all the number that contain i as factor has
                  // been marked, thus the smallest number is i*i
                  // j > 0 in case the overflow
                  for (j = i*i; j * j <= n; j += i) {
                        is_prime[j] = false;    // j contain prime i as a factor thus not a prime
                  }
            }
      }
      for (i = 2; i <= n; ++i) {
            primes.push_back(i);
      }
}

ll 
numberOfFactors(ll n)
{
    ll res = 1;
    for (ll p: primes) {
        ll cnt = 0;
        while (n % p == 0) {
            n /= p;
            cnt++;
        }
        res *= (cnt + 1);
        if (n < p)  return res;
    }
    cout << "This should not happen" << endl;
    exit(-1);
} 

ll 
findNumberOfWays(ll n)
{
    vector<ll> factors;
    ll res = 0;
    ll i;
    for (i = 1; i * i < n; ++i) {
        if (n % i == 0) {
            factors.push_back(i);
            factors.push_back(n / i);
        }
    }
    if (i * i == n) factors.push_back(i);
    for (ll f: factors) {
        for (ll j = 1; j * j <= f; ++j) {
            if (f % j == 0) {
                res += numberOfFactors(n / f * (j + f / j));
            }
        }
    }
    return res;
}

int
main()
{
    Toolbox::timer();
    findPrimes(MAXN);
    ll powers = 10, expt = 10;
    ll res = 0;
    for (ll i = 1; i < 10; ++i) {
        res += findNumberOfWays(powers); 
        powers *= expt;
    }
    cout << res << endl;
    Toolbox::timeCost();
}
