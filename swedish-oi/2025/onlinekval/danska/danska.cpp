#include <bits/stdc++.h>

#ifdef DBG
  #include "../../../../dbg.h"

  #define PRINTABLE(...)                                                  \
    void print() const {                                                  \
      std::cout << #__VA_ARGS__ << ":\n";                                 \
      auto tuple = std::make_tuple(__VA_ARGS__);                          \
      std::apply([](const auto&... args) { ((dbg(args)), ...); }, tuple); \
      std::cout << std::endl;                                             \
    }
#else
  #define dbg(...)
  #define PRINTABLE(...) \
    void print() const {}
#endif

using namespace std;

using ll = long long;

const ll MOD = 1e9 + 7;
const ll K = 26;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define sz(c) ((ll)c.size())

struct Vertex {
  vector<int> next;
  bool output = false;
  bool calced = false;
  int p = -1;
  char pch;
  int link = -1;
  vector<int> go;

  Vertex(int p = -1, char ch = '$')
      : p(p), pch(ch), next(vector<int>(K, -1)), go(vector<int>(K, -1)) {}

  PRINTABLE(next, output, calced, p, pch, link, go)
};

vector<Vertex> t(1);

void add_string(string const& s) {
  int v = 0;
  for (char ch : s) {
    int c = ch - 'a';
    if (t[v].next[c] == -1) {
      t[v].next[c] = t.size();
      t.emplace_back(v, ch);
    }
    v = t[v].next[c];
  }
  t[v].output = true;
}

int go(int v, char ch);

int get_link(int v) {
  if (t[v].link == -1) {
    if (v == 0 || t[v].p == 0)
      t[v].link = 0;
    else
      t[v].link = go(get_link(t[v].p), t[v].pch);
  }
  return t[v].link;
}

int go(int v, char ch) {
  int c = ch - 'a';
  if (t[v].go[c] == -1) {
    if (t[v].next[c] != -1)
      t[v].go[c] = t[v].next[c];
    else
      t[v].go[c] = v == 0 ? 0 : go(get_link(v), ch);
  }
  return t[v].go[c];
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  ll n, m;
  cin >> n >> m;

  rep(i, m) {
    string s;
    cin >> s;

    add_string(s);
  }

  // Update output values
  queue<ll> q;
  q.push(0);
  while (!q.empty()) {
    ll curr = q.front();
    q.pop();

    if (t[curr].calced)
      continue;

    ll s = get_link(curr);
    while (get_link(s) != s) {
      if (t[s].output) {
        t[curr].output = true;
        t[curr].calced = true;
        break;
      }

      if (t[s].calced) {
        t[curr].output = t[s].output;
      }

      s = get_link(s);
    }

    rep(i, 26) {
      ll nx = t[curr].next[i];
      if (nx < 0 || nx >= sz(t))
        continue;
      if (t[nx].calced)
        continue;
      q.push(nx);
    }
  }

  ll l = sz(t);
  vector<ll> l1(l, 0);  // curr
  vector<ll> l2(l, 0);  // prev

  l2[0] = 1;

  rep(i, n) {
    l1.assign(l, 0);

    rep(j, l) {
      rep(k, 26) {
        ll nv = go(j, 'a' + k);
        l1[nv] = (l1[nv] + l2[j]) % MOD;

        if (t[nv].output)
          l1[nv] = 0;
      }
    }

    dbg(l1);

    l2 = l1;
  }

  for (auto i : t) {
    i.print();
  }

  ll ans = 0;
  rep(i, l) {
    dbg(t[i].output);
    ans = (ans + l1[i]) % MOD;
  }

  cout << ans << endl;
}
