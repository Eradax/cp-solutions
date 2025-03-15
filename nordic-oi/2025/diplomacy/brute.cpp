#include <bits/stdc++.h>
#include <queue>

using namespace std;

#define rep(i, n) for (int i = 0; i < n; i++)

using pi = pair<int, int>;
using vi = vector<int>;

#define sz(c) ((int)c.size())
#define rall(c) c.rbegin(), c.rend()

int main() {
  int n, q;
  cin >> n >> q;

  vector<unordered_set<int>> adj(n);
  priority_queue<tuple<int, int, int>> pq;

  auto add = [&](int u, int v, int p) {
    pq.emplace(p, u, v);
    adj[u].insert(v);
    adj[v].insert(u);
  };

  auto rem = [&]() {
    auto [p, u, v] = pq.top();
    pq.pop();

    adj[u].erase(v);
    adj[v].erase(u);
  };

  auto calc = [&]() {
    vi szs, seen(n);

    function<int(int)> dfs = [&](int u) {
      int size = 1;
      seen[u] = 1;

      for (auto v : adj[u]) {
        if (seen[v]) continue;
        size += dfs(v);
      }

      return size;
    };

    rep(i, n) {
      if (seen[i]) continue;
      szs.push_back(dfs(i));
    }

    sort(rall(szs));

    if (sz(szs) % 2 == 1) {
      szs.push_back(0);
    }

    int ans = 0;
    rep(i, sz(szs)/2) {
      ans += szs[2 * i] - szs[2 * i + 1];
    }

    return ans;
  };

  rep(_, q) {
    char op;
    cin >> op;
    if (op == 'a') {
      int u, v, p;
      cin >> u >> v >> p;
      u--;
      v--;

      add(u, v, p); 
    } else if (op == 'r') {
      rem();
    } else {
      int ans = calc();
      cout << ans << endl;
    }
  }
}
