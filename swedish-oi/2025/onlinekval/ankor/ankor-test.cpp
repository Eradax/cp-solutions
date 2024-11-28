#include <bits/stdc++.h>

using namespace std;

using ld = long double;

#define rep(i, n) for (int i = 0; i < (n); i++)



int main() {
    int n;
    cin >> n;

    vector<pair<ld, ld>> points(2*n);
    rep(i, 2*n) {
        cin >> points[i].first >> points[i].second;
    }

    ld k, m;
    cin >> k >> m;

    int a = 0;
    for (auto [x, y] : points) {
        if (y > k*x+m) a++;
    }

    cout << (a == n) && (-5e9 <= k && k <= 5e9) && (-5e9 <= m && m <= 5e9);
}
