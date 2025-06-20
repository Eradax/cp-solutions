#include <bits/stdc++.h>
using namespace std;

// NOTE: for 0.01 on kattis use faster io

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  vector<int> cnts(n);
  for (int i = 0; i < n-1; i++) {
    int v;
    cin >> v;
    cnts[v - 1]++;
  }

  vector<int> ans(n, -1);

  int i = 0;
  while (i < n) {
    int j = i + 1;
    while (j < n && cnts[j] == 0) j++;
    if (j >= n) break;

    ans[j] = i;
    cnts[i]--;
    i = j;
  }

  i = 0;
  for (int j = 1; j < n; j++) {
    if (ans[j] != -1) continue;
    while (cnts[i] == 0) i++;

    ans[j] = i;
    cnts[i]--;
  }

  for (int i = 1; i < n; i++) {
    cout << ans[i] + 1 << ' ';
  }
}
