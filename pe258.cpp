#include <iostream>
using std::cout;
using std::endl;
#include <vector>
using std::vector;
#include <cstdint>
using Long=int64_t;
using Int=int32_t;
#include <cassert>
#include <sys/time.h>

const Int sz = 2000;
const Long MOD = 20092010LL;
const Long M = 1000000;
Long P = M*M*M / sz;

vector<Long> sum;
vector<Long> G;
vector<Long> A;

void
multiply(vector<Long>& a, vector<Long>& b)
{
    vector<Long> tmp(2*sz, 0);
    // Now get the first value of a
    for (Int i = sz; i < 2*sz; ++i) {
        tmp[i] = a[i-sz];
    }
    // Get the shift value of second column
    for (Int i = sz-1; i >= 0; --i) {
        tmp[i] = tmp[sz+i] - tmp[i+1];
    }
    // Now compute matrix multiplication
    // First column
    for (Int i = 0; i < sz; ++i) {
        sum[i] = tmp[i+1] * b[0];
    }
    for (Int i = 1; i < sz; ++i) {
        for (Int j = 0; j < sz; ++j) {
            sum[j] = (sum[j] + b[i] *  tmp[sz - i + j + 1] % MOD) % MOD;
        }
    }
    for (Int i = 0; i < sz; ++i) {
        b[i] = sum[i];
    }
}

int
main()
{
    struct timeval begin, end;
    gettimeofday(&begin, nullptr);
    sum.resize(sz, 0);
    G.resize(sz, 0);
    A.resize(sz, 0);
    for (Int i = 0; i < sz; ++i) A[i] = 1;
    G[0] = 1;
    G[1] = 1;
    G[sz-1] = 1;
    Long expt = P;
    while (expt) {
        if (expt & 1) {
            multiply(G, A);
        }
        multiply(G, G);
        expt >>= 1;
    }
    gettimeofday(&end, nullptr);
    printf("%ld\n", A[0]);
    printf("%.5fs\n", (double) ((end.tv_sec - begin.tv_sec) * M + end.tv_usec - begin.tv_usec) / M);
}
