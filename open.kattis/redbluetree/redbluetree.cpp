#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,inline,unroll-loops")

#ifdef DBG
  #include "../../dbg.h"
#else
  #define dbg(...)
#endif

#define gc() getchar_unlocked()
template <typename T>
inline void read(T& v) {
  v = 0;
  char c;
  while ((c = gc()) && c != ' ' && c != '\n') {
    v *= 10;
    v += c - '0';
  }
}

#define rint(a) read(a)
// #define rint(a) cin >> a

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define repp(i, s, n) for (int i = s; i < (n); i++)

#define sz(c) ((int)c.size())

static constexpr int M = 1000 * (1000 - 1) / 2;
static constexpr int N = 1000;

struct UF {
  wchar_t e[N];
  UF(int n) { wmemset(e, -1, n); }
  bool sameset(int a, int b) { return find(a) == find(b); }
  int size(int x) { return -e[find(x)]; }
  int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
  bool join(int a, int b) {
    a = find(a);
    b = find(b);

    if (a == b) {
      return false;
    }

    if (size(a) > size(b))
      swap(a, b);

    e[a] += e[b];
    e[b] = a;

    return true;
  }
};

int main() {
  int n, m, k;
  rint(n);
  rint(m);
  rint(k);

  pair<int, int> r[M], b[M];
  int rr = 0, bb = 0;

  rep(i, m) {
    char o;
    int u, v;

    o = getchar_unlocked();
    getchar_unlocked();
    rint(u);
    rint(v);

    u--;
    v--;

    if (o == 'R') {
      r[rr++] = make_pair(u, v);
    } else {
      b[bb++] = make_pair(u, v);
    }
  }

  int mi = n - 1, ma = 0;

  UF uf(n);

  rep(i, rr) {
    auto [x, y] = r[i];

    if (!uf.sameset(x, y)) {
      uf.join(x, y);
      mi--;
    }
  }

  wmemset(uf.e, -1, n);

  rep(i, bb) {
    auto [x, y] = b[i];

    if (!uf.sameset(x, y)) {
      uf.join(x, y);
      ma++;
    }
  }

  putchar_unlocked((mi <= k && k <= ma) ? '1' : '0');
  putchar_unlocked('\n');
}
