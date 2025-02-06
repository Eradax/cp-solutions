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

int n, l;

vector<vector<p2>> adj;

void dijkstra(int s, vector<int>& d, vector<int>& p) {
  int n = adj.size();
  d.assign(n, inf);
  p.assign(n, -1);

  d[s] = 0;
  set<pair<int, int>> q;
  q.insert({0, s});
  while (!q.empty()) {
    int v = q.begin()->second;
    q.erase(q.begin());

    for (auto edge : adj[v]) {
      int to = edge.first;
      int len = edge.second;

      if (d[v] + len < d[to]) {
        q.erase({d[to], to});
        d[to] = d[v] + len;
        p[to] = v;
        q.insert({d[to], to});
      }
    }
  }
}

signed main() {
  fast();

  cin >> n >> l;

  adj.resize(n);

  rep(i, l) {
    int m;
    cin >> m;
    vi line(m);
    rep(j, m) {
      cin >> line[j];
      line[j]--;
    }

    repp(j, 1, m) {
      adj[line[0]].emplace_back(line[j], m - 1 - j);
      adj[line[j]].emplace_back(line[0], m - 1 - j);
    }

    perr(j, m, 1) {
      adj[line[m - 1]].emplace_back(line[j], j);
      adj[line[j]].emplace_back(line[m - 1], j);
    }

    dbg(adj[line[0]]);
  }

  repe(i, adj) {
    dbg(i);
  }

  vi dist, back_track;
  dijkstra(0, dist, back_track);

  cout << dist[n - 1];

  return 0;
}
