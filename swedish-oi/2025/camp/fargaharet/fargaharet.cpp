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

template <class T, int N>
struct Vec {
  array<T, N> d{};
  Vec operator+(const Vec& v) const {
    Vec res{};
    for (int i = 0; i < N; i++) {
      res.d[i] = d[i] + v.d[i];
    }
    return res;
  }
};

template <class T, int N>
struct Matrix {
  array<array<T, N>, N> d{};
  Matrix operator*(const Matrix& m) const {
    Matrix a{};
    for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++)
        for (int k = 0; k < N; k++)
          a.d[i][j] += d[i][k] * m.d[k][j];
    return a;
  }
  Vec<T, N> operator*(const Vec<T, N>& vec) const {
    Vec<T, N> ret{};
    for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++)
        ret.d[i] += d[i][j] * vec.d[j];
    return ret;
  }
};

using IT = pair<Matrix<ui, 10>, Vec<ui, 10>>;

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

  static IT opFromBit(int b) {
    IT ret;
    ret.first.d[0] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    ret.first.d[1] = {0, 1, 0, 0, 0, 0, 0, 0, 0, 0};
    ret.first.d[2] = {0, 0, 1, 0, 0, 0, 0, 0, 0, 0};
    ret.first.d[3] = {0, 0, 0, 1, 0, 0, 0, 0, 0, 0};
    ret.first.d[4] = {0, 0, 0, 0, 1, 0, 0, 0, 0, 0};
    ret.first.d[5] = {0, 0, 0, 0, 0, 1, 0, 0, 0, 0};
    ret.first.d[6] = {0, 0, 0, 0, 0, 0, 1, 0, 0, 0};
    ret.first.d[7] = {0, 0, 0, 0, 0, 0, 0, 1, 0, 0};
    ret.first.d[8] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 0};
    ret.first.d[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
    ret.second.d = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    rep(i, 10) ret.first.d[b][i] = 1;
    ret.second.d[b] = 1;
    return ret;
  }

  T(const vi& bits) {
    n = bits.size();
    ID.first.d[0] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    ID.first.d[1] = {0, 1, 0, 0, 0, 0, 0, 0, 0, 0};
    ID.first.d[2] = {0, 0, 1, 0, 0, 0, 0, 0, 0, 0};
    ID.first.d[3] = {0, 0, 0, 1, 0, 0, 0, 0, 0, 0};
    ID.first.d[4] = {0, 0, 0, 0, 1, 0, 0, 0, 0, 0};
    ID.first.d[5] = {0, 0, 0, 0, 0, 1, 0, 0, 0, 0};
    ID.first.d[6] = {0, 0, 0, 0, 0, 0, 1, 0, 0, 0};
    ID.first.d[7] = {0, 0, 0, 0, 0, 0, 0, 1, 0, 0};
    ID.first.d[8] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 0};
    ID.first.d[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
    ID.second.d = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    t.resize(2 * n, ID);
    for (int i = 0; i < n; i++) {
      t[n + i] = opFromBit(bits[i]);
    }
    for (int i = n - 1; i > 0; i--) {
      t[i] = t[2 * i] + t[2 * i + 1];
    }
  }

  void set(int i, int b) {
    i += n;

    t[i] = opFromBit(b);

    for (i /= 2; i > 0; i /= 2) {
      t[i] = t[2 * i] + t[2 * i + 1];
    }
  }

  IT query(int l, int r) {
    IT ld = ID;
    IT rd = ID;

    for (l += n, r += n; l < r; l /= 2, r /= 2) {
      if (l & 1)
        ld = ld + t[l++];
      if (r & 1)
        rd = t[--r] + rd;
    }

    return ld + rd;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, q;
  cin >> n >> q;
  vi bits(n);
  for (int i = 0; i < n; i++)
    cin >> bits[i];

  T seg(bits);

  IT overall = seg.query(0, n);
  ui ans = 1;
  rep(i, 10) ans += overall.second.d[i];
  cout << ans << "\n";

  rep(_, q) {
    int i, v;
    cin >> i >> v;
    i--;
    if (bits[i] != v) {
      bits[i] = v;
      seg.set(i, v);
    }

    overall = seg.query(0, n);
    ui ans = 1;
    rep(i, 10) ans += overall.second.d[i];

    cout << ans << "\n";
  }
}
