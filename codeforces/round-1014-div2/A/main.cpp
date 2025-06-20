#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (auto& i : a) cin >> i;
        
        auto [mi, ma] = minmax_element(a.begin(), a.end());
        cout << *ma - *mi << '\n';
    }
}
