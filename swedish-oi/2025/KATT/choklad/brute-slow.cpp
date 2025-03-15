// #pragma GCC optimize("Ofast")
// #include <bitset>
// #pragma GCC target("avx2")
#include <bits/stdc++.h>

#ifdef DBG
  #include "../../../../dbg.h"
#else
  #define dbg(...)
#endif

using namespace std;

#define repp(i, s, n) for (int i = s; i < n; i++)
#define rep(i, n) repp(i, 0, n)

#define perr(i, s, n) for (int i = n - 1; i >= s; i--)
#define per(i, n) perr(i, 0, n)

#define all(c) c.begin(), c.end()

using ll = long long;
#define int ll

using vi = vector<int>;
using vvi = vector<vi>;

using pi = pair<int, int>;
using vpi = vector<pi>;
using vvpi = vector<vpi>;

static constexpr int INF = 1e9;

using ch = tuple<int, int, pi>;

struct Choc {
  int r, c, k;
  Choc(int r, int c, int k) : r(r), c(c), k(k) {}
};

signed main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  vector<Choc> choc;
  rep(i, n) {
    int r, c, k;
    cin >> r >> c >> k;
    choc.emplace_back(r, c, k);
  }

  auto calc = [&]() {
    priority_queue<ch> pq;
    rep(i, n) {
      auto [r, c, k] = choc[i];

      if (k %2 == 0) continue;

      int maxval;
      pi nxt;
      if (r == c && r == 1) {
        maxval = 1;
        nxt = {0, 0};
      } else {
        if (r / 2 * c >= c / 2 * r) {
          maxval = r / 2 * c;
          nxt = {r - r / 2, c};
        } else {
          maxval = c / 2 * r;
          nxt = {r, c - c / 2};
        }
      }
      pq.emplace(maxval, k, nxt);
    }

    int ans = 0;
    int p = 1;
    while (!pq.empty()) {
      dbg(pq);
      auto [val, k, cur] = pq.top();
      pq.pop();

      if (k % 2) {
        ans += p * val;
        p *= -1;
      }
      auto [r, c] = cur;
      int maxval;
      pi nxt;
      if (r == c && r == 1) {
        maxval = 1;
        nxt = {0, 0};
      } else {
        if (r / 2 * c >= c / 2 * r) {
          maxval = r / 2 * c;
          nxt = {r - r / 2, c};
        } else {
          maxval = c / 2 * r;
          nxt = {r, c - c / 2};
        }
      }

      if (maxval == 0) continue;

      pq.emplace(maxval, k, nxt);
    }

    return ans;
  };

  int ans = abs(calc());
  dbg(ans);
  rep(i, n) {
    choc[i].k--;
    ans = min(ans, abs(calc()));
    choc[i].k++;

    dbg(ans);
  }

  cout << ans << endl;
}
