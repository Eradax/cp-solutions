#include <bits/stdc++.h>

// #include "../../../../dbg.h"
#define dbg(...)

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define max(u, v) ((u) > (v) ? (u) : (v))

const vector<pair<int, int>> dirs = {
    {1, 0},
    {-1, 0},
    {0, 1},
    {0, -1}
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, t;
    cin >> n >> m >> t;

    unordered_map<long long, int> points;

    rep(i, t) {
        long long r, c;
        cin >> r >> c;

        points[(r << 32) + c] = i+1;
    }

    unordered_set<long long> vis;
    priority_queue<pair<int, long long>, vector<pair<int, long long>>, greater<pair<int, long long>>> pq;

    for (auto& [u, w] : points) {
        if ((u >> 32) > 1) continue;

        pq.emplace(w, u);
    }

    int res = -1;

    while (!pq.empty()) {
        auto [w, u] = pq.top();
        pq.pop();

        dbg(w, (u>>32), (int)u);

        if (u >> 32 == n-2) {
            res = w;
            break;
        }

        if (vis.find(u) != vis.end()) continue;

        vis.insert(u);

        for (auto& [rd, cd] : dirs) {
            long long up = (((u >> 32) + rd) << 32) + (long long)((int)u + cd);

            if (points.find(up) == points.end()) continue;

            pq.emplace(max(points[up], w), up);
        }
    }
    
    if (res > 0) {
        cout << res;
    } else {
        cout << "nej";
    }
    cout << endl;
}
