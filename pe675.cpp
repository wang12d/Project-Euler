#include <iostream>
#include "Toolbox.h"
#include <vector>
#include <cassert>

using std::vector;
using std::cout;
using std::endl;

const int MAX = 1e7;
const unsigned long long MOD = 1000000087;
// const vector<int> primes{Toolbox::findPrimes(MAX)};
vector<vector<int>> prime_factors(MAX+1, vector<int>{});
vector<int> prime_powers(MAX+1, 0);;

void 
find_distinct_primes()
{
    vector<bool> primes(MAX+1, true);
    vector<int> numbers(MAX+1, 0);
    for (int i = 0; i <= MAX; ++i) {
        numbers[i] = i;
    }
    primes[0] = primes[1] = false;
    for (long long i = 2; i <= MAX; ++i) {
        if (primes[i]) {
            for (long long j = 2*i; j <= MAX; j += i) {
                prime_factors[j].push_back(i);
                primes[j] = false;
            }
        }
    }
}

int
main(int argc, char** argv)
{
    Toolbox::timer();
    long long res = 0;
    long long init = 1;
    int val = MAX;
    find_distinct_primes();
    if (argc > 1) sscanf(argv[1], "%d", &val);
    for (auto i = 2; i <= val; ++i) {
        if (prime_factors[i].size() != 0) {
            for (auto p: prime_factors[i]) {
                // Find power the prime
                auto cnt = 0;
                auto v = i;
                while (v % p == 0) {
                    cnt++;
                    v /= p;
                }
                // cout << "p = " << p << " cnt = " << cnt << " power[" << p << "] = " << prime_powers[p] << endl;
                // assert(init % (2*prime_powers[p] + 1) == 0);
                long long inv, tmp;
                Toolbox::extendGCD(2*prime_powers[p]+1, MOD, &inv, &tmp);
                // init = (init + init / (2 * prime_powers[p] + 1) * 2 * cnt) % MOD;
                if (inv < 0) {
                    inv += MOD;
                }
                auto cp = init;
                init = (init * 2 * cnt) % MOD;
                init = (init * inv) % MOD;
                init = (init + cp) % MOD;
                prime_powers[p] += cnt;
            }
        }
        else {
            init = 3*init % MOD;
            prime_powers[i]++;
        }
        // cout << "i = " << i << " init = " << init << endl;
        res = (res + init) % MOD;
    }
    cout << (res + MOD) % MOD << endl;
    Toolbox::timeCost();
}
