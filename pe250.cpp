#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MOD = 250;
const int INF = 250250;
const long long TAIL = 10000000000000000LL;

vector<ll> numbers;
vector<ll> moduloCount(MOD, 0);

ll 
slowMod(ll base, ll expt, ll m)
{
    ll res = 1;
    while (expt--) {
        res = res * base % m;
    }
    return res;
}

ll
fastMod(ll base, ll expt, ll m)
{
    ll res = 1;
    while (expt) {
        if (expt & 1) {
            res = res * base % m;
        }
        base = base * base % m;
        expt >>= 1;
    }
    if (res < 0) {
        return slowMod(base, expt, m);
    }
    return res;
}

ll
getNumberOfSum(const vector<ll>& numbers)
{
    vector<ll> dp(MOD, 0);
    dp[0] = 1;
    vector<ll> dpCopy = dp;
    for (ll n: numbers) {
        for (ll i = 0; i < MOD; ++i) {
            ll modulo = (n + i) % MOD;
            dp[modulo] = (dp[modulo] + dpCopy[i]) % TAIL;
        }
        dpCopy = dp;
    }
    return --dp[0];
}

int
main(int argc, char** argv)
{
    ll val = 0;
    for (int i = 1; i <= INF; ++i) {
        numbers.push_back(fastMod(i, i, MOD));
    }
    // sort(numbers.begin(), numbers.end());
    cout << getNumberOfSum(numbers) << endl;
}