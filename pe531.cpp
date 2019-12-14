#include <iostream>
using std::cout;
using std::endl;
#include <vector>
using std::vector;
#include <assert.h>
using namespace std;

long long 
extend_gcd(long long a, long long b, long long *x, long long *y)
{
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }

    long long x1, y1;
    long long d = extend_gcd(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;

    return d;
}

int
gcd(int a, int b) {
      if (b == 0) return a;
      return gcd(b, a%b);
}

vector<vector<int>>
prime_factors(const int& n)
{
      long long i, j, tmp;
      vector<vector<int>> prime_factors(n+1, vector<int>{});
      vector<bool> is_prime(n+1, true);
      vector<int> numbers(n+1);
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

vector<int>
totients(const int& n)
{
      long long i, j;  // use long long in case overflow
      vector<int> totients(n+1, 0);
      for (i = 2; i <= n; ++i) {
            if (!totients[i]) {
                  totients[i] = i - 1;
                  for (j = 2*i; j <= n; j += i) {
                        if (!totients[j]) totients[j] = j;
                        totients[j] = totients[j]*(i - 1) / i;
                  }
            }
      }
      return totients;
}

long long 
crt(const vector<int>& coprimes, const vector<int>& moduli)
{
      long long prod(1LL);
      for (auto i: coprimes) {
            prod *= i;
      }
      long long res(0LL);
      long long inv, tmp;
      int sz = coprimes.size();
      long long d;
      long long p;
      for (auto i = 0; i < sz; ++i) {
            p = prod / coprimes[i];
            d = extend_gcd(p, coprimes[i], &inv, &tmp);
            res = (res + p*inv*moduli[i] % prod) % prod;
      }
      return (res + prod) % prod;
}

void
find_common(const vector<int>& nfactors, const vector<int>& mfactors, const vector<int>& totients, const int& n, const int& m,
vector<int>& coprimes, vector<int>& moduli)
{     
      int nsz = nfactors.size();
      int msz = mfactors.size();
      vector<bool> nused(nsz, false);
      vector<bool> mused(msz, false);
      bool flag;
      for (int i = 0; i < nsz; ++i) {
            flag = false;
            for (int j = 0; j < msz; ++j) {
                  if (!nused[i] && !mused[j]) {
                        if (nfactors[i] % mfactors[j] == 0) {
                              coprimes.push_back(nfactors[i]);
                              moduli.push_back(totients[n]);
                              nused[i] = true;
                              mused[j] = true;
                              break;
                        }
                        else if (mfactors[j] % nfactors[i] == 0) {
                              coprimes.push_back(mfactors[j]);
                              moduli.push_back(totients[m]);
                              nused[i] = true;
                              mused[j] = true;
                              break;
                        }
                  }
            }
      }
      for (int i = 0; i < nsz; ++i) {
            if (!nused[i]) {
                  coprimes.push_back(nfactors[i]);
                  moduli.push_back(totients[n]);
                  nused[i] = true;
            }
      }
      for (int j = 0; j < msz; ++j) {
            if (!mused[j]) {
                  coprimes.push_back(mfactors[j]);
                  moduli.push_back(totients[m]);
                  mused[j] = true;
            }
      }
}

long long
solve(const vector<vector<int>>& factors, const vector<int>& totients, const int& n, const int& m)
{
      // first find all coprimes
      long long d, inv, tmp;
      d = extend_gcd(n, m, &inv, &tmp);
      if ((totients[n] - totients[m]) % d)      return 0;
      if (d == 1) return crt({n, m}, {totients[n], totients[m]});
      vector<int> coprimes;
      vector<int> moduli;
      vector<int> nfactors = factors[n];
      vector<int> mfactors = factors[m];
      find_common(nfactors, mfactors, totients, n, m, coprimes, moduli);
      return crt(coprimes, moduli);
}

int
main(int argc, char** argv)
{
      const int n = 1000000;
      const int m = 1005000;
      vector<vector<int>> factors = prime_factors(m);
      vector<int> to = totients(m);
      long long res = 0;
      for (int i = n; i < m; ++i) {
            for (int j = i + 1; j < m; ++j) {
                  res += solve(factors, to, i, j);
            }
      }
      cout << res << endl;
}