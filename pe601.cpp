#include <stdio.h>

typedef long long ll;

ll gcd(ll n, ll m)
{
	if (m == 0)
		return n;
	return gcd(m, n % m);
}

ll lcm(ll n, ll m)
{
	return n * m / gcd (n, m);
}

ll solver(ll s, ll n)
{
	int i;
	ll cm = 1;
	for (i = 1; i <= s; ++i) {
		cm = lcm(cm, i);
	}
	ll m = lcm(cm, i);

	return (n / cm - (n % cm == 0 ? 1 : 0)) - (n / m);
}


int main()
{
	printf("F(%d, %d) = %lld\n", 3, 14, solver(3, 14));
	printf("F(%d, %d) = %lld\n", 6, 1000000, solver(6, 1000000));
	ll res = 0;
	int i;
	ll n; ll m;
	for (i = 1; i < 32; ++i) {
		m = 1LL << (2 * i);
		printf("F(%d, %lld) = %lld\n", i, m, n = solver(i, m));
		res += n;
	}

	printf("Ans = %lld\n", res);
}

