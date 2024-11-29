#include <bits/stdc++.h>

using ll = long long;
#define int ll

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); i++)

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int s, p, a, b;
    cin >> s >> p >> a >> b;

    
    int ans = 1e9;

    rep(x, 2e5) {
        int y = p - 2*s - 2*x - 10;
        while (2*(s+x+y) <= p+y) y++;
        if (y < 0) y = 0;

        int cost = a*x + b*y;
        ans = min(ans, cost);
    }

    cout << ans << endl;
}
