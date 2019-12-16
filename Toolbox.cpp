#include "Toolbox.h"
#include <iostream>
using std::cout;
using std::endl;

template<typename T>
struct timeval Toolbox<T>::begin;

template<typename T>
bool
Toolbox<T>::isPrime(const T& n)
{
    if (n == 1)     return false;
    if (n % 2 == 0) return false;
    for (long long i = 3; i*i <= n; i += 2) {
        if (i < 0) return true;
        if (n % i == 0) return false;
    }
    return true;
}


template<typename T>
void
Toolbox<T>::timer()
{
    gettimeofday(&Toolbox::begin, nullptr);
}

template<typename T>
void
Toolbox<T>::timeCost()
{
    struct timeval end; gettimeofday(&end, nullptr);
    cout << "Time cost: " << (double) ((end.tv_sec - Toolbox::begin.tv_sec) * 1000000 + end.tv_usec - Toolbox::begin.tv_usec) / 1000000 << "s" << endl;
}

template<typename T>
T
Toolbox<T>::GCD(T a, T b)
{
    if (a == 0) return b;
    return GCD(b%a, a);
}

template<typename T>
T
Toolbox<T>::extendGCD(T a, T b, T *x, T *y)
{
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }

    T x1, y1;
    T d = extendGCD(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;

    return d;
}

template <typename T>
std::vector<T>
Toolbox<T>::findPrimes(const T& n)
{
      T i, j;  // use long in case overflow
      std::vector<bool> is_prime(n+1, true);
      std::vector<T> primes;
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

template<typename T>
std::vector<T>
Toolbox<T>::findTotients(const T& n)
{
      T i, j;  // use long long in case overflow
      std::vector<T> totients(n+1, 0);
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

template<typename T>
std::vector<std::vector<T>>
Toolbox<T>::findPrimeFactors(const T& n)
{
    long long i, j, tmp;
    std::vector<std::vector<T>> prime_factors(n+1, std::vector<T>{});
    std::vector<bool> is_prime(n+1, true);
    std::vector<T > numbers(n+1);
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

template<typename T>
std::vector<std::vector<T>>
Toolbox<T>::findSubset(const T& n)
{
      T bound = 1 << n;
      std::vector<std::vector<T>> subsets(bound, std::vector<T>{});
      for (T i = 0; i < bound; ++i) {
            T p  = i;
            for (T j = 0; j < n; ++j) {
                  subsets[i].push_back(p & 1);
                  p >>= 1;
            }
      }
      return subsets;
}

// sovle x=moduli(mod coprimes)
template<typename T>
T
Toolbox<T>::CRT(const std::vector<T>& coprimes, const std::vector<T>& moduli)
{
      T prod(1LL);
      for (auto i: coprimes) {
            prod *= i;
      }
      T res(0LL);
      T inv, tmp;
      T sz = coprimes.size();
      T d = 0;
      T p = 0;
      for (auto i = 0; i < sz; ++i) {
            p = prod / coprimes[i];
            d = extendGCD(p, coprimes[i], &inv, &tmp);
            res = (res + p*inv*moduli[i] % prod) % prod;
      }
      return (res + prod) % prod;
}

template<typename T>
T
Toolbox<T>::power(T base, T expt, T init)
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

template<typename T>
T
Toolbox<T>::powerWithMOD(T base, T expt, const T& m, T init)
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

template class Toolbox<int>;
template class Toolbox<unsigned int>;
template class Toolbox<unsigned long>;
template class Toolbox<unsigned long long>;
template class Toolbox<long>;
template class Toolbox<long long>;
