#include <bits/stdc++.h>
#include <ext/rope>

using namespace std;
using rop = __gnu_cxx::rope<int>;

#define sz(c) ((int)c.size())

// NOTE: This solves the problem as described in the problemstatement
// since the problemstatement is faulty this doesn't work
// the items should be sorted within each group
int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, q;
  cin >> n >> q;

  vector<rop> v(n + 1);
  for (int i = 0; i < n + 1; i++)
    v[i].insert(0, i);

  vector<int> tags;

  while (q--) {
    int op, i, j;
    cin >> op >> i >> j;

    assert(1 <= i && i <= n);

    if (op == 1) {
      assert(1 <= j && j <= sz(v[i]));
      cout << v[i][j - 1] << '\n';
    } else if (op == 2) {
      assert(1 <= j && j <= n);
      v[i].append(v[j]);
      v[j] = {};
      tags.push_back(j);
    } else if (op == 3) {
      assert(0 <= j && j <= sz(v[i]));
      rop tmp = v[i].substr(j, sz(v[i]) - j);
      v[i].erase(j, sz(v[i]) - j);
      int tag = tags.back();
      tags.pop_back();
      v[tag] = tmp;
    } else {
      assert(0);
    }
  }
}