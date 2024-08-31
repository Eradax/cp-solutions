#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

int main() {
	int n, k;
	cin >> n >> k;
	vi contests(n*3);
	for (int i=0; i<n; i++) {
		cin >> contests[i];
		contests[n+i] = contests[i];
		contests[2*n+i] = contests[i];
	}

	vi seen(k, 0);
	int l = 0, r = 0;
	int best = INT_MAX;
	while (r < 3*n) {
		if (all_of(seen.begin(), seen.end(), [](int i) {return i==0 ? false : true;})) {
			if (contests[l] == 1) {
				best = min(best, r-l);
			}
			seen[contests[l]]--;
			l++;
			seen[contests[l]]++;
		} else {
			seen[contests[r]]++;
			r++;
		}
	}
	cout << best << endl;
}