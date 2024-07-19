#include <bits/stdc++.h>
using namespace std;

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

bitset<4000*1000> dp;

int main() {
    fast();

    dp[0] = 1;

    short n;
    cin >> n;

    short block;

    for (short i=0; i<n; i++) {
        cin >> block;
        dp |= dp << block;
    }

    cout << dp.count();

    return 0;
}
