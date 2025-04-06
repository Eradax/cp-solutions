#include "bits/stdc++.h"
using namespace std;

/*
* this validator is borrowed from upidapi
*/

#ifdef LOCAL
    #include "../../../../pp.h"
    #define pp_grid(g) pp::grid(g)
    #
    #include "../../../../dbg.h"
#else
    #define dbg(...)
    #define pp_grid(g)
#endif

#define repp(i, lo, hi) for (int i = lo; i < hi; i++)
#define rep(i, hi) repp(i, 0, hi)

#define perr(i, lo, hi) for (int i = hi - 1; i >= 0; i--)
#define per(i, hi) perr(i, 0, hi)

#define all(cont) cont.begin(), cont.end()

using ll = long long;
#define int ll

using vb = vector<bool>;
using vi = vector<int>;
using vvi = vector<vi>;
using pi = pair<int, int>;

const int K = 26;
const ll MOD = 1e9 + 7;

struct UF {
    // if - parent
    vi p;

    UF(int n) : p(n, -1) {}

    bool sameset(int a, int b) { return find(a) == find(b); }

    // get root
    int find(int a) { return p[a] < 0 ? a : p[a] = find(p[a]); }

    int size(int a) { return -p[find(a)]; }

    bool join(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b)
            return false;

        if (size(b) > size(a)) {
            swap(a, b);
        }

        p[a] += p[b];
        p[b] = a;

        return true;
    }
};

signed main() {
    int n;
    cin >> n;

    vi val(n);
    rep(i, n) {
        cin >> val[i];
    }

    // submission data
    int ans;
    cin >> ans;

    vi perm(n);
    rep(i, n) cin >> perm[i];

    vi order(n - 1);
    rep(i, n - 1) cin >> order[i];

    vi count(n);
    rep(i, n) count[perm[i]]++;
    rep(i, n) assert(count[i] == 1);

    // re orderd vals
    vi oval(n, -1);
    rep(i, n) oval[i] = val[perm[i]];

    // everything is in the terms of the oval
    vi right(n, -1);
    vi left(n, -1);
    rep(i, n) {
        right[i] = i + 1;
        left[i] = i - 1;
    }
    left[0] = -1;
    right[n - 1] = -1;

    int sum = 0;
    UF uf(n);
    rep(k, n - 1) {
        // transfer the jar i to the jar to the right of it
        // ie remove i
        int i = order[k]; 
        int j = right[i];
        assert(j != -1);

        assert(uf.join(i, j));
    
        sum += oval[i] ^ oval[j];
        
        left[j] = left[i];
        if (left[i] != -1) right[left[i]] = j;
        // if (right[j] != -1) left[right[j]] = i;
        // right[i] = right[j];
    }
    
    // printf("%d %d", sum, ans);
    assert(sum == ans);
}
