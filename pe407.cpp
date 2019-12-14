#include <bits/stdc++.h>

using namespace std;

map<int, vector<vector<int>>> combIndex;
vector<vector<int>> primeProcts;
vector<int> numbers;

int 
extend_gcd(int a, int b, int *x, int *y)
{
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }

    int x1, y1;
    int d = extend_gcd(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b)*y1;

    return d;
}

void 
findPrimeProductFactors(int n, vector<bool>& isprime)
{
    for (int i = 0; i <= n; ++i) {
        primeProcts.push_back(vector<int>{});
        numbers.push_back(i);
    }
    isprime[0] = isprime[1] = 0;
    int i, j;
    for (i = 2; i*i <=  n; ++i) {
        if (isprime[i]) {
            for (j = 2*i; j <= n; j += i) {
                long long tmp = i;
                isprime[j] = 0;
                do {
                    numbers[j] /= i;
                    tmp *= i;
                } while (j % tmp == 0);
                tmp /= i;
                primeProcts[j].push_back((int) tmp);
            }
        }
    }
    for (i = 2; i <= n; ++i) {
        if (numbers[i] != 1 && !isprime[i]) {
            primeProcts[i].push_back(numbers[i]);
        }
    }
}

// 生成所有从n中选择k个元素的组合
void
combination(int offset, int k, int n, vector<int>& cm, vector<vector<int>>& combs, const vector<int>& nums)
{
    if (k == 0) {
        combs.push_back(cm);
        return;
    }
    for (int i = offset; i <= n - k; ++i) {
        cm.push_back(nums[i]);
        combination(i+1, k-1, n, cm, combs, nums);
        cm.pop_back();
    }
}

vector<vector<int>>
combination(int n, int k, const vector<int>& nums)
{
    vector<vector<int>> combs;
    vector<int> cm;
    combination(0, k, n, cm, combs, nums);
    return combs;
}

int
vectorProduct(const vector<int>& ind, const vector<int>& vec)
{
    int res = 1;
    for (int i: ind) {
        res *= vec[i];
    }
    if (res < 0) {
        cout << res << endl;
    }
    return res;
}

int
getM(const vector<int>& primeFactors, int n, const vector<bool>& isprime)
{
    if (isprime[n]) return 1;
    int sz = primeFactors.size();
    vector<vector<int>> allCombs = combIndex[sz];
    int a, b;
    int res = 1;
    for (auto v: allCombs) {
        int prod = vectorProduct(v, primeFactors);
        assert(prod > 0);
        extend_gcd(prod, n / prod, &a, &b);
        if (a < 0) a += (n / prod);
        int val = a * prod;
        if (val < n && val > 0) {
            res = max(res, val);
        }
    }
    return res;
}

int
main(int argc, char** argv)
{
    int n = 10000000;
    vector<bool> isprime(n+1, 1);
    vector<vector<int>> allCombs;
    vector<int> nums;
    findPrimeProductFactors(n, isprime);
    for (int i = 2; i <= 8; ++i) {
        vector<vector<int>> allCombs;
        vector<int> nums;
        for (int v = 0; v < i; ++v) {
            nums.push_back(v);
        }
        for (int j = 1; j < i; ++j) {
            vector<vector<int>> combs = combination(i, j, nums);
            allCombs.insert(allCombs.end(), combs.begin(), combs.end());
        }
        combIndex[i] = allCombs;
    }
    long long res = 0;
    for (int i = 2; i <= n; ++i) {
        int t2 = getM(primeProcts[i], i, isprime);
        res = res + t2;
    }
    cout << res << endl;
}
