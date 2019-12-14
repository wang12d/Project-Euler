#include "Toolbox.h"
#include <iostream>
using std::cout;
using std::endl;
#include <cstdint>
typedef int32_t Int;
typedef int64_t Long;
#include <map>
using std::map;
#include <vector>
using std::vector;
using std::pair;
#include <sys/time.h>
#include <algorithm>
#include <tuple>
using std::tuple;

const Long INF = 10000000LL;
vector<Int> T;
map<tuple<Long, Long, Long, Long>, Int> lines;
map<tuple<Long, Long>, Int> parallel;
map<Long, Int> infInter;

void
init(Int n)
{
    Long s = 290797;
    while (n--) {
        s = s * s % 50515093;
        T.push_back(s % 2000 - 1000);
    }
}

void
findLines(Int n)
{
    for (Int i = 0; i < n; i+=2) {
        Int v = T[i], m = T[i+1];
        for (Int j = i+2; j < n; j += 2) {
            Int x = T[j], y = T[j+1];
            Int numerator = x-v;
            Int intercept = y-m;
            Int constants = m*x-y*v;
            if (numerator == 0) infInter[x]++;
            else {
                Int gcdNI = std::__gcd(numerator, intercept), gcdNC = std::__gcd(constants, numerator);
                intercept /= gcdNI;
                constants /= gcdNC;
                lines[std::make_tuple(intercept, numerator / gcdNI, constants, numerator / gcdNC)]++;
            }
        }
    }
    for (auto const& i: lines) {
        parallel[std::make_tuple(std::get<0>(i.first), std::get<1>(i.first))]++;
    }
    parallel[std::make_tuple(INF, 1)] += infInter.size();
}

int
main(int argc, char** argv)
{
    struct timeval begin, end;
    gettimeofday(&begin, nullptr);
    Int n = 2500;
    if (argc > 1) {
        sscanf(argv[1], "%d", &n);
    }
    init(2*n);
    findLines(2*n);
    Long m = lines.size() + infInter.size();
    Long res = 0;
    for (auto i = parallel.begin(); i != parallel.end(); ++i) {
        res += i->second*(m - i->second);
    }
    cout << "Unique lines: " << m << endl;
    gettimeofday(&end, nullptr);
    cout << res << endl;
    cout << "time cost: " << (double) ((end.tv_sec - begin.tv_sec)*1000000 + end.tv_usec - begin.tv_usec) / 1000000 << "s" << endl;
}
