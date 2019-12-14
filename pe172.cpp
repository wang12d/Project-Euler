/*
 * @Author: WangHeng 
 * @Date: 2018-12-27 18:34:29 
 * @Last Modified by: WangHeng
 * @Last Modified time: 2018-12-27 18:48:45
 */

#include <iostream>
#include <vector>
#include <set>
#define M 10
#define N 17
#define VAL 355687428096000

std::vector<int> digits;
std::set<long> numbers;
std::vector<int> combs;

int repeatTimes[M]; // 每个数字的重复出现次数
int n = 29, r = 17;
long ways;

long
fact(int n)
{
    long val = 1;
    int i;
    for (i = 1; i <= n; ++i) {
        val *= i;
    }
    return val;
}

long
pow(int expt)
{
    long val = 1;
    while (expt--) {
        val *= 10;
    }

    return val;
}

// 生成所有需要的数字
void
init()
{
    int i;
    for (i = 0; i < 9; ++i) {
        digits.push_back(i);
        digits.push_back(i);
        digits.push_back(i);
    }
    digits.push_back(9);
    digits.push_back(9);
}

// 将数字生成对应的数
long
generateNumber(const std::vector<int> &vec)
{
    long val = 0;
    long p = 0;
    int i;
    for (auto i = vec.begin(); i != vec.end(); ++i) {
        val += pow(p) * (*i);
        ++p;
    }

    return val;
}

// 计算每个生成数的组合情况
void
numberOfWays(long number)
{
    int i;
    long val = VAL;
    for (i = 0; i < M; ++i) {
        repeatTimes[i] = 0;
    }

    for (i = 0; i < N; ++i) {
        repeatTimes[number%10]++;
        number /= 10;
    }
    for (i = 0; i < M; ++i) {
        val /= fact(repeatTimes[i]);
    }

    ways += val;
}

// 生成所有的排列
void
combVec(int offset, int k)
{
    if (k == 0) {
        numbers.insert(generateNumber(combs));
        return;
    }
    int i;
    for (i = offset; i <= digits.size() - k; ++i) {
        combs.push_back(digits[i]);
        combVec(i+1, k-1);
        combs.pop_back();
    }
}

int
main(int argc, char **argv)
{
    init();
    combVec(0, r);
    for (auto i = numbers.begin(); i != numbers.end(); ++i) {
        numberOfWays(*i);
    }

    std::cout << "number of ways = " << 9*ways << std::endl;
}