#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
    int l, r, d, u;
    cin >> l >> r >> d >> u;
    cout << ((l == r && d == u && l == d) ? "Yes" : "No") << endl;
    }
}
