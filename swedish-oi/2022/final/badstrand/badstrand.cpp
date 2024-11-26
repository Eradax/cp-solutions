#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i<(n); i++)

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, b;
    cin >> n >> b;

    vector<int> a(n);
    rep(i, n) cin >> a[i];

    int l, r, s;
    l = 0;
    r = 1;
    s = 0;

    int ans = 0;
    s += a[0];
    while (r <= n) {
        if (s <= b) {
            ans = max(ans, r-l);
            
            s += a[r];
            r += 1;
        } else {
            s -= a[l];
            l += 1;
        }
    }

    cout << ans << endl;
}
