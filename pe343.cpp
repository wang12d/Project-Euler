#include <iostream>
#include <stdlib.h>
#include <map>
#include <vector>
#include <math.h>

typedef long long ll;
using namespace std;

int cache_found = 0;
map<long, long> re;
map<long, vector<long>> mvec;

/**
 * 素数检测算法
 */
ll mulmod(ll a, ll b, ll mod)
{
    ll x = 0,y = a % mod;
    while (b > 0)
    {
        if (b % 2 == 1)
        {    
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
ll modulo(ll base, ll exponent, ll mod)
{
    ll x = 1;
    ll y = base;
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
            x = (x * y) % mod;
        y = (y * y) % mod;
        exponent = exponent / 2;
    }
    return x % mod;
}
 
/*
 * Miller-Rabin primality test, iteration signifies the accuracy
 */
bool Miller(ll p, int iteration)
{
    if (p < 2)
    {
        return false;
    }
    if (p != 2 && p % 2==0)
    {
        return false;
    }
    ll s = p - 1;
    while (s % 2 == 0)
    {
        s /= 2;
    }
    for (int i = 0; i < iteration; i++)
    {
        ll a = rand() % (p - 1) + 1, temp = s;
        ll mod = modulo(a, temp, p);
        while (temp != p - 1 && mod != 1 && mod != p - 1)
        {
            mod = mulmod(mod, mod, p);
            temp *= 2;
        }
        if (mod != p - 1 && temp % 2 == 0)
        {
            return false;
        }
    }
    return true;
}

long bin_search(long n)
{
    long lo = 1, hi = n;
    long mid, m, v;
    long res;
    bool flag = false;
    while (hi - lo >= 1) {
        mid = (lo + hi) / 2;
        m = n / mid;
        // if (m % 2 != 0) ++m;
        v = mid * m + mid - 1;
        if (v < n) {
            lo = mid;
        }
        else {
            hi = mid;
        }
    }

    return hi;
}

long sqrt_method(long n)
{
    long v, tmp1, tmp2;
    long ret_val = 0;
    if (Miller(n, 50)) return n - 1;

    while (n % 2 == 0) {
        ret_val = 1;
        n /= 2;
    }
    if (n == 1) return ret_val;
    tmp1 = n;
    bool flag = true;
    for (long i = 3; i*i <= n; i += 2) {
        while (tmp1 % i == 0) {
            tmp1 /= i;
            ret_val = i - 1;
        }

        if (tmp1 == 1) {
            return ret_val;
        }
        else if (Miller(tmp1, 50)) {
            return max(ret_val, tmp1-1);
        }
            /**
            v = n / i;
            tmp1 = sqrt_method(v);
            tmp2 = sqrt_method(i);
            stored = max(tmp1, tmp2);
            re[v] = tmp1;
            re[i] = tmp2;
            re[n] = stored;
            **/
    }
    if (tmp1 != 1) {ret_val = max(ret_val, tmp1-1);}
    return ret_val;
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        cout << "Input error!" << endl;
        return 0;
    }

    int n;

    sscanf(argv[1], "%d", &n);

    long tmp, tri_tmp;
    long res = 0;
    for (long i = 1; i <= n; ++i) {
        tri_tmp = i;
        // tmp = f(tri_tmp);
        tmp = max(sqrt_method(tri_tmp+1), sqrt_method(i*i - i + 1));
        res += tmp;
    }
    cout << res << endl;
}