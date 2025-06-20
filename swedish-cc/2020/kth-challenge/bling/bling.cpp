#include <bits/stdc++.h>

#ifdef DBG
  #define dbg(expr)                                                          \
    cerr << "[" << __FUNCTION__ << ", " << __LINE__ << "] " << #expr << ": " \
         << expr << endl
#else
  #define dbg(...)
#endif
using namespace std;

#define sz(c) ((int)c.size())

template <typename T>
ostream& operator<<(ostream& o, vector<T> v) {
  o << "{";
  for (int i = 0; i < sz(v); i++)
    o << v[i] << " \n"[i == sz(v) - 1];
  o << "}";
  return o;
}

template <typename T, size_t len>
ostream& operator<<(ostream& o, array<T, len> v) {
  o << "{";
  for (int i = 0; i < sz(v); i++)
    o << v[i] << (i == sz(v) - 1 ? "" : ", ");
  o << "}";
  return o;
}

template <typename... Args>
ostream& operator<<(ostream& o, tuple<Args...>& t) {
  o << "{";
  apply(
      [&](auto&... elems) {
        int idx = 0;
        ((o << (idx++ == 0 ? "" : ", ") << elems), ...);
      },
      t
  );
  o << "}";
  return o;
}

#define idx(d, b, ft, et) [d][b][ft[0]][ft[1]][ft[2]][et[0]][et[1]][et[2]]

using ll = long long;

#define int ll

using a3 = array<int, 3>;

signed main() {
  cin.tie(0)->sync_with_stdio(0);

  ll dp[41][13][5][5][5][2][2][2];
  memset(dp, -1, sizeof(dp));

  auto calc = [](int d) -> ll {
    if (d < 0)
      return 0;

    ll ans = 3;
    while (d >= 3) {
      ans *= 4;
      d -= 3;
    }
    return ans;
  };

  auto solve = [&](auto self, int d, ll b, a3 ft, a3 et, int lf) {
    if (d == -1)
      return b;

    auto dd = d;
    auto bb = b;
    auto fftt = ft;
    auto eett = et;

    ll cm = 0;  // cm = clean_money

    for (int i = 0; i < 3; i++) {
      cm += calc(d - i) * max(ft[i] - 4, 0ll);
      ft[i] -= max(ft[i] - 4, 0ll);
    }

    for (int i = 0; i < 3; i++) {
      cm += calc(d - i) * max(et[i] - 1, 0ll) * 5;
      et[i] -= max(et[i] - 1, 0ll);
    }

    ll f = ft[0] * 3 + lf;
    ll e = et[0] * 3;

    // cm += max(calc(d - 3), 1ll) * max(f - 12, 0ll);
    // f -= max(f - 12, 0ll);
    //
    // cm += max(calc(d - 3), 1ll) * max(e - 3, 0ll) * 5;
    // e -= max(e - 3, 0ll);

    cm += max(b - 12, 0ll);
    b -= max(b - 12, 0ll);

    assert(0 <= d && d <= 40);
    assert(0 <= b && b <= 12);

    for (auto i : ft)
      assert(0 <= i && i <= 4);
    for (auto i : et)
      assert(0 <= i && i <= 1);

    auto ffftt = ft;
    auto eeett = et;

    if (dp idx(d, b, ft, et) != -1)
      return cm + dp idx(d, b, ft, et);

    rotate(ft.begin(), ft.begin() + 1, ft.end());
    rotate(et.begin(), et.begin() + 1, et.end());

    ll ans = 0;
    tuple<ll, int, int, int> state;
    for (int ff = 0; ff < f + 1; ff++) {
      ft[2] += f - ff;
      b += ff;

      for (int ee = 0; ee < e + 1; ee++) {
        et[2] += e - ee;
        b += ee * 5;
        if (b >= 4) {
          et[2]++;
          b -= 4;
          if (self(self, d - 1, b, ft, et, 0) > ans) {
            ans = self(self, d - 1, b, ft, et, 0);
            state = {self(self, d - 1, b, ft, et, 0), ff, ee, 0};
          }
          b += 4;
          et[2]--;
        }

        if (self(self, d - 1, b, ft, et, 0) > ans) {
          ans = self(self, d - 1, b, ft, et, 0);
          state = {self(self, d - 1, b, ft, et, 0), ff, ee, 1};
        }

        if (b >= 4) {
          b += 1;
          if (self(self, d - 1, b, ft, et, 0) > ans) {
            ans = self(self, d - 1, b, ft, et, 0);
            state = {self(self, d - 1, b, ft, et, 0), ff, ee, 2};
          }
          b -= 1;
        }

        if (self(self, d - 1, b, ft, et, 0) > ans) {
          ans = self(self, d - 1, b, ft, et, 0);
          state = {self(self, d - 1, b, ft, et, 0), ff, ee, 3};
        }

        et[2] -= e - ee;
        b -= ee * 5;
      }

      ft[2] -= f - ff;
      b -= ff;
    }

    dbg(dd);
    dbg(bb);
    dbg(fftt);
    dbg(eett);
    dbg(d);
    dbg(b);
    dbg(ft);
    dbg(et);
    dbg(cm);
    dbg(f);
    dbg(e);
    dbg(ans + cm);
    dbg(state);

    dp idx(d, b, ffftt, eeett) = ans;
    return cm + ans;
  };

  int d;
  ll b;
  cin >> d >> b;
  d--;

  ll ans = b % 100;
  b /= 100;

  int f;
  cin >> f;

  a3 ft, et = {0};
  for (auto& i : ft)
    cin >> i;

  ans += solve(solve, d, b, ft, et, f) * 100;
  cout << ans << endl;
}
