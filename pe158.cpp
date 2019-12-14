#include <stdio.h>


long combs[30][30];


void
computeComb()
{
    combs[0][0] = 1;
    for (int i = 1; i < 30; ++i) {
        combs[i][i] = 1;
        combs[i][0] = 1;
        combs[i][1] = i;
    }

    for (int i = 1; i < 30; ++i) {
        for (int k = 2; k < i; ++k) {
            combs[i][k] = combs[i-1][k-1] + combs[i-1][k];
        }
    }
}

long 
comb(int n, int c)
{
    if (c < 0 || c > n)     return 0;
    return combs[n][c];
}

long  
print_ans(int n)
{
    long res = 0;
    int d, i, j;
    for (d = 2; d <= n; ++d) {
        for (i = 1; i <= 26; ++i) {
            for (j = 0; j < d-1; ++j) {
                // 对于每一个字符i，设字符串长度为n，那么每个字符可以放的位置为2～n，
                // 这也是第一重循环的意思，第二重循环表示一个有26个字母
                // 由于题目要求只能有一个字符在其左边的位置，那么在该字符后面的字符只能
                // 放在其位置的前面，因此有comb(26-i, j)，j的位置为0~d-2,即一个也不用
                // 后面的到最多填充d-2个，第d-1个必须为d个位置左边的字符。
                // 根据题目意思，这些字符放置的位置都是逆序的
                // 那么很容易得到下面的公式。。
                res += comb(26-i, j) * comb(i-1, d-j-1) * comb(i-d+j, n-d);
            }
        }
    }

    return res;
}

int 
main(int argc, char **argv)
{
    int n;
    computeComb();

    long ans = 0;
    
    for (int i = 3; i <= 26; ++i) {
        long v = print_ans(i);
        if (ans < v) {
            n = i;
            ans = v;
        }
    }

    printf("Get most word at n = %3d, words = %ld\n", n, ans);
}