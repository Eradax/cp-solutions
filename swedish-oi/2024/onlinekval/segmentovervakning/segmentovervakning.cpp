#include <bits/stdc++.h>
using namespace std;

// dbg
#ifdef LOCAL
  #include "../../../../dbg.h"
#else
  #define dbg(...)
#endif

// typedefs
using ll = long long;
#define int ll
const int inf = int(1e18);

using vi = vector<int>;
using vvi = vector<vi>;
using p2 = pair<int, int>;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (int i = high - 1; i >= 0; i--)
#define perr(i, high, low) for (int i = high - 1; i >= low; i--)

#define clz(x) __builtin_clz(x)
#define popcount(x) __builtin_popcountll(x)

// fast io
inline void fast() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
}

#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define setcontains(set, x) (set.find(x) != set.end())
#define sz(container) ((int)container.size())
vector<p2> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

// time and rng
auto Start = chrono::high_resolution_clock::now();
void resettimer() {
  Start = chrono::high_resolution_clock::now();
}
int elapsedmillis() {
  return chrono::duration_cast<chrono::milliseconds>(
             chrono::high_resolution_clock::now() - Start
  )
      .count();
}
random_device rd;
mt19937 rng(rd());
template <typename T, typename U>
inline int randint(T lo, U hi) {
  return uniform_int_distribution<int>((int)lo, (int)hi)(rng);
}  // [lo,hi]
template <typename T>
inline T randel(vector<T>& v) {
  return v[uniform_int_distribution<int>(int(0), int(v.size()) - int(1))(rng)];
}  // [lo,hi]

// custom
vector<p2> deltas = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
#define beti(a, x, b) (a <= x && x <= b)

template <typename T, typename U>
inline void operator+=(pair<T, U>& l, const pair<T, U>& r) {
  l = {l.first + r.first, l.second + r.second};
}
template <typename T, typename U>
inline pair<T, U> operator+(const pair<T, U> l, const pair<T, U> r) {
  return {l.first + r.first, l.second + r.second};
}
template <typename T, typename U>
inline pair<T, U> operator-(const pair<T, U> l, const pair<T, U> r) {
  return {l.first - r.first, l.second - r.second};
}
template <typename T, typename U>
inline pair<T, U> operator*(const pair<T, U> l, const int m) {
  return {l.first * m, l.second * m};
}

priority_queue<p2> l;
priority_queue<p2> r;
unordered_set<int> removed;

int xmin, xmax;
int q;

signed main() {
  fast();

  cin >> xmin >> xmax >> q;

  dbg(xmin, xmax, q);

  repp(i, 1, q + 1) {
    string opt;
    cin >> opt;

    dbg(opt);

    if (opt == "-") {
      int s;
      cin >> s;
      removed.insert(s);
    }

    if (opt == "+") {
      int s, lo, hi;
      cin >> s >> lo >> hi;

      if (lo <= xmin) {
        l.push({hi, s});
      } else if (hi >= xmax) {
        r.push({-lo, s});
      }
    }

    int ll, ls = -1, rr, rs = -1;

    dbg(ls);
    while (ls == -1) {
      if (l.empty()) {
        ll = xmin;
        ls = -2;
        continue;
      }
      tie(ll, ls) = l.top();
      if (setcontains(removed, ls)) {
        l.pop();
        ls = -1;
      }
    }
    dbg(ll, ls);

    if (ll >= xmax) {
      cout << 1 << '\n';
      continue;
    }

    dbg(rs);
    while (rs == -1) {
      if (r.empty()) {
        rr = -xmax;
        rs = -2;
        continue;
      }
      tie(rr, rs) = r.top();
      if (setcontains(removed, rs)) {
        r.pop();
        rs = -1;
      }
    }
    rr = -rr;
    dbg(rr, rs);

    if (rr <= ll) {
      cout << 2 << '\n';
      continue;
    }

    cout << -1 << '\n';
  }

  return 0;
}
