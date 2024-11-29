#include <bits/stdc++.h>

#ifdef DBG
    #include "../../../../dbg.h"
#else
    #define dbg(...)
#endif

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define sz(c) ((int)c.size())

vector<pair<int, int>> w;
vector<int> ans;

vector<int> solve(int h, vector<pair<int, int>> v) {
    if (h == 0) {
        return {v[0].second};
    }

    vector<int> ans(sz(v));
    vector<pair<int, int>> q1; q1.reserve(sz(v) / 2);
    vector<pair<int, int>> q2; q2.reserve(sz(v) / 2);

    unordered_map<int, int> cnt;
    unordered_map<int, int> cntu;

    for (auto& u : v) u.first = min(u.first, h-1);
    for (auto& u : v) cnt[u.first]++;
    for (auto& u : cnt) cntu[u.first] = 0;

    sort(v.begin(), v.end());
    for (auto& u : v) {
        if (cntu[u.first] < cnt[u.first] / 2) {
            q1.push_back(u);
            cntu[u.first]++;
        } else {
            q2.push_back(u);
        }
    }

    vector<int> a1 = solve(h-1, q1);
    rep(i, sz(v) / 2) {
        ans[i] = a1[i];
    }


    vector<int> a2 = solve(h-1, q2);
    rep(i, sz(v) / 2) {
        ans[i + sz(v)/2] = a2[i];
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    w.resize(n);
    ans.resize(n, -1);

    rep(i, n) {
        cin >> w[i].first;
        w[i].second = i;
    }

    // validate
    sort(w.rbegin(), w.rend());
    int h = (int)log2(n);
    rep(i, n) {
        int eh = h - (int)ceil(log2(i+1));
        
        dbg("-----", h, eh, n, i);

        if (w[i].first != eh) {
            cout << -1 << endl;
            return 0;
        }
    }


    ans = solve((int)log2(n), w);

    rep(i, n) {
        cout << ans[i]+1 << " ";
    }
    cout << endl;
}
