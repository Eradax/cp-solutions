#include <bits/stdc++.h>

#ifdef DBG
    #include "../../../../dbg.h"
#else
    #define dbg(...)
#endif

using namespace std;

#define repp(i, s, n) for (int i = s; i < n; i++)
#define rep(i, n) repp(i, 0, n)

struct Pipe {
    int u, v, a, b;

    Pipe(int u, int v, int a, int b) : u(u), v(v), a(a), b(b) {}
};

using vi = vector<int>;
using vvi = vector<vi>;

using pi = pair<int, int>;
using vpi = vector<pi>;
using vvpi = vector<vpi>;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n, m, q;
    cin >> n >> m >> q;

    vector<Pipe> pipes;
    vvpi adj(n);

    rep(i, m) {
        int u, v, a, b;
        cin >> u >> v >> a >> b;
        u--, v--, a--, b--;

        pipes.emplace_back(u, v, a, b);

        adj[u].emplace_back(v, a);
        adj[v].emplace_back(u, b);
    }

    auto solve = [&](int s, int r, int t) -> bool {
        dbg(s, r, t);

        vvi vis(n, vi(n));

        queue<pi> q;

        q.emplace(s, r);
        vis[s][r] = 1;

        while (!q.empty()) {
            dbg(q);
            auto [u, v] = q.front();
            q.pop();

            dbg(u, v);

            if (v == t) {
                return 1;
            }

            for (auto [nu, nv] : adj[u]) {
                dbg(nu, nv);
                if (nu != v && !vis[nu][v]) {
                    vis[nu][v] = 1;
                    q.emplace(nu, v);
                    dbg("placed: ", nu, v);
                } else if (nu == v && !vis[nu][nv]) {
                    vis[nu][nv] = 1;
                    q.emplace(nu, nv);
                    dbg("placed: ", nu, nv);
                } else {
                    dbg("didn't place");
                }
            }
        }

        return 0;
    };

    rep(_, q) {
        int s, r, t;
        cin >> s >> r >> t;

        s--, r--, t--;

        int can = solve(s, r, t);

        cout << can << '\n';
    }
}
