#pragma GCC optimize("Ofast")
#include <bitset>
#pragma GCC target("avx2,tune=native")
#include <bits/stdc++.h>

#ifdef DBG
  #include "../../../../dbg.h"
#else
  #define dbg(...)
#endif

using namespace std;

using ll = long long;
using ui = unsigned long long;

using vi = vector<int>;

#define rep(i, n) for (int i = 0; i < n; i++)

static const int V = 10;

template <class T, int N>
struct Vec {
  array<T, N> d{};
  Vec operator+(const Vec& v) const {
    Vec res{};
    rep(i, N) res.d[i] = d[i] + v.d[i];
    return res;
  }
};

template <class T, int N>
struct Matrix {
  array<array<T, N>, N> d{};
  Matrix operator*(const Matrix& m) const {
    Matrix a{};
    rep(i, N) rep(j, N) rep(k, N) a.d[i][j] += d[i][k] * m.d[k][j];
    return a;
  }

  Vec<T, N> operator*(const Vec<T, N>& vec) const {
    Vec<T, N> ret{};
    rep(i, N) rep(j, N) ret.d[i] += d[i][j] * vec.d[j];
    return ret;
  }
};

using IT = pair<Matrix<ui, V>, Vec<ui, V>>;

IT operator+(const IT& L, const IT& R) {
  IT res;
  res.first = R.first * L.first;
  res.second = R.first * L.second + R.second;
  return res;
}

struct T {
  IT ID;
  vector<IT> t;
  int n;

  IT getIT(int b) {
    IT ret;
    rep(i, V) ret.first.d[i][i] = 1;
    rep(i, V) ret.first.d[b][i] = 1;
    ret.second.d[b] = 1;
    return ret;
  }

  T(const vi& bits) {
    n = bits.size();
    rep(i, V) ID.first.d[i][i] = 1;

    t.resize(2 * n, ID);
    for (int i = 0; i < n; i++)
      t[n + i] = getIT(bits[i]);

    for (int i = n - 1; i > 0; i--)
      t[i] = t[2 * i] + t[2 * i + 1];
  }

  void set(int i, int b) {
    i += n;

    t[i] = getIT(b);

    for (i /= 2; i > 0; i /= 2)
      t[i] = t[2 * i] + t[2 * i + 1];
  }

  ui q(int l, int r) {
    IT ld = ID;
    IT rd = ID;

    for (l += n, r += n; l < r; l /= 2, r /= 2) {
      if (l & 1)
        ld = ld + t[l++];
      if (r & 1)
        rd = t[--r] + rd;
    }

    ld = ld + rd;
    ui ans = 1;
    rep(i, V) ans += ld.second.d[i];
    return ans;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, q;
  cin >> n >> q;

  vi bits(n);
  rep(i, n) cin >> bits[i];

  T t(bits);

  cout << t.q(0, n) << "\n";

  rep(_, q) {
    int i, v;
    cin >> i >> v;
    i--;
    if (bits[i] != v) {
      bits[i] = v;
      t.set(i, v);
    }

    cout << t.q(0, n) << "\n";
  }
}
