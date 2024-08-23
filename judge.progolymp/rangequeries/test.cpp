#include <bits/stdc++.h>

// dbg
#ifdef LOCAL
    #include "dbg.h"
#else
    #define dbg(...)
#endif

using namespace std;



typedef long long ll;

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

const int N = 20;
struct Node {
    p2 left; // {len, bit}
    p2 tot; // {len, bit}
    p2 right; // {len, bit}
    
    int onecnt; // num of ones
    int zerocnt; // num of zeros

    Node() : left({0, 0}), tot({0, 0}), right({0, 0}), onecnt(0), zerocnt(0) {}
    Node(int x): left({1, x}), tot({1, x}), right({1, x}), onecnt(int(x == 1)), zerocnt(int(x == 0)) {}
    Node(p2 l, p2 m, p2 r, int o, int z) : left(l), tot(m), right(r), onecnt(o), zerocnt(z) {}
};

struct Update {
    bool sorted;
    bool xored;

    Update() : sorted(false), xored(false) {}
    Update(bool s, bool x) : sorted(s), xored(x) { }
};

struct Tree {
    using Val = Node;
    using Upd = Update;

    const int n;
    const int h;
    Val tree[2 * N];
    Upd lazy[N]; // Don't store lazy for leaf nodes

    Tree(int n) : n(n), h(32 - __builtin_clz(n))  { dbg(n, h); assert(n <= N); }
    Tree(int n, int a[]) : n(n), h(32 - __builtin_clz(n)) { rep(i, n) tree[n + i] = a[i]; t_build(0, n); dbg(n, h); assert(n <= N); }


    Val t_merge(Val a, Val b) {
        p2 mid = {0, 0};
        if (a.right.second == b.left.second) {
            mid.first = a.right.first + b.left.first;
            mid.second = a.right.second;
        } else {
            mid = max(a.right, b.left);
        }

        p2 left = a.left;
        if (a.zerocnt == 0 && b.left.second == 1) {
            left.first += b.left.second;
        }
        if (a.onecnt == 0 && b.left.second == 0) {
            left.first += b.left.second;
        }

        p2 right = a.right;
        if (b.zerocnt == 0 && a.right.second == 1) {
            right.first += a.right.second;
        }
        if (b.onecnt == 0 && a.right.second == 0) {
            right.first += a.right.second;
        }

        int onecnt = a.onecnt + b.onecnt;
        int zerocnt = a.zerocnt + b.zerocnt;
        
        mid = max(max(mid, left), right);

        return Val(left, mid, right, onecnt, zerocnt);
    }

    void t_calc(int p) {
        assert(p < n);
        assert(!(lazy[p].xored && lazy[p].sorted));
        tree[p] = t_merge(tree[p * 2], tree[p * 2 + 1]);
        if (lazy[p].xored) { // xored
            dbg(p, tree[p].onecnt, tree[p].zerocnt);
            swap(tree[p].onecnt, tree[p].zerocnt);
            dbg(p, tree[p].onecnt, tree[p].zerocnt);
            tree[p].left.second ^= 1;
            tree[p].tot.second ^= 1;
            tree[p].right.second ^= 1;
        }
        if (lazy[p].sorted) { // sorted
            if (tree[p].zerocnt)
                tree[p].left = {tree[p].zerocnt, 0};
            else
                tree[p].left = {tree[p].onecnt, 1};

            if (tree[p].onecnt)
                tree[p].right = {tree[p].onecnt, 1};
            else
                tree[p].right = {tree[p].zerocnt, 0};
        }
    }

    void t_apply(int p, Upd v) {
        if (v.sorted) {
            if (tree[p].zerocnt) {
                tree[p].left = {tree[p].zerocnt, 0};
            } else {
                tree[p].left = {tree[p].onecnt, 1};
            }
            if (tree[p].onecnt) {
                tree[p].right = {tree[p].onecnt, 1};
            } else {
                tree[p].right = {tree[p].zerocnt, 0};
            }

        } else if (v.xored) {
            swap(tree[p].onecnt, tree[p].zerocnt);
            tree[p].left.second ^= 1;
            tree[p].tot.second ^= 1;
            tree[p].right.second ^= 1;
        }

        if (p < n) {
            lazy[p] = v;
        }
    }

    void t_build(int l, int r) { // [l, r)
      for (l += n, r += n-1; l > 1;) {
        l >>= 1, r >>= 1;
        for (int i = r; i >= l; --i) t_calc(i);
      }
    }

    void t_push(int l, int r) { // [l, r)
      int s = h;
      for (l += n, r += n-1; s > 0; --s)
        for (int i = l >> s; i <= r >> s; ++i) if (!lazy[i].sorted && !lazy[i].xored) {
          t_apply(i<<1, lazy[i]);
          t_apply(i<<1|1, lazy[i]);
          lazy[i] = Upd(0, 0);
        }
    }

    void t_sort(int l, int r) { // [l, r)
        assert(0 <= l && l <= r && r <= n);
        t_push(l, l+1);
        t_push(r-1, r);
        int l0 = l, r0 = r;
        for (l += n, r += n; l < r; l /= 2, r/= 2) {
            if (l&1) t_apply(l++, Upd(1, 0));
            if (r&1) t_apply(--r, Upd(1, 0));
        }
        t_build(l0, l0+1);
        t_build(r0-1, r0);
    }

    void t_xor(int l, int r) { // [l, r)
        assert(0 <= l && l <= r && r <= n);
        t_push(l, l+1);
        t_push(r-1, r);
        int l0 = l, r0 = r;
        for (l += n, r += n; l < r; l /= 2, r/= 2) {
            if (l&1) t_apply(l++, Upd(0, 1));
            if (r&1) t_apply(--r, Upd(0, 1));
        }
        t_build(l0, l0+1);
        t_build(r0-1, r0);       
    }

    Val t_max(int l, int r) { // [l, r)
        assert(0 <= l && l <= r && r <= n);
        t_push(l, l+1);
        t_push(r-1, r);


        t_push(0, n);
        repp(i, 0, 2*n) {
            #define t tree[i]
            dbg(i, t.onecnt, t.zerocnt, t.left, t.tot, t.right);
            #undef t
        }

        Val l_res = Val();
        Val r_res = Val();
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l&1) l_res = t_merge(l_res, tree[l++]);
            if (r&1) r_res = t_merge(tree[--r], r_res);
        }
        return t_merge(l_res, r_res); 
    }
};

// Read
#define gc() getchar_unlocked()
inline void read(int& v) { v = 0; int sign = 1; char c = gc(); if (c == '-') { sign = -1; } else { v += c - '0'; } while ((c = gc()) && c != ' ' && c != '\n') { if (c == EOF) { v = -1; return; } v *= 10; v += c - '0'; } v *= sign; }
void readinput() {} // Recursion base case
template<typename T, typename... Args> void readinput(T& arg, Args&... args) { read(arg); readinput(args...);}
#define dread(type, ...) type __VA_ARGS__; readinput(__VA_ARGS__);

signed main() {
	fast();

    dread(int, n, q);

    int a[N];
    rep(i, n) {
        char b = gc();
        a[i] = int(b == '1');
    }
    gc();

    Tree tree = Tree(n, a);

    rep(i, q) {
        dread(int, T, l, r);
        dbg(T, l, r);

        if (T == 1) { // xor
            tree.t_xor(l, r);
        } else { // sort
            tree.t_sort(l, r);
        }

        cout << tree.t_max(l, r).tot.first << '\n';
    }


	return 0;
}
