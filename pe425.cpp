#include <stdlib.h>
#include <stdio.h>
#include <time.h>
// #include "pe_algs.h"

#define MAX 10000000
int nums[MAX + 16];
int sz[MAX + 16];
int primes[MAX + 16];   // 1不是素数，0是素数
long res;

void sieve()
{
    primes[0] = primes[1] = 1;
    for (int i = 2; i * i <= MAX; ++i) {
        if (!primes[i]) {
            for (int j = i * i; j <= MAX; j += i) {
                primes[j] = 1;
            }
        }
    }
}
// 查并集算法
int find(int q)
{
    if (nums[q] != q) {
        return nums[q] = find(nums[q]);
    }

    return q;
}

bool connected(int q, int p)
{
    return find(q) == find(p);
}

void unite(int p, int q)
{
    int p_root = find(p);
    int q_root = find(q);

    if (p_root == q_root) {
        return;
    }

    if (sz[p_root] > sz[q_root]) {
        nums[q_root] = p_root;
    }
    else {
        nums[p_root] = q_root;
        if (sz[p_root] == sz[q_root]) {sz[p_root]++;}
    }
}

void change_one_digit(int n)
{
    int head, mid, tail;
    tail = 0;
    int mutiple = 1;
    int val;

    while (mutiple < n) {
        head = n / mutiple;
        mid = head % 10;
        head = head / 10 * 10;   // 除去中间位
        for (int i = mid - 1; i >= (!(tail < mutiple / 10 && head == 0) ? 0 : 1) ; --i) {
            val = (head + i) * mutiple + tail;
            // printf("%d\n", val);
            if (!primes[val]) {
                // printf("%d\n", val);
                unite(n, val);
            }
        }
        mutiple *= 10;
        tail = n % mutiple;
    }

    if (!connected(n, 2)) {
        // printf("%d\n", n);
        res += n;
    }
}

void run(int n)
{
    long start = clock();
    sieve();
    for (int i = 0; i <= MAX; ++i) {
        nums[i] = i;
        sz[i] = 0;
    }

    for (int i = 2; i <= n; ++i) {
        if (!primes[i]) change_one_digit(i);
    }

    printf("%ld\n", res);
    long end = clock();
    printf("%.4fms", (double) (end - start) / CLOCKS_PER_SEC * 1000);
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Input error!\n");
        return 0;
    }

    int n;
    sscanf(argv[1], "%d", &n);

    // change_one_digit(307);
    run(n);
}