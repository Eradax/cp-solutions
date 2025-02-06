#include <bits/stdc++.h>
#include <iomanip>

using namespace std;

using vi = vector<int>;

#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  unordered_map<char, int> cnt;

  rep(i, n) {
    string a;
    cin >> a;

    cnt[a[0]]++;
  }

  int m = 1e9;
  for (auto [a, b] : cnt) {
    m = min(m, b);
  }

  if (cnt.size() < 13) {
    m = 0;
  }

  // cout << cnt.size() << endl;
  // cout << m << endl;
  // cout << 52 - n << endl;

  long double ans;
  ans = 4 - m;
  ans /= 52 - n;

  cout << setprecision(15) << ans << endl;
}
