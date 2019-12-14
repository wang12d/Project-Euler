#include <iostream>

#define M 30 + 1
int n;
int ways;
bool day[M];

void 
countHelp(int now, int numberOfOnTime, int numberOfAbsent)
{
    if (now == n) {
        ways += numberOfOnTime + 1;
        return;
    }

    if (numberOfAbsent == 2) {
        countHelp(now+1, numberOfOnTime + 1, 0);
    }
    else {
        countHelp(now+1, numberOfOnTime + 1, 0);
        countHelp(now+1, numberOfOnTime, numberOfAbsent + 1);
    }
}

int
main(int argc, char **argv)
{
    sscanf(argv[1], "%d", &n);
    countHelp(0, 0, 0);
    std::cout << "number of ways = " << ways << std::endl;
}