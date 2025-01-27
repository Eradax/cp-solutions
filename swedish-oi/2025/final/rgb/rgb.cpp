#include <bits/stdc++.h>

#ifdef DBG
#include "../../../../dbg.h"
#else
#define dbg(...)
#endif

using namespace std;

using ll = unsigned long long;

#define int ll

using vi = vector<int>;
using vvi = vector<vi>;

static constexpr int INF = 1e18;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define per(i, n) for (int i = n - 1; i >= 0; i--)
#define sz(c) ((int)c.size())

signed main() {
  cin.tie(0)->sync_with_stdio(0);

  int r, g, b, k;
  cin >> r >> g >> b >> k;

  if (g == 0 && b == 0 && k >= 2) {
    r--;
    g++;
    b++;
    k--;
  } else if (g + b == 0 && k <= 1){
    k = 0;
  }

  r += k;

  // int take;
  // take = min(g, k);
  // k -= take;
  // g -= take;
  // r += take;
  // b += take;
  //
  // take = min(b, k);
  // k -= take;
  // b -= take;
  // g += take;
  // r += take;


  // take = min(r, k / 3);
  // k -= take;
  // r -= take;
  // g += take;
  // b += take;
  //
  // take = min(g, k);
  // k -= take;
  // g -= take;
  // r += take;
  // b += take;
  //
  // take = min(b, k);
  // k -= take;
  // b -= take;
  // g += take;
  // r += take;

  cout << r << endl;
}
