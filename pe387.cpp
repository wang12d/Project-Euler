/**
 * Project Euler 387 Harshad Numbers
 * 
 * 按照题目的意思去做即可
 */

#include <bits/stdc++.h>

using namespace std;

int tail_digit[4] = {1, 3, 7, 9};
long ans = 0;
long N;

bool is_prime(long n)
{
	if (n == 2) return true;
	if (n % 2 == 0) return false;
	for (long i = 3; i*i <= n; i += 2) {
		if (n % i == 0) {
			return false;
		}
	}
	return true;
}

// 判断一个数是不是niven数
bool is_niven(long n, int digit_sum)
{
	return (n % digit_sum) == 0;
}

void add_ans(long n)
{
	long m1, m2;
	m1 = n*10;
	if (m1 > N) {
		return;
	}

	for (int i = 0; i < 4; ++i) {
		m2 = m1 + tail_digit[i];
		if (is_prime(m2)) {
			ans += m2;
		}
	}
}

void iter(long n, int digit_sum) 
{
	long m = 10 * n;
	if (m > N) {
		return;
	}

	long m1;
	int ds;
	for (int i = 0; i < 10; ++i) {
		m1 = m + i;
		ds = digit_sum + i;
		if (m1 % ds == 0) {
			if (is_prime(m1 / ds)) {
				add_ans(m1);
			}
			iter(m1, ds);
		}
	}
}

void solver()
{
	for (int i = 1; i < 10; ++i) {
		iter(i, i);
	}

	cout << ans << endl;
}

int main(int argc, char **argv) 
{
	sscanf(argv[1], "%ld", &N);

	solver();

}
