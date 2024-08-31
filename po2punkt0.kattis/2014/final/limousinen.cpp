#include <bits/stdc++.h>
using namespace std;

// dbg
#ifdef LOCAL
    #include "dbg.h"
#else
    #define dbg(x)
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

inline int nabs(int x) {
    return x >= 0 ? x : -x;
}

struct
{
    bool operator()(p2 a, p2 b) const { return nabs(a.first) + nabs(a.second) < nabs(b.first) + nabs(b.second); }
}
customLess;

signed main() {
    fast();

    int n, t;
    cin >> n >> t;

    vector<p2> poss(n);

    rep(i, n) {
        cin >> poss[i].first >> poss[i].second;
    }

    sort(all(poss), customLess);

    int time = 0;
    int next_person = 0;

    while (next_person < n && time + 2 * (nabs(poss[next_person].first) + nabs(poss[next_person].second)) <= t) {
        time += 2 * (nabs(poss[next_person].first) + nabs(poss[next_person].second));
        next_person++;
    }

    cout << next_person << endl;

    return 0;
}
