#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;

const ull MOD = 1e10;
ull mmul(ull a, ull b) {
	ll ret = a * b - MOD * ull(1.L / MOD * a * b);
	return ret + MOD * (ret < 0) - MOD * (ret >= (ll)MOD);
}
ull mpow(ull b, ull e) {
	ull ans = 1;
	for (; e; b = mmul(b, b), e /= 2)
		if (e & 1) ans = mmul(ans, b);
	return ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  ll a = 0;
  for (int i = 1; i < n + 1; i++)
    a = (a + mpow(i, i)) % MOD;

  cout << a << endl;
}
