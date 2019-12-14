/**
 * Project euler 266
 * 找到最大的小于等于sqrt(n)的因子
 */


#include <bits/stdc++.h>
#include <string.h>
using namespace std;

const int n = 190;
const double ESP = 1e-9;
long M = 10000000000000000L;
vector<int> primes;	// 用来保存素数
// vector<long> p_factor;	// 用来构成乘数的因子
int number[190 + 1];

// 采用素数筛方法找到1~n的素数
void sieve()
{
	memset(number, 1, sizeof(number));
	number[0] = number[1] = 0;
	int i, j;	// 循环指针
	for (i = 2; i*i <= n; ++i) {
		if (number[i]) {
			for (j = i*i; j <= n; j += i) {
				number[j] = 0;
			}
		}
	}

	for (i = 0; i <= n; ++i) {
		if (number[i]) {
			primes.push_back(i);
		}
	}

}


// 采用贪心算法搜寻最大的因子
// 每次将最大的素数因子放到里面，如果放不下，则将下一个放到里面
void calcu()
{
	int size = primes.size();
	int i;
	double logs[size];
	double total = 0.0; 	// 总的素数乘积
	double taken_log;

	for (i = 0; i < size; ++i) {
		taken_log = log(primes[i]);
		total += taken_log;
		logs[i] = taken_log;
	}
	double half_total = total / 2;		// 取根号
	vector<long> p_factor1;
	vector<long> p_factor2;
	vector<long> p_factor3;
	double half_back = half_total;
	double total_back = total;

	for (i = size - 1; i >= 0; --i) {
		taken_log = logs[i];
		if (half_back - taken_log > ESP) {
			p_factor1.push_back(primes[i]);
			half_back -= taken_log;
		}

		if (total_back - half_total > ESP) {
			p_factor2.push_back(primes[i]);
			total_back -= taken_log;
		}
			
	}

	for (i = 0; i < size; ++i) {
		taken_log = logs[i];
		if (half_total - taken_log > ESP) {
			p_factor3.push_back(primes[i]);
			half_total -= taken_log;
		}
	}

	long ret = 1;
	size = p_factor1.size();
	for (i = 0; i < size; ++i) {
		ret = ((ret % M) * p_factor1[i]) % M;
	}
	cout << ret << endl;

	ret = 1;
	size = p_factor2.size();
	for (i = 0; i < size; ++i) {
		ret = ((ret % M) * p_factor2[i]) % M;
	}
	cout << ret << endl;

	ret = 1;
	size = p_factor3.size();
	for (i = 0; i < size; ++i) {
		ret = ((ret % M) * p_factor3[i]) % M;
	}
	cout << ret << endl;
}

int main(void)
{
	sieve();
	calcu();
}
