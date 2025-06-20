#include <bits/stdc++.h>
#ifdef DBG
  #include "../../../dbg.h"
#else
  #define dbg(...)
#endif
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;

    int ev = 0;
    int od;

    vector<int> e, o;
    for (int ii = 0; ii < n; ii++) {
      int i;
      cin >> i;
      if (i % 2) {
        o.push_back(i);
      } else {
        e.push_back(i);
      }
      ev += i % 2 == 0;
    }


    od = n - ev;

    dbg(o, e);

    sort(e.begin(), e.end());
    sort(o.rbegin(), o.rend());

    vector<int> e2(e), o2(o);

    dbg(o, e);

    long long ans = 0;
    if (e.empty()) {
      ans = 0;
    } else {
      ans = e.back();
      e.pop_back();
    }

    dbg(o, e);
    dbg(ans);

    for (auto oo : o) {
      if (e.empty()) {
        ans += oo;
        break;
      }
      dbg(oo, e.back());
      ans += oo + e.back() - 1;
      e.pop_back();
    }

    dbg(o, e);

    swap(o, e2);
    swap(e, o2);

    long long be = ans;
    if (e.empty()) {
      ans = 0;
    } else {
      ans = e.back();
      e.pop_back();
    }

    dbg(o, e);
    dbg(ans);

    for (auto oo : o) {
      if (e.empty()) {
        ans += oo;
        break;
      }
      dbg(oo, e.back());
      ans += oo + e.back() - 1;
      e.pop_back();
    }

    dbg(o, e);

    cout << max(be, ans) << '\n';
  }
}
