#pragma GCC optimize("O3")
#include <bits/stdc++.h>
#ifdef DBG
	#include "../../dbg.h"
#else
	#define dbg(...)
#endif

using namespace std;

struct UInt256 {
	using u64 = uint64_t;
	using u128 = __uint128_t;
	array<u64, 4> num;

	UInt256(u64 v = 0) { num[3] = num[2] = num[1] = 0; num[0] = v; }

	bool operator<(const UInt256& o) const {
		for (int i = 3; i >= 0; i--)
			if (num[i] != o.num[i])
				return num[i] < o.num[i];
		return 0;
	}

	bool operator>(const UInt256& o) const {
		for (int i = 3; i >= 0; i--)
			if (num[i] != o.num[i])
				return num[i] > o.num[i];
		return 0;
	}

	bool operator<=(const UInt256& o) const {
		for (int i = 3; i >= 0; i--)
			if (num[i] != o.num[i])
				return num[i] <= o.num[i];
		return 1;
	}

	bool operator>=(const UInt256& o) const {
		for (int i = 3; i >= 0; i--)
			if (num[i] != o.num[i])
				return num[i] >= o.num[i];
		return 1;
	}

	bool operator==(const UInt256& o) const {
		return num == o.num;
	}

	bool operator!=(const UInt256& o) const {
		return num != o.num;
	}

	UInt256 operator&(const UInt256& o) const {
		UInt256 res;
		for (int i = 0; i < 4; i++)
			res.num[i] = num[i] & o.num[i];
		return res;
	}

	UInt256 operator&=(const UInt256& o) {
		for (int i = 0; i < 4; i++)
			num[i] &= o.num[i];
		return *this;
	}

	UInt256 operator|(const UInt256& o) const {
		UInt256 res;
		for (int i = 0; i < 4; i++)
			res.num[i] = num[i] | o.num[i];
		return res;
	}

	UInt256 operator|=(const UInt256& o) {
		for (int i = 0; i < 4; i++)
			num[i] |= o.num[i];
		return *this;
	}

	UInt256 operator<<(int s) const {
		UInt256 res = *this;
		while (s) {
			int s2 = min(s, 64);
			s -= s2;

			if (s2 == 64) {
				for (int i = 3; i > 0 ; i--)
					res.num[i] = res.num[i - 1];
				res.num[0] = 0;
				continue;
			}

			u64 c = 0;
			for (int i = 0; i < 4; i++) {
				u64 c2 = res.num[i] >> (64 - s2);
				res.num[i] = (res.num[i] << s2) | c;
				c = c2;
			}
		}

		return res;
	}

	UInt256 operator<<=(int s) {
		while (s) {
			int s2 = min(s, 64);
			s -= s2;

			if (s2 == 64) {
				for (int i = 3; i > 0 ; i--)
					num[i] = num[i - 1];
				num[0] = 0;
				continue;
			}

			u64 c = 0;
			for (int i = 0; i < 4; i++) {
				u64 c2 = num[i] >> (64 - s2);
				num[i] = (num[i] << s2) | c;
				c = c2;
			}
		}

		return *this;
	}


	UInt256 operator>>(int s) const {
		UInt256 res = *this;
		while (s) {
			int s2 = min(s, 64);
			s -= s2;

			if (s2 == 64) {
				for (int i = 0; i < 3 ; i++)
					res.num[i] = res.num[i + 1];
				res.num[3] = 0;
				continue;
			}

			u64 c = 0;
			for (int i = 3; i >= 0; i--) {
				u64 c2 = res.num[i] & ((1ull << s2) - 1);
				res.num[i] = (res.num[i] >> s2) | (c << (64 - s2));
				c = c2;
			}
		}

		return res;
	}

	UInt256 operator>>=(int s) {
		while (s) {
			int s2 = min(s, 64);
			s -= s2;

			if (s2 == 64) {
				for (int i = 0; i < 3 ; i++)
					num[i] = num[i + 1];
				num[3] = 0;
				continue;
			}

			u64 c = 0;
			for (int i = 3; i >= 0; i--) {
				u64 c2 = num[i] & ((1ull << s2) - 1);
				num[i] = (num[i] >> s2) | (c << (64 - s2));
				c = c2;
			}
		}

		return *this;
	}

	UInt256 operator+(const UInt256& o) const {
		UInt256 res;
		u64 c = 0;
		for (int i = 0; i < 4; i++) {
			u128 sum = (u128)num[i] + o.num[i] + c;
			res.num[i] = (u64)sum;
			c = (u64)(sum >> 64);
		}

		return res;
	}

	UInt256 operator+=(const UInt256& o) {
		u64 c = 0;
		for (int i = 0; i < 4; i++) {
			u128 sum = (u128)num[i] + o.num[i] + c;
			num[i] = (u64)sum;
			c = (u64)(sum >> 64);
		}

		return *this;
	}

