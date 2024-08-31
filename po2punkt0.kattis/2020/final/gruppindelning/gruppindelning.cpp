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

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }


#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define setcontains(set, x) (set.find(x) != set.end())
#define sz(container) ((int)container.size())
vector<p2> dirs = { {0,1},{0,-1},{1,0},{-1,0} };

// time and rng
auto Start = chrono::high_resolution_clock::now();
void resettimer() { Start = chrono::high_resolution_clock::now(); }
int elapsedmillis() { return chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count(); }
random_device rd;
mt19937 rng(rd());
template<typename T, typename U> inline int randint(T lo, U hi) { return uniform_int_distribution<int>((int)lo, (int)hi)(rng); } // [lo,hi]
template<typename T> inline T randel(vector<T>& v) { return v[uniform_int_distribution<int>(int(0), int(v.size()) - int(1))(rng)]; } // [lo,hi]


signed main() {
    fast();

    int n, m;
    cin >> n >> m;
    
    int groups = (n+1)/2;

    vector<vector<p2>> graph(groups);
    rep(i, m) {
        int u, v;
        cin >> u >> v;

        bool pairtyeq = u%2 == v%2;

        u = (u-1) / 2;
        v = (v-1) / 2;

        graph[u].emplace_back(v, pairtyeq);
        graph[v].emplace_back(u, pairtyeq);
    }

    vector<int> pattern(groups, -1);
    /*
    * -1: not determined
    *  0: 12
    *  1: 21
    */ 


    rep(i, groups) {
        dbg(i, pattern);
        if (pattern[i] != -1) { continue; }

        // BFS update
        pattern[i] = 0;
        queue<int> st;
        st.push(i);
        while (!st.empty()) {
            int u = st.front();
            st.pop();

            repe(v, graph[u]) {
                dbg(i,u,v,pattern);
                int pat = v.second ? pattern[u] : 1 - pattern[u];
                if (pattern[v.first] == -1) {
                    pattern[v.first] = pat;
                    st.push(v.first);
                } else if (pattern[v.first] != pat) { cout << -1; exit(0); }

            }
        }
    }

    rep(i, groups - 1) {
        cout << (pattern[i] ? "21" : "12");
    }

    if (n % 2) cout << (pattern[groups-1] ? "2" : "1");
    else cout << (pattern[groups-1] ? "21" : "12");;

    return 0;
}

