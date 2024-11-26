#include <bits/stdc++.h>

#include "../../../../dbg.h"
// #define dbg(...)

#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,tune=native")

using namespace std;

#define rep(i, n) for (int (i)=0; (i)<(n); (i)++)
#define repe(i, c) for (auto (i): (c))

#define min(a, b) ((a) <= (b) ? (a) : (b))
#define sz(c) ((int)c.size())

using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

const int INF = 1e9;
const int N = 500;
const int M = 2000;



int main() {
    assert(min(1, 3) == 1);


    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;

    cin >> n;


    // vvi adj(n), jda(n);

    array<vi, N> adj; 
    array<vi, N> jda;
 
    array<array<int, N>, N> dists = {};

    // vvi dists(n, vi(n, -1));

    rep(i, n) {
        int s;
        cin >> s;

        rep(j, s) {
            int a;
            cin >> a;

            a--;

            adj[i].emplace_back(a);
            jda[a].emplace_back(i);
        }
    }

    dbg(adj);

    rep(i, n) {
        queue<int> q;

        dists[i][i] = 1;
        q.emplace(i);


        while (!q.empty()) {
            auto u = q.front();
            q.pop();

            repe(v, adj[u]) {
                if (dists[i][v] == 0) {
                    dists[i][v] = dists[i][u]+1;
                    q.emplace(v);
                }
            }
        }
    }
    
    // rep(k, n) rep(i, n) rep(j, n) dists[i][j] = min(dists[i][j], dists[i][k] + dists[k][j]);




    if (dists[n-1][0] == 0 || dists[0][n-1] == 0) {
        cout << "nej" << endl;
        return 0;
    }

    array<vector<pii>, N> qs;
    qs[0].emplace_back(0, 0);

    array<array<bool, N>, N> seen = {};
    rep(w, n) {
        int j = 0;
        while (j < sz(qs[w])) {
            auto [u, v] = qs[w][j];
            j++;

            if (seen[u][v]) continue;
            if (u == n-1 && v == n-1) {
                cout << w << endl;
                return 0;
            }

            seen[u][v] = true;

            repe(up, adj[u]) {
                int w1 = !(up == v);
                if (w+w1 <= n-1 && !seen[up][v]) qs[w+w1].emplace_back(up, v);
            }

            repe(vp, jda[v]) {
                int w1 = !(vp == u);
                if (w+w1 <= n-1 && !seen[u][vp]) qs[w+w1].emplace_back(u, vp);
            }

            if (u != v && dists[u][v]-1 > 0) {
                if (w + dists[u][v]-2 <= n-1 && !seen[v][u]) qs[w + dists[u][v]-2].emplace_back(v, u);
            }
        }
    }
}

