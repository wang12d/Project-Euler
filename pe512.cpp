#include <iostream>
#include <time.h>
#include <stdlib.h>
using std::cout;
using std::endl;

#define MAX 500000000

int *totients;

long fast_pow_mod(long base, long exp, int mod)
{
    long res = 1;
    while (exp > 0) {
        if (exp & 1) {
            res = (res * base) % mod;
        }
        base = (base * base) % mod;
        exp >>= 1;
    }

    return res;
}

void init(int n)
{
    totients = (int *) malloc((n+1)*sizeof(int));
    for (int i = 0; i <= n; ++i) {
        totients[i] = 0;
    }
    totients[0] = 0;
    totients[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!totients[i]) {
            for (int j = i; j <= n; j += i) {
                if (!totients[j]) totients[j] = j;
                totients[j] = totients[j] / i * (i - 1);
            }
        }
    }
}

long sum_seq_mod(int q, int n, int mod)
{
    if (n == 0) return 1;
    if (n % 2 == 0) {
        return (1 + q * sum_seq_mod(q, n - 1, mod) % mod) % mod;
    }
    else {
        int half = (n + 2) / 2;
        return (1 + fast_pow_mod(q, half, mod)) * sum_seq_mod(q, half-1, mod) % mod;
    }
}

void run(int n)
{
    long res = 0;
    for (long i = 1; i <= n; i+=2) {
        res += totients[i];
    }

    cout << res << endl;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        cout << "Error! More arguement needed." << endl;
        return 0;
    }

    int n;
    sscanf(argv[1], "%d", &n);
    long start = clock();
    init(n);
    run(n);
    long end = clock();
    free(totients);
    cout << "Time cost: " << ((float) end - start) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
    return 0;
}