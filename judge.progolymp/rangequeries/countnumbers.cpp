#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>
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

struct Val {
    typedef unordered_map<int, int> T;
    T times;

    Val() : times() {}
    Val(int i) : times() {times[i] = 1;}
    Val(T times) : times(times) {}
    
    Val operator+(Val o) {
        T new_map;
        new_map = times;
        repe(i, o.times) {
            new_map[i.first] += i.second;
        }
        return Val(
            new_map
        );
    }

    Val operator+=(Val o) {
        repe(i, o.times) {
            times[i.first] += i.second;
        }
        return Val(
            times
        );
    }

    int operator[](int o) {
        return times[o];
    }

};

const int N = 2e5;  // limit for array size
int n;  // array size
Val t[2 * N];

void build() {  // build the tree
    for (int i = n - 1; i > 0; --i) t[i] = t[i<<1] + t[i<<1|1];
}

int query(int l, int r, int V) {  // sum on interval [l, r)
    int res = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l&1) res += t[l++][V];
        if (r&1) res += t[--r][V];
    }
    return res;
}

signed main() {
    fast();
    int q;
    cin >> n >> q;

    rep(i, n) {
        int tmp;
        cin >> tmp;
        t[n + i] = Val(tmp);
    }
    
    build();

    rep(i, q) {
        int l, r, V;
        cin >> l >> r >> V;
        cout << query(l, r+1, V) << '\n';
    }
    
    return 0;
}
