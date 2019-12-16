#include <iostream>
#include <vector>
#include "Toolbox.h"
#include <queue>

using std::vector;
using std::cout;
using std::endl;
using std::queue;

// 这个程序能够解决问题，但是需要的空间开销
// 实在是太大了，需要16GB的堆内存
const unsigned long MAX = 1e5;

template<typename T>
vector<T>
findPrimes(const T& n)
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

int
main(int argc, char** argv)
{
    unsigned long n = MAX;
    if (argc > 1) {
        sscanf(argv[1], "%lu", &n);
    }
    unsigned long sq = n*n;
    vector<unsigned long> primes{findPrimes(n)};
    vector<queue<unsigned long>> smooth_numbers(primes.size(), queue<unsigned long>{});
    for (unsigned long i = 0; i < primes.size(); ++i) {
        smooth_numbers[i].push(primes[i]);
    }
    unsigned long cnt = 1;
    for (unsigned long i = 0; i < primes.size(); ++i) {
        // auto &ind = indexes[i];
        auto &qe = smooth_numbers[i];
        while (!qe.empty()) {
            auto &p = qe.front(); qe.pop();
            for (unsigned long j = i; j < primes.size(); ++j) {
                auto q = primes[j] * p;
                if (q > sq) break;
                if (j > i && p > primes[j]) {
                    ++cnt;
                }
                else if (j == i && primes[j] != p) {
                    ++cnt;
                }
                smooth_numbers[j].push(q);
            }
        }
    }
    cout << "cnt = " << cnt << endl;
}
