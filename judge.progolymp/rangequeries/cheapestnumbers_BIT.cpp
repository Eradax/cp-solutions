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

struct Tree
{
    vi sums, counts;
    Tree(int n) : sums(n+1), counts(n+1) {}

    void update(int i, int v)
    {
        for (i++; i < sums.size(); i += i & -i) 
        {
            sums[i] += v;
            counts[i] += 1;
        }
    }

    int query(int r)
    {
        int ret = 0;
        for (r++; r > 0; r -= r & -r)
            ret += sums[r];
        return ret;
    }

    int query_count(int r)
    {
        int ret = 0;
        for (r++; r > 0; r -= r & -r)
            ret += counts[r];
        return ret;
    }

    int sum(int l, int r) // [l, r]
    {
        if (l) l = query(l-1);
        return query(r) - l;
    }

    int sum_count(int l, int r) // [l, r]
    {
        if (l) l = query_count(l-1);
        return query_count(r) - l;
    }
};

/*
void dbg(vector<tuple<int, int, int, int>> a) {
    cout << "--------- Q --------------\n";
    repe(i, a) {
        cout << get<0>(i) << " ";
        cout << get<1>(i) << " ";
        cout << get<2>(i) << " ";
        cout << get<3>(i) << " ";
        cout << endl;
    }
}

void dbg(vector<p2> a) {
    cout << "-------------- V -------------\n";
    repe(i, a) {
        cout << i.first << " " << i.second << endl;
    }
}
*/

signed main()
{
	fast();

    int n, q;
    cin >> n >> q;

    vector<p2> vals(n);
    rep(i, n) {
        cin >> vals[i].first;
        vals[i].second = i;
    }

    vector<tuple<int, int, int, int>> queries(q);
    rep(i, q) {
        int l, r, V;
        cin >> l >> r >> V;
        queries[i] = {V, l, r, i};
    }


    // dbg(vals);
    // dbg(queries);
    sort(all(vals));
    sort(all(queries));
    // dbg(vals);
    // dbg(queries);

    vi ans(q);
    Tree bit(n);
    
    int idx = 0;
    repe(query, queries) {
        int V, l, r, i;
        tie(V, l, r, i) = query;
        
        /*
        cerr << "----------- I -------------\n";
        */
        ans[i] = bit.sum_count(l, r);
        while (idx < n) {
            int val, pos;
            tie(val, pos) = vals[idx];

            if (bit.sum_count(l, r) >= r - l + 1) {break;}
            if (bit.sum(l, r) + val > V) {break;}
            /*
            cout << "idx: " << idx << " pos: " << pos << " val: " << val << endl;
            */
            bit.update(pos, val);
            ans[i] = bit.sum_count(l, r);

            idx++;
        }
        /*
        cerr << "------------ A ------------\n";
        cerr << "r: " << bit.query(r) << " l: " << bit.query(l-1) << endl;
        cerr << "r: " << bit.query_count(r) << " l: " << bit.query_count(l-1) << endl;
        */
    }
    

    /*
    repe(i, bit.sums)
        cerr << i << " ";
    cerr << "\n";

    repe(i, bit.counts)
        cerr << i << " ";
    cerr << "\n";
    */


    repe(i, ans) {
        cout << i << '\n';
    }

	return 0;
}
