#pragma GCC optimize("O3")
#include <bits/allocator.h>
#pragma GCC target("avx2")
#include <bits/stdc++.h>
using namespace std;

// #define dbg(expr)                                                          \
  //   cerr << "[" << __FUNCTION__ << ", " << __LINE__ << "] " << #expr << ": " \
  //        << expr << endl;
#ifdef DBG
  #include "../../../../dbg.h"
#else
  #define dbg(...)
#endif

ostream& operator<<(ostream& o, vector<int> v) {
  o << "{";
  for (auto i : v)
    o << i << ", ";
  o << "}";
  return o;
}

#define sz(c) ((int)c.size())

const int INF = 1e9;

const int MX = 1e6 + 1;
const int NL = __bit_width(MX) * 2;

using vi = vector<int>;
using vvi = vector<vi>;

struct RMQ {
  int n;
  vi t;

  RMQ(int n) : n(n), t(2 * n) {}
  void set(int i, int v) {
    for (t[i += n] = v; i > 1; i /= 2)
      t[i / 2] = max(t[i], t[i ^ 1]);
  }

  int query(int l, int r) {
    int ans = 0;

    for (l += n, r += n; l < r; l /= 2, r /= 2) {
      if (l & 1)
        ans = max(ans, t[l++]);
      if (r & 1)
        ans = max(ans, t[--r]);
    }

    return ans;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, q;
  cin >> n >> q;

  RMQ rmq(n);
  vvi groups(MX);

  for (int i = 0; i < n; i++) {
    int v;
    cin >> v;

    rmq.set(i, v);
    groups[v].push_back(i);
  }

  auto calc_dp = [](vvi& dp, vi a) {
    int n = sz(a);
    dp.assign(n, vi(NL, -1));

    for (int i = 0; i < n; i++)
      for (int j = a[i]; j < NL; j++)
        dp[i][j] = i;

    for (int i = n - 1; i >= 0; i--) {
      for (int j = 1; j < NL; j++) {
        int nod = dp[i][j - 1];
        if (nod == -1)
          continue;

        dp[i][j] = nod;

        if (nod == n - 1)
          continue;

        int nxt_nod = dp[nod + 1][j - 1];

        if (nxt_nod == -1)
          continue;

        dp[i][j] = nxt_nod;
      }
    }
  };

  vector<vector<array<int, 3>>> queries(MX);
  vi res(q);

  for (int i = 0; i < q; i++) {
    int l, r;
    cin >> l >> r;
    l--, r--;

    int mx = rmq.query(l, r + 1);

    queries[mx].push_back({l, r, i});
  }

  for (int i = 0; i < MX; i++) {
    if (!sz(queries[i]))
      continue;

    int mn = max(i - NL / 2, 0);
    dbg(mn);
    vector<pair<int, int>> b;
    for (int j = mn; j <= i; j++)
      for (auto k : groups[j])
        b.emplace_back(k, j - mn);

    sort(b.begin(), b.end());

    dbg(b);

    vi bcomp;
    vi pos, p2p;
    if (b[0].first != 0) {
      bcomp.push_back(0);
    }
    pos.push_back(b[0].first);
    p2p.push_back(sz(bcomp));
    bcomp.push_back(b[0].second);

    for (int j = 1; j < sz(b); j++) {
      if (b[j-1].first + 1 != b[j].first) {
        bcomp.push_back(0);
      }

      pos.push_back(b[j].first);
      p2p.push_back(sz(bcomp));
      bcomp.push_back(b[j].second);
    }

    if (b.back().first != n-1) {
      bcomp.push_back(0);
    }

    vvi dp;
    calc_dp(dp, bcomp);

    dbg(pos, p2p);
    dbg(bcomp);
    dbg(queries);

    for (auto [l, r, k] : queries[i]) {
      int ll = lower_bound(pos.begin(), pos.end(), l) - pos.begin();
      int rr = upper_bound(pos.begin(), pos.end(), r) - pos.begin() - 1;

      // dbg(ll, rr);


      int lll = p2p[ll];
      lll -= pos[ll] > l;

      int rrr = p2p[rr];
      rrr += pos[rr] < r;

      dbg(l, r);
      dbg(ll, rr);
      dbg(lll, rrr);

      int ans = -1;
      for (int j = 0; j < NL; j++) {
        if (dp[lll][j] >= rrr) {
          ans = j;
          break;
        }
      }

      res[k] = ans + mn;
    }
  }


  for (auto i : res)
    cout << i << '\n';
}
