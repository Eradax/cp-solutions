#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
#define all(c) c.begin(), c.end()
#define sz(c) ((int)c.size())

#define rep(i, l, h) for (int i = l; i < h; i++)

typedef vector<bitset<200>> vb;
struct Maxclique {
  double limit = 0.025, pk = 0;
  struct Vertex {
    int i, d = 0;
  };
  typedef vector<Vertex> vv;
  vb e;
  vv V;
  vector<vi> C;
  vi qmax, q, S, old;
  void init(vv& r) {
    for (auto& v : r)
      v.d = 0;
    for (auto& v : r)
      for (auto j : r)
        v.d += e[v.i][j.i];
    sort(all(r), [](auto a, auto b) { return a.d > b.d; });
    int mxD = r[0].d;
    rep(i, 0, sz(r)) r[i].d = min(i, mxD) + 1;
  }
  void expand(vv& R, int lev = 1) {
    S[lev] += S[lev - 1] - old[lev];
    old[lev] = S[lev - 1];
    while (sz(R)) {
      if (sz(q) + R.back().d <= sz(qmax))
        return;
      q.push_back(R.back().i);
      vv T;
      for (auto v : R)
        if (e[R.back().i][v.i])
          T.push_back({v.i});
      if (sz(T)) {
        if (S[lev]++ / ++pk < limit)
          init(T);
        int j = 0, mxk = 1, mnk = max(sz(qmax) - sz(q) + 1, 1);
        C[1].clear(), C[2].clear();
        for (auto v : T) {
          int k = 1;
          auto f = [&](int i) { return e[v.i][i]; };
          while (any_of(all(C[k]), f))
            k++;
          if (k > mxk)
            mxk = k, C[mxk + 1].clear();
          if (k < mnk)
            T[j++].i = v.i;
          C[k].push_back(v.i);
        }
        if (j > 0)
          T[j - 1].d = 0;
        rep(k, mnk, mxk + 1) for (int i : C[k]) T[j].i = i, T[j++].d = k;
        expand(T, lev + 1);
      } else if (sz(q) > sz(qmax))
        qmax = q;
      q.pop_back(), R.pop_back();
    }
  }
  vi maxClique() {
    init(V), expand(V);
    return qmax;
  }
  Maxclique(vb conn) : e(conn), C(sz(e) + 1), S(sz(C)), old(S) {
    rep(i, 0, sz(e)) V.push_back({i});
  }
};

int main() {
  int v, e;
  cin >> v >> e;

  vb adj(v);

  for (int i = 0; i < e; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].set(b);
    adj[b].set(a);
  }

  Maxclique mc(adj);
  int ans = sz(mc.maxClique());
  cout << ans << endl;
}
