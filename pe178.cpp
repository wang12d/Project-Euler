#include <cstdio> 
#include <cstring> 
#include <cstdint> 
#include <cassert> 
#include <sys/time.h>
typedef int32_t Int; 
typedef int64_t Long;


const Int MAXDN = 40 + 1;
//const Int MAXN = 10 + 1;
const Int MAXT = 10;
const Int INTERVAL = 32;

Long dp[MAXDN][MAXT];

int
main(int argc, char** argv)
{
    struct timeval begin, end;
    gettimeofday(&begin, nullptr);
    Int n = MAXDN;
    if (argc > 1) {
        sscanf(argv[1], "%d", &n);
    }
    assert(n >= 9);
    Long result = 0;
    for (Int v = 1; v < MAXT-1; ++v) {
        dp[1][v] = 1;
        for (Int i = 2; i <= INTERVAL; ++i) {
            for (Int t = 0; t < MAXT; ++t) {
                if (t == 0) {
                    dp[i][t] = dp[i-1][t+1];
                }
                else if (t == 9){
                    dp[i][t] = dp[i-1][t-1];
                }
                else {
                    dp[i][t] = dp[i-1][t+1] + dp[i-1][t-1];
                }
            }
        }
        for (Int i = 2; i <= INTERVAL; ++i) {
            result += dp[i][v+1];
        }
    }
    gettimeofday(&end, nullptr);
    printf("%ld\n", result);
    printf("%.5fs\n", (double) ((end.tv_sec - begin.tv_sec)*1000000 + end.tv_usec - end.tv_usec) / 1000000);
}
