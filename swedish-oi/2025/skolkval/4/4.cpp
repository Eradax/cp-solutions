#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int s = 0, l = 0;
    while (n > 0) {
        s += n % 10;
        n /= 10;
        l++;
    }

    int mi = 0, ma = 0, sc;

    sc = s;
    int e = 1;
    rep(i, l-1) {
        mi += min(sc - 1, 9) * e;
        sc -= min(sc - 1, 9);
        e *= 10;
    } mi += min(sc, 9) * e;

    sc = s;
    rep(i, l) {
        ma *= 10;
        ma += min(sc, 9);
        sc -= min(sc, 9);
    }

    cout << mi << " " << ma << endl;
}

