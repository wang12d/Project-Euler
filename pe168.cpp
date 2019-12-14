#include <iostream>
using std::cout;
using std::endl;
#include <cassert>
#include "Toolbox.h"

typedef long long ll;

int n = 10;

ll
findSumOfRotationNumber(int n, ll MOD = 100000)
{
    // a number of n can be expressed as
    // the form of head*10**(n-1) + y
    ll result = 0;
    ll head, quotient;
    for (head = 1; head < 10; ++head) {
        for (quotient = 1; quotient <= head; ++quotient) {
            int divded = 10*quotient - 1;
            int remain = Toolbox::powerWithMOD(10, n, divded, head) - (quotient*head % divded);
            if (remain == 0) {
               ll residule = Toolbox::powerWithMOD(10, n, divded*MOD, head) - head*quotient;
               result = (result + 10*residule/divded + head) % MOD;
            }
        }
    }
    return result;
}

int
main(int argc, char** argv)
{
    Toolbox::timer();
    if (argc > 1) {
       sscanf(argv[1], "%d", &n); 
    }
    ll ans = 0, resV;
    for (int i = 1; i < n; ++i) {
        resV = findSumOfRotationNumber(i);
        ans += resV;
    }
    cout << ans % 100000 << endl;
    Toolbox::timeCost();
}
