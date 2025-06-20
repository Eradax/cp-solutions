#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;

    while (t--) {
        int n, k;
        cin >> n >> k;

        vector<int> l(n), r(n);
        for (int i = 0; i < n; i++) {
            cin >> l[i];
        }
        
        for (int i = 0; i < n; i++) {
            cin >> r[i];
        }


        vector<int> A(n), B(n);
        for (int i = 0; i < n; i++) {
            A[i] = max(l[i], r[i]);
            B[i] = min(l[i], r[i]);
        }


        long long ans = 0;
        sort(B.rbegin(), B.rend());
        for (int i = 0; i < n; i++) {
            ans += A[i];
        }

        for (int i = 0; i < k-1; i++) {
            ans += B[i];
        }
        ans += 1;
        cout << ans << '\n';
    }
}
