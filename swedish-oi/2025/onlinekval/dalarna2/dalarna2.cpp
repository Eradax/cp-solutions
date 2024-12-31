#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define int ll

#define rep(i, n) for (int i = 0; i < (n); i++)

int n;
vector<int> p;
vector<vector<int>> adj;

int dfs(int u, int last) {

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    p.resize(n);
    adj.resize(n);

    rep(i, n) {
        cin >> p[i];
    }

    
    rep(i, n) {
        int u, v;
        cin >> u >> v;

        u--;
        v--;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int ans = 1e18;
    rep(i, n) {
        int ans = dfs(i, -1);
    }

    cout << ans << endl;
}
