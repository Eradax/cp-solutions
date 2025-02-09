#pragma GCC optimize("Ofast")
#include <iostream>
#pragma GCC target("avx2")
#include <algorithm>
#include <utility>
#include <vector>

#ifdef DBG
  #include "../../../../dbg.h"
#else
  #define dbg(...)
#endif

using namespace std;

#define repp(i, s, n) for (size_t i = s; i < n; i++)
#define rep(i, n) repp(i, 0, n)

#define perr(i, s, n) for (int i = n - 1; i >= s; i--)
#define per(i, n) perr(i, 0, n)

#define all(c) c.begin(), c.end()

using ui = unsigned int;
using pi = pair<ui, ui>;

static constexpr ui INF = 1e9;

using vi = vector<ui>;
using vpi = vector<pi>;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  ui n, t;
  cin >> n >> t;

  dbg(n, t);

  vpi v(2 * n);
  rep(i, n) {
    cin >> v[2 * i].first;
    v[2 * i + 1].first = (3 * v[2 * i].first) / 2;
    v[2 * i].second = i;
    v[2 * i + 1].second = (1 << 31) | i;
  }

  dbg(v);

  sort(all(v));

  dbg(v);

  vi w(t, INF);
  w[0] = 0;

  rep(i, 2 * n) {
    rep(k, t - v[i].first) {
      w[k + v[i].first] = min(
          w[k + v[i].first], w[k] + 1 + (v[i].second >> 31)
      );
    }
  }

  for (auto i : w) dbg(i);

  ui ip = 0;
  tuple<ui, ui, ui> curr{INF, INF, INF};
  per(tp, t) {
    if (w[tp] == INF) continue;
    while (ip < 2 * n && tp + v[ip].first < t)
      ip++;

    if (ip >= 2 * n)
      break;

    curr = min(curr, {tp + v[ip].first, w[tp] + 1 + (v[ip].second >> 31), ip});
    dbg(tp, ip, curr);
  }

  dbg(curr);

  cout << get<0>(curr) << " " << get<1>(curr) << '\n';

  vi ans(n);
  ans[v[get<2>(curr)].second << 1 >> 1] += v[get<2>(curr)].first;

  auto best = curr;
  swap(get<0>(best), get<1>(best));

  dbg(best);
  dbg(1 + (v[get<2>(best)].second >> 31));

  get<0>(best) -= 1 + (v[get<2>(best)].second >> 31);
  get<1>(best) -= v[get<2>(best)].first;

  dbg(best);
  int ic = 0;

  tuple<ui, ui, ui> new_best{INF, INF, INF};
  while (get<0>(best)) {
    // if (ic++ > 10) {break;}
    rep(ip, 2 * n) {
      new_best = min(
          new_best,
          {get<0>(best) - 1 - (v[ip].second >> 31),
           get<1>(best) - v[ip].first,
           ip}
      );
      tuple<ui, ui, ui> tmp{
          get<0>(best) - 1 - (v[ip].second >> 31),
          get<1>(best) - v[ip].first,
          ip
      };
      dbg(tmp);
    }
    ans[v[get<2>(new_best)].second << 1 >> 1] += v[get<2>(new_best)].first;

    swap(best, new_best);

    dbg(best, ans);
  }

  rep(i, n) cout << ans[i] << ' ';
  cout << '\n';
}
