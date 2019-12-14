#include <bits/stdc++.h>

using namespace std;

long long n;

bool
isPrime(unsigned long long n)
{
    if (n == 1) return false;
    if (n % 2 == 0) return false;
    for (unsigned long long i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

unsigned long long
computeFirstVal(unsigned long long n)
{
    return 3*n*n - 3*n + 2;
}

unsigned long long
computeLastVal(unsigned long long n)
{
    return 3*n*n + 3*n + 1;
}

unsigned long long
findNthVal(unsigned long long nth)
{
    if (nth == 1)   return 1;
    unsigned long long layer = 1;
    unsigned long long primeCount = 1;
    unsigned long long val;
    while (1) {
        if (isPrime(6*layer - 1) && isPrime(6*layer + 1) && isPrime(12*layer + 5)) {
            val = computeFirstVal(layer);
            primeCount++;
        }
        if (primeCount == nth)  return val;
        if (layer > 1 && isPrime(6*layer - 1) && isPrime(12*layer - 7) && isPrime(6*layer + 5)) {
            val = computeLastVal(layer);
            primeCount++;
        }
        if (primeCount == nth)  return val;
        layer++;
    }
}

int
main(int argc, char** argv)
{
    cin >> n;
    cout << findNthVal(n) << endl;
}