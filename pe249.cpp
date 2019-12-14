#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;

const unsigned long long MOD = 10000000000000000LL;

vector<int> sieve(int n)
{
    int *number = (int*) malloc(sizeof(int) * (n+1));
    std::vector<int> primes;
    for (int i = 0; i <= n; ++i) {
        number[i] = 1;
    }
	number[0] = number[1] = 0;
	int i, j;	// 循环指针
	for (i = 2; i*i <= n; ++i) {
		if (number[i]) {
			for (j = i*i; j > 0 && j <= n; j += i) {
				number[j] = 0;
			}
		}
	}

	for (i = 0; i <= n; ++i) {
		if (number[i]) {
			primes.push_back(i);
		}
	}

    free(number);
    return primes;
}

vector<ull>
findNumberOfWays(const vector<int>& numbers, ull sum)
{
    vector<ull> ways(sum+1, 0);
    ways[0] = 1;
    for (int i: numbers) {
        for (int j = sum - i; j >= 0; --j) {
            if (ways[j]) {
                ways[j + i] = (ways[j] + ways[j + i]) % MOD;
            }
        }
    }
    return ways;
}

int
main(int argc, char** argv)
{
    int n;
    cin >> n;
    vector<int> primes = sieve(n);
    ull primeSum = 0;
    for (int p: primes) {
        primeSum += p;
    }
    vector<int> sumPrime = sieve(primeSum);
    vector<bool> isPrime(primeSum+1, false);
    for (int p: sumPrime) {
        isPrime[p] = true;
    }
    ull res = 0;
    vector<ull> ways = findNumberOfWays(primes, sumPrime[sumPrime.size() - 1]);
    for (int i = 0; i < ways.size(); ++i) {
        if (isPrime[i]) {
            res = (res + ways[i]) % MOD;
        }
    }
    cout << res << endl;
}