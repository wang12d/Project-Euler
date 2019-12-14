#include <iostream>

#define MAX 1000000
#define max(x, y) ((x) > (y)) ? (x) : (y)

int drs[MAX+16];
bool is_prime[MAX+16];

int get_drs_val(int n) 
{
    int val = 0;
    while (n) {
        val += n % 10;
        n /= 10;
    }
    if (val >= 10) {
        val = get_drs_val(val);
    }
    return val;
}

// 初始化值
void set_init()
{
    for (int i = 1; i <= MAX; ++i) {
        drs[i] = get_drs_val(i);
    }

    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i*i <= MAX; ++i) {
        if (is_prime[i]) {
            for (int j = i*i; j <= MAX; j += i) {
                is_prime[j] = false;
            }
        }
    }
}

void factor(int n)
{
    for (int i = 2; i*i <= n; ++i) {
        if (n % i == 0) {
            drs[n] = max(drs[i] + drs[n / i], drs[n]);
        }
    }
}

int main(void)
{
    long val = 0;
    set_init();
    for (int i = 1; i <= MAX; ++i) {
        if (!is_prime[i]) factor(i);
    }

    for (int i = 2; i < MAX; ++i) {
        val = val + drs[i];
    }

    std::cout << drs[24] << std::endl;
    std::cout << val << std::endl;
}