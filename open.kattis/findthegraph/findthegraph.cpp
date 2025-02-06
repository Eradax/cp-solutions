#include <bits/stdc++.h>

#ifdef DBG
  #include "../../dbg.h"
#else
  #define dbg(...)
#endif

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define repp(i, s, n) for (int i = s; i < (n); i++)

int q = 0;
int query(vi* v) {
  q++;

  cout << "? " << v->size();
  for (auto a : *v) {
    cout << ' ' << a + 1;
  }
  cout << endl;
  cout.flush();

  int a;
  cin >> a;

  if (a == -1)
    exit(0);

  return a;
}

int main() {
  int n;
  cin >> n;

  if (n == -1)
    exit(0);

  vi c(n);
  vvi mat(n, vi(n, 0));

  rep(i, n) {
    vi tmp = {i};
    c[i] = query(&tmp);
  }

  rep(i, n) {
    repp(j, i + 1, n) {
      vi tmp = {i, j};
      int val = query(&tmp);

      if (c[i] + c[j] == val + 2) {
        mat[i][j] = 1;
        mat[j][i] = 1;
      } else if (c[i] + c[j] == val) {
        continue;
      } else {
        dbg(val, c[i], c[j]);
      }
    }
  }

  cout << '!' << endl;
  rep(i, n) {
    rep(j, n) {
      if (j == n - 1) {
        cout << mat[i][j] << endl;
      } else {
        cout << mat[i][j] << ' ';
      }
    }
  }
  cout.flush();
}
