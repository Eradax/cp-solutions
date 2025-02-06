#include <bits/stdc++.h>

#ifdef DBG
  #include "../../../../dbg.h"
#else
  #define dbg(...)
#endif

/*
links:
    https://open.kattis.com/problems/slottsmur
    https://po2punkt0.kattis.com/problems/slottsmur
source:
    Programmeringsolympiadens onlinekval 2025
*/

using namespace std;

using ll = long long;
using vi = vector<int>;

const int N = 2e5;
const int Q = 2e5;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define repp(i, s, n) for (int i = s; i < (n); i++)
#define sz(c) ((int)(c).size())

int n;

struct SolverBase {
  vi wall;

  SolverBase(vi h) : wall(h) {}
  SolverBase() {}

  virtual void updB(int ind, int w) {};
  virtual ll query(int l, int r) { return -1; };
  virtual int get_sz() { return sz(wall); }
  virtual vi get_h() { return wall; }
};

template <const int BS>
struct Solver : SolverBase {
  vi wall;

  int preMax[(N + BS - 1) / BS][BS] = {0};
  ll preSum[(N + BS - 1) / BS][BS] = {0};
  ll preWa[(N + BS - 1) / BS][BS] = {0};

  Solver(vi h) : wall(h) {
    dbg(sz(wall));
    dbg(wall);

    int pad = sz(wall) % BS ? BS - (sz(wall) % BS) : 0;

    dbg(pad);

    wall.insert(wall.end(), pad, 0);

    dbg(wall);

    dbg(sz(wall));
    dbg(BS);

    rep(i, (n + BS - 1) / BS) {
      updB(i * BS, 0);
    }

    dbg(preMax, preSum, preWa);
  }

  int get_sz() override { return sz(wall); }

  vi get_h() override { return wall; }

  void updB(int ind, int h) override {
    dbg(ind, h);

    int block = ind / BS;
    int blockInd = ind % BS;

    // Strategy: First, we will only update the block that we are currently in
    // secondly, only things to our right will be affected when we update this
    // index

    wall[ind] += h;

    int ib = ind / BS;
    ind %= BS;

    int m = 0;
    if (ind > 0)
      m = preMax[ib][ind - 1];

    int sb = ib * BS;

    dbg(ib, sb);

    repp(i, ind, BS) {
      m = max(m, wall[sb + i]);

      dbg(i, m, wall[sb + i]);

      if (i) {
        preMax[ib][i] = max(preMax[ib][i - 1], m);
        preSum[ib][i] = preSum[ib][i - 1] + wall[sb + i];
        preWa[ib][i] = preWa[ib][i - 1] + (m - wall[sb + i]);
      } else {
        preMax[ib][i] = m;
        preSum[ib][i] = wall[sb + i];
        preWa[ib][i] = m - wall[sb + i];
      }
    }

    dbg(preMax, preSum, preWa);
  }

  ll queryB(int b, int l, int& h) {
    dbg(b, l, h);

    if (l == 0) {
      return 0;
    }

    ll ans = -1;
    if (h < preMax[b][l - 1]) {
      int lo = 0, hi = l;
      while (lo < hi) {
        int mi = lo + (hi - lo) / 2;

        if (preMax[b][mi] > h) {
          hi = mi;
        } else {
          lo = mi + 1;
        }
      }

      dbg(lo, hi, b, l);
      dbg(preWa);
      dbg(preWa[b][l - 1]);

      ans = preWa[b][l - 1];
      ans += (ll)lo * h;
      if (lo) {
        ans -= preWa[b][lo - 1];
        ans -= preSum[b][lo - 1];
      }

      h = preMax[b][l - 1];
    } else {
      ans = (ll)l * h - preSum[b][l - 1];
    }

    return ans;
  }

  ll query(int l, int r) override {
    dbg(l, r);

    ll ans = 0;
    int h = 0;

    // Strategy: Go through left block, then trough middle and end by going
    // through the right.

    int lb = l / BS;
    int rb = r / BS;

    dbg(lb, rb);

    // left
    repp(i, l, min(r, (lb + 1) * BS)) {
      dbg(i);
      h = max(h, wall[i]);
      ans += h - wall[i];
    }

    dbg(ans, h);

    // mid
    repp(i, lb + 1, rb) {
      ans += queryB(i, BS, h);
    }

    dbg(ans, h);

    // right
    l %= BS;
    r %= BS;

    dbg(l, r);

    if (lb != rb)
      ans += queryB(rb, r, h);

    dbg(ans, h);

    return ans;
  }
};

struct Rmq {
  vector<pair<int, int>> t;
  Rmq() : t(n) {}
  Rmq(vi tt) : t(2 * n) {
    rep(i, n) {
      t[n + i] = {tt[i], i};
    }

    for (int i = n - 1; i > 0; i--) {
      t[i] = max(t[i * 2], t[i * 2 + 1]);
    }
  }

  void inc(int p, int v) {
    for (t[p += n].first += v; p > 1; p /= 2) {
      t[p / 2] = max(t[p], t[p ^ 1]);
    }
  }

  int query(int l, int r) {
    pair<int, int> res = {0, -1};
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1)
        res = max(res, t[l++]);
      if (r & 1)
        res = max(res, t[--r]);
    }
    return res.second;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int q;
  cin >> n >> q;

  dbg(n, q);

  vi h(n);
  rep(i, n) {
    cin >> h[i];
  }

  dbg(h);

  SolverBase* s;
  SolverBase* rs;
  s = new Solver<500>(h);
  reverse(h.begin(), h.end());
  rs = new Solver<500>(h);
  reverse(h.begin(), h.end());

  Rmq rmq(h);

  rep(j, q) {
    int t, l, r;
    cin >> t >> l >> r;

    if (t == 1) {
      l--;
      r--;

      int m = rmq.query(l, r + 1);

      dbg(l, r, m);

      ll ans = 0;
      ans += s->query(l, m);

      dbg(ans);

      ans += rs->query(n - 1 - r, n - 1 - m);

      dbg(ans);

      cout << ans << '\n';
    } else {
      int i = l;
      int w = r;

      i--;
      s->updB(i, w);
      rs->updB(n - 1 - i, w);
      rmq.inc(i, w);
    }
  }
}
