#include <bits/stdc++.h>

using namespace std;

#define sz(c) ((int)c.size())

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string f, h;
    cin >> f >> h;

    int i=0, j=0;

    while (i < sz(f) && j < sz(h)) {
        i += f[i] == h[j];
        j++;
    }
    cout << (i == sz(f) ? "Ja" : "Nej") << endl;
}

