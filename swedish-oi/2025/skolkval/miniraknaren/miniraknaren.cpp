#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, t = 0;
    cin >> n >> m;

    while (n > 0) {
        if (n < 2 * m) {
            n -= m - 1;
        } else {
            t+=n%m > 0;
            n/=m;
        }
        t++;
    }

    cout << t << endl;
}

