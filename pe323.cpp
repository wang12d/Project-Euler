#include <cstdio>
#include <cmath>

using namespace std;

const double ESP = 1e-11;

int main(int argc, char **argv)
{
    int bits, rounds;
    sscanf(argv[1], "%d", &bits);
    sscanf(argv[2], "%d", &rounds);

    double val = 1.0;

    int iter = 1;
    while (iter <= rounds) {
        auto allZero = pow(0.5, iter);
        auto prev = pow(0.5, iter-1);
        auto done = pow(allZero, bits) - pow(prev, bits);
        val += iter * done;
        iter++;
    }

    printf("%.10lf\n", val);
}