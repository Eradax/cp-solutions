#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#ifdef DBG
  #include "../persist/cp/cp-solutions/dbg.h"
#else
  #define dbg(...)
#endif
using namespace std;

// using ll = long long;
// #define int ll

#define sz(c) ((int)c.size())

using ll = long long;

typedef pair<int, int> P;

const int maxn = 500007;
const int NDEP = 40;
const int K = 1;
const int DEP = (NDEP + K - 1) / K;

inline ll convert(ll s, int i) {
  return ((s >> (i * K)) & ((1 << K) - 1));
}

struct Trie {
  int frq, nxt[1<<K];
} pool[maxn * (DEP + 1)];

int cnt, n;

inline void insert(ll s) {
  int cur = 0;
  for (int i = DEP - 1; i >= 0; --i) {
    int& pos = pool[cur].nxt[convert(s, i)];
    if (!pos)
      pos = ++cnt;
    cur = pos;
    pool[cur].frq++;
  }
}

inline void insert2(ll s) {
  int cur = 0;
  for (int i = DEP - 1; i >= 0; --i) {
    cur = pool[cur].nxt[convert(s, i)];
    pool[cur].frq++;
  }
}

inline ll findmaxxor(ll s) {
  int cur = 0;
  ll c = 0;
  for (int i = DEP - 1; i >= 0; --i) {
    int b = convert(s, i);
    int d = b ^ ((1 << K) - 1);
    int pos = pool[cur].nxt[d];

    for (int j = 0; j < 1 << K; j++) {
      pos = pool[cur].nxt[d ^ j];
      if (pos && pool[pos].frq > 0) {
        c |= ((ll)d ^ j) << (i * K);
        cur = pos;
        break;
      }
    }
  }
  return c;
}

inline void del(ll s) {
  int cur = 0;
  for (int i = DEP - 1; i >= 0; --i) {
    cur = pool[cur].nxt[convert(s, i)];
    pool[cur].frq--;
  }
}

ll a[maxn];
pair<ll, int> a2[maxn];
int pa[maxn], used[maxn];

int find(int x) {
  return x == pa[x] ? x : pa[x] = find(pa[x]);
}

int join(int x, int y) {
  int px = find(x), py = find(y);
  if (px == py)
    return 0;
  pa[py] = px;
  return 1;
}

ll res = 0;
P ps[maxn];

int trans[maxn];

signed main() {
  int i, j, u, pj;
  ll v;
  ll mx, cv;
  cnt = 0;
  scanf("%d", &n);

  vector<vector<int>> mst(n);

  // assert(n <= 1e5);
  for (i = 1; i <= n; ++i)
    pa[i] = i;

  for (i = 1; i <= n; ++i) {
    scanf("%lld", &a2[i].first);
    a2[i].second = i;
  }

  sort(a2 + 1, a2 + 1 + n);

  vector<pair<ll, int>> og, dup;
  og.push_back(a2[1]);
  for (int i = 1; i < n; i++) {
    if (a2[i].first != a2[i+1].first) {
      og.push_back(a2[i+1]);
    }else {
      dup.push_back(a2[i+1]);
    }
  }

  dbg(og, dup);

  for (i = 0; i < sz(og); ++i) {
    trans[i+1] = og[i].second;
    a[i+1] = og[i].first;
    insert(a[i+1]);
  }

  for (int i = 0; i < sz(dup); i++) {
    ll v = findmaxxor(dup[i].first);
    int pv = trans[lower_bound(a+1, a+1+sz(og), v) - a] - 1;
    dbg(pv, dup[i].second, v, dup[i].first);
    mst[dup[i].second-1].push_back(pv);
    mst[pv].push_back(dup[i].second-1);
    res += dup[i].first ^v;
  }

  dbg(trans);
  dbg(mst);

  dbg(res);

  n = sz(og);

  int gen = 0;
  int mct = n - 1;
  vector<vector<int>> pss(n + 1);
  while (mct) {
    gen++;

    for (auto& vec : pss)
      vec.clear();
    for (i = 1; i <= n; ++i)
      pss[find(i)].push_back(i);
    int cc = 0;
    for (i = 1; i <= n; i++)
      for (auto j : pss[i])
        ps[++cc] = make_pair(i, j);

    int pre = ps[1].first, last = 1;

    for (i = 1; i <= n; ++i) {
      u = ps[i].second;
      if (used[pre] != gen && ps[i].first == pre)
        del(a[u]);

      if (i == n || ps[i + 1].first != pre) {
        if (used[find(u)] == gen) {
          for (j = last; j <= i; j++)
            insert2(a[ps[j].second]);
          last = i + 1;
          if (i < n)
            pre = ps[i + 1].first;
          continue;
        }

        used[pre] = gen;
        mx = -1;
        int jj = -1;

        for (j = last; j <= i; ++j) {
          v = findmaxxor(a[ps[j].second]);
          if ((v ^ a[ps[j].second]) > mx) {
            mx = (v ^ a[ps[j].second]);
            cv = v;

            dbg(v, mx, j, ps[j].second);
            jj = ps[j].second;
          }
        }

        res += mx;
        for (j = last; j <= i; ++j)
          insert2(a[ps[j].second]);

        pj = lower_bound(a + 1, a + 1 + n, cv) - a;
        dbg(cv, pj, u, mx, jj);
        int pjo = trans[pj] - 1;
        int preo = trans[jj] - 1;
        pj = find(pj);
        pre = find(u);
        if (pre > pj)
          swap(pre, pj);
        if (pj != pre) {
          dbg(pj, pre);
          dbg(pjo, preo);
          mst[pjo].push_back(preo);
          mst[preo].push_back(pjo);
          dbg(mst);
          mct--;
          join(pre, pj);
        }

        if (i < n) {
          pre = ps[i + 1].first;
          last = i + 1;
        }
      }
    }
  }

  dbg(mst);

  using vi = vector<int>;

  vi ord, comb;

  auto getFromMST = [&]() {
    vi link(sz(og) + sz(dup), -1);
    function<void(int, int)> dfs = [&](int u, int p) {
      // dbg(u, p);
      for (auto v : mst[u]) {
        if (v == p)
          continue;
        dfs(v, u);
      }

      for (auto it = mst[u].rbegin(); it != mst[u].rend(); it++) {
        int v = *it;
        if (v == p)
          continue;
        // dbg(u, v);
        comb.push_back(link[v]);
      }

      link[u] = sz(ord);
      ord.push_back(u);
    };

    dfs(0, 0);
  };

  getFromMST();

  printf("%lld\n", res);

  for (auto i : ord)
    printf("%d ", i);
  printf("\n");
  for (auto i : comb)
    printf("%d ", i);
  printf("\n");
}
