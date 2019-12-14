#include <iostream>
using std::cout;
using std::endl;
#include "Toolbox.h"
typedef int32_t Int;
typedef int64_t Long;
#include <vector>
using std::vector;

Int base = 10;

bool isPrime(const Long&);

Int
main(Int argc, char** argv)
{
    Toolbox::timer();
    if (argc > 1) {
        sscanf(argv[1], "%d", &base);
    }
    vector<Int> primes;
    Long maxV = (Long) (1.0 / .00000000137);
    for (Long i = (Long) (1.0/.00000000138); i < maxV; ++i) {
        if (56789LL * (i % 100000) % 100000 == 99999 && isPrime(i)) primes.push_back(i);
    }
    cout << "number of prime: " << primes.size() << endl;
    for (auto p = primes.rbegin(); p != primes.rend(); ++p) {
        Long t = 0, r = 1, n = 0;
        Long length = *p-1;
        Long res = 0; bool flag = true;
        do {
            t++;
            Long x = r*base;
            Long d = x / (*p);
            r = x % (*p);
            if (t <= 11 || length < 6) n = n*base + d;
            res += d;
            if (t == 11) {
                if (n != 137) {flag = false; break;}
            }
            length--;
        } while (r != 1);
        if (t == *p-1 && flag && n%100000 == 56789) {
            cout << res << " " << *p << endl;
            Toolbox::timeCost();
        }
    }
}

bool
isPrime(const Long& n)
{
    if (n == 1)     return false;
    if (n % 2 == 0) return false;
    for (Long i = 3; i*i <= n; i += 2) {
        if (i < 0) return true;
        if (n % i == 0) return false;
    }
    return true;
}
