#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (int i = high - 1; i >= 0; i--)

string solve(string alien, string source, string target) {
  int n = source.length();
  int m = target.length();
  int l = alien.length();

  ll base10 = 0;
  rep(i, l) {
    base10 += source.find(alien[i]) * pow(n, l - 1 - i);
  }
  vector<int> baseM;
  while (base10) {
    baseM.push_back(base10 % m);
    base10 /= m;
  }

  string ans;
  repe(ch, baseM) {
    ans.push_back(target[ch]);
  }
  reverse(ans.begin(), ans.end());
  return ans;
}

int main() {
  int tc;
  cin >> tc;

  repp(i, 1, tc + 1) {
    string alien, source, target;
    cin >> alien >> source >> target;
    cout << "Case #" << i << ": " << solve(alien, source, target) << endl;
  }
}