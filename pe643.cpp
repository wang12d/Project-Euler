#include <bits/stdc++.h>

using namespace std;

const long long MOD = 1000000007LL;
typedef long long ll;

long long MODINV;
map<ll, ll> coprime;

ll 
extend_gcd(ll a, ll b, ll *x, ll *y)
{
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }

    ll x1, y1;
    ll d = extend_gcd(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b)*y1;

    return d;
}

// 计算所有的互素对的个数，1 <= x < y <= n
ll
numberOfCoprimePairs(ll n)
{
    if (coprime[n]) return coprime[n];
    ll integerRoot = (ll) sqrt(n);
    vector<ll> indexes;
    for (auto i = 1; i <= integerRoot; ++i) {
        indexes.push_back(i);
    }
    ll sz = indexes.size();
    for (auto i = integerRoot; i > 0; --i) {
        if (indexes[sz-1] != n / i) {
            sz++;
            indexes.push_back(n / i);
        }
    }
    for (auto v: indexes) {
        if (coprime[v]) continue;
        ll tmp = (( (v % MOD) * ((v - 1) % MOD) % MOD) * MODINV) % MOD;
        if (tmp < 0) {
            cout << "Overflow " << v << endl;
            exit(0);
        }
        if (1 < v) {
            ll sqrtv = (ll) sqrt(v);
            for (ll i = 1; i <= sqrtv; ++i) {
                tmp = (tmp - (coprime[i] * (v / i - v / (i + 1)) % MOD));
            }
            ll ap = 1 + v / (1 + sqrtv);
            for (ll d = 2;  d < ap; ++d) {
                tmp -= coprime[v / d];
            }
        }
        coprime[v] = (tmp + MOD) % MOD;
    }
    return coprime[n];
}

int
main(int argc, char** argv)
{
    // ll n = 100;
    // vector<ll> primes = sieve(n);
    // cout << "sieve done." << endl;
    // vector<vector<ll>> allPrimeFactor = getAllPrimeFactor(primes, n);
    // ll res = 0;
    // cout << "compute begin" << endl;
    // auto pf = allPrimeFactor.begin();
    // ll val = 2;
    // while (val <= n && val > 0) {
    //     res = (res + (n / 2 - val / 2)) % MOD;
    //     val *= 2;
    // }
    // for (++pf; pf != allPrimeFactor.end(); ++pf) {
    //     res = (res + getNumberOfPairs(*pf, n)) % MOD;
    // }
    // cout << res << endl;
    ll P;
    extend_gcd(2, MOD, &MODINV, &P);
    MODINV += MOD;
    ll powerOfTwo = 2;
    ll n = 100000000000LL;
    // ll n = 1000000LL;
    ll val = 0;
    while (powerOfTwo < n) {
        powerOfTwo *= 2;
    }

    while (powerOfTwo != 1) {
        val = (val + numberOfCoprimePairs(n / powerOfTwo)) % MOD;
        powerOfTwo /= 2LL;
    }
    cout << val << endl;
}