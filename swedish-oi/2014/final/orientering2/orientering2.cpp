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

#define bet(lo, x, hi) ((lo) <= (x) && (x) < (hi))

/*
 * Upp: ^ 0
 * Right: > 1
 * Down: v 2
 * Left: < 3
 */
char graph[800][800];
int dist[800][800][4];

int n, m;

int solve(int r, int c) {
  rep(i, 800) {
    rep(j, 800) {
      rep(k, 4) {
        dist[i][j][k] = inf;
      }
    }
  }

  deque<tuple<int, int, int>> q;

  dist[0][0][1] = 0;
  q.push_front({0, 0, 1});

  while (!q.empty()) {
    int y, x, dir;
    tie(y, x, dir) = q.front();
    q.pop_front();

    int dy = 0, dx = 0, ndir = -1;
    if (graph[y][x] == '>') {
      ndir = 1;
      dx = 1;
    }
    if (graph[y][x] == '<') {
      ndir = 3;
      dx = -1;
    }
    if (graph[y][x] == '^') {
      ndir = 0;
      dy = -1;
    }
    if (graph[y][x] == 'v') {
      ndir = 2;
      dy = 1;
    }

    if (bet(0, y + dy, 800) && bet(0, x + dx, 800) && ndir != -1) {
      if (dist[y + dy][x + dx][ndir] > dist[y][x][dir]) {
        dist[y + dy][x + dx][ndir] = dist[y][x][dir];
        dbg(y + dy, x + dx, ndir, dist[y + dy][x + dx][ndir]);
        q.emplace_front(y + dy, x + dx, ndir);
      }
    }

    dy = 0;
    dx = 0;
    if (dir == 1) {
      dx = 1;
    }
    if (dir == 3) {
      dx = -1;
    }
    if (dir == 0) {
      dy = -1;
    }
    if (dir == 2) {
      dy = 1;
    }
    assert(bet(0, dir, 4));

    if (bet(0, y + dy, 800) && bet(0, x + dx, 800)) {
      if (dist[y + dy][x + dx][dir] > dist[y][x][dir] + 1 - (ndir == -1)) {
        dist[y + dy][x + dx][dir] = dist[y][x][dir] + 1 - (ndir == -1);
        dbg(y + dy, x + dx, dir, dist[y + dy][x + dx][dir]);
        q.emplace_back(y + dy, x + dx, dir);
      }
    }
  }

  int ans = inf;

  rep(i, 4) {
    dbg(dist[r][c][i]);
    ans = min(ans, dist[r][c][i]);
  }

  assert(ans >= 0);
  return ans;
}

signed main() {
  fast();

  int n, m, r, c;
  cin >> n >> m >> r >> c;
  r--;
  c--;

  rep(i, n) {
    string line;
    cin >> line;
    rep(j, m) {
      graph[i][j] = line[j];
    }
  }

  cout << solve(r, c);

  return 0;
}
