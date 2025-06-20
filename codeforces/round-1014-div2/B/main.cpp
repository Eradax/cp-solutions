#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;

    int fo = 0, fe = 0;
    int so = 0, se = 0;

    string s;
    cin >> s;
    for (int i = 0; i < n; i++) {
      if (s[i] == '1')
        continue;
      if (i % 2)
        fe++;
      else
        fo++;
    }

    cin >> s;
    for (int i = 0; i < n; i++) {
      if (s[i] == '1')
        continue;
      if (i % 2)
        se++;
      else
        so++;
    }

    cout << (((fo+se >= (n + 1) / 2) && (fe + so) >= n/2) ? "YES" : "NO") << '\n';
  }
}
