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
#define sz(c) ((int)c.size())

using ll = long long;
#define int ll

using vi = vector<int>;
using vvi = vector<vi>;

using pi = pair<int, int>;
using vpi = vector<pi>;
using vvpi = vector<vpi>;

using t3 = tuple<int, int, int>;
using v3 = vector<t3>;
using vv3 = vector<v3>;

static constexpr int INF = 1e9;
static constexpr int MAXRC = 1e6;

struct Choc {
  int r, c, k;
  Choc(int r, int c, int k) : r(r), c(c), k(k) {}
};

signed main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  dbg(n);

  auto getsz = [](int& r, int& c) -> int {
    dbg(r, c);
    if (r == c && r == 1) {
      r = c = 0;
      return 1;
    }

    int ret = max(r / 2 * c, c / 2 * r);
    if (r / 2 * c > c / 2 * r) {
      r -= r / 2;
    } else {
      c -= c / 2;
    }

    dbg(ret);

    return ret;
  };

  vector<Choc> choc;
  rep(i, n) {
    int r, c, k;
    cin >> r >> c >> k;
    k %= 2;
    if (!k)
      k = 2;
    choc.emplace_back(r, c, k);
  }

  vv3 chains;  // all the small chains
  v3 megachain;

  int cnt = 0;
  rep(i, n) {
    auto [r, c, k] = choc[i];

    dbg(r, c, k);

    rep(_, k) {
      int rr = r;
      int cc = c;

      int cnt2 = 0;
      v3 chain;
      while (rr + cc != 0) {
        dbg(rr, cc);
        chain.emplace_back(getsz(rr, cc), cnt, cnt2);
        cnt2++;
      }

      dbg(chain);

      chains.push_back(chain);
      cnt++;
    }
  }

  vvi chain_pos(sz(chains));  // indexes into megachain

  for (auto chain : chains)
    dbg(chain);

  for (auto& chain : chains) {
    assert(sz(chain) <= 3 * __bit_ceil(MAXRC) * MAXRC);

    megachain.insert(megachain.end(), all(chain));
  }

  sort(all(megachain), greater<t3>());

  dbg(megachain);

  rep(i, sz(megachain)) {
    auto [_, cnt, cnt2] = megachain[i];
    dbg(i, cnt, cnt2);
    dbg(chain_pos[cnt]);
    // assert(cnt2 == sz(chain_pos[cnt]));

    chain_pos[cnt].push_back(i);
  }

  dbg(chain_pos);

  vi tot;

  int p = 1;
  rep(i, sz(megachain)) {
    tot.push_back(
        (!tot.empty() ? tot[sz(tot) - 1] : 0) + p * get<0>(megachain[i])
    );

    p *= -1;
  }

  dbg(tot);

  int ans = tot[sz(tot) - 1];

  auto getpref = [](vi& pref, int l, int h) -> int {
    if (l >= h)
      return 0;
    l = max(l, 0LL);
    h = min(h, sz(pref));

    int res = pref[h - 1] - (l ? pref[l - 1] : 0);

    return res;
  };

  for (auto& chainpos : chain_pos) {
    int tmp = 0;

    int prev = -1;
    int p = 1;
    for (auto i : chainpos) {
      tmp += getpref(tot, prev + 1, i) * p;
      prev = i;
      p *= -1;
    }

    tmp += getpref(tot, prev + 1, sz(tot)) * p;

    assert(tmp >= 0);

    dbg(tmp);

    ans = min(ans, tmp);
  }

  dbg(ans);

  cout << ans << endl;
}
