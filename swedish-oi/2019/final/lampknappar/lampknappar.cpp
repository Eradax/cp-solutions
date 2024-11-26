#include <bits/stdc++.h>

// #include "../../../../dbg.h"
#define dbg(...)

using namespace std;

#define rep(i, n) for (int (i)=0; (i)<(n); (i)++)
#define repe(i, c) for (auto (i): (c))

using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

const int INF = 1e9;

int n;
vvi adj, jda;
vvi dists;

struct State {
    int u, v, w;
    State() {u = 0; v = 0; w = 0;}
    State(int uu, int vv, int ww) { u = uu; v = vv; w = ww; }
    bool operator>(const State &s) const { return w > s.w; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    adj.resize(n);
    jda.resize(n);
    dists.resize(n, vi(n, -1));

    dbg(n);

    rep(i, n) {
        int s;
        cin >> s;

        rep(j, s) {
            int a;
            cin >> a;

            a--;

            // dbg(j, a);

            adj[i].push_back(a);
            jda[a].push_back(i);
        }
    }

    repe(i, adj) {
        // dbg(i);
    }

    rep(i, n) {
        queue<pii> q;

        dists[i][i] = 0;
        q.push({i, 0});

        // dbg(i);

        while (!q.empty()) {
            auto [u, w] = q.front();
            q.pop();

            // dbg(u, w);

            repe(v, adj[u]) {
                // dbg(u, v);
                if (dists[i][v] == -1) {
                    dists[i][v] = w+1;
                    q.push({v, w+1});
                }
            }
        }
    }

    repe(i, dists) {
        dbg(i);
    }

    if (dists[n-1][0] == -1 || dists[0][n-1] == -1) {
        cout << "nej" << endl;
        return 0;
    }

    vvi resd(n, vi(n, INF));

    repe(i, resd) {
        dbg(i);
    }

    priority_queue<State, vector<State>, greater<State>> pq;
    pq.push(State(0, 0, 0));

    while (!pq.empty()) {
        State s = pq.top();
        pq.pop();

        dbg(s.u, s.v, s.w);

        // if (resd[s.u][s.v] < s.w) continue;
        if (resd[s.u][s.v] < INF) continue;

        resd[s.u][s.v] = s.w;

        repe(up, adj.at(s.u)) {
            int w = !(up == s.v);

            dbg("Add adj", up, s.v, s.w+w);

            pq.push(State(up, s.v, s.w+w));
        }

        repe(vp, jda.at(s.v)) {
            int w = !(vp == s.u);

            dbg("Add jda", s.u, vp, s.w+w);
            
            pq.push(State(s.u, vp, s.w+w));
        }

        if (s.u != s.v && dists[s.u][s.v] > 0) {
            assert(dists[s.u][s.v] > 0);

            pq.push(State(s.v, s.u, s.w + dists[s.u][s.v] - 1));

            dbg("Add long", s.v, s.u, s.w + dists[s.u][s.v] - 1);
        }
    }

    cout << resd[n-1][n-1] << endl;
}

