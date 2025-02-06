#include <bits/stdc++.h>

#define DBG
#ifdef DBG
  #include "../../../../dbg.h"
#else
  #define dbg(...)
#endif

/*
source:
    Programmeringsolympiadens final 2023
links:
    https://po2punkt0.kattis.com/problems/hoppers2?tab=metadata
*/

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int r, c, n;

  cin >> r >> c >> n;

  vi nxt(r * c);
  vvi txn(r * c);

  rep(i, r) {
    string line;
    cin >> line;

    rep(j, c) {
      int curr = i * c + j;

      if (line[j] == '^') {
        nxt[curr] = curr - c;
      }
      if (line[j] == '>') {
        nxt[curr] = curr + 1;
      }
      if (line[j] == 'v') {
        nxt[curr] = curr + c;
      }
      if (line[j] == '<') {
        nxt[curr] = curr - 1;
      }

      txn[nxt[curr]].emplace_back(curr);
    }
  }
}
