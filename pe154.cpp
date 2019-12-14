#include <bits/stdc++.h>

#define MAXN 200000
using namespace std;

typedef long long ll;
typedef struct {
    int num_two;
    int num_five;
}   mul;

mul M[MAXN + 16];

ll factorial(int n)
{
    ll res = 1;
    for (int i = 2; i <= n; ++i) {
        res *= i;
    }

    return res;
}

int get_ways(int i, int j, int k)
{
    int equal1 = i == j;
    int equal2 = j == k;
    if (equal1 & equal2) {
        return 1;
    }
    else if (equal1 | equal2) {
        return 3;
    }

    return 6;
}

int pot(int n, int p)
{
    int ans = 0;
    for (int i = p; i <= n; i *= p) {
        ans += n / i;
    }
    return ans;
}

void compute_pot()
{
    for (int i = 0; i <= MAXN; ++i) {
        M[i].num_two = pot(i, 2);
        M[i].num_five = pot(i, 5);
    }
}

// 计算该金字塔数是否能被10^12整除
bool is_mupltiple(int i, int j, int k)
{
    int twos = M[i].num_two + M[j].num_two + M[k].num_two;
    int fives = M[i].num_five + M[j].num_five + M[k].num_five;

    return M[MAXN].num_two - twos >= 12 && M[MAXN].num_five - fives >= 12;
}

// 得到所有的a+b+c = n的组合
ll solver(int n)
{
    ll res = 0;
    for (int i = 0; i <= n / 3; ++i) {
        int m = n - i;
        int half_m = m / 2;
        for (int j = i; j <= half_m; ++j) {
            int num = n - i - j;
            if (is_mupltiple(i, j, num)) {
                res += get_ways(i, j, num);
            }
        }
    }
    return res;
}

int main(void)
{
    compute_pot();
    printf("%lld\n", solver(MAXN));
}