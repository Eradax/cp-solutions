#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string g;
    cin >> g;

    int t = 0, h = 0;

    for (auto i : g) {
        t += i == 'T';
        h += i == 'H';

        if (abs(t - h) >= 2 && max(t, h) >= 11) {
            t = h = 0;
        }
    }

    cout << t << "-" << h << endl;
}

