#include <iostream>
using std::endl;
using std::cout;
#include "Toolbox.h"
typedef int32_t Int;
typedef int64_t Long;

int
main(int argc, char** argv)
{
    Toolbox::timer();
    Int n = 12345;
    if (argc > 1) {
       sscanf(argv[1], "%d", &n);
    }
    Long hexagon = 0;
    Long ans = 0 ;
    for (Long i = 1; i <= n; ++i) {
        Long tmp = 0;
        Long half = i / 3;
        /**
        for (Int j = 1; j <= half; ++j) {
            tmp = tmp + (i - 3*j + 1)*j;
        }
        **/
        hexagon = hexagon + ((i+1)*(half*half+half) - 2*half*half*half-3*half*half-half)/2;
        ans += hexagon;
    }
    cout << ans << endl;
    Toolbox::timeCost();
}
