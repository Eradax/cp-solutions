#include <bits/stdc++.h>
#include "sort.hpp"

using namespace std;

int tc;
int n, a, b, c, x, y;

int main() {
	cin >> tc;
	for (int i=0; i<tc; i++) {
		cin >> n;
		cin >> a >> b >> c;
		cin >> x >> y;

		a%=c;b%=c;
		x%=y;

		vector<int> s(n);
		s[0] = a;
		int curr = a;
		for (int j=1; j<n; j++) {
			curr = ((curr*b % c)+a)%c;
			s[j] = curr;
		}

        ska::ssort(s.begin(), s.end());

		int ans = 0;
		for (int j=0; j<n; j++) {
			ans = ((ans*x % y) + s[j]) % y;
		}

		cout << ans << "\n";
	}
	return 0;
}
