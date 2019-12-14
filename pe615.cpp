#include <iostream>
#include <vector>
#include "Toolbox.h"
#include <queue>
#include <algorithm>
#include <cmath>

using std::cout;
using std::endl;
using std::vector;


vector<double> fractions;
const int MAX = 1e6;
const vector<int> primes{Toolbox::findPrimes(MAX/2)};
const int BOUND = primes[primes.size() - 1] / 2;
const double ESP = 1e-5;


void 
generate_fraction(double p, int index)
{
    auto v = p;
    while (p <= BOUND) {
        fractions.push_back(p);
        p *= 2;
    }

    for (auto i = index; i < primes.size(); ++i) {
        // cout << primes[i] << endl;
        auto c = v * primes[i] / 2;
        if (c <= BOUND) {
            generate_fraction(c, i);
        }
        else {
            return;
        }
    }
}

int
main(int argc, char** argv)
{
    Toolbox::timer();
    generate_fraction(1.0, 1);
    sort(fractions.begin(), fractions.end());
    double v = fractions[MAX - 1];
    int i;
    for (i = 0;; ++i, v *= 2) { 
        if (std::abs(round(v) - v) < ESP)
            break;
    }
    
    cout << Toolbox::powerWithMOD(2, MAX - i, 123454321) * static_cast<long>(round(v)) % 123454321 << endl;
    Toolbox::timeCost();
}
