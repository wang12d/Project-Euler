#include <stdio.h>
#define SMOD 50515093
#define MAX_N 10000000

long s = 290797;
int p, n, v;
long p_sum[24];
int t[MAX_N];
long m;

long pow(long base, long expt)
{
	long res = 1;
	while (expt--) {
		res = base * res;
	}
	return res;
}

void get_next()
{
	s = s * s % SMOD;
	int mo;
	for (int i = 0; i < v; ++i) {
		mo = s % p;
		t[i] = mo;
		s = s * s % SMOD;
	}
	
}

long fast_mod(long base, long expt)
{
	long res = 1;
	
	while (expt > 0) {
		if (expt & 1) {
			res = res * base % m;
		}

		base = base * base % m;
		expt >>= 1;
	}

	return res;
}

int main(int argc, char **argv)
{
	sscanf(argv[1], "%d", &p);
	sscanf(argv[2], "%d", &n);
	sscanf(argv[3], "%d", &v);
	
	for (int i = 0; i < n; ++i) {
		p_sum[i] = pow(p, i);
	}
	for (int i = 1; i < n; ++i) {
		p_sum[i] += p_sum[i-1];
	}

	m = pow(p, n);
	get_next();
	long res = 0;
	int last = n - 1;
	for (int i = 0; i < v; ++i) {
		res = (res + t[i] * p_sum[i >= n ? last : i] % m) % m;
	}

	printf("%ld\n", res);
}

