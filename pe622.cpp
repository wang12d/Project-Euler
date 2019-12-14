/*
 * @Author: WangHeng 
 * @Date: 2018-12-27 13:10:14 
 * @Last Modified by: WangHeng
 * @Last Modified time: 2018-12-27 13:31:58
 */

#include <iostream>
// n是2的指数
int
reverseCom(long val)
{
    long mod = 2 * val - 1;
    long a = val, b = mod - a;
    int cnt = 1;

    while (a != 1) {
        if (a % 2) {
            b /= 2;
            a = mod - b;
        }
        else {
            a /= 2;
            b = mod - a;
        }
        cnt++;
        if (cnt > 60)   return -1;
    }

    return cnt;
}

int
main(int argc, char **argv)
{
    long x, y;
    long val, res = 0;

    // 验证输入已由网页端处理完毕，存储在pe622.out里面
    // 设S(n) = p
    // 则有2^(p-1) % (n - 1) == n / 2
    // 我不知道如何证明它，这是我通过验证数据得出来的结论
    while (std::cin >> x >> y) {
        if (y > 0) {
            if (reverseCom(y) == 60) {
                res += 2 * y;
            }
        }
    }
    
    printf("res = %ld\n", res);
}