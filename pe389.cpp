#include <iostream>
#include <iomanip>

/**
 * 利用随机数个相互独立随机变量之和的性质：
 * Y = X_1 + ... + X_N
 * 那么则有：
 * 期望-E[Y] = E[X]E[N]
 * 方差-var(Y) = var(X)E[N] + (E[X])^2*var(N)
 */

double E[21];   // n-面体期望
double var[21]; // n-面体的方差
double res_var[21];
double res_e[21];
int nums[] = {4, 6, 8, 12, 20};

// 用来计算1-n的总和
double square(double x)
{
    return x*x;
}

double sum_linear(int n)
{
    return n*(n + 1) / 2;
}

double sum_sq(int n)
{
    return n*(n+1)*(2*n+1) / 6;
}

// n-面色子的期望值
double dice_expc(double n)
{
    return sum_linear(n) / n;
}

// 计算期望及方差
void compute_expcetion_var()
{
    for (int j = 0; j < 5; ++j) {
        int i = nums[j];
        E[i] = dice_expc(i);
        var[i] = (sum_sq(i) / i) - square(E[i]);
    }
    res_e[4] = E[4];
    res_var[4] = var[4];
}

void solver()
{
    compute_expcetion_var();
    int size = 5;

    std::cout << std::fixed;
    double e1, e2;
    int prev, now;
    for (int i = 1; i < size; ++i) {
        prev = nums[i-1], now = nums[i];
        e1 = res_e[prev], e2 = E[now];
        res_e[now] = e1*e2;
        res_var[now] = var[now]*e1 + square(e2)*res_var[prev];
    }

    std::cout << std::setprecision(4) << std::fixed << res_var[20] << std::endl;
}

int main(void)
{
    solver();
}