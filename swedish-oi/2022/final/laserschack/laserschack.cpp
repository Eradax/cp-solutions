#include <bits/stdc++.h>
#include <cstdint>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); i++)

const vector<pair<int, int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
const int INF = 1e9;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int r, c;
  cin >> r >> c;

  vector<pair<int, int>> bombs;
  pair<int, int> start, end;

  vector<vector<int>> graph(r, vector<int>(c));
  vector<vector<int>> bomb_times(r, vector<int>(c, INF));

  rep(i, r) {
    string line;
    cin >> line;
    rep(j, c) {
      graph[i][j] = 0;
      if (line[j] == 'A')
        start = {i, j};
      if (line[j] == 'K')
        end = {i, j};
      if (line[j] == 'R')
        bombs.emplace_back(i, j);
      if (line[j] == 'o')
        graph[i][j] = 1;
    }
  }

  queue<pair<int, int>> q;
  for (auto& [y, x] : bombs) {
    q.emplace((y << 16) + x, 0);
  }

  while (!q.empty()) {
    auto [n, t] = q.front();
    q.pop();

    int y, x;
    y = n >> 16;
    x = 0xFFFF & n;

    for (auto& [dx, dy] : dirs) {
    }
  }
}
