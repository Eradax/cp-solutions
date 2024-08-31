#include <bits/stdc++.h>
#include <climits>
using namespace std;

// Ints
typedef long long int ll;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<vvll> vvvll;

// Floats
typedef long double ld;
typedef vector<ld> vld;
typedef vector<vld> vvld;
typedef vector<vvld> vvvld;

constexpr ll INF = LLONG_MAX;

istream &operator>>(istream &in,vll &arr) {
	for (ll i=0; i<arr.size(); i++) {
		cin >> arr[i];
	}
    return in;
}

ll n, c;
vll S, C;
vll mins;

ll solve2a1(ll i, ll m) {
	if (i == n) {return 0;}
	if (m < mins[i]) {return 0;}

	ll ans;
	if (m >= C[i]) {
		ans = S[i] + solve2a1(i+1, m-C[i]);
	} else {
		ans = solve2a1(i+1, m);
	}
	return ans;
}

void group2a1() {
	mins.resize(n);
	ll lo = INF;
	for (int i=n-1; i>=0; i--) {
		lo = min(lo, C[i]);
		mins[i] = lo;
	}

	for (ll k=0; k<n; k++) {
		cout << solve2a1(k, c) << " ";
	}
}

void group3() {
	vll prefixS;
	prefixS.push_back(0);
	ll curr = 0;
	for (int i=0; i<n; i++) {
		curr += S[i];
		prefixS.push_back(curr);
	}

	vll prefixC;
	prefixC.push_back(0);
	curr = 0;
	for (int i=0; i<n; i++) {
		curr += C[i];
		prefixC.push_back(curr);
	}


	for (ll k=0; k<n; k++) {
		ll lo=k, hi=n;
		while (lo < hi) {
			ll mi = (lo+hi)/2;

			if (prefixC[mi]-prefixC[k] > c) {
				hi = mi;
			} else {
				lo = mi+1;
			}
		}
		// cout << "lo: " << lo << endl;
		if (prefixC[lo]-prefixC[k] > c) {lo--;}
		cout << prefixS[lo]-prefixS[k] << " ";
	}
}

int main() {
	cin >> n >> c;
	S.resize(n); C.resize(n);
	cin >> S >> C;

	if (n <= 1000 || c<=50) {
		group2a1();
	} else {
		group3();
	}
	cout << endl;
}