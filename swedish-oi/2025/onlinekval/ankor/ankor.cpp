#include <bits/stdc++.h>
#include <cmath>

#ifdef DBG
    #include "../../../../dbg.h"
#else
    #define dbg(...)
#endif

using namespace std;

using ld = long double;

#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cout.precision(15);

    int n;
    cin >> n;


    ld px, py;
    px = 1e6 * 3.14159265358979;
    py = 0.5;

    vector<pair<ld, ld>> points(2*n);
    vector<ld> angles(2*n);
    rep(i, 2*n) {
        cin >> points[i].first >> points[i].second;
    }

    sort(points.begin(), points.end(), [&](pair<ld, ld> l, pair<ld, ld> h){
        auto [lx, ly] = l;
        auto [hx, hy] = h;

        return atan2(py - ly, px - lx) < atan2(py - hy, px - hx);
    });

    rep(i, 2*n) {
        angles[i] = atan2(py - points[i].second, px - points[i].first);
    }

    dbg(points);
    dbg(angles);

    ld ang = (angles[n-1]+angles[n]) / 2;

    ld k = tan(ang);
    ld m = py - k*px;

    cout << fixed << k << " " << m << endl;
}
