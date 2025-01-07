#include <bits/stdc++.h>

#ifdef DBG
#include "../../../../dbg.h"
#else
#define dbg(...)
#endif

using namespace std;

using vi = vector<int>;

#define rep(i, n) for (int i = 0; i < n; i++)

const int N = 2e5;
int n;
int t[2 * N];

void modify(int l, int r, int value) {
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1)
      t[l++] += value;
    if (r & 1)
      t[--r] += value;
  }
}

void push() {
  for (int i = 1; i < n; ++i) {
    t[i << 1] += t[i];
    t[i << 1 | 1] += t[i];
    t[i] = 0;
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int v;
  cin >> n >> v;

  rep(i, v) {
    int l, r, k;
    cin >> l >> r >> k;
    modify(l, r + 1, k);
  }

  push();

  rep(i, n) {
    cout << t[n + i] << " ";
  }
  cout << endl;
}
