#include <bits/stdc++.h>

using namespace std;

#define gc() getchar()

int main() {
	int n;
	cin >> n;
	int ans=0, coffee=0;
	gc();
	for (int i=0; i<n; i++) {
		if (gc() == '1') {
			coffee=2;
			ans++;
		} else {
			if (coffee > 0) {
				ans++;
				coffee--;
			}
		}
	}
	cout << ans;
}