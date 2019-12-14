/**
 * Project Euler 211 Disvisor Square Sum
 * @anthour: Wang
 * @Date: 2018/08/25
 * @Last-modified: 2018/08/25
 * 
 * using the sieve to find out all divisors.First choose a number i,
 * then 2*i, 3*i, ... can be divied by i, then add them up.
 * Time compliexity, O(nlog(n))
 **/

#include <iostream>
#define MAX 64000000 + 16

long v[MAX];

bool is_square(long n)
{
    if (n == 1) return true;
    long lo = 1, hi = n / 2;
    long mid, val;
    while (hi >= lo) {
        mid = (lo + hi) / 2;
        val = mid * mid;
        if (val == n) {
            return true;
        }
        // mid is biger than actual
        else if (val < 0 || val > n) {
            hi = mid - 1;
        }
        else {
            lo = mid + 1;
        }
    }

    return false;
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        std::cout << "Input error." << std::endl;
        return 0;
    }

    long n;
    sscanf(argv[1], "%ld", &n);
    long res = 0;
    for (int i = 1; i <= n; ++i) {
        v[i] = 1;
    }

    for (long i = 2; i <= n/2; ++i) {
        for (long j = i; j <= n; j += i) {
            v[j] += (i * i);
        }
    }

    for (long i = n/2+1; i <= n; ++i) {
        v[i] += (i * i);
    }

    for (int i = 1; i <= n; ++i) {
        if (is_square(v[i])) {
            res += i;
        }
    }

    std::cout << res << std::endl;
}