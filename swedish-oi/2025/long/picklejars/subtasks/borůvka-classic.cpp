#pragma GCC optimize("Ofast")
#include <bits/allocator.h>
// #pragma GCC target("avx2")
#include <bits/stdc++.h>

#ifdef DBG
  #include "../../../../dbg.h"
#else
  #define dbg(...)
#endif

using namespace std;

#define sz(c) ((int)c.size())
#ifdef DBG
auto Start = chrono::high_resolution_clock::now();
void resettimer() {
  Start = chrono::high_resolution_clock::now();
}
int elapsedmillis() {
  return chrono::duration_cast<chrono::milliseconds>(
             chrono::high_resolution_clock::now() - Start
  )
      .count();
}
#else
  #define resettimer()
  #define elapsedmillis()
#endif

using ll = long long;
using vl = vector<ll>;
using vvl = vector<vl>;

using vi = vector<int>;
using vvi = vector<vi>;

using vpli = vector<pair<ll, int>>;

struct UF {
  vi e;
  UF(int n) : e(n, -1) {}

  int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
  bool sameset(int u, int v) { return find(u) == find(v); }
  int size(int x) { return -e[find(x)]; }
  bool join(int u, int v) {
    u = find(u);
    v = find(v);

    if (u == v)
      return 0;

    if (e[u] > e[v])
      swap(u, v);

    e[u] += e[v];
    e[v] = u;

    return 1;
  }
};

static const int NDEP = 40;
const int K = 2;
const int DEP = (NDEP + K - 1) / K;

inline ll convert(ll s, int i) {
  return ((s >> (i * K)) & ((1 << K) - 1));
}

static char buf2[450 << 20];
void* operator new(size_t s) {
  static size_t i = sizeof buf2;
  // assert(s < i);
  return (void*)&buf2[i -= s];
}
void operator delete(void*) {}
struct Trie {
  Trie* ch[1 << K];

  int cnt;
  int id;

  Trie() {
    for (int i = 0; i < 1 << K; i++)
      ch[i] = nullptr;
    cnt = 0;
  }

  ~Trie() {
    for (int i = 0; i < 1 << K; i++)
      if (ch[i]) delete ch[i];
  }

  void insert(ll x, int mid) {
    Trie* curr = this;

    curr->cnt++;

    for (int i = DEP; i >= 0; i--) {
      int n = convert(x, i);
      if (curr->ch[n] == nullptr) {
        curr->ch[n] = new Trie();
      }
      curr = curr->ch[n];

      curr->cnt++;
    }

    curr->id = mid;
  }

  void remove(ll x, int mid) {
    Trie* curr = this;

    for (int i = DEP; i >= 0; i--) {
      curr->cnt--;
      int n = convert(x, i);
      // assert(curr->ch[n] != nullptr && curr->ch[n]->cnt > 0);
      curr = curr->ch[n];
    }
    curr->cnt--;
  }

  pair<ll, int> max(ll x) {
    Trie* curr = this;
    ll res = 0;
    for (int i = DEP; i >= 0; i--) {
      int n = convert(x, i);

      for (int j = (1 << K) - 1; j >= 0; j--) {
        if (curr->ch[n ^ j] != nullptr && curr->ch[n ^ j]->cnt > 0) {
          res |= (ll)j << (i * K);
          curr = curr->ch[n ^ j];
          break;
        }
      }
    }

    return {res, curr->id};
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  resettimer();

  int n;
  cin >> n;

  assert(n <= 1e5);

  vpli a(n), use, rest;
  for (int i = 0; i < n; i++) {
    cin >> a[i].first;
    a[i].second = i;
  }
  use.reserve(n);
  sort(a.begin(), a.end());
  use.push_back(a[0]);
  for (int i = 1; i < n; i++) {
    if (a[i - 1] != a[i]) {
      use.push_back(a[i]);
    } else {
      rest.push_back(a[i]);
    }
  }

  dbg(elapsedmillis());

  vvi mst(n);
  ll ans = 0;

  {
    UF uf(n);
    Trie trie;

    dbg(elapsedmillis());
    for (int i = 0; i < sz(use); i++)
      trie.insert(use[i].first, use[i].second);
    dbg(elapsedmillis());

    vi groups[2];
    int o = 0;
    vector<vpli> comps(n);
    for (int i = 0; i < sz(use); i++)
      comps[i].push_back(use[i]);

    for (int i = 0; i < sz(use); i++)
      groups[o].push_back(use[i].second);

    while (sz(groups[o]) > 1) {
      o ^= 1;

      // dbg(groups[0], groups[1], o);
      // dbg(comps);

      for (auto i : groups[o ^ 1]) {
        for (auto j : comps[i]) {
          trie.remove(j.first, j.second);
        }

        ll xor_val = -1;
        int xor_node = 0;
        int prev_node = 0;
        for (auto j : comps[i]) {
          auto [tmp_xor_val, tmp_node] = trie.max(j.first);
          if (tmp_xor_val > xor_val) {
            xor_val = tmp_xor_val;
            xor_node = tmp_node;
            prev_node = j.second;
          }
        }

        // dbg(i, prev_node, xor_node, xor_val);
        if (uf.join(prev_node, xor_node)) {
          ans += xor_val;
          mst[prev_node].push_back(xor_node);
          mst[xor_node].push_back(prev_node);
        }

        for (auto j : comps[i]) {
          trie.insert(j.first, j.second);
        }
      }

      groups[o].clear();
      for (auto& i : comps)
        i.clear();

      for (int i = 0; i < sz(use); i++) {
        int x = uf.find(use[i].second);
        comps[x].emplace_back(use[i].first, use[i].second);
        if (x == use[i].second)
          groups[o].push_back(x);
      }
    }

    for (auto j : rest) {
      auto [xor_val, xor_node] = trie.max(j.first);
      ans += xor_val;
      mst[j.second].push_back(xor_node);
      mst[xor_node].push_back(j.second);
    }
  }

  dbg(elapsedmillis());

  vi ord, comb;

  auto getFromMST = [&]() {
    vi link(n, -1);
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

  dbg(elapsedmillis());

  cout << ans << '\n';
  for (auto i : ord)
    cout << i << ' ';
  cout << '\n';
  for (auto i : comb)
    cout << i << ' ';
  cout << '\n';
}
