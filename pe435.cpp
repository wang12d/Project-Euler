/**
 * Project Euler Problem 435 Polynomials of Fibonacci numbers
 * @author: Heng
 * @date: 2018/08/29
 * @modified: 2019/08/6
 * Use polynominal of fibnocacc and q-matrix
 **/

#include <cstdio>
#include <vector>
using std::vector;
#include <cstdint>
#include <sys/time.h>
#include <cassert>
typedef uint64_t ULong;
typedef uint32_t UInt;
typedef int64_t Long;
typedef __int128 LL;
typedef vector<LL> Vec;
typedef vector<vector<LL>> Matrix;

void multiply(Matrix& a, Matrix& b);
LL dotP(const Vec& a, const Vec& b);
void fastME(Matrix& a, Matrix& b, ULong expt, ULong MOD);

ULong n = (ULong) (1e15);
ULong MOD = 1307674368000LL;
const UInt size = 3;
Matrix C(size, Vec(size, 0));

int
main(int argc, char** argv)
{
    struct timeval begin, end;
    LL res = 0;
    gettimeofday(&begin, nullptr);
    if (argc > 1) {
        sscanf(argv[1], "%ld", &n);
    }
    --n;
    for (UInt x = 0; x <= 100; ++x) {
        Matrix M{{x, x*x, 1},
                {1, 0, 0},
                {0, 0, 1}};
        Vec b{x, 0, x};
        Matrix A{{1, 0, 0},
                 {0, 1, 0},
                 {0, 0, 1}};
        ULong expt = n;
        fastME(A, M, expt, MOD);
        LL val = dotP(A[0], b);
        res = (res + val) % MOD;
    }
    gettimeofday(&end, nullptr);
    printf("%ld\n", (ULong) res);
    printf("%.5fs\n", (double) ((end.tv_sec - begin.tv_sec) * 1000000 + end.tv_usec - begin.tv_usec) / 1000000);
}

void
multiply(Matrix& a, Matrix& b, ULong MOD)
{
    for (UInt i = 0; i < size; ++i) {
        for (UInt j = 0; j < size; ++j) {
            LL val = 0;
            for (UInt k = 0; k < size; ++k) {
                val = (val + (a[i][k] % MOD) * (b[k][j] % MOD) % MOD) % MOD;
            }
            C[i][j] = val;
        }
    }
    for (UInt i = 0; i < size; ++i) {
        for (UInt j = 0; j < size; ++j) {
            a[i][j] = C[i][j];
        }
    }
    for (UInt i = 0; i < size; ++i) {
        for (UInt j = 0; j < size; ++j) {
            C[i][j] = 0;
        }
    }
}

LL
dotP(const Vec& a, const Vec& b)
{
    LL res = 0;
    for (UInt i = 0; i < size; ++i) {
        res = (res + (a[i] % MOD) * (b[i] % MOD) % MOD) % MOD;
    }
    return res;  
}

void
fastME(Matrix& A, Matrix& M, ULong expt)
{
    while (expt) {
        if (expt & 1) {
            multiply(A, M, MOD);
        }
        multiply(M, M, MOD);
        expt >>= 1;
    }
}
