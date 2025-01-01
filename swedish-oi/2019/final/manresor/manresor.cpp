#include <bits/stdc++.h>

#ifdef DBG
#include "../../../../dbg.h"
#else
#define dbg(...)
#endif

#pragma GCC optimize("Ofast,inline,unroll-loops")

/*
source:
    Programmeringsolympiadens final 2019
links:
    https://open.kattis.com/problems/manresor
*/

using namespace std;

static constexpr int INF = 1e9;

using vi = vector<int>;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define per(i, n) for (int i = n - 1; i >= 0; i--)

#define all(c) (c.begin()), (c.end())
#define setcontains(c, i) (c.find(i) != c.end())

#define gc() getchar_unlocked()
inline void read(int& v) { v = 0; int sign = 1; char c = gc(); if (c == '-') { sign = -1; } else { v += c - '0'; } while ((c = gc()) && c != ' ' && c != '\n') { if (c == EOF) { v = -1; return; } v *= 10; v += c - '0'; } v *= sign; }

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m, k;
  read(n);
  read(m);
  read(k);

  vi d(n), g(m), p(m), r(k);
  bitset<(int)5e5> D(0), R(0);

  rep(i, n) {
    read(d[i]);
    d[i]--;
    D[d[i]] = 1;
  }
  rep(i, m) { read(g[i]); }
  rep(i, m) read(p[i]);
  rep(i, k) {
    read(r[i]);
    r[i]--;
    R[r[i]] = 1;
  }

  {
    int di = 0, Di = D._Find_first();
    while (di < n) {
      d[di++] = Di;
      Di = D._Find_next(Di);
    }
  }

  {
    int ri = 0, Ri = R._Find_first();
    while (ri < k) {
      r[ri++] = Ri;
      Ri = R._Find_next(Ri);
    }
  }

  dbg(d, g, p, r);

  int l = *max_element(all(d));
  dbg(l);

  vi nxt(l + 1, -2);
  {
    int num = 0;
    rep(i, l + 1) {
      while (num < n && d[num] < i)
        num++;

      // Technically not needed but makes it easier to understand.
      nxt[i] = num >= n ? -1 : num;
    }
  }
  dbg(nxt);

  vi half(n, -2);
  {
    int num = k - 1;
    per(i, n) {
      while (num >= 0 && r[num] > d[i])
        num--;

      // Technically not needed but makes it easier to understand.
      half[i] = num < 0 ? -1 : r[num];
    }
  }
  dbg(half);

  vi dp(n, INF);

  per(i, n) {
    dbg(i);

    int cost = dp[i];

    rep(j, m) {
      int nd = d[i] + g[j];
      int next = nd <= l ? nxt[nd] : -3;
      cost = min(cost, p[j] + (next >= 0 ? dp[next] : 0));

      dbg(i, j, g[j], nd, next, cost);
    }

    rep(j, m) {
      int nd = half[i] + g[j];
      if (half[i] < 0 || nd <= d[i]) {
        dbg("cont", nd);
        continue;
      };
      int next = nd <= l ? nxt[nd] : -3;
      cost = min(cost, p[j] / 2 + (next >= 0 ? dp[next] : 0));

      dbg(j, nd, next, cost);
    }

    dp[i] = cost;
  }

  dbg(dp);

  cout << dp[0] << endl;
}
