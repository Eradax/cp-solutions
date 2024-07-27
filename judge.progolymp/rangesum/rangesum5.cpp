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

const int mod = 1e9+7;
struct Mod {
	typedef int T;
    T val;
    Mod(T val = 0) : val(val%mod) {}

    Mod operator+(Mod y) {return Mod(val+y.val);}
    Mod operator*(Mod y) {return Mod(val*y.val);}
    Mod operator+=(Mod y) {return Mod(val = (val+y.val)%mod);}

    bool operator>(Mod y) {return (val > y.val);}
    bool operator>=(Mod y) {return (val >= y.val);}
    bool operator<(Mod y) {return (val < y.val);}
    bool operator<=(Mod y) {return (val <= y.val);}
};

struct Sums {
    typedef Mod T;
    T linear, square, cube, len;
    Sums(T len = 0) : linear(0), square(0), cube(0), len(len) {}
    Sums(T a, T b, T c, T d) : linear(a), square(b), cube(c), len(d) {}

    Sums operator+(Sums y) {
        return Sums(
            linear + y.linear,
            square + y.square,
            cube + y.cube,
            len + y.len
        );
    }

    Sums operator+=(Sums y) {
        return Sums(
            linear += y.linear,
            square += y.square,
            cube += y.cube,
            len += y.len
        );
    }

    Sums operator+=(T y) {
        cube += square * y * 3 + linear * y * y * 3 + len * y * y * y;
        square += linear * y * 2 + len * y * y;
        linear += len * y;
        return Sums(
                linear,
                square,
                cube,
                len
        );
    }
};

struct LazyTree // Range add, range max query
{
    typedef Sums T;
    const T unit = Sums(1);
    int n;
    vector<T> tree;
    vector<Mod> lazy;
    LazyTree(int n) : n(n), tree(n * 4, unit), lazy(n * 4, 0) {rep(i, n) {add(i, i, 0);}}

    T merge(T a, T b)
    {
        return a + b;
    }

    void push(int x)
    {
        tree[x * 2] += lazy[x];
        tree[x * 2 + 1] += lazy[x];
        lazy[x * 2] += lazy[x];
        lazy[x * 2 + 1] += lazy[x];
        lazy[x] = 0;
    }



    void add(int x, int l, int r, int ql, int qr, Mod v)
    {
        if (l > qr || r < ql) return;
        if (l >= ql && r <= qr)
        {
            lazy[x] += v;
            tree[x] += v;
            return;
        }
        push(x);

        int mid = (l + r) / 2;
        add(x * 2, l, mid, ql, qr, v);
        add(x * 2 + 1, mid + 1, r, ql, qr, v);
        tree[x] = merge(tree[x * 2], tree[x * 2 + 1]);
    }



    void add(int ql, int qr, Mod v) {
        add(1, 0, n - 1, ql, qr, v);
    }



    T query(int x, int l, int r, int ql, int qr)
    {
        if (l > qr || r < ql) return Sums(0);
        if (l >= ql && r <= qr) return tree[x];
        push(x);

        int mid = (l + r) / 2;
        return merge(query(x * 2, l, mid, ql, qr), query(x * 2 + 1, mid + 1, r, ql, qr));
    }

    T query(int ql, int qr) { return query(1, 0, n - 1, ql, qr); }
};

signed main() {
	fast();

    int n, q;
    cin >> n >> q;

    LazyTree tree(n);

    rep(i, q) {
        int t, l, r;
        cin >> t >> l >> r;

        if (t == 0) {
            cout << tree.query(l, r).cube.val << endl;
        } else {
            int v;
            cin >> v;
            tree.add(l, r, v);
        }
    }

	return 0;
}
