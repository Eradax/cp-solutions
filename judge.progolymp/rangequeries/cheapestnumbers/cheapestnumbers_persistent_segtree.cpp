#include <bits/stdc++.h>
using namespace std;

// dbg
#ifdef LOCAL
  #include "dbg.h"
#else
  #define dbg(...)
#endif

// typedefs
using ll = long long;
#define int ll
using vi = vector<int>;
using vvi = vector<vi>;
using p2 = pair<int, int>;

// consts
const int inf = int(1e18);
vector<p2> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

// itr
#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (int i = high - 1; i >= 0; i--)
#define perr(i, high, low) for (int i = high - 1; i >= low; i--)

// funcs
#define clz(x) __builtin_clz(x)
#define popcount(x) __builtin_popcountll(x)

// don't sync with stdio. (Makes things faster)
inline void fast() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
}

// macros
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
#define setcontains(set, x) ((set).find(x) != (set).end())
#define sz(container) ((int)(container).size())

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
inline int randint(T lo, U hi) {  // [lo, hi]
  return uniform_int_distribution<int>((int)lo, (int)hi)(rng);
}

template <typename T>
inline T randel(vector<T>& v) {  // [lo, hi]
  return v[uniform_int_distribution<int>(int(0), int(v.size()) - int(1))(rng)];
}

struct vertex {
  vertex *l, *r;
  int sum;
  int cnt;

  vertex(int val, int cnt, bool q) : l(NULL), r(NULL), sum(val), cnt(cnt) {}

  vertex(int val) : l(NULL), r(NULL), sum(val), cnt(1) {}

  vertex(vertex* l, vertex* r) : l(l), r(r), sum(0), cnt(0) {
    if (l) {
      sum += l->sum;
      cnt += l->cnt;
    }
    if (r) {
      sum += r->sum;
      cnt += r->cnt;
    }
  }
};

vertex* build(int tl, int tr) {  // [tl, tr]
  if (tl == tr)
    return new vertex(0, 0, false);
  int tm = (tl + tr) / 2;
  return new vertex(build(tl, tm), build(tm + 1, tr));
}

p2 operator+(p2 l, p2 r) {
  return {l.first + r.first, l.second + r.second};
}
p2 get_sum(vertex* t, int tl, int tr, int l, int r) {
  if (l > r)
    return {0, 0};
  if (l == tl && tr == r)
    return {t->sum, t->cnt};
  int tm = (tl + tr) / 2;
  return get_sum(t->l, tl, tm, l, min(r, tm)) +
         get_sum(t->r, tm + 1, tr, max(l, tm + 1), r);
}

vertex* update(vertex* t, int tl, int tr, int pos, int new_val) {
  if (tl == tr)
    return new vertex(new_val);
  int tm = (tl + tr) / 2;
  if (pos <= tm)
    return new vertex(update(t->l, tl, tm, pos, new_val), t->r);
  else
    return new vertex(t->l, update(t->r, tm + 1, tr, pos, new_val));
}

signed main() {
  int n, q;
  cin >> n >> q;

  vector<p2> a(n);
  rep(i, n) {
    cin >> a[i].first;
    a[i].second = i;
  }

  vector<vertex*> roots;

  roots.push_back(build(0, n - 1));

  sort(all(a));
  rep(i, n) {
    roots.push_back(update(roots.back(), 0, n - 1, a[i].second, a[i].first));
  }

  rep(i, q) {
    int l, r, V;
    cin >> l >> r >> V;

    int lo = 0, hi = n, res = -1;
    while (lo <= hi) {
      int mi = lo + (hi - lo) / 2;
      if (get_sum(roots[mi], 0, n - 1, l, r).first > V)
        hi = mi - 1;
      else {
        res = mi;
        lo = mi + 1;
      }
    }

    dbg(res, get_sum(roots[res], 0, n - 1, l, r));
    cout << get_sum(roots[res], 0, n - 1, l, r).second << '\n';
  }
}
