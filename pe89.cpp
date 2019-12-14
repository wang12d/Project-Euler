#include <iostream>

using namespace std;

int rawNumberOfChar;    // 原始表示方法所占用的字符数
int optNumberOfchar;    // 改成最优表示方式之后的字符数
int N = 1000;           // 最大的罗马数字数量

// 直接将改成IV之类的就行了

int
main(int argc, char **argv)
{
    string str;
    int i;

    for (i = 0; i < N; ++i) {
        cin >> str;
        rawNumberOfChar += str.size();
    }

    for (i = 0; i < N; ++i) {
        cin >> str;
        optNumberOfchar += str.size();
    }

    cout << rawNumberOfChar - optNumberOfchar << endl;
}