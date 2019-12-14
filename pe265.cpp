#include <vector>
#include <iostream>
#include <ctime>

using std::vector;
using std::cout;
using std::endl;

const int n = 5;
const int N = 1 << n;
vector<bool> bitNumber(N, false);
const int MAX = N - 1;
long sum = 0;

void
recurConstructVal(int layer = 1, long val = 0)
{
    if (layer < N) {
        val <<= 1;
        if (bitNumber[val & MAX] == false) {
            bitNumber[val & MAX] = true;
            recurConstructVal(layer+1, val);
            bitNumber[val & MAX] = false;
        }
        if (bitNumber[(val+1) & MAX] == false) {
            bitNumber[(val+1) & MAX] = true;
            recurConstructVal(layer+1, val+1);
            bitNumber[(val+1) & MAX] = false;
        }
    }
    else {
        sum += val >> (n - 1);
    }
}

int
main(int argc, char** argv)
{
    clock_t begin = clock();
    bitNumber[0] = true;
    recurConstructVal();
    clock_t end = clock();
    cout << "sum = " << sum << endl;
    cout << "time cost: " << (double) (end - begin) / CLOCKS_PER_SEC << "s" << endl;
}

