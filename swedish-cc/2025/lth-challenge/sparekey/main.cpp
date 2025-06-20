#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  vector<vi> rev(n + 1);
  for (int i = 1; i <= n; i++) {
    int m;
    cin >> m;
    while (m--) {
      int s;
      cin >> s;
      rev[s].push_back(i);
    }
  }

  vector<int> ordr(n);
  for (int i = 0; i < n; i++)
    cin >> ordr[i];

  vi ans(n + 1);
  vi seen(n + 1);
  queue<int> q;
  int reach = 0;

  ans[0] = n;

  for (int i = 1; i <= n; i++) {
    int v = ordr[n - i];

    if (!seen[v]) {
      seen[v] = 1;
      reach++;
      q.push(v);
    }

    while (!q.empty()) {
      int u = q.front();
      q.pop();

      for (int w : rev[u]) {
        if (!seen[w]) {
          seen[w] = 1;
          reach++;
          q.push(w);
        }
      }
    }

    ans[i] = n - reach;
  }

  for (int k = 1; k <= n; k++)
    cout << ans[n - k] << ' ';
  cout << endl;
}
