#include <bits/stdc++.h>

#ifdef DBG
  #include "../../dbg.h"
#else
  #define dbg(...)
#endif

/*
links:
    https://open.kattis.com/problems/drunktexting
source:
    Will Code for Drinks 2023
*/

using namespace std;

#define rep(i, n) for (int i = 0; i < n; i++)
#define sz(c) ((int)c.size())

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  string w1, w2;
  getline(cin, w1);
  getline(cin, w2);

  vector<vector<bool>> vis(sz(w1) + 10, vector<bool>(sz(w2) + 10, 0));
  vector<vector<pair<int, int>>> par(
      sz(w1) + 10, vector<pair<int, int>>(sz(w2) + 10, {-1, -1})
  );

  queue<pair<int, int>> q;

  q.emplace(0, 0);
  vis[0][0] = 1;

  dbg(sz(w1), sz(w2));

  while (sz(q)) {
    auto [i, j] = q.front();
    q.pop();

    dbg("-------");
    dbg(i, j);

    if (i < sz(w1) && j < sz(w2))
      if (w1[i] == w2[j]) {
        if (!vis[i + 1][j + 1]) {
          vis[i + 1][j + 1] = 1;
          par[i + 1][j + 1] = {i, j};
          q.emplace(i + 1, j + 1);

          dbg(i + 1, j + 1);
        }
      }

    if (i < sz(w1)) {
      if (!vis[i + 1][j]) {
        vis[i + 1][j] = 1;
        par[i + 1][j] = {i, j};
        q.emplace(i + 1, j);

        dbg(i + 1, j);
      }
    }

    if (j < sz(w2)) {
      if (!vis[i][j + 1]) {
        vis[i][j + 1] = 1;
        par[i][j + 1] = {i, j};
        q.emplace(i, j + 1);

        dbg(i, j + 1);
      }
    }
  }

  for (auto& i : par) {
    dbg(i);
  }

  for (auto& i : vis) {
    dbg(i);
  }

  int ans_len = 0;
  string ans = "";

  int i = sz(w1), j = sz(w2);

  while (i || j) {
    ans_len++;

    dbg(ans_len);

    auto [ni, nj] = par[i][j];

    dbg(ni, nj);

    if (ni + 1 == i && nj + 1 == j) {
      ans += w1[ni];
    } else if (ni + 1 == i) {
      ans += w1[ni];
    } else if (nj + 1 == j) {
      ans += w2[nj];
    } else {
      cout << "Fuck!!!" << endl;
      exit(1);
    }

    i = ni;
    j = nj;
  }

  reverse(ans.begin(), ans.end());

  cout << ans << endl;
}
