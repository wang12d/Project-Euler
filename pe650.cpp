#include <bits/stdc++.h>

using namespace std;

#define MOD 1000000007
#define MAXN 20000
typedef long long int lli;

vector<int> number_of_prime_power[MAXN+1];
vector<int> primes;
vector<int> the_inverse_of_prime;
bool not_prime[MAXN+1];

int 
extend_gcd(int a, int b, int *x, int *y)
{
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }

    int x1, y1;
    int gcd = extend_gcd(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b)*y1;
    return gcd;
}

// find the primes up to MAXN
void
find_primes()
{
    not_prime[0] = not_prime[1] = true;
    int i, j;
    for (i = 2; i * i <= MAXN; ++i) {
        if (!not_prime[i]) {
            for (j = i * i; j <= MAXN; j += i) {
                not_prime[j] = true;
            }
        }
    }
    for (i = 0; i <= MAXN; ++i) {
        if (!not_prime[i]) {
            primes.push_back(i);
        }
    }
}

// find the prime power of factorial
int
pot(int n, int p)
{
    int res = 0;
    int acc_prod = p;
    int div_val = n / acc_prod;
    while (div_val) {
        res += div_val;
        acc_prod = acc_prod * p;
        div_val = n / acc_prod;
    }
    return res;
}

void
find_the_power_of_prime()
{
    // 找出所有的n的二项式阶乘，其相应的二项式系数所对应的素数的次数
    int i, j;
    int init_power;
    int power;
    for (auto i = primes.begin(); i != primes.end(); ++i) {
        init_power = 0;
        for (j = 2; j <= MAXN; ++j) {
            power = pot(j, *i);
            if (power) {
                // 只有在所获取的乘数大于零时，才将其添加到对应的数字当中以节约空间
                number_of_prime_power[j].push_back(power*(j-1) - init_power*2);
            }
            init_power += power;
        }
    }
}

lli
fast_mod(lli n, int expt)
{
    lli res = 1;
    while (expt) {
        if (expt & 1) {
            res = res * n % MOD;
        }
        expt >>= 1;
        n = n * n % MOD;
    }
    return res;
}

int
main(int argc, char **argv)
{
    find_primes();
    for (auto i = primes.begin(); i != primes.end(); ++i) {
        int inv, dumb;
        extend_gcd(*i - 1, MOD, &inv, &dumb);
        while (inv < 0) inv += MOD;
        the_inverse_of_prime.push_back(inv);
    }
    find_the_power_of_prime();

    lli res = 1;
    for (int i = 2; i <= MAXN; ++i) {
        int p_size = number_of_prime_power[i].size();
        lli tmp = 1, residual, fm;
        for (int j = 0; j < p_size; ++j) {
            fm = fast_mod(primes[j], number_of_prime_power[i][j]+1);
            if (fm == 0) {
                fm = MOD - 1;
            }
            else {
                fm--;
            }
            residual = (the_inverse_of_prime[j] * fm) % MOD;
            tmp = tmp * residual % MOD;
        }
        res = (tmp + res) % MOD;
    }

    cout << res << endl;
}