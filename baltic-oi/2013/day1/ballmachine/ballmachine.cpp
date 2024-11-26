#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

// dbg
#ifdef LOCAL
    #include "dbg.h"
#else
    #define dbg(...)
#endif

// typedefs
using ll = long long;
#define int ll
const int inf = int(1e18);

using vi = vector<int>;
using vvi = vector<vi>;
using p2 = pair<int, int>;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (int i = high-1; i >= 0; i--)
#define perr(i, high, low) for (int i = high-1; i >= low; i--)

#define clz(x) __builtin_clz(x)
#define popcount(x) __builtin_popcountll(x)

inline void fast() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
}


#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define setcontains(set, x) (set.find(x) != set.end())
#define sz(container) ((int)container.size())
vector<p2> dirs = { {0,1},{0,-1},{1,0},{-1,0} };

// time and rng
auto Start = chrono::high_resolution_clock::now();
void resettimer() {
    Start = chrono::high_resolution_clock::now();
}
int elapsedmillis() {
    return chrono::duration_cast<chrono::milliseconds>(
        chrono::high_resolution_clock::now() - Start
    ).count();
}


random_device rd;
mt19937 rng(rd());
template<typename T, typename U>
inline int randint(T lo, U hi) {
    return uniform_int_distribution<int>((int)lo, (int)hi)(rng);
} // [lo,hi]

template<typename T> 
inline T randel(vector<T>& v) {
    return v[uniform_int_distribution<int>(
        int(0), int(v.size()) - int(1)
    )(rng)];
} // [lo,hi]

const int N = 100000;
 
int n, q, root;

int cntRank;
int rnk[N + 10], subMin[N + 10], revRank[N + 10];

int par[N + 10], h[N + 10], sz[N + 10];
int tim, st[N + 10], head[N + 10], revSt[N + 10];

vector<int> adj[N + 10];
vector<pair<int, int>> adj2[N + 10];
 
void calcRank(int u = root) {
    for (auto [x, v]: adj2[u])
        calcRank(v);
    rnk[u] = ++cntRank;
    revRank[cntRank] = u;
}
 
void hld(int u = root, int hed = 0) {
    head[u] = (hed? hed: u);
    st[u] = ++tim;
    revSt[tim] = u;
    int bigChild = 0;
    for (auto v: adj[u])
        if (sz[v] > sz[bigChild])
            bigChild = v;
    if (bigChild)
        hld(bigChild, head[u]);
    for (auto v: adj[u])
        if (v != bigChild)
            hld(v, 0);
}
 
int mn[2][4 * N + 10];
 
int get(int st, int en, int t, int id = 1, int l = 1, int r = n + 1) {
    if (en <= l || r <= st || mn[t][id])
        return 0;
    if (l + 1 == r)
        return l;
    int mid = (l + r) >> 1;
    int case1 = get(st, en, t, id << 1, l, mid);
    if (case1)
        return case1;
    return get(st, en, t, id << 1 | 1, mid, r);
}
 
void update(int idx, int val, int t, int id = 1, int l = 1, int r = n + 1) {
    if (idx < l || r <= idx)
        return;
    if (l + 1 == r) {
        mn[t][id] = val;
        return;
    }
    int mid = (l + r) >> 1;
    update(idx, val, t, id << 1, l, mid);
    update(idx, val, t, id << 1 | 1, mid, r);
    mn[t][id] = min(mn[t][id << 1], mn[t][id << 1 | 1]);
}
 
void build() {
    fill(mn[1] + 1, mn[1] + 4 * n + 10, 1);
}
 
int lastHave(int u) {
    int res = 0;
    while (u) {
        int tmp = get(st[head[u]], st[u] + 1, 1);
        if (tmp)
            res = tmp;
        u = par[head[u]];
    }
    return revSt[res];
}
 
void queryDel() {
    int u;
    cin >> u;
    int p = lastHave(u);
    cout << h[u] - h[p] << '\n';
    update(st[p], 1, 1);
    update(rnk[p], 0, 0);
}
 
void queryAdd() {
    int k;
    cin >> k;
    int ans;
    while (k--) {
        int u = revRank[get(1, n + 1, 0)];
        update(st[u], 0, 1);
        update(rnk[u], 1, 0);
        ans = u;
    }
    cout << ans << '\n';
}
 
void solve() {
    while (q--) {
        int type;
        cin >> type;
        if (type == 1)
            queryAdd();
        else
            queryDel();
    }
    cout.flush();
}
 
signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> par[i];
        if (par[i])
            adj[par[i]].push_back(i);
        else
            root = i;
    }

    int u = root;
    h[u] = h[par[u]] + 1;
    sz[u] = 1;
    subMin[u] = u;
    for (auto v: adj[u]) {
        init(v);
        sz[u] += sz[v];
        subMin[u] = min(subMin[u], subMin[v]);
        adj2[u].push_back({subMin[v], v});
    }

    sort(adj2[u].begin(), adj2[u].end());
    
    calcRank();
    hld();
    build();


    while (q--) {
        int type;
        cin >> type;
        if (type == 1)
            queryAdd();
        else
            queryDel();
    }
    return 0;
}

