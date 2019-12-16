#include <cstdio>
#ifndef TOOLBOX_H
#define TOOLBOX_H
#endif
#include <vector>
#include <sys/time.h>

template <typename T>
class Toolbox
{
public:
    // find all the prime numbers between 1~n
    static std::vector<T> findPrimes(const T&);
    // find all the totient value between 1~n
    static std::vector<T> findTotients(const T&);
    // find all the sole prime factors betwen 2~n
    static std::vector<std::vector<T>> findPrimeFactors(const T&);
    // find all the subset of size n
    static std::vector<std::vector<T>> findSubset(const T&);
    static T CRT(const std::vector<T>&, const std::vector<T>&);
    static T extendGCD(T, T, T*, T*);
    static T GCD(T, T);
    static T power(T, T, T init=1);
    static T powerWithMOD(T, T, const T&, T init=1);
    static void timer();
    static void timeCost();
    static bool isPrime(const T&);
private:
    static struct timeval begin;
};

