#include <iostream>
using std::cout;
using std::endl;
 
const int val = 30000;
int cnt[val+1];

int
main(int argc, char** argv)
{
    int n, m;
    sscanf(argv[1], "%d", &n);
    sscanf(argv[2], "%d", &m);
    int a, b, c;
    for (a = 1; a <= n; ++a) {
        for (b = a; b <= n; ++b) {
            int p = a*b;
            for (c = b; c <= n; ++c) {
                int raw = 2*p + 2*c*(a+b);
                if (raw <= val && raw > 0) cnt[raw]++;
                else    break;
                int summation = a+b+c;
                for (int i = 1; ; ++i) {
                    int total = raw + 4*summation + 8*(i - 1);
                    if (total <= val && total > 0) cnt[total]++;
                    else break;
                    raw = total;
                }
            }
        }
    }
    for (int i = 0; i <= val; ++i) {
        if (cnt[i] == m) {
            cout << i << endl;
            return 0;
        }
    }
}