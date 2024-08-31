#include <bits/stdc++.h>
using namespace std;

// dbg
#ifdef LOCAL
    #include "../dbg.h"
#else
    #define dbg(...)
#endif

// typedefs
using ll = long long;
#define LONG_LONGS
#ifdef LONG_LONGS
    #define int ll
    const int inf = (int)1e18;
#else
    const int inf = int(1e9);
#endif    

using vi = vector<int>;
using vvi = vector<vi>;

using p2 = pair<int, int>;
using vp2 = vector<p2>;
using vvp2 = vector<vp2>;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (int i = high-1; i >= 0; i--)
#define perr(i, high, low) for (int i = high-1; i >= low; i--)

// Builtins
#define clz(x) __builtin_clz(x)
#define popcount(x) __builtin_popcountll(x)

// Fast I/O
inline void fast() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
}
void readinput() {} // Recursion base case
template<typename T, typename... Args>
void readinput(T& arg, Args&... args) { read(arg); readinput(args...);}
#define dread(type, ...) \
    type __VA_ARGS__;\
    readinput(__VA_ARGS__);
template<typename T>
istream& operator>>(istream& is, vector<T>& v) {
    repe(u, v) read(u);
    return is;
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

const int N = 5050;
int dp[N][N];
int nxt_ne[N];
int nxt[N][20];
int num_es[N];
vi e_pos;
int es = 0;

int dpf(int a, int b) {
    if (b == es) return 0;

    int &ans = dp[a][b];
    if (ans != -1) return dp[a][b];

    ans = inf;
    if (a >= e_pos[b]) {
        ans = a - e_pos[b];
        ans += dpf(nxt_ne[e_pos[b]], num_es[a]);
    }

    rep(i, 10) {
        if (i + 'a' == 'e') continue;
        int n = nxt[a][i];
        if (n == -1) continue;
        ans = min(ans, 2 + dpf(n, b));
    }
    return ans;
}


signed main() {
    fast();

    memset(dp, -1, sizeof(dp));
    memset(nxt, -1, sizeof(nxt));
    memset(num_es, 0, sizeof(num_es));

    int n;
    string line;
    cin >> n >> line;

    int prev[20];
    int preve = 0;

    rep(i, sz(line)) {
        int chr = line[i] - 'a';
        repp(j, prev[chr], i) nxt[j][chr] = i;
        prev[chr] = i;

        if (chr + 'a' == 'e') {
            e_pos.push_back(i);
            es++;
        } else {
            repp(j, preve, i) nxt_ne[j] = i;
            preve = i;
        }
        num_es[i] = es;
        num_es[i+1] = es;
    }

    // dbg(num_es, es);
    dbg(nxt, nxt_ne);

    cout << dpf(0, 0) + es; 

    return 0;
}
