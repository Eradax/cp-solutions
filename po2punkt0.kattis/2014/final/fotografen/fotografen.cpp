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

    unordered_map<char, int> ci = {
        {'U', 0},
        {'H', 1},
        {'N', 2},
        {'V', 3}
    };

    int n, k;
    cin >> n >> k;

    string line;
    cin >> line;

    vi vals(n);
    rep(i, n) {
        vals[i] = ci[line[i]];
    }

    vi rots(n);

    int rot_prev = 0;
    int rot = 0;

    int moves = 0;
    rep(i, n - k + 1) {
        dbg("Rep", i);
        int move = (4 - ((vals[i] + rot - rot_prev) % 4)) % 4;
    
        rots[i] = move;

        moves += move;
        rot += move;

        dbg(i, move, moves);

        if (i >= k-1) {
            dbg("rot_prev", rots[i - k + 1]);
            rot_prev += rots[i - k + 1];
        }
    }

    bool succ = true;
    repp(i, n - k + 1, n) {
        dbg("Repp", i, rot, rot_prev);
        int turn = (rot - rot_prev) % 4;
        if ((vals[i] + turn) % 4 != 0) {
            dbg(i, turn, vals[i]);
            succ = false;
            break;
        }
        if (i >= k-1) { rot_prev += rots[i - k + 1]; }
    }

    if (succ) {
        cout << moves;
    } else {
        cout << -1;
    }

    return 0;
}
