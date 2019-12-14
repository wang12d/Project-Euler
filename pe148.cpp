#include <bits/stdc++.h>
#include <time.h>

using namespace std;

// 利用卢卡斯定理计算
long compute_base_7(long k)
{
    long ret = 1;
    long rem = 0;
    while (k > 0) {
        rem = k % 7;
        k /= 7;
        ret *= (rem+1);
    }
    return ret;
}
int main()
{
    clock_t t_start = clock();
    long n = 1000000000 - 1;
    long c = 1;
    long sum = 0;
    while (n >= 0) {
        sum += compute_base_7(n);
        n -= 1; 
    }

    printf("%ld\n", sum);
}  