	UInt256 operator++(int) {
		return *this += 1;
	}

	UInt256 operator-(const UInt256& o) const {
		UInt256 res;
		u64 b = 0;
		for (int i = 0; i < 4; i++) {
			u128 diff = (u128)num[i] - o.num[i] - b;
			res.num[i] = (u64)diff;
			b = (u64)(diff >> 64) & 1;
		}

		return res;
	}

	UInt256 operator-=(const UInt256& o) {
		u64 b = 0;
		for (int i = 0; i < 4; i++) {
			u128 diff = (u128)num[i] - o.num[i] - b;
			num[i] = (u64)diff;
			b = (u64)(diff >> 64) & 1;
		}

		return *this;
	}

	UInt256 operator--(int) {
		return *this -= 1;
	}

	UInt256 operator%(const UInt256& m) const {
		if (m == UInt256(0))
			return 0;

		if (*this < m)
				return *this;

		UInt256 div = *this;
		UInt256 rem = 0;
		UInt256 qot = 0;

		int s = 255;
		while (s >= 0 && !(div.num[s / 64] & (1ull << (s % 64)))) {
			s--;
		}

		for (int i = s; i >= 0; i--) {
			rem = (rem << 1) | ((div >> i) & UInt256(1));
			qot = qot << 1;

			if (!(rem < m)) {
				rem = rem - m;
				qot = qot | UInt256(1);
			}
		}

		return rem;
	}

	UInt256 operator%=(const UInt256& m) {
		if (m == UInt256(0))
			return 0;

		if (*this < m)
				return *this;

		UInt256 div = *this;
		UInt256 rem = 0;
		UInt256 qot = 0;

		int s = 255;
		while (s >= 0 && !(div.num[s / 64] & (1ull << (s % 64)))) {
			s--;
		}

		for (int i = s; i >= 0; i--) {
			rem = (rem << 1) | ((div >> i) & UInt256(1));
			qot = qot << 1;

			if (!(rem < m)) {
				rem = rem - m;
				qot = qot | UInt256(1);
			}
		}

		num = rem.num;
		return *this;
	}


	UInt256 operator/(const UInt256& m) const {
		if (m == UInt256(0))
			return 0;

		if (*this < m)
				return *this;

		UInt256 div = *this;
		UInt256 rem = 0;
		UInt256 qot = 0;

		int s = 255;
		while (s >= 0 && !(div.num[s / 64] & (1ull << (s % 64)))) {
			s--;
		}

		for (int i = s; i >= 0; i--) {
			rem = (rem << 1) | ((div >> i) & UInt256(1));
			qot = qot << 1;

			if (!(rem < m)) {
				rem = rem - m;
				qot = qot | UInt256(1);
			}
		}

		return qot;
	}

	UInt256 operator/=(const UInt256& m) {
		if (m == UInt256(0))
			return 0;

		if (*this < m)
				return *this;

		UInt256 div = *this;
		UInt256 rem = 0;
		UInt256 qot = 0;

		int s = 255;
		while (s >= 0 && !(div.num[s / 64] & (1ull << (s % 64)))) {
			s--;
		}

		for (int i = s; i >= 0; i--) {
			rem = (rem << 1) | ((div >> i) & UInt256(1));
			qot = qot << 1;

			if (!(rem < m)) {
				rem = rem - m;
				qot = qot | UInt256(1);
			}
		}

		num = qot.num;
		return *this;
	}

	UInt256 operator*(const UInt256& o) const {
		UInt256 res;
		for (int i = 0; i < 4; i++) {
			u64 a = num[i];
			u64 c = 0;

			for (int j = 0; j + i < 4; j++) {
				u128 mul = (u128)a * o.num[j];
				u128 sum = (u128)res.num[i + j] + mul + c;
				res.num[i + j] = (u64)sum;
				c = (u64)(sum >> 64);
			}
		}

		return res;
	}

	UInt256 operator*=(const UInt256& o) {
		UInt256 res;
		for (int i = 0; i < 4; i++) {
			u64 a = num[i];
			u64 c = 0;

			for (int j = 0; j + i < 4; j++) {
				u128 mul = (u128)a * o.num[j];
				u128 sum = (u128)res.num[i + j] + mul + c;
				res.num[i + j] = (u64)sum;
				c = (u64)(sum >> 64);
			}
		}

		*this = res;
		return *this;
	}

	int bit_width() const {
		if (num[3])
			return 64 * 3 + __bit_width(num[3]);

		if (num[2])
			return 64 * 2 + __bit_width(num[2]);

		if (num[1])
			return 64 * 1 + __bit_width(num[1]);

		return __bit_width(num[0]);
	}

