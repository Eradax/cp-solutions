#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#ifdef DBG
  #include "../../../../dbg.h"
#else
  #define dbg(...)
#endif
#define convert(s, i) ((s >> i) & 1)
using namespace std;

using ll = long long;

typedef pair<int, int> P;

const int maxn = 500007;
const int DEP = 40;

struct Trie {
  int frq, nxt[2];
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
    int b = (s >> i) & 1;
    int d = 1 ^ b;
    int pos = pool[cur].nxt[d];

    if (pos && pool[pos].frq > 0) {
      c |= ((ll)d << i);
      cur = pos;
    } else {
      pos = pool[cur].nxt[b];
      c |= ((ll)b << i);
      cur = pos;
    }
  }
  return c;
}


// inline ll findmaxxor(ll s) {
//   int cur = 0;
//   ll c = 0;
//
//   for (int i = DEP - 1; i >= 0; --i) {
//     int b = convert(s, i);
//     int pos = pool[cur].nxt[b ^ 1];
//     int d = b ^ (pos && pool[pos].frq > 0);
//
//     cur = pool[cur].nxt[d];
//     c |= ((ll)d << i);
//   }
//
//   return c;
// }

inline void del(ll s) {
  int cur = 0;
  for (int i = DEP - 1; i >= 0; --i) {
    cur = pool[cur].nxt[convert(s, i)];
    pool[cur].frq--;
  }
}

ll a[maxn];
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

int main() {
  int i, j, u, pj;
  ll v;
  ll mx, cv;
  cnt = 0;
  scanf("%d", &n);
  assert(n <= 1e5);
  for (i = 1; i <= n; ++i)
    pa[i] = i;

  for (i = 1; i <= n; ++i)
    scanf("%lld", &a[i]);

  sort(a + 1, a + 1 + n);

  for (i = 1; i <= n; ++i)
    insert(a[i]);

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

        for (j = last; j <= i; ++j) {
          v = findmaxxor(a[ps[j].second]);
          if ((v ^ a[ps[j].second]) > mx) {
            mx = (v ^ a[ps[j].second]);
            cv = v;
          }
        }

        res += mx;
        for (j = last; j <= i; ++j)
          insert2(a[ps[j].second]);

        pj = lower_bound(a + 1, a + 1 + n, cv) - a;
        pj = find(pj);
        pre = find(u);
        if (pre > pj)
          swap(pre, pj);
        mct -= join(pre, pj);

        if (i < n) {
          pre = ps[i + 1].first;
          last = i + 1;
        }
      }
    }
  }
  printf("%lld\n", res);
}
