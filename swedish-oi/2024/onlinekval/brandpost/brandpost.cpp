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

vvi water;
vector<p2> fire;
int w, h, n;

inline int dist(p2 a, p2 b) {
  int ans = abs(a.first - b.first) + abs(a.second - b.second);
  // dbg(a, b, ans);
  return ans;
}

signed main() {
  fast();

  cin >> w >> h >> n;

  dbg(w, h, n);

  water.resize(h, vi(w));

  bool fn = 0;
  rep(i, n) {
    int a, b;
    cin >> a >> b;
    --a;
    --b;

    if (a == 0 && b == 0)
      fn = 1;
    fire.emplace_back(a, b);
  }

  dbg(fn);
  dbg(fire);

  rep(y, h) {
    dbg(y);
    int time = y + 1;
    int x = 0;

    int wa = 0;
    repe(f, fire) {
      wa += max(0LL, time - dist(f, {x, y}));
    }

    priority_queue<int, vi, greater<int>> fq;
    int fi = 0;
    sort(all(fire), [&](p2 a, p2 b) {
      // return a.first + abs(a.second - i) < b.first + abs(b.second - i);
      return dist(a, {x, y}) < dist(b, {x, y});
    });

    while (fi < n && dist(fire[fi], {x, y}) <= time) {
      fq.push(fire[fi].first);
      fi++;
    }

    rep(x, w) {
      dbg(fq);
      time = y + x + 2;
      water[y][x] = wa;

      while (!fq.empty() && fq.top() < x + 1)
        fq.pop();
      wa += 2 * sz(fq);
      if (x == w - 1)
        dbg(sz(fq));

      while (fi < n && fire[fi].first < x + 1)
        fi++;

      while (fi < n && dist(fire[fi], {x + 1, y}) <= time) {
        wa += max(0LL, time - dist(fire[fi], {x + 1, y}));
        fq.push(fire[fi].first);
        fi++;
      }
    }
  }
  repe(i, water) dbg(i);

  vvi dp(h, vi(w, inf));

  dp[0][0] = fn;
  rep(y, h) {
    rep(x, w) {
      if (y + 1 < h)
        dp[y + 1][x] = min(dp[y + 1][x], dp[y][x] + water[y + 1][x]);
      if (x + 1 < w)
        dp[y][x + 1] = min(dp[y][x + 1], dp[y][x] + water[y][x + 1]);
    }
  }

  dbg("--------- CR ----------");
  rep(y, h) {
    vi r;
    rep(x, w) {
      int wa = 0;
      repe(f, fire) {
        wa += max(0LL, y + x + 1 - dist(f, {x, y}));
      }
      r.push_back(wa);
    }
    dbg(r);
  }

  dbg("--------- DP ----------");
  repe(d, dp) dbg(d);

  cout << dp[h - 1][w - 1];

  return 0;
}
