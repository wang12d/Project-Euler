#include <bits/stdc++.h>

using namespace std;

vector<vector<int> > all_combinations;  // 所有的k个组和
vector<int> mids;   // 在生成k-combinations时的中间函数


void pretty_print(vector<int> sour)
{
    printf("[ ");
    vector<int>::iterator end = sour.end();
    for (vector<int>::iterator it = sour.begin(); it != end; ++it) {
        printf("%d%c", *it, (it+1 == end ? ' ' : ','));
    }
    printf("]\n");
}

// k-combinations
// 从一个数组中生成全部的k个组合
void k_combinations(int k, vector<int> sour, int offset)
{
    if (k == 0) {
        all_combinations.push_back(mids);
        return;
    }

    for (int i = offset; i <= sour.size() - k; ++i) {
        mids.push_back(sour[i]);
        k_combinations(k-1, sour, i+1);
        mids.pop_back();        
    }
}

// 给出两个数组，判断其是否符合条件
// size(vec1) == size(vec2)
int need_check(vector<int> vec1, vector<int> vec2)
{
    int size = vec1.size();
    for (int i = 0; i < size; ++i) {
        int a = vec1[i];
        for (int j = 0; j < size; ++j) {
            if (a == vec2[j]) {
                return 0;
            }
        }
    }

    bool flag = false;
    for (int i = 0; i < size; ++i) {
        int a = vec1[i], b = vec2[i];
        if (a > b) {
            flag = true;
            break;
        }
    }

    return flag;
}

int main(int argc, char **argv)
{
    vector<int> sour {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

    int cnt = 0;
    int size = sour.size();

    for (int i = 2; 2*i <= size; ++i) {
        k_combinations(i, sour, 0);
        int comb_size = all_combinations.size();
        for (int j = 0; j < comb_size; ++j) {
            vector<int> vec = all_combinations[j];
            for (int v = j+1; v < comb_size; ++v) {
                cnt += need_check(vec, all_combinations[v]);
            }
        }
        all_combinations.clear();
    }
    printf("%d\n", cnt);
}