#include <bits/stdc++.h>
#include <unordered_map>
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

struct pair_hash {
  inline std::size_t operator()(const std::pair<int, int>& v) const {
    return v.first * 31 + v.second;
  }
};

signed main() {
  fast();

  int n;
  cin >> n;

  vector<p2> pic1(n), pic2(n);

  rep(i, n) {
    cin >> pic1[i].first >> pic1[i].second;
  }

  rep(i, n) {
    cin >> pic2[i].first >> pic2[i].second;
  }

  unordered_map<p2, int, pair_hash> counts;

  repe(i, pic1) {
    repe(j, pic2) {
      int u, v;
      u = j.first - i.first;
      v = j.second - i.second;
      counts[{u, v}] += 1;
    }
  }

  int maxnum = 0;
  repe(i, counts) {
    if (i.second >= maxnum)
      maxnum = i.second;
  }

  cout << n - maxnum;

  return 0;
}
