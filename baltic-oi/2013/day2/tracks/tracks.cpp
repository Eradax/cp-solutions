#include <bits/stdc++.h>
#include <deque>
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
#define gc() getchar_unlocked()
inline void read(int& v) { v = 0; int sign = 1; char c = gc(); if (c == '-') { sign = -1; } else { v += c - '0'; } while ((c = gc()) && c != ' ' && c != '\n') { if (c == EOF) { v = -1; return; } v *= 10; v += c - '0'; } v *= sign; }
inline void read(int& u, int& v) { read(u); read(v); }
inline void read(int& u, int& v, int& k) { read(u); read(v); read(k); }
//inline void read(int& v) { char c; while ((c = getchar()) != EOF && c != ' ' && c != '\n') { v *= 10; v += c - '0'; } }
inline void read(string& s) { char c; while ((c = gc()) != EOF && c != '\n' && c != ' ') { s.push_back(c); } }
inline void readline(string& s) { char c; while ((c = gc()) != EOF && c != '\n') { s.push_back(c); } }
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

#define bet(lo, i, hi) (((lo) <= (i)) && ((i) < (hi)))

const int H = 4000;
const int W = 4000;
int grid[H][W];
int h, w;
/*
 * 0 -> '.'
 * 1 -> 'F'
 * 2 -> 'R'
*/

/*
int fcnt = 0;
int rcnt = 0;
bool vis[H][W];
void dfs(int r, int c, bool rec) {
    if (!(bet(0, r, h) && bet(0, c, w))) return;
    if (vis[r][c]) return;
    dbg(r, c, rec);
    vis[r][c] = 1;
    
    if (!rec) {
        if (grid[r][c] == 1) fcnt++;
        if (grid[r][c] == 2) rcnt++;
    }

    repe(dir, dirs) {
        int rr = r + dir.first;
        int cc = c + dir.second;
        if (!(bet(0, rr, h) && bet(0, cc, w))) continue;
        if (grid[r][c] == grid[rr][cc]) dfs(rr, cc, true);
    }
}
*/


// Depth of conected component tree
bool vis[H][W] = { 0 };
int bfs(int r, int c) {
    int ans = 0;
    vis[r][c] = 1;
    deque<tuple<int, int, int>> dq;
    dq.push_front({r, c, 0});
    while (!dq.empty()) {
        int rr, cc, vv;
        tie(rr, cc, vv) = dq.front();
        dq.pop_front();

        ans = max(ans, vv);

        vis[rr][cc] = 1;
        repe(dir, dirs) {
            int rrr = rr + dir.first;
            int ccc = cc + dir.second;
            if (!(bet(0, rrr, h) && bet(0, ccc, w))) continue;
            if (vis[rrr][ccc]) continue;
            if (grid[rr][cc] == grid[rrr][ccc]) dq.push_front({rrr, ccc, vv});
            else if (grid[rrr][ccc] > 0) dq.push_back({rrr, ccc, vv+1});
        }
    }
    return ans + 1;
}

signed main() {
    fast();

    cin >> h >> w;

    rep(i, h) {
        string line;
        cin >> line;
        dbg(line);
        rep(j, w) {
            if (line[j] == '.') {
                grid[i][j] = 0;
            }
            if (line[j] == 'F') {
                grid[i][j] = 1;
            }
            if (line[j] == 'R') {
                grid[i][j] = 2;
            }
        }
    }

    rep(i, h) {
        dbg(grid[i]);
    }

    /*
    rep(i, h) {
        rep(j, w) {
            dfs(i, j, false);
        }
    }

    dbg(fcnt, rcnt);

    cout << 1 + min(fcnt, rcnt);
    */
    
    int ans = bfs(0, 0);

    cout << ans;

    return 0;
}
