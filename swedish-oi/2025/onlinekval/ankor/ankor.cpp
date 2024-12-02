#include <bits/stdc++.h>

#ifdef DBG
    #include "../../../../dbg.h"
#else
    #define dbg(...)
#endif

using namespace std;

using ld = long double;
using pll = pair<ld, ld>;

#define rep(i, n) for (int i = 0; i < (n); i++)

const ld k = 3.141592653589793;
const ld eps = 1e-9;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<pll> ducks(2 * n);

    rep(i, 2 * n) {
        cin >> ducks[i].first >> ducks[i].second;
    }

    // nth_element(ducks.begin(), ducks.end(), ducks.begin() + n - 1, [](pll l, pll r){
    //     return (l.second - l.first * k) < (r.second - r.first * k);
    // });
    //
    // dbg(ducks[n - 1]);

    sort(ducks.begin(), ducks.end(), [](pll l, pll r){
        return (l.second - l.first * k) < (r.second - r.first * k);
    });

    dbg(ducks[n - 1]);

    ld m = (ducks[n - 1].second - ducks[n - 1].first * k) + eps;

    cout.precision(15);
    cout << fixed << k << " " << m << endl;
}
