#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  vector<ll> vals;
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    ll v;
    cin >> v;
    vals.push_back(v);
  }

  sort(vals.rbegin(), vals.rend());

  ll ans = 0;
  for (int i = 0; i < n; i += 2) {
    ans += vals[i];
  }

  cout << ans << endl;
}
