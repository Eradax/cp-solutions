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

int asks = 0;
vi betcnt;
int n, q;

void ans(int u) {
    printf("! %lld\n", u+1);
    fflush(stdout);
    exit(0);
}

int ask(int u, int v, int p) {
     if (q - asks < 10) {
        int h1 = max_element(all(betcnt)) - betcnt.begin();
        ans(h1);
    }

    asks++;
    printf("? %lld %lld %lld\n", u+1, v+1, p+1);
    fflush(stdout);

    int ret;
    cin >> ret;
    return ret - 1;
}


bool solve() {
    vi cnt(n);
    vi between;
    
    int u, v;


    u = randint(0LL, n-1);
    v = randint(0LL, n - 1);
    while (u == v) { u = randint(0LL, n-1); v = randint(0LL, n-1); }

    cnt[u]++;
    cnt[v]++;

    rep(i, n) {
        if (i == u || i == v) continue;
        int ret = ask(u, v, i);
        cnt[ret]++;
        if (i == ret) { between.push_back(ret); betcnt[ret]++; }
    }


    set<int> perL, perR;

    perL.insert(u);
    perR.insert(v);


    if (between.empty()) return 0;
    // Find centroid candidate
    while (1) {
        if (between.empty()) return 0;
        int cen = randel(between);

        set<int> left;
        set<int> right;

        repe(i, between) {
            if (i == u || i == cen) continue;
            int ret = ask(u, cen, i);
            if (i == ret) { left.insert(i); }
            else { right.insert(i); }
        }

        int lcnt = 0, rcnt = 0;
        repe(i, left) lcnt += cnt[i];
        repe(i, right) rcnt += cnt[i];
        repe(i, perL) lcnt += cnt[i];
        repe(i, perR) rcnt += cnt[i];

        if (lcnt <= n / 2 && rcnt <= n / 2 && cnt[cen] - 1 <= n/2) ans(cen);

        if (lcnt > n / 2) {
            repe(i, right) { perR.insert(i); }
            between = vi(all(left));
            // u = cen;
            perR.insert(cen);
        } else if (rcnt > n / 2){
            repe(i, left) { perL.insert(i); }
            between = vi(all(right));
            // v = cen;
            perL.insert(cen);
        }
        if (between.size() <= 1) return 0;
    }
}


signed main() {
    cin >> n >> q;

    betcnt.resize(n, 0);
    while (1) solve(); 

    return 0;
}
