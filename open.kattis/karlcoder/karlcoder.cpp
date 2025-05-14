#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    auto ask = [](ll i) {
        cout << "buf[" << i << "]" << endl;
        int ans;
        cin >> ans;
        return ans;
    };

    auto ans = [](ll i) {
        cout << "strlen(buf) = " << i << endl;
    };

    ll h = 1;
    while (ask(h) != 0) h*=2;

    ll l = h/2;

    // Both of these work
    // while (l < h) {
    //     ll m = l + (h - l) / 2;
    //     if (ask(m) == 0) {
    //         h = m;
    //     } else {
    //         l = m+1;
    //     }
    // }

    while (l+1 < h) {
        ll m = l + (h - l + 1) / 2;
        if (ask(m) == 0) {
            h = m;
        } else {
            l = m;
        }
    }

    ans(h);
}
