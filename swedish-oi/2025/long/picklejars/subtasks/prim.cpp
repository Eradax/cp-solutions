#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int lim_n = 5e5 + 5, lim_b = 41;

struct node {
  char b;
  bool v;
  int cnt, ind;
  node* p[2];
  node(int _b, int _v) {
    p[0] = p[1] = nullptr;
    b = _b;
    v = _v;
    cnt = 0;
  }
} root(lim_b, 0);

struct Data {
  int u, v;
  ll x;
  inline bool operator<(const Data& b) const { return x < b.x; }
};

int n, nold, r[lim_n], r2[lim_n], cnt;
ll a[lim_n], b[lim_n];
vector<int> mst[lim_n];
priority_queue<Data> q;
bool vis[lim_n];
long long ans;

void read_data() {
  scanf("%d", &n);
  assert(n <= 1e5);
  nold = n;
  pair<ll, int> t[lim_n];
  for (int i = 0; i < n; ++i)
    scanf("%lld", &t[i].first), t[i].second = i;
  sort(t, t + n);
  t[n] = {-1, -1};
  int j = 0;
  for (int i = 0; i < n; ++i)
    if (t[i].first != t[i + 1].first) {
      a[j++] = t[i].first, r[j-1] = t[i].second;
    } else {
      b[i - j] = t[i].first;
      r2[i - j] = t[i].second;
    }
  n = j;
}

void add(int i) {
  ll x = a[i];
  node* cur = &root;
  ++cur->cnt;
  while (cur->b > 0) {
    bool tmp = x >> cur->b - 1 & 1;
    if (cur->p[tmp] == nullptr) {
      cur->p[tmp] = new node(cur->b - 1, tmp);
      cur->p[!tmp] = new node(cur->b - 1, !tmp);
    }
    cur = cur->p[tmp];
    ++cur->cnt;
  }
  cur->ind = i;
}

void remove(int i) {
  ll x = a[i];
  node* cur = &root;
  --cur->cnt;
  while (cur->b > 0) {
    bool tmp = x >> cur->b - 1 & 1;
    cur = cur->p[tmp];
    --cur->cnt;
  }
}

int get_next(int i) {
  ll x = a[i];
  node* cur = &root;
  if (cur->cnt == 0)
    return n;
  while (cur->b > 0) {
    bool tmp = x >> cur->b - 1 & 1;
    tmp ^= 1;
    if (cur->p[tmp]->cnt > 0)
      cur = cur->p[tmp];
    else
      cur = cur->p[!tmp];
  }
  if (vis[cur->ind])
    return n;
  else
    return cur->ind;
}

int get_next(int i, ll x) {
  node* cur = &root;
  if (cur->cnt == 0)
    return n;
  while (cur->b > 0) {
    bool tmp = x >> cur->b - 1 & 1;
    tmp ^= 1;
    if (cur->p[tmp]->cnt > 0)
      cur = cur->p[tmp];
    else
      cur = cur->p[!tmp];
  }
  if (vis[cur->ind])
    return n;
  else
    return cur->ind;
}

signed main() {
  read_data();
  for (int i = 0; i < n; ++i)
    add(i);

  for (int i = 0; i < nold - n; i++) {
    int tar = get_next(-1, b[i]);
    ans += a[tar] ^ b[i];
    mst[r2[i]].push_back(r[tar]);
    mst[r[tar]].push_back(r2[i]);
  }

  remove((int)0);
  vis[0] = 1;
  q.push({0, get_next(0), a[0] ^ a[get_next(0)]});
  while (cnt < n - 1) {
    Data cur = q.top();
    q.pop();
    if (!vis[cur.v]) {
      ++cnt;
      ans += a[cur.u] ^ a[cur.v];
      mst[r[cur.u]].push_back(r[cur.v]);
      mst[r[cur.v]].push_back(r[cur.u]);
      vis[cur.v] = true;
      remove(cur.v);
      int tar = get_next(cur.v);
      if (tar != n)
        q.push({cur.v, tar, a[cur.v] ^ a[tar]});
    }
    int tar = get_next(cur.u);
    if (tar != n)
      q.push({cur.u, tar, a[cur.u] ^ a[tar]});
  }

  vector<int> ord, comb;

  vector<int> link(nold, -1);
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

    link[u] = ord.size();
    ord.push_back(u);
  };

  dfs(0, 0);

  printf("%lld\n", ans);
  for (auto i : ord)
    printf("%d ", i);
  printf("\n");
  for (auto i : comb)
    printf("%d ", i);
  printf("\n");
}
