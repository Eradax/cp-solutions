#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

typedef vector<ll> vl;
typedef vector<vl> vvl;

int main() {
  ll n, m, k;
  cin >> n >> m >> k;

  vl shops(k);
  for (int i = 0; i < k; i++) {
    ll tmp;
    cin >> tmp;
    shops[i] = --tmp;
  }

  vvl adj(n, vl());

  for (int i = 0; i < m; i++) {
    ll u, v;
    cin >> u >> v;

    adj[--u].push_back(--v);
    adj[v].push_back(u);
  }

  // BFS
  vl ans(n, -1);
  vl roots(n, -1);
  vl q;

  for (auto i : shops) {
    q.push_back(i);
  }

  for (auto i : shops)
    roots[i] = i;

  ll layer = 0;
  while (!q.empty()) {
    // cout << "New layer\n";
    layer++;
    vl nq;

    for (auto v : q) {
      for (auto w : adj[v]) {
        if (roots[w] == -1) {
          ans[w] = layer;
          roots[w] = roots[v];
          nq.push_back(w);
        } else if (roots[v] != roots[w]) {
          ll ansv = ans[v], answ = ans[w];

          if (v == roots[v]) {
            ansv = 0;
          }

          if (w == roots[w]) {
            answ = 0;
          }

          ans[roots[v]] = min(ansv + 1 + answ, ans[roots[v]]);
          ans[roots[w]] = min(ansv + 1 + answ, ans[roots[w]]);

          if (ans[roots[v]] == -1) {
            ans[roots[v]] = ansv + 1 + answ;
          }

          if (ans[roots[w]] == -1) {
            ans[roots[w]] = answ + 1 + ansv;
          }
        }
      }
    }
    q = nq;
  }

  // Display the answer

  for (auto i : ans) {
    cout << i << " ";
  }
  cout << endl;
}