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

struct Tree {
	typedef int T;
	T f(T a, T b) { return a + b; } // (any associative fn)
    T g(T a, T b) { return (a > b) ? a : b;}
	vector<T> s; int n;
    vector<T> m;
	Tree(int n = 0, T def = 0) : s(2*n, def), m(2*n, def), n(n) {}

	void update(int pos, T val) {
        pos += n;
		for ((s[pos] = m[pos] = val); pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
            m[pos] = g(m[pos * 2], m[pos * 2 + 1]);
	}
    void mod_update(int pos, int mod) {
        pos += n;
		for ((s[pos] = m[pos] = (s[pos]%mod)); pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
            m[pos] = g(m[pos * 2], m[pos * 2 + 1]);

    }
    void update(int l, int r, int mod) {
        if (r - l < 10) {
            repp(i, l, r+1) {
                mod_update(i, mod);
            }
            return;
        }

        if (query_max(l, r+1) < mod) {
            return;
        } else {
            int mid = l + (r - l) / 2;
            update(l, mid, mod);
            update(mid+1, r, mod);
        }
    }

	T query_sum(int b, int e) { // query [b, e)
		T ra = 0, rb = 0;
        b += n; e += n;
		for (; b < e; b /= 2, e /= 2) {
			if (b % 2) ra = f(ra, s[b++]);
			if (e % 2) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
	T query_max(int b, int e) { // query [b, e)
		T ra = 0, rb = 0;
        b += n; e += n;
		for (; b < e; b /= 2, e /= 2) {
			if (b % 2) ra = g(ra, s[b++]);
			if (e % 2) rb = g(s[--e], rb);
		}
		return g(ra, rb);
	}
};


signed main()
{
	fast();
    int n, q;
    cin >> n >> q;

    Tree tree(n, 0);

    rep(i, q) {
        int opt;
        cin >> opt;
        
        if (opt == 0) {
            int l, r;
            cin >> l >> r;
            cout << tree.query_sum(l, r+1) << "\n";
        } else if (opt == 1) {
            int i, v;
            cin >> i >> v;
            tree.update(i, v);
        } else {
            int l, r, mod;
            cin >> l >> r >> mod;
            tree.update(l, r, mod);
        }
    }

	return 0;
}
