#include <bits/stdc++.h>

#ifdef DBG
  #include "../../../../dbg.h"
#else
  #define dbg(...)
#endif

using namespace std;

#define sz(c) ((int)c.size())

struct UF {
  vector<int> e;
  vector<pair<int, int>> st;
  UF(int n) : e(n, -1) {}
  int find(int x) { return e[x] < 0 ? x : find(e[x]); }
  bool same(int a, int b) { return find(a) == find(b); }
  void undo() {
    dbg(st);

    e[st.back().first] = st.back().second;
    st.pop_back();

    e[st.back().first] = st.back().second;
    st.pop_back();
  }
  int join(int a, int b) {
    a = find(a);
    b = find(b);

    if (a == b) {
      st.emplace_back(a, e[a]); // phony
      st.emplace_back(b, e[b]); // phony
      return 0;
    }

    if (e[a] > e[b]) swap(a, b);

    st.emplace_back(a, e[a]);
    st.emplace_back(b, e[b]);
    e[a] += e[b];
    e[b] = a;

    return 1;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m;
  cin >> n >> m;

  vector<array<int, 3>> edgs;

  for (int i = 0; i < m; i++) {
    int u, v, m;
    cin >> u >> v >> m;
    u--, v--;

    edgs.push_back({u, v, m});
  }

  sort(edgs.begin(), edgs.end(), [](auto l, auto r) {
    return l[2] < r[2];
  });

  int ans = 0;

  UF uf(n);

  function<int(int, int, vector<array<int, 3>>&)> dc = [&](int l, int r, vector<array<int, 3>>& v) -> int {
    if (l >= r)
      return 0;
    if (l + 1 == r)
      return uf.same(v[l][0], v[l][1]);

    int mid = (l + r) / 2;
    int ans = 0;

    dbg(l, r, mid);

    for (int i = l; i < mid; i++)
      uf.join(v[i][0], v[i][1]);
    ans += dc(mid, r, v);
    for (int i = l; i < mid; i++)
      uf.undo();

    
    for (int i = mid; i < r; i++)
      uf.join(v[i][0], v[i][1]);
    ans += dc(l, mid, v);
    for (int i = mid; i < r; i++)
      uf.undo();

    return ans;
  };

  for (int i = 0; i < m;) {
    vector<array<int, 3>> samew;
    
    int w = edgs[i][2];

    while (i < m && edgs[i][2] == w) {
      samew.push_back(edgs[i]);
      i++;
    }

    dbg(samew, i);

    ans += dc(0, sz(samew), samew);

    for (auto [a, b, _] : samew)
      uf.join(a, b); 
  }

  cout << ans << endl;
}
