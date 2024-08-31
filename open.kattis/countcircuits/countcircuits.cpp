#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto &i : container)
#define per(i, high) for (int i = high - 1; i >= 0; i--)

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
void resettimer() { Start = chrono::high_resolution_clock::now(); }
int elapsedmillis() {
  return chrono::duration_cast<chrono::milliseconds>(
             chrono::high_resolution_clock::now() - Start)
      .count();
}
random_device rd;
mt19937 rng(rd());
template <typename T, typename U> inline int randint(T lo, U hi) {
  return uniform_int_distribution<int>((int)lo, (int)hi)(rng);
} // [lo,hi]
template <typename T> inline T randel(vector<T> &v) {
  return v[uniform_int_distribution<int>(int(0), int(v.size()) - int(1))(rng)];
} // [lo,hi]

const int N = 40;
const int M = 20 * N + 1;
array<array<array<int, N + 1>, M>, M> dp;
void initialize_array() {
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < M; ++j) {
            for (int k = 0; k <= N; ++k) {
                dp[i][j][k] = -1;
            }
        }
    }
}

int n;
vector<p2> vecs;

int solve(int x, int y, int next) {
  if (dp[x+400][y+400][next] != -1)
    return dp[x+400][y+400][next];

  int ans = 0;
  if ((x == 0 && y == 0 && next !=0 ))
    ans++;

  for (int i = next; i < n; i++) {
    ans += solve(x + vecs[i].first, y + vecs[i].second, i + 1);
  }

  dp[x+400][y+400][next] = ans;
  return ans;
}

signed main() {
  fast();
  initialize_array();
  cin >> n;

  vecs.resize(n);

  repe(i, vecs) { cin >> i.first >> i.second; }


  // dp[x][y][i] = sum(vec to (x, y) that isn't before index i)

  cout << solve(0, 0, 0) << endl;
  return 0;
}