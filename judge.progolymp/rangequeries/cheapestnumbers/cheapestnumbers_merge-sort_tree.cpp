#include <bits/stdc++.h>
using namespace std;

// dbg
#ifdef LOCAL
  #include "dbg.h"
#else
  #define dbg(x)
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

const int N = 1e5;
const int MAX_V = 1e9;

struct Node {
  vi arr;
  vi pre;

  Node() : arr(0), pre(0) {}
  Node(vi arr) : arr(arr), pre(arr) {
    repp(i, 1, sz(arr)) {
      pre[i] += pre[i - 1];
    }
  }
  Node(int a) : arr(1), pre(1) {
    arr[0] = a;
    pre[0] = a;
  }

  // {count < V, cout == V}
  p2 count(int V) {  // count of all elements leq V
    auto lo = arr.begin();
    auto hi_lo = upper_bound(all(arr), V - 1);
    auto hi = upper_bound(all(arr), V);
    return {hi_lo - lo, hi - hi_lo};
  }

  // {sum < V, sum == V}
  p2 sum(int V) {  // sum of all elements leq V
    auto lo = arr.begin();
    auto hi_lo = upper_bound(all(arr), V - 1);
    auto hi = upper_bound(all(arr), V);
    int i = hi_lo - lo;
    int j = hi - hi_lo;

    int a = (i > 0) ? pre[i - 1] : 0;
    int b = (j > 0) ? pre[j - 1] - a : 0;

    return {a, b};
  }
};

ostream& operator<<(ostream& os, Node o) {
  rep(i, sz(o.arr) - 1) os << o.arr[i] << ' ';
  if (sz(o.arr)) {
    os << o.arr.back();
  }
  return os;
}

using T = Node;
T t[2 * N];
inline T merge(T a, T b) {
  assert(is_sorted(all(a.arr)));
  assert(is_sorted(all(b.arr)));

  vi res;
  merge(all(a.arr), all(b.arr), back_inserter(res));
  return res;
}

void build() {
  perr(i, N, 1) {
    t[i] = merge(t[2 * i], t[2 * i + 1]);
  }
}

p2 operator+(p2 lhs, p2 rhs) {
  return {lhs.first + rhs.first, lhs.second + rhs.second};
}
p2 query_sum(int l, int r, int V) {  // query [l, r)
  p2 res = {0, 0};
  for (l += N, r += N; l < r; l /= 2, r /= 2) {
    if (l & 1)
      res = res + t[l++].sum(V);
    if (r & 1)
      res = res + t[--r].sum(V);
  }
  return res;
}

p2 query_count(int l, int r, int V) {  // query [l, r)
  p2 res = {0, 0};
  for (l += N, r += N; l < r; l /= 2, r /= 2) {
    if (l & 1)
      res = res + t[l++].count(V);
    if (r & 1)
      res = res + t[--r].count(V);
  }
  return res;
}

signed main() {
  fast();

  int n, q;
  cin >> n >> q;
  rep(i, n) {
    int tmp;
    cin >> tmp;
    // dbg(tmp);
    t[i + N] = Node(tmp);
  }
  build();

  rep(i, q) {
    int l, r, V;
    cin >> l >> r >> V;

    // find last x s.t. `query_sum(l, r+1, x) <= V`
    int lo = 0, hi = MAX_V, res = -1;
    while (lo <= hi) {
      int mi = lo + (hi - lo) / 2;
      if (query_sum(l, r + 1, mi).first > V)
        hi = mi - 1;
      else {
        res = mi;
        lo = mi + 1;
      }
    }

    p2 sum = query_sum(l, r + 1, res);
    p2 cnt = query_count(l, r + 1, res);

    int ans = cnt.first + (min((V - sum.first) / res, cnt.second));
    cout << ans << '\n';
  }
  // dbg(query(0, 4));
  // dbg(t);

  return 0;
}
