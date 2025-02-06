#include <bits/stdc++.h>

#ifdef DBG
  #inlcude "../../dbg.h"
#else
  #define dbg(...)
#endif

using namespace std;

using vi = vector<int>;

#define rep(i, n) for (int i = 0; i < (n); i++)

struct T {
  vi t;
  int n;
  T(int n) : t(2 * n, 0), n(n) { dbg(n); }

  void flip(int i) {
    dbg(n, i, t);

    i += n;
    t[i] = 1 - t[i];
    for (i /= 2; i > 0; i /= 2) {
      t[i] = t[2 * i] + t[2 * i + 1];
    }
  }

  int sum(int l, int r) {
    int ans = 0;
    l += n;
    r += n;
    for (; l < r; l /= 2, r /= 2) {
      if (l % 2)
        ans += t[l++];
      if (r % 2)
        ans += t[--r];
    }

    return ans;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio();

  int n, k;
  cin >> n >> k;

  T t(n);
  rep(i, k) {
    char o;
    cin >> o;
    if (o == 'F') {
      int a;
      cin >> a;
      a--;

      t.flip(a);
    } else {
      int a, b;
      cin >> a >> b;
      a--;
      b--;

      cout << t.sum(a, b + 1) << '\n';
    }
  }
}
