#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <cstring>
#include <map>

#define MOD 1000000000
#define MAX 50000

using namespace std;
typedef long long ll;
typedef unsigned int ui;
typedef pair<ui, ui> Key;

vector<ui> primes;
ui prev_fib = 0;
ui next_fib = 1;
map<Key, ll> mems;
ui numbers[MAX+1];
ll res;

ui get_next_fib()
{
	ui tmp = next_fib;
	next_fib = prev_fib + tmp;
	prev_fib = tmp;
}

void sieve()
{
	memset(numbers, 1, sizeof(numbers));
        numbers[0] = numbers[1] = 0;	
	for (ui i = 2; i * i <= MAX; ++i) {
		if (numbers[i]) {
			for (ui j = i * i; j <= MAX; j += i) {
				numbers[j] = 0;
			}
		}
	}

	for (ui i = 2; i <= MAX; ++i) {
		if (numbers[i]) {
			primes.push_back(i);
		}
	}
}

// 可以采用相当于动态规划的方法来优化这个问题
// 采用不断的向下进行拆分的方法，将n拆解成一个一个素数的和
ll recur_solver(ll primes_sum, int number, ll prod, ui ind)
{
	if (number == 1 || number < 0 || ind < 0 || primes_sum == 0) {
		return 0;
	}

	if (number == 0) {
		return prod;
	}

	if (mems.find(Key (primes_sum, number)) != mems.end()) {
		return prod * mems[Key (primes_sum, number)] % MOD;
	}

	ui p = primes[ind];

	Key pa (primes_sum, number);
	mems[pa] = (recur_solver(primes_sum, number - p, p, ind) + recur_solver(primes_sum - p, number, 1, ind - 1)) % MOD;
	return prod * mems[pa] % MOD;
}

ll slow_solver (ll primes_sum, int number, ll prod, ui ind)
{
	if (number == 0) {
		return prod;
	}

	if (number == 1 || number < 0 || ind < 0 || primes_sum == 0) {
		return 0;
	}

	// if (mems.count(Key (primes_sum, number))) {
		// return prod * mems[Key (primes_sum, number)] % MOD;
	// }

	ui p = primes[ind];

	return mems[Key (primes_sum, number)] = (slow_solver(primes_sum, number - p, prod * p % MOD, ind) + slow_solver(primes_sum - p, number, prod, ind - 1)) % MOD;
}

void solver(int cnt)
{
	sieve();
	ui size = primes.size();
	ui i;
	ui p;
	ll ps = 0;
	
	while (cnt--) {

		get_next_fib();
		for (i = 0; i < size; ++i) {
			p = primes[i];
			ps += p; 
		}	
	
		res = (res + recur_solver(ps, next_fib, 1, i-1)) % MOD;
		printf("fib = %u, F = %lld\n", next_fib, mems[Key (ps, next_fib)]);
		ps = 0;
	}
}

int main(int argc, char **argv)
{
	int cnt;
	cnt = atoi(argv[1]);
	solver(cnt);
	printf("%lld\n", res);
}
