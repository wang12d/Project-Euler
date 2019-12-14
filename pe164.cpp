/*
 * @Author: WangHeng 
 * @Date: 2018-12-27 15:14:27 
 * @Last Modified by: WangHeng
 * @Last Modified time: 2018-12-27 15:21:55
 */

#include <iostream>
#define max(x, y)   ((x) > (y) ? (x) : (y))

long sum[21][11][10];
long ways;
int n;


long
bruteWay(int twoSum, int oneSum, int m)
{
    if (m == 1) {
        return 10 - max(twoSum, oneSum);
    }

    int i, v = max(oneSum, twoSum);
    long val = 0;
    for (i = 0; i < 10 - v; ++i) {
        val += bruteWay(oneSum+i, i, m-1);
    }

    return val;

}

long
countWay(int twoSum, int oneSum, int m, int one, int two)
{
    if (sum[m][two][one]) {
        return sum[m][two][one];
    }
    if (m == 1) {
        return sum[m][two][one] = 10 - max((twoSum == 10 ? -1 : twoSum), oneSum);
    }

    int i, v = max(oneSum, (twoSum == 10 ? -1 : twoSum));
    for (i = 0; i < 10 - v; ++i) {
        sum[m][two][one] += countWay(oneSum + i, i, m-1, i, one);
    }

    return sum[m][two][one];
}

int
main(int argc, char **argv)
{
    sscanf(argv[1], "%d", &n);
    int i;
    long brute = 0;
    if (n == 1) {
        ways = 10;
    }
    else {
        for (i = 1; i < 10; ++i) {
            brute = countWay(10, i, n-1, i, 10);
            ways += brute;
        }
    }


    std::cout << "number of ways = " << ways << std::endl;
}