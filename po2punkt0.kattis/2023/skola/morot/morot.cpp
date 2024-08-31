#include <bits/stdc++.h>

#ifdef LOCAL
    #include "dbg.h"
#else
    #define dbg(...)
#endif

using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (int i = high-1; i >= 0; i--)

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

// Read
#define gc() getchar_unlocked()
inline void read(int& v) { v = 0; int sign = 1; char c = gc(); if (c == '-') { sign = -1; } else { v += c - '0'; } while ((c = gc()) && c != ' ' && c != '\n') { if (c == EOF) { v = -1; return; } v *= 10; v += c - '0'; } v *= sign; }
void readinput() {} // Recursion base case
template<typename T, typename... Args> void readinput(T& arg, Args&... args) { read(arg); readinput(args...);}
#define dread(type, ...) type __VA_ARGS__; readinput(__VA_ARGS__);

signed main() {
	fast();

    dread(int, T, M);

    int t = 0;
    int m = 0;

    int c = 40;
    int s = 0;
    while (c > 0) {
        if (!(s % T)) {
            c--;
            t++;
        }
        if (!(s % M)) {
            c--;
            m++;
        }
        s++;
    }

    if (c < 0) {
        t--;
        m--;
    }

    // dbg(t);
    // dbg(m);
    cout << t << " " << m;

	return 0;
}
