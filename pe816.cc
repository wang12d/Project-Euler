#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using std::vector;
using ll =  long long;

const ll inf = 0x7fffffffffffffff;
ll
distanceSquare(vector<ll>& a, vector<ll>& b)
{  
    ll dx = a.at(0) - b.at(0);
    ll dy = a.at(1) - b.at(1);
    return dx * dx + dy * dy;
}

ll
mergeLeftRight(vector<vector<ll>>& arr, int left, int mid, int right)
{
    ll minDistance = inf;
    if (mid > left) {
    vector<ll> leftPoint = arr.at(mid - 1);
    for (auto i = mid; i < right; i++) {
        const ll distance = distanceSquare(leftPoint, arr.at(i));
        minDistance = std::min(distance, minDistance);
    }
    }
    if (right > mid) {
        vector<ll> rightPoint = arr.at(mid);
        for (auto i = left; i < mid; i++) {
            const ll distance = distanceSquare(rightPoint, arr.at(i));
            minDistance = std::min(distance, minDistance);
        }
    }
    return minDistance;
}

ll
solve(vector<vector<ll>>& arr, int left, int right)
{
    if (right - left <= 1) {
        return inf;
    }
    int mid = left + ((right - left) >> 1);
    ll leftMin = solve(arr, left, mid);
    ll rightMin = solve(arr, mid, right);
    return std::min(leftMin, std::min(rightMin, mergeLeftRight(arr, left, mid, right)));
};

int
main(int argc, char** argv)
{   
    int n = 14;
    if (argc > 1) {
        sscanf(argv[1], "%d", &n);
    }
    const ll MOD =  50515093;
    vector<vector<ll>> arr;
    vector<ll> p(2*n+5);
    p.at(0) = 290797;
    for (auto i = 1; i <= 2*n+1; ++i) {
        p.at(i) = (p.at(i-1) * p.at(i-1)) % MOD;
    }
    for (auto i = 0; i < n; ++i) {
        arr.push_back({p.at(2*i), p.at(2*i+1)});
    }

    sort(arr.begin(), arr.end(), [](const auto& a, const auto& b) {
        return a.front() > b.front();
    });

    printf("%.9f\n", sqrt(solve(arr, 0, arr.size())));
}
