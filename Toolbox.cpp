#include "Toolbox.h"
#include <iostream>
using std::cout;
using std::endl;

struct timeval Toolbox::begin;

bool
isPrime(const unsigned long long& n)
{
    if (n == 1)     return false;
    if (n % 2 == 0) return false;
    for (long long i = 3; i*i <= n; i += 2) {
        if (i < 0) return true;
        if (n % i == 0) return false;
    }
    return true;
}

void
Toolbox::timer()
{
    gettimeofday(&Toolbox::begin, nullptr);
}

void
Toolbox::timeCost()
{
    struct timeval end; gettimeofday(&end, nullptr);
    cout << "Time cost: " << (double) ((end.tv_sec - Toolbox::begin.tv_sec) * 1000000 + end.tv_usec - Toolbox::begin.tv_usec) / 1000000 << "s" << endl;
}

int
Toolbox::GCD(int a, int b)
{
    if (a == 0) return b;
    return GCD(b%a, a);
}

long long
Toolbox::extendGCD(long long a, long long b, long long *x, long long *y)
{
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }

    long long x1, y1;
    long long d = extendGCD(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;

    return d;
}

std::vector<int>
Toolbox::findPrimes(const int& n)
{
      long long i, j;  // use long in case overflow
      std::vector<bool> is_prime(n+1, true);
      std::vector<int> primes;
      is_prime[0] = is_prime[1] = false;
      for (i = 2; i*i <= n; ++i) {
            if (is_prime[i]) {
                  // all the number that contain i as factor has
                  // been marked, thus the smallest number is i*i
                  // j > 0 in case the overflow
                  for (j = i*i; j <= n; j += i) {
                        is_prime[j] = false;    // j contain prime i as a factor thus not a prime
                  }
            }
      }
      for (i = 2; i <= n; ++i) {
            if (is_prime[i]) primes.push_back(i);
      }
      return primes;
}

std::vector<int>
Toolbox::findTotients(const int& n)
{
      long long i, j;  // use long long in case overflow
      std::vector<int> totients(n+1, 0);
      for (i = 2; i <= n; ++i) {
            if (!totients[i]) {
                  totients[i] = i - 1;
                  for (j = 2*i; j <= n; j += i) {
                        if (!totients[j]) totients[j] = j;
                        totients[j] = totients[j] / i * (i - 1);
                  }
            }
      }
      return totients;
}

std::vector<std::vector<int>>
Toolbox::findPrimeFactors(const int& n)
{
      long long i, j, tmp;
      std::vector<std::vector<int>> prime_factors(n+1, std::vector<int>{});
      std::vector<bool> is_prime(n+1, true);
      std::vector<int> numbers(n+1);
      for (i = 0; i <= n; ++i) {
            numbers[i] = i;
      }
      is_prime[0] = is_prime[1] = false;
      for (i = 2; i*i <= n; ++i) {
            if (is_prime[i]) {
                  for (j = 2*i; j <= n; j += i) {
                        tmp = i;
                        do {
                              numbers[j] /= i;
                              tmp *= i;
                        } while (j % tmp == 0);
                        prime_factors[j].push_back(tmp / i);
                        is_prime[j] = false;
                  }
            }
      }
      for (i = 2; i <= n; ++i) {
            if (numbers[i] != 1 && !is_prime[i]) {
                  prime_factors[i].push_back(numbers[i]);
            }
      }
      return prime_factors;
}

std::vector<std::vector<int>>
Toolbox::findSubset(const int& n)
{
      int bound = 1 << n;
      std::vector<std::vector<int>> subsets(bound, std::vector<int>{});
      for (int i = 0; i < bound; ++i) {
            int p  = i;
            for (int j = 0; j < n; ++j) {
                  subsets[i].push_back(p & 1);
                  p >>= 1;
            }
      }
      return subsets;
}

// sovle x=moduli(mod coprimes)
int
Toolbox::CRT(const std::vector<int>& coprimes, const std::vector<int>& moduli)
{
      long long prod(1LL);
      for (auto i: coprimes) {
            prod *= i;
      }
      long long res(0LL);
      long long inv, tmp;
      int sz = coprimes.size();
      long long d = 0;
      long long p = 0;
      for (auto i = 0; i < sz; ++i) {
            p = prod / coprimes[i];
            d = extendGCD(p, coprimes[i], &inv, &tmp);
            res = (res + p*inv*moduli[i] % prod) % prod;
      }
      return (res + prod) % prod;
}

long long
Toolbox::power(long long base, long long expt, long long init)
{
    long long res = init;
    while (base) {
        if (expt & 1) {
            res *= base;
        }
        base *= base;
        expt >>= 1;
    }
    return res;
}

long long
Toolbox::powerWithMOD(long long base, long long expt, const long long& m, long long init)
{
    long long res = init;
    while (expt) {
        if (expt & 1) {
            res = (base * res) % m;
        }
        base = (base * base) % m;
        expt >>= 1;
    }
    return res;
}
