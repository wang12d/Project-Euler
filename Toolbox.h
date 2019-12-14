#include <cstdio>
#ifndef TOOLBOX_H
#define TOOLBOX_H
#endif
#include <vector>
#include <sys/time.h>

class Toolbox
{
public:
    // find all the prime numbers between 1~n
    static std::vector<int> findPrimes(const int&);
    // find all the totient value between 1~n
    static std::vector<int> findTotients(const int&);
    // find all the sole prime factors betwen 1~n
    static std::vector<std::vector<int>> findPrimeFactors(const int&);
    // find all the subset of size n
    static std::vector<std::vector<int>> findSubset(const int&);
    static int CRT(const std::vector<int>&, const std::vector<int>&);
    static long long extendGCD(long long, long long, long long*, long long*);
    static int GCD(int, int);
    static long long power(long long, long long, long long init=1);
    static long long powerWithMOD(long long, long long, const long long&, long long init=1);
    static void timer();
    static void timeCost();
    static bool isPrime(const unsigned long long&);
private:
    static struct timeval begin;
};
