#include <iostream>
using std::cout;
using std::endl;
typedef int32_t Int;
typedef int64_t Long;
#include "Toolbox.h"
#include <set>
using std::set;
using std::pair;
using std::make_pair;
#include <vector>
using std::vector;

Long n = 100000000LL;
set<pair<Int, Int>> intercept;

Int
main(int argc, char** argv)
{
    Toolbox::timer();
    if (argc > 1) {
        sscanf(argv[1], "%ld", &n);
    }
    Long res = (n+1)*n/2;
    vector<Int> totients = Toolbox::findTotients(n); 
    totients[1] = 1;
    for (Int i = 1; i <= n; ++i) {
        // cout << "totient[" << i << "] = " << totients[i] << endl;
        res -= totients[i];
    }
    res = 6 * res;
    cout << res << endl;
    Toolbox::timeCost();
}
