#include <iostream>
#include <vector>
#include <queue>
#include "Toolbox.h"

using std::vector;
using std::queue;

const long long MAX = 10e13;
vector<long long> p_smooth;
const vector<long long> init_primes{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
vector<queue<long long>> candidates(init_primes.size(), queue<long long>{});

void generate_47_smooth()
{
    for (auto i = 0; i < init_primes.size(); ++i) {
        candidates[i].push(init_primes[i]);
    }
    
    while (true) { 
        long long min_val = MAX+1;
        auto index = -1;
        for (auto i = 0; i < candidates.size(); ++i) {
            auto& q = candidates[i];
            if (!q.empty() && min_val > q.front()) {
                index = i;
                min_val = q.front();
            }
        }
        if (index != -1) {
            auto& q = candidates[index];
            p_smooth.push_back(q.front()); q.pop();
            for (auto j = index; j < candidates.size(); ++j) {
                long long val = min_val * init_primes[j];
                if (val <= MAX && val > 0) {
                    candidates[j].push(val);
                }
            }
        }
        else {
            break;
        }
    }
}

int
main(int argc, char** argv)
{
    Toolbox::timer();
    generate_47_smooth();
    long long sum = 1;
    for (auto i = p_smooth.begin(); i != p_smooth.end(); ++i) {
        auto p = *i;
        if (*(i+1) == p+1) {
            sum += p;
        }
    }
    std::cout << sum << std::endl;
    Toolbox::timeCost();
}
