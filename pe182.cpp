#include <stdio.h>
#include <string.h>
#include <vector>

#define INF 4000000
#define min(x, y) ((x) > (y)) ? (y) : (x)

int count[INF];
// 扩展gcd算法
// 计算ax + by = gcd(a, b)
int extend_gcd(int a, int b, int *x, int *y)
{
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }

    int x1, y1;
    int d = extend_gcd(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b)*y1;

    return d;
}

int fast_pow_mod(int base, int exp, int mod)
{
    int res = 1;
    while (exp > 0) {
        if (exp & 1) {
            res = (res * base) % mod;
        }
        base = (base * base) % mod;
        exp >>= 1;
    }

    return res;
}

int gcd(int a, int b)
{
    if (b == 0) {
        return a;
    }
    return gcd(b, a%b);
}

int main(void)
{
    int p = 1009, q = 3643;
    int phi = (p-1)*(q-1);
    int n = p*q;

    memset(count, INF, sizeof(count));

    long res = 0;
    for (int i = 3; i < phi; i+=2) {
        if (gcd(i, phi) == 1 && gcd(i-1, phi) == 2) {
            res += i;
        }
    }
    printf("%ld\n", res);
}