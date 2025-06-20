#include <bits/stdc++.h>
using namespace std;

#define sz(c) ((int)c.size())
#define all(c) c.begin(), c.end()

using ll = long long;

const int N = 1.5e5 + 10;
const int A = 26;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int trie[N][A];
  int id[N];
  int cant;

  vector<string> s(N), org(N);
  string ss;

  vector<bool> d(N);

  int n = 0, k = 0;
  while (cin >> ss) {
    org[n] = ss;
    sort(all(ss));
    s[n] = ss;

    int u = 0;
    for (auto c : ss) {
      int& v = trie[u][c - 'a'];
      if (!v)
        v = ++k;
      u = v;
    }

    id[n] = u;
    n++;
  }

  function<void(int, int)> trwlk = [&](int u, int i) {
    if (u && u != cant)
      d[u] = 1;
    for (int j = i; j < sz(ss); j++) {
      int v = trie[u][ss[j] - 'a'];
      if (v)
        trwlk(v, j + 1);
    }
  };

  for (int i = 0; i < n; i++) {
    ss = s[i];
    cant = id[i];
    trwlk(0, 0);
  }

  vector<string> ans;
  for (int i = 0; i < n; i++) {
    if (!d[id[i]])
      ans.push_back(org[i]);
  }

  sort(all(ans));
  for (auto i : ans)
    cout << i << '\n';
}
