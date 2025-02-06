#include <bits/stdc++.h>

#ifdef DBG
  #include "../../../../dbg.h"
#else
  #define dbg(...)
#endif

/*
source:
    Rocky Mountain Regional Programming Contest 2019
links:
    https://open.kattis.com/problems/integerdivision
*/

using namespace std;

using ull = unsigned long long;

using vi = vector<int>;

#define rep(i, n) for (int i = 0; i < (n); i++)

struct UF {
  vi e;
  UF(int n) : e(n, -1) {}
  bool sameSet(int a, int b) { return find(a) == find(b); }
  int size(int x) { return -e[find(x)]; }
  int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
  bool join(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b)
      return false;

    if (e[a] > e[b])
      swap(a, b);
    e[a] += e[b];
    e[b] = a;
    return true;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, q;
  cin >> n >> q;

  UF uf(n);

  rep(i, q) {
    string opt;
    int a, b;
    cin >> opt >> a >> b;
    if (opt == "?") {
      cout << (uf.sameSet(a, b) ? "yes" : "no") << '\n';
    } else {
      uf.join(a, b);
    }
  }
}
