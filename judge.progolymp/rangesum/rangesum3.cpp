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

const ll mod = 1e9 + 7;
struct Mod {
    ll x;
    Mod() : x(0) {}
    Mod(ll xx) : x(xx % mod) {}
    Mod operator+(Mod b) { return Mod((x + b.x) % mod); }
    Mod operator-(Mod b) { return Mod((x - b.x + mod) % mod); }
    Mod operator*(Mod b) { return Mod((x * b.x) % mod); }
};

struct Node
{
	Node* lchild;
	Node* rchild;
	int l, r;
	Mod sum;
	Mod lazy;

	Node(int l, int r) : lchild(nullptr), rchild(nullptr), l(l), r(r), sum(0), lazy(0) {}

	void push()
	{
		int mid = (l + r) / 2;
		if (!lchild)
		{
			lchild = new Node(l, mid);
			rchild = new Node(mid + 1, r);
		}
		lchild->sum = lchild->sum + lazy * Mod(mid - l + 1);
		lchild->lazy = lchild->lazy + lazy;

		rchild->sum = rchild->sum + lazy * Mod(r - (mid + 1) + 1);
		rchild->lazy = rchild->lazy + lazy;
		lazy = 0;
	}

	void add(int ql, int qr, Mod v)
	{
		if (l > qr || r < ql) return;
		if (l >= ql && r <= qr)
		{
			sum = sum + v * Mod(r - l + 1);
			lazy = lazy + v;
		}
		else
		{
			push();
			lchild->add(ql, qr, v);
			rchild->add(ql, qr, v);
			sum = rchild->sum + lchild->sum;
		}
	}

	Mod query(int ql, int qr)
	{
		if (l > qr || r < ql) return 0;
		if (l >= ql && r <= qr) return sum;
		else
		{
			push();
			return lchild->query(ql, qr) + rchild->query(ql, qr);
		}
	}
};

signed main()
{
	fast();
    int q;
    cin >> q;

    Node tree(0, 1e9);

    rep(i, q) {
        int opt, l, r;
        cin >> opt >> l >> r;
        
        if (opt == 0) {
            cout << tree.query(l, r).x << "\n";
        } else {
            int v;
            cin >> v;
            tree.add(l, r, v);
        }
    }

	return 0;
}
