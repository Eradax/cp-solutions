#include <bits/stdc++.h>

#ifdef LOCAL
  #include "dbg.h"
#else
  #define dbg(...)
#endif

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

string line;
int solve(int start) {
  dbg(start);
  if (start > sz(line)) {
    return 0;
  }
  if (start == sz(line)) {
    return 1;
  }

  if (line[start] - '0' == 0) {
    return 0;
  }

  int res = 0;

  res += solve(start + 1);

  if ((line[start] - '0') * 10 + (line[start + 1] - '0') <= 29) {
    res += solve(start + 2);
  }

  return res;
}

signed main() {
  fast();

  cin >> line;

  dbg(sz(line));

  int ans = solve(0);

  cout << ans;

  return 0;
}
