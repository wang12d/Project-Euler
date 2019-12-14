/**
 * Project Euler 516 5-smooth totients
 *
 * @date: 2018/05/05
 * @author: 王珩
 *
 **/

#include <bits/stdc++.h>

using namespace std;

long M;
const long MOD = 1L << 32;
long res = 0;

vector<long> smooth_numbers;
vector<long> smooth_primes;	// smooth_number + 1是一个素数
vector<long> power_2;	// 2的幂乘
vector<long> power_3;	// 3的幂乘
vector<long> power_5;	// 5的幂乘

// 给出一个数n，判断其是不是素数
bool is_prime(long n)
{
	if (n == 2) return true;
	if (n % 2 == 0) {
		return false;
	}

	// 循环检测
	for (long i = 3; i*i <= n && i > 0; i += 2) {
		if (n % i == 0) {
			return false;
		}
	}

	return true;
}

void get_power2()
{
	long i = 1;
	while (i <= M && i > 0) {
		power_2.push_back(i);
		i *= 2;
	}
}
			
void get_power3()
{
	long i = 1;
	while (i <= M && i > 0) {
		power_3.push_back(i);
		i *= 3;
	}
}
			
void get_power5()
{
	long i = 1;
	while (i <= M && i > 0) {
		power_5.push_back(i);
		i *= 5;
	}
}
			
// 采用深度优先的策略生成5-smooth数
void genrate_smooth () 
{
	get_power2();
	get_power3();
	get_power5();

	unsigned i, j, k;

	long beg;
	long mid_prod, last_prod;

	unsigned size2 = power_2.size();
	unsigned size3 = power_3.size();
	unsigned size5 = power_5.size();

	for (i = 0; i < size2; ++i) {
		beg = power_2[i];
		for (j = 0; j < size3; ++j) {
			mid_prod = beg*power_3[j];
			if (mid_prod > M || mid_prod < 0) {
				break;
			}	
			for (k = 0; k < size5; ++k) {
				last_prod = mid_prod * power_5[k];
				if (last_prod <= M && last_prod > 0) {
					smooth_numbers.push_back(last_prod);
				}
			}
		}
	}
	
	sort(smooth_numbers.begin(), smooth_numbers.end());

	unsigned size = smooth_numbers.size();
	for (unsigned i = 0; i < size; ++i) {
		long n = smooth_numbers[i] + 1;
		if (n >= 7 && is_prime(n)) {
			smooth_primes.push_back(n);
		}
	}
	
}
// 产生符合题目要求的数
void genrate_smooth_phi(long smooth, unsigned index, unsigned size)
{
	
	for (unsigned i = index; i < size;) {
		long m = smooth*smooth_primes[i];
		// 题目要求和溢出检测
		if (m <= M && m > 0) {
			res = (res + m) % MOD;
			genrate_smooth_phi(m, ++i, size);
		}
		else {
			return;
		}
	}
}

// 计算产生所有题目要求的数
void calc()
{
	cout << "number of smooth number is " << smooth_numbers.size() << endl;
	unsigned size = smooth_numbers.size();
	unsigned p_size = smooth_primes.size();
	cout << "number of prime is: " << smooth_primes.size() << endl;
	long m;

	for (unsigned  i = 0; i < size; ++i) {
		m = smooth_numbers[i];
		res = (res + m) % MOD;
		genrate_smooth_phi(m, 0, p_size);
	}
	/**	
	cout << "having found all number" << endl;
	long res = 0;
	size = smooth_numbers.size();
	for (unsigned i = 0; i < size; ++i) {
		res = (res + smooth_numbers[i]) % MOD;
	}
	**/
	cout << res << endl;
}

int main(int argc, char **argv)
{
	sscanf(argv[1], "%ld", &M);
	cout << "M = " << M << endl;
	genrate_smooth();
	cout << "smooth done." << endl;
	calc();
}
