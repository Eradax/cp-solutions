#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        int s = 0;
        int m = 0;

        vector<int> a(n), b;

        for (int i = 1; i < n; i++) {
            char c;
            cin >> c;
            if (c == '<') {
                a[i] = s-1;
                s--;
            } else {
                a[i]=m+1;
                m++;
            }
        }

        b = a;
        sort(b.begin(), b.end());
        map<int, int> ma;
        for (int i = 0; i < n; i++) {
            ma[b[i]] = i;
        }

        for (int i = 0; i < n; i++) {
            cout << 1+ma[a[i]] << " ";
        }cout << '\n';
    }
}
