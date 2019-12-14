#include <cstdio>

int 
f(int n)
{
    if (n == 1) return 1;
    if (n == 3) return 3;

    if (n % 2 == 0) return f(n/2);

    int k = n / 4;
    int v = n % 4;
    if (v == 1) {
        return 2*f(2*k+1) - f(k);
    }
    if (v == 3) {
        return 3*f(2*k+1) - 2*f(k);
    }
}

int
main(int argc, char **argv)
{
    int i, n;
    sscanf(argv[1], "%d", &n);
    
    for (i = 1; i <= n; ++i) {
        printf("%d: %d\n", i, f(i));
    }
}