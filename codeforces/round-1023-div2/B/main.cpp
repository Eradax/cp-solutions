#include <bits/stdc++.h>
using namespace std;

#define sz(c) ((int)c.size())

using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int t;
  cin >> t;
  
  while (t--) {
    int n, k;
    cin >> n >> k;

    int m = 0;
    int ma = -1;
    int mac = 0;
    int mi = 2e9;
    int mic = 0;

    for (int i = 0; i < n; i++) {
      int v;
      cin >> v;

      if(v > ma) {
        ma = v;
        mac = 1;
      } else if (v == ma) {
        mac++;
      }

      if(v < mi) {
        mi = v;
        mic = 1;
      } else if (v == mi) {
        mic++;
      }

      m += v % 2;
    }

    if (ma - mi - (mac == 1) > k) {
      cout << "Jerry" << '\n';
      continue;
    }

    if (m % 2 > 0) {
      cout << "Tom" << '\n';
      continue;
    }

    cout << "Jerry" << '\n';
  }
}
