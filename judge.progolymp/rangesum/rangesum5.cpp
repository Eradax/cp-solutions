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

struct Mod {
	typedef int T;
    T val, mod;
    Mod(T val = 0, T mod = 1e9+7) : val(val%mod), mod(mod) {}

    Mod operator+(Mod y) {return Mod(val+y.val, mod);}
    Mod operator*(Mod y) {return Mod(val*y.val, mod);}
    Mod operator+=(Mod y) {return Mod(val = (val+y.val), mod);}
};

struct Seg { // everything is [l, r)
    typedef int T;
    T combine(T a, T b) {return a + b;} // combine can be any associative function ((a + b) + b = a + (b + c)).
                                        // Note that combine doesn't have to be commutative (a + b = b + a).
    vector<T> seg; // underlying segment tree array
    vector<T> lazy; // stores the lazy values
    int num_nodes; //
    
    void apply(int node, T value, int length) { // set
        seg[node] = value * length;
        if (node < num_nodes) {
            lazy[node] = value;
        }
    }
    
    void build() {
        for (int i = num_nodes - 1; i > 0; i--) {
            seg[i] = combine(seg[i * 2], seg[i * 2 + 1]);
        }
    }

    void push() { // propagate **down** the tree
        for (int i = 1; i < num_nodes; i++) {
            seg[i * 2] += seg[i];
            seg[i * 2 + 1] += seg[i];
        }
    }

    void set(int node, T value) { // set `node` to `value`
        node += num_nodes; // we add num_nodes because we want to be at the bottom layer
        seg[node] = value;
        for (; node > 1; node /= 2) {
            seg[node / 2] = combine(seg[node], seg[node ^ 1]); // parent = aggregate of lchild and rchild
                                                       // node^1 flips last bit i.e. other child 
        }
    }

    void modify(int l, int r, T value) { // [l, r)
        l += num_nodes; r += num_nodes;
        int l0 = l, r0 = r;
        for (; l < r; l /= 2, r /= 2) {
            if (l % 2 == 0) {

            }
        }
    }

    // supports non commutative functions
    T query(int l, int r) { // [l, r)
        T resl, resr;
        l += num_nodes; r += num_nodes;
        
        for (; l < r; l /= 2, r /= 2) {
            if (l % 2 == 0) { // checks if on edge and parent not in range
                resl = combine(resl, seg[l++]);
            }
            if (r % 2 == 0) { // same
                resr = combine(seg[--r], resr);
            }
        }
        return combine(resl, resr);
    }


};


struct Tree {
	typedef Mod T;
	T f(T a, T b) { return a + b; } // (any associative fn)
    int n;
	vector<T> segt, vals, lazy;
    Tree(int n = 0, T def = 0) : segt(2*n, def), vals(n, def), lazy(n, def), n(n) {}

	void update(int l, int r, T val) {
        T org = vals[l];
        l += n;
        T add = org * val * (org + val) * 3 + val*val*val;
		for (segt[l] += (add); l /= 2;)
			segt[l] = f(segt[l * 2], segt[l * 2 + 1]);
	}
	T query(int b, int e) { // query [b, e)
		T ra = 0, rb = 0;
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2) ra = f(ra, segt[b++]);
			if (e % 2) rb = f(segt[--e], rb);
		}
		return f(ra, rb);
	}
};

signed main()
{
	fast();
    int n, q;
    cin >> n >> q;

    Tree tree(n);

    rep(i, q) {
        int opt, l ,r;
        cin >> opt >> l >> r;
        
        if (opt == 0) {
            cout << tree.query(l, r+1).val << "\n";
        } else {
            int v;
            cin >> v;
            tree.update(l, r+1, v);
        }
    }

	return 0;
}
