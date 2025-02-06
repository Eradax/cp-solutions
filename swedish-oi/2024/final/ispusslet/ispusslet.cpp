#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int(i) = 0; (i) < (n); (i)++)
#define repe(i, n) for (auto&(i) : (n))

#define sz(c) ((int)c.size())
#define all(c) (c.begin()), (c.end())

using pii = pair<int, int>;
using vpi = vector<pii>;

using vi = vector<int>;
using vvi = vector<vi>;

struct PIIHASH {
  size_t operator()(const pii& x) const {
    return hash<long long>()(
        ((long long)x.first) ^ (((long long)x.second) << 32)
    );
  }
};

const int K = 20000;
vvi graph;

vi ans;

void add(int u, int v) {
  // Add the edge between u and v to the ans
  // FIXME: This should do something
}

vector<bool> seen(K, 0);
bool dfs_tree(int u) {
  seen[u] = true;
  bool start = false;

  repe(v, graph[u]) {
    if (seen[v])
      continue;

    add(u, v);

    bool ret = dfs_tree(v);

    if (!ret) {
      // Go down and up
      add(u, v);
      add(v, u);

      start = !start;
    }

    start = !start;
  }
  return start;
}

vi par(K);
int cycle_start = -1;
int cycle_end = -1;

bool dfs_cycle(int u, int v) {
  seen[v] = true;

  repe(w, graph[u]) {
    if (w == v)
      continue;

    if (seen[w]) {
      cycle_start = u;
      cycle_end = w;
      return true;
    }

    par[w] = v;
    if (dfs_cycle(w, v))
      return true;
  }
  return false;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m, r;
  cin >> n >> m >> r;

  vpi cords;

  unordered_map<pii, int, PIIHASH> compress;
  pii s;

  rep(i, n) {
    string line;

    rep(j, sz(line)) {
      if (line[j] == 'S') {
        s = {i, j};
        cords.push_back(s);
      } else if (line[j] == 'X') {
        cords.emplace_back(i, j);
      }
    }
  }

  int k = sz(cords);

  int idx = 0;
  repe(i, cords) {
    compress[i] = idx++;
  }

  vvi rows(k);
  vvi columns(k);

  for (auto [u, v] : cords) {
    rows[u].push_back(v);
    columns[v].push_back(u);
  }

  sort(all(rows));
  sort(all(columns));

  rep(r, k) {
    if (!sz(rows[r]))
      continue;
    rep(c, sz(rows[r]) - 1) {
      int u = compress[{r, rows[r][c]}];
      int v = compress[{r, rows[r][c + 1]}];

      graph[u].push_back(v);
      graph[v].push_back(u);
    }
  }

  rep(c, k) {
    if (!sz(columns[c]))
      continue;
    rep(r, sz(columns[c]) - 1) {
      int u = compress[{columns[c][r], c}];
      int v = compress[{columns[c][r + 1], c}];

      graph[u].push_back(v);
      graph[v].push_back(u);
    }
  }

  // dfs to generate a solve
  seen.assign(K, 0);
  bool ret = dfs_tree(0);

  if (ret) {
    print_ans();
    return 0;
  }

  // find cycle

  seen.assign(K, false);
  par.assign(K, -1);

  rep(i, k) {
    if (!seen[i] && dfs_cycle(i, par[i]))
      break;
  }

  bool isCycle = cycle_start != -1;

  if (!ret && !isCycle) {
    cout << -1 << endl;
    return 0;
  }

  // go through cycle if needed (i.e. the root node is wrongly flipped)
}
