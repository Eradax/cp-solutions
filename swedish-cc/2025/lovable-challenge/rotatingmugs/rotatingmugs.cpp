#include <bits/stdc++.h>
using namespace std;

unordered_map<char, int> ma = {
  {'N', 0},
  {'E', 1},
  {'S', 2},
  {'W', 3},
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int m;
  cin >> m;

  string s;
  cin >> s;

  int sr = 0;
  int mr = 0;

  for (int i = 0; i < m; i++) {
    sr += ma[s[i]];
    mr = max(mr, ma[s[i]]);
  }

  if (m == 2)
      cout << (s[0] == s[1] ? sr / 2 : -1);
  else if (sr % 2)
      cout << -1;
  else if (mr <= sr / 2)
      cout << sr / 2;
  else
      cout << 4;
}
