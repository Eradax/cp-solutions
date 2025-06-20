#include <bits/stdc++.h>
using namespace std;

#define check(a, b) ((a >> b) & 1)

#ifdef DBG
#define dbg(expr) cerr << "[" << __FUNCTION__ << ", " << __LINE__ << "] " << #expr << ": " << expr << endl;
#else
#define dbg(...)
#endif

using ll = long long;
#define int ll

using vi = vector<int>;

struct UF {
  vi e;
  UF(int n) : e(n, -1) {}
  int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
  bool join(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return 0;

    if (e[a] > e[b]) swap(a, b);
    e[a] += e[b];
    e[b] = a;

    return 1;
  }
};

signed main() {
  int n, k, m;
  cin >> n >> k >> m;

  dbg(n);
  dbg(k);
  dbg(m);

  vi imp(k);
  int choice_num = 0;
  for (auto& i : imp) {
    cin >> i, i--;
    choice_num |= 1 << i;
  }

  dbg(choice_num);

  vector<vector<pair<int, int>>> adj(n);
  vector<tuple<int, int, int>> edg;
  for (int i = 0; i < m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    a--, b--;
    adj[a].emplace_back(b, c);
    adj[b].emplace_back(a, c);
    edg.emplace_back(a, b, c);
  }

  sort(edg.begin(), edg.end(), [](tuple<int, int, int> a, tuple<int, int, int> b) {
    return get<2>(a) < get<2>(b);
  });

  ll best = 3e18;

  for (int choices = 0; choices < 1 << n; choices++) {
    int mc = choices | choice_num;

    dbg(mc);

    ll ans = 0;

    UF uf(n);
    for (auto [a, b, c] : edg) {
      if (uf.find(a) == uf.find(b)) continue;
      if (!check(mc, a) || !check(mc, b)) continue;
      
      ans += c;
      assert(uf.join(a, b));
    }

    bool flag = 1;
    for (auto i : imp) {
      if (uf.find(i) != uf.find(imp[0])) flag = 0;
    }

    dbg(ans);

    if (flag) best = min(best, ans);
  }

  assert(best < 3e18);

  cout << best;
}
