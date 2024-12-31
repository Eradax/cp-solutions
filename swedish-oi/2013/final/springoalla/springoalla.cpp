#include <bits/stdc++.h>

#ifdef DBG
#include "../../../../dbg.h"
#else
#define dbg(...)
#endif

/*
source:
    Programmeringsolympiadens finaltävling 2013
links:
    https://open.kattis.com/problems/springoalla
*/

using namespace std;

static constexpr int INF = 1e9;

using vi = vector<int>;

#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, t;
    cin >> n >> t;

    dbg(n, t);

    vi v(n);

    int maxl = 0;
    rep(i, n) {
        cin >> v[i];
        maxl = max(maxl, v[i]);
    }

    vi w(t + maxl * 3 / 2 + 10, INF), p(t + maxl * 3 / 2 + 10);

    w[0] = 0;

    dbg(v);

    rep(i, n) {
        rep(j, 2) {
            rep(k, t + 1) {
                if (w[k] + j + 1 < w[k + v[i] * (j + 2) / 2]) {
                    dbg("-----", k, j, i);

                    w[k + v[i] * (j + 2) / 2] = w[k] + j + 1;
                    p[k + v[i] * (j + 2) / 2] = (i + 1) * (j == 1 ? -1 : 1);
                }
            }
        }
    }

    dbg(w, p);

    int anst, ansn;
    vi ansl(n);

    int i = t;

    for (; i < 160100; i++) {
        if (w[i] == INF) continue;

        anst = i;
        ansn = w[i];
        break;
    }

    dbg(i);

    while (i) {
        dbg(i);

        int road = p[i];

        dbg(road);

        int times = road < 0 ? 3 : 2;
        road = abs(road) - 1;

        ansl[road] += v[road] * times / 2;
        i -= v[road] * times / 2;

        dbg(road, times);
    }

    cout << anst << " " << ansn << endl;
    rep(i, n) {
        cout << ansl[i] << " ";
    }
    cout << endl;
}
