#include <bits/stdc++.h>

#ifdef DBG
#include "../../persist/cp/cp-solutions/dbg.h"
#else
#define dbg(...)
#endif

using namespace std;

#define sz(c) ((int)c.size())
#define all(c) c.begin(), c.end()
#define rep(i, l, h) for (int i = l; i < h; i++)

using vi = vector<int>;

typedef complex<double> C;
typedef vector<double> vd;
void fft(vector<C>& a) {
	int n = sz(a), L = 31 - __builtin_clz(n);
	static vector<complex<long double>> R(2, 1);
	static vector<C> rt(2, 1);  // (^ 10% faster if double)
	for (static int k = 2; k < n; k *= 2) {
		R.resize(n); rt.resize(n);
		auto x = polar(1.0L, acos(-1.0L) / k);
		rep(i,k,2*k) rt[i] = R[i] = i&1 ? R[i/2] * x : R[i/2];
	}
	vi rev(n);
	rep(i,0,n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
	rep(i,0,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += 2 * k) rep(j,0,k) {
			// C z = rt[j+k] * a[i+j+k]; // (25% faster if hand-rolled)  /// include-line
			auto x = (double *)&rt[j+k], y = (double *)&a[i+j+k];        /// exclude-line
			C z(x[0]*y[0] - x[1]*y[1], x[0]*y[1] + x[1]*y[0]);           /// exclude-line
			a[i + j + k] = a[i + j] - z;
			a[i + j] += z;
		}
}
vd conv(const vd& a, const vd& b) {
	if (a.empty() || b.empty()) return {};
	vd res(sz(a) + sz(b) - 1);
	int L = 32 - __builtin_clz(sz(res)), n = 1 << L;
	vector<C> in(n), out(n);
	copy(all(a), begin(in));
	rep(i,0,sz(b)) in[i].imag(b[i]);
	fft(in);
	for (C& x : in) x *= x;
	rep(i,0,n) out[i] = in[-i & (n - 1)] - conj(in[i]);
	fft(out);
	rep(i,0,sz(res)) res[i] = imag(out[i]) / (4 * n);
	return res;
}

using ll = long long;
#define int ll

const int ADD = 50'000;

signed main() {
	cin.tie(0)->sync_with_stdio(0);

	int n;
	cin >> n;

	vd a(100'001);
	vi a2(100'001);

	int zc = 0;

	for (int i = 0; i < n; i++) {
		int v;
		cin >> v;
	
		if (v == 0)
			zc++;

		a[v + ADD]++;
		a2[v + ADD]++;
	}

	vd b = conv(a, a);
	vi c(sz(b));
	for (int i = 0; i < sz(b); i++)
		c[i] = round(b[i]);

	dbg(a2, c);

	ll ans = 0;
	rep(i, 0, sz(a))
		c[2 * i] -= a2[i];
	
	ans -= zc * (n - 1) * 2;

	dbg(a2, c);

	rep(i, 0, sz(a))
		ans += a2[i] * c[i + ADD];

	cout << ans << endl;
}
