#include <bits/stdc++.h>

#ifdef DBG
  #include "../../../../dbg.h"
#else
  #define dbg(...)
#endif

using namespace std;

using ui = unsigned long long;

using pui = pair<ui, ui>;

using vui = vector<ui>;
using vvui = vector<vui>;

using vpui = vector<pui>;
using vvpui = vector<vpui>;

#define repp(i, s, n) for (int i = s; i < n; i++)
#define rep(i, n) repp(i, 0, n)

int main() {
  cin.tie(0)->sync_with_stdio();

  int n, q;
  cin >> n >> q;

  vui cols(n);
  rep(i, n) cin >> cols[i];

  dbg(cols);

  {
    vui dp_curr(10);
    vui dp_nxt(10);
    ui curr_sum = 0, nxt_sum = 0;

    rep(i, n) {
      rep(j, 10) {
        ui col = cols[i];
        ui val = dp_curr[j];

        if (col == j) {
          dp_nxt[j] = curr_sum + 1;
        } else {
          dp_nxt[j] = val;
        }
        nxt_sum += dp_nxt[j];
      }

      dbg(i, dp_curr, dp_nxt);

      swap(dp_curr, dp_nxt);
      swap(curr_sum, nxt_sum);
      nxt_sum = 0;
    }

    dbg(dp_curr);
    dbg(dp_nxt);

    ui ans = 0;
    rep(i, 10) {
      ans += dp_curr[i];
    }

    cout << 1 + ans << endl;
  }

  rep(_, q) {
    vui dp_curr(10);
    vui dp_nxt(10);
    ui curr_sum = 0, nxt_sum = 0;

    int i, v;
    cin >> i >> v;
    i--;
    cols[i] = v;

    rep(i, n) {
      rep(j, 10) {
        ui col = cols[i];
        ui val = dp_curr[j];

        if (col == j) {
          dp_nxt[j] = curr_sum + 1;
        } else {
          dp_nxt[j] = val;
        }
        nxt_sum += dp_nxt[j];
      }

      dbg(i, dp_curr, dp_nxt);

      swap(dp_curr, dp_nxt);
      swap(curr_sum, nxt_sum);
      nxt_sum = 0;
    }

    dbg(dp_curr);
    dbg(dp_nxt);

    ui ans = 0;
    rep(i, 10) {
      ans += dp_curr[i];
    }

    cout << 1 + ans << endl;
  }
}
