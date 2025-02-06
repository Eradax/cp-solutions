#include <bits/stdc++.h>
// #include "dbg.h"
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

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

// dbg
// #define dbg(x)

const int N = 2e5;

struct Node {
  vi arr;

  Node() : arr(0) {}
  Node(vi arr) : arr(arr) {}
  Node(int a) : arr(1) { arr[0] = a; }

  int count(int V) {
    auto lo = lower_bound(all(arr), V);
    auto hi = upper_bound(all(arr), V);
    return hi - lo;
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

int query(int l, int r, int V) {  // query [l, r)
  int res = 0;
  for (l += N, r += N; l < r; l /= 2, r /= 2) {
    if (l & 1)
      res += t[l++].count(V);
    if (r & 1)
      res += t[--r].count(V);
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

    int ans = query(l, r + 1, V);

    cout << ans << '\n';
  }
  // dbg(query(0, 4));
  // dbg(t);

  return 0;
}
