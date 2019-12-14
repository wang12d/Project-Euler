/**
 * Project Euler Investigating the primality of numbers of the form 2n*n-1
 * Consider numbers t(n) of the form t(n) = 2n2-1 with n > 1.
 * The first such numbers are 7, 17, 31, 49, 71, 97, 127 and 161.
 * It turns out that only 49 = 7*7 and 161 = 7*23 are not prime.
 * For n ≤ 10000 there are 2202 numbers t(n) that are prime.
 *
 * How many numbers t(n) are prime for n ≤ 50,000,000 ?
 *
 **/

// using Miller-Rabin Test
// C++ program Miller-Rabin primality test
/* 
 * C++ Program to Implement Miller Rabin Primality Test
 */
#include <iostream>
#include <stdlib.h>
#include <random>
using namespace std;

/**
 * 素数检测算法
 */
long mulmod(long a, long b, long mod)
{
    long x = 0,y = a % mod;
    while (b > 0)
    {
        if (b % 2 == 1) {    
            x = (x + y) % mod;
        }
        y = (y * 2) % mod;
        b /= 2;
    }
    return x % mod;
}

/* 
 * modular exponentiation
 */
long modulo(long base, long exponent, long mod)
{
    long x = 1;
    while (exponent > 0)
    {
        if (exponent & 1)
            x = (x * base) % mod;

        base = (base * base) % mod;
        exponent >>= 1;
    }
    return x;
}
 
/*
 * Miller-Rabin primality test, iteration signifies the accuracy
 */
bool Miller(long p, int iteration)
{
    if (p == 2 || p == 3) {
        return true;
    }
    if (p <= 4) {
        return false;
    }
    cout << p << endl;
    long s = p - 1;
    long k = 0;
    default_random_engine generator;
    uniform_int_distribution<long> dis(2, p-1);
    while (s % 2 == 0) {
        s /= 2;
        ++k;
    }

    for (int i = 0; i < iteration; i++) {
        long a = dis(generator);
        long mod = modulo(a, s, p);
        if (mod == 1 || mod == p - 1) {
            continue;
        }
        bool some_minus_one = false;
        for (int r = 0; r < k-1; ++r) {
            mod = (mod * mod) % p;
            if (mod == p - 1) {
                some_minus_one = true;
                break;
            }
        }
        if (!some_minus_one) {
            return false;
        }
    }

    return true;
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        cout << "Input error!" << endl;
        return 0;
    }

    int iter = 1000;
    long n, v;
    sscanf(argv[1], "%ld", &n);
    cout << "n = " << n << endl;
    int res = 0;
    for (long i = n; i >= n-20; --i) {
        v = 2 * i * i - 1;
        if (Miller(v, iter)) {
            ++res;
        }
    }

    cout << res << endl;
}