	int ctz() const {
		if (num[0])
			return __builtin_ctzll(num[0]);

		if (num[1])
			return 64 * 1 + __builtin_ctzll(num[1]);

		if (num[2])
			return 64 * 2 + __builtin_ctzll(num[2]);

		return 64 * 3 + __builtin_ctzll(num[3]);
	}

	UInt256 getMu() {
		int k = this->bit_width();
		// assert(k <= 127);

		UInt256 mu = 1;
		mu <<= 2 * k;
		mu /= *this;

		// assert(mu.bit_width() <= 127);

		return mu;
	}

	UInt256 reduce(UInt256 mod, UInt256 mu, int k) const {
		// assert(*this <= mod * mod * 2);
		// assert(this->bit_width() <= 127);
		// assert(k <= 127);

		dbg(*this, this->bit_width(), mod, mod.bit_width(), mu, mu.bit_width(), k);

		UInt256 q = (*this * mu) >> (2 * k);
		UInt256 r = *this - q * mod;

		dbg(*this > q * mod);

		dbg(q, r, mod);

		while (r >= mod)
			r -= mod;

		dbg(r, mod);

		return r;
	}

	friend UInt256 gcd(UInt256 a, UInt256 b) {
		if (a == 0)
			return b;
		if (b == 0)
			return a;

		dbg(a, b);

		int az = a.ctz();
		int bz = b.ctz();
		a >>= az;
		b >>= bz;
		int s = min(az, bz);

		dbg(az, bz);

		while (a != 0) {
			dbg(a, b);
			UInt256 d = max(a, b) - min(a, b);
			b = min(a, b);
			a = d;
			dbg(a.ctz());
			a >>= a.ctz();
		}

		return b << s;
	}

	friend ostream& operator<<(ostream& o, UInt256 v) {
		string s;
		while (v >= 10) {
			char c = '0' + (char)(v % 10).num[0];
      s += c;
			v = v / 10;
		}

    char c = '0' + (char)(v % 10).num[0];
		if (c != '0' || s.empty()) s += c;

    reverse(s.begin(), s.end());

		o << s;

		return o;
	}

	friend istream& operator>>(istream& o, UInt256& v) {
		string s;
		o >> s;

    v = 0;
		for (auto i : s) {
			v *= 10;
			v += (i - '0');
		}

		return o;
	}
};

UInt256 modpow(UInt256 b, UInt256 e, UInt256 m) {
	UInt256 res = 1;

	while (e > 0) {
		if ((e & 1) > 0)
			res = (res * b) % m;
		b = (b * b) % m;
		e >>= 1;
	}

	return res;
}

UInt256 modpow(UInt256 b, UInt256 e, UInt256 m, UInt256 mu, int k) {
	UInt256 res = 1;

	while (e > 0) {
		if ((e & 1) > 0)
			res = (res * b).reduce(m, mu, k);
		b = (b * b).reduce(m, mu, k);
		e >>= 1;
	}

	return res;
}

bool isPrime(UInt256 n) { // NOTE: This function isn't critical for performance
	if (n < 2 || n % 6 % 4 != 1)
		return (n | 1) == 3;

	dbg(n);

	UInt256 A[] = {2}; // NOTE: This is not always be enough, but bad testdata so... :D
	int s = (n - 1).ctz();
	UInt256 d = n >> s; 

	for (auto a : A) {
		UInt256 p = modpow(a % n, d, n);
		int i = s;
		while (p != 1 && p != n - 1 && a % n > 0 && i--)
			p = (p * p) % n;
		if (p != n - 1 && i != s)
			return 0;
	}

	return 1;
}

const int acc = 1000;
UInt256 pollard(UInt256 n) {
  UInt256 x = 0;
  UInt256 y = 0;
	UInt256 prd = 2;
	UInt256 q;

	UInt256 mu = n.getMu();
	int k = n.bit_width();

	dbg(n, mu, k);

	int t = 700;

	int b = 1;
	auto g = [&](UInt256 x) { return (x * x + b).reduce(n, mu, k); };
  while (t++ % acc || gcd(prd, n) == 1) {
		dbg(t);

		if (x == y) {
			x = ++b;
			y = g(x);
		}

		dbg(t);

		q = (prd * (max(x, y) - min(x, y))).reduce(n, mu, k);
		if (q > 0)
			prd = q;

		dbg(t);

		x = g(x);
		y = g(g(y));

		dbg(t);
	}

	return gcd(prd, n);
}

vector<UInt256> factor(UInt256 n) {
	if (n == 1) return {};
	if (isPrime(n)) return {n};

	dbg(n);

	UInt256 x = pollard(n);
	auto l = factor(x);
	auto r = factor(n / x);
	l.insert(l.end(), r.begin(), r.end());

	return l;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);

	UInt256 n;
	cin >> n;

	dbg(n);

	auto f = factor(n);
	sort(f.begin(), f.end());

	dbg(f);

	for (auto i : f)
		cout << i << ' ';
	cout << endl;
}
