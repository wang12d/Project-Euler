/**
 * Project Euler 429 Sum of squares of unitary divisors
 * @author：王珩
 * @date：2018/5/6
 *
 * 解题思路：又算术基本定理可得，n=p_1^k_n*...*p_n^k_n。
 *			 则每一个unitary divisors都是包含一个完全的素数因子。
 *			 由数学归纳法可得：(p_1^(2*k_1)+1)...(p_n^(2*k_n)+1)
 **/

#include <bits/stdc++.h>

using namespace std;

long N;	// 输入

const int MOD = 1000000009;
map<int, int> prime_power;	// 用来储存每一个素数和它的指数
vector<int> primes;

void sieve ()
{
	vector<int> numbers;

	numbers.resize(N+1, 1);
	// 设置筛选条件
	//memset(&numbers, 1, sizeof(numbers));
	// 排除0和1
	numbers[0] = numbers[1] = 0;
	// 用筛选法找出所有的素数
	for (int i = 2; i*i <= N; ++i) {
		if (numbers[i]) {
			for (int j = i*i; j > 0 && j <= N; j += i) {
				numbers[j] = 0;
			}
		}
	}

	for (int i = 2; i <= N; ++i) {
		if (numbers[i]) {
			primes.push_back(i);
		}
	}

}

// 给出一个素数找出它在n!中的幂
int pot(int p) 
{
	int power = 0;
	long mul = p;
	while (mul <= N && mul > 0) {
		power += (N / mul);
		mul *= p;
	}

	return power;
}

// 产生所有的素数和指数对
void generate_power()
{
	vector<int>::iterator end = primes.end();
	for (vector<int>::iterator it = primes.begin(); it != end; ++it) {
		int p = (*it);
		prime_power[p] = pot(p);
	}
}

// 快速幂模算法
long fast_mod(long base, long power)
{
	long res = 1;
	base = base % MOD;
	while (power > 0) {
		if (power & 1) {
			res = res * base % MOD;
		}
		base = base * base % MOD;
		power >>= 1;
	}

	return res;
}

// 对程序进行初始化，将它分解成算术基本形式 
void init()
{
	sieve();
	generate_power();
}

void solver()
{
	init();
	long res = 1;
	map<int, int>::iterator end = prime_power.end();
	long m;
	for (map<int, int>::iterator it = prime_power.begin(); it != end; ++it) {
		m = fast_mod(it->first, 2*(it->second));
		m = (m + 1) % MOD;
		res = (res * m) % MOD;
	}

	cout << res << endl;
}

int main (int argc, char **argv)
{
	sscanf(argv[1], "%ld", &N);
	solver();
}
