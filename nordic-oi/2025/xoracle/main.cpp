#include <bits/stdc++.h>

using namespace std;


#define repp(i, s, n) for (int i = s; i < n; i++)
#define rep(i, n) repp(i, 0, n)

using ll = long long;
#define int ll

using vi = vector<int>;

signed main() {
    int n, q;
    cin >> n >> q;

    assert(q >= n-1);

    auto ask = [&](int u) {
        cout << "? " << 1 << " " << u + 1 << endl;
        int tmp;
        cin >> tmp;
        return tmp;
    };

    vi xors(n);
    repp(i, 1, n) {
        xors[i] = ask(i);
    }

    int xor_sum = 0;
    rep(i, n) xor_sum += xors[i];

    int l = ceil(log2(n)) + 1;
    vi cnt(l);

    rep(j, l) {
        rep(i, n) {
            cnt[j] += (xors[i] >> j) & 1;
        }
    }

    vi seen(1 << l);
    rep(i, n) seen[xors[i]] = 1;

    int xor0 = -1;
    int cnts = 0;

    rep(i, n) {
        if (seen[i]) continue;

        int sum = 0;
        rep(j, l) {
            sum += (i & (1 << j)) * cnt[j];
        }

        if (xor_sum - 2 * sum == 2 * n - 2 - i * n) {
            xor0 = i;
            cnts++;
        }
    }

    assert(xor0 >= 0);
    assert(seen[xor0] == 0);

    // if (cnts != 1) {
    //     cout << "cnts; " << cnts << endl;
    //     exit(0);
    // }

    rep(i, n) {
        xors[i] ^= xor0;

        assert(xors[i] >= 1);
    }

    cout << "! ";
    rep(i, n) {
        cout << xors[i];
        if (i != n-1) cout << " ";
    }
    cout << endl;
}
