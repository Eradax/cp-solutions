#include <bits/stdc++.h>
using namespace std;
using vi = vector<int>;
using pii = pair<int, int>;
#define rep(i, l, h) for (int i = l; i < h; i++)
const int LIM = 1e7;
bitset<LIM> isPrime;
vi eratosthenes() {
	const int S = (int)round(sqrt(LIM)), R = LIM / 2;
	vi pr = {2}, sieve(S+1); pr.reserve(int(LIM/log(LIM)*1.1));
	vector<pii> cp;
	for (int i = 3; i <= S; i += 2) if (!sieve[i]) {
		cp.push_back({i, i * i / 2});
		for (int j = i * i; j <= S; j += 2 * i) sieve[j] = 1;
	}
	for (int L = 1; L <= R; L += S) {
		array<bool, S> block{};
		for (auto &[p, idx] : cp)
			for (int i=idx; i < S+L; idx = (i+=p)) block[i-L] = 1;
		rep(i,0,min(S, R - L))
			if (!block[i]) pr.push_back((L + i) * 2 + 1);
	}
	for (int i : pr) isPrime[i] = 1;
	return pr;
}

int main() {
	auto i = eratosthenes();

	int n;
	cin >> n;

	int j = 0;
	long long sum = 0;
	while (j < i.size() && i[j] < n) sum += i[j++];

	cout << sum;
}
