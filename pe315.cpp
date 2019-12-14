// Project Euler 315
// Digital root clocks

#include <bits/stdc++.h>

const int MAX_N = 20000000;
using namespace std;
int numbers[MAX_N + 1];
vector<int> primes;
map<int, int> max_bits = { {0, 119}, {1, 68}, {2, 61}, {3, 109}, {4, 78},
						   {5, 107}, {6, 123}, {7, 71}, {8, 127}, {9, 111}};	// MAX的时钟的bit
int saving_bits[1 << 8];

// 给出一个int值，求出它的bit值中1的个数
int get_ones(int n)
{
	int count = 0;

	while (n > 0) {
		// 如果末尾有1
		if (n & 1) {
			++count;
		}
		n >>= 1;
	}
	return count;
}

// 找出从10^7到2*10^7的所有素数
void sieve() 
{
	int i, j;
	memset(numbers, 1, sizeof(numbers));
	numbers[0] = numbers[1] = 0;

	for (i = 2; i*i <= MAX_N; ++i) {
		if (numbers[i]) {
			for (j = i*i; j <= MAX_N && j > 0; j += i) {
				numbers[j] = 0;
			}
		}
	}
	
	for (i = MAX_N / 2; i <= MAX_N; ++i) {
		if (numbers[i]) {
			primes.push_back(i);
		}
	}

}

// 对比特位的初始化
void init_bits() 
{
	int m = (1 << 8) - 1;
	while (m) {
		saving_bits[m] = get_ones(m);
		--m;
	}
}

// 将数的各个数字相加
int sum_digit(int n) 
{
	int sum = 0;
	while (n > 0) {
		sum += n % 10;
		n /= 10;
	}

	return sum;
}

int calc_saving(int n, int m) 
{
	int saving = 0;
	int n_last, m_last;
	while (n && m) {
		n_last = n % 10;
		m_last = m % 10;
		saving += 2*(saving_bits[max_bits[n_last]&max_bits[m_last]]);
		n /= 10; m /= 10;
	}
	return saving;
}

// 计算max的时钟消耗的能量
// 输入是数字跟数组
int calc_max(vector<int> nums) 
{
	vector<int>::iterator first = nums.begin();	// 数组的开头
	vector<int>::iterator last = nums.end();	// 数组的结尾
	int power = 0;
	for (vector<int>::iterator it = first; it + 1 != last; ++it) {
		power += calc_saving(*it, *(it+1));
	}
	return power;
}

vector<int> make_vector(int n) {
	vector<int> res;

	while (n >= 10) {
		res.push_back(n);
		n = sum_digit(n);
	}

	res.push_back(n);
	return res;
}

int main() {
	sieve();
	init_bits();
	cout << calc_max(make_vector(137)) << endl;
	long ans = 0;
	vector<int>::iterator last = primes.end();
	for (vector<int>::iterator it = primes.begin(); it != last; ++it) {
		ans += calc_max(make_vector(*it));
	}
	cout << ans << endl;
}
