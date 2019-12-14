/**
 * Project Euler 609 π sequences
 * @author：王珩
 * @date：2018/5/11
 **/

#include <bits/stdc++.h>
#define MAX_M 100000000 + 1
#define MOD 1000000007
using namespace std;

long ans = 1;
long M;
int is_prime[MAX_M];	// 1为素数，0为合数
int pie_seq[MAX_M];	// π(n)
int prime_size;
vector<int> primes;
map<int, int> ks;

void sieve()
{
	memset(is_prime, 1, sizeof(is_prime));
	memset(pie_seq, 0, sizeof(pie_seq));

	is_prime[0] = is_prime[1] = 0;

	for (int i = 2; i*i <= M; ++i) {
		if (is_prime[i]) {
			for (int j = i*i; j > 0 && j <= M; j += i) {
				is_prime[j] = 0;
			}
		}
	}

	for (int i = 2; i <= M; ++i) {
		if (is_prime[i]) {
			primes.push_back(i);
		}
	}

	prime_size = primes.size() - 1;

}

void clacu_pie()
{
	int prime_cout = 0;
	for (int i = 0; i <= M; ++i) {
		if (is_prime[i]) {
			pie_seq[i] = ++prime_cout;
		}
		else {
			pie_seq[i] = prime_cout;
		}
	}
}

void find_k(int ind)
{
	int flag = (ind == prime_size);
	int p = primes[ind];
	int np;

	flag ? np = M+1 : np = primes[ind+1];
	
	int k = 0;
	int count = 0;
	int pie = pie_seq[p];
	while (1) {
		if (is_prime[pie]) {
			++count;
		}
		else {
			ks[k] += count;
			ks[++k] += (np - p - 1) * count;
			count = 1;
			if (pie == 1) {
				ks[k] += count;
				ks[k+1]  += (np - p - 1) * count;
				break;
			}
		}
		pie = pie_seq[pie];	
	}	
}

void init()
{
	sieve();
	clacu_pie();
	for (int i = 0; i <= 15; ++i) {
		ks[i] = 0;
	}
}

void slover()
{
	init();
	for (int i = 0; i <= prime_size; ++i) {
		find_k(i);
	}
	
	map<int, int>::iterator end = ks.end();	
	for (map<int, int>::iterator it = ks.begin(); it != end; ++it) {
		int val = (it->second);
		if (val == 0) break;
		ans = (ans*(it->second)) % MOD;
	}
	cout << ans << endl;
}
int main(int argc, char *argv[])
{
	sscanf(argv[1], "%ld", &M);
	slover();
}
