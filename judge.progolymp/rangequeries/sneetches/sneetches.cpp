#include <bits/stdc++.h>

#ifdef DBG
  #include "../../../dbg.h"
#else
  #define dbg(...)
#endif

using namespace std;

using pi = pair<int, int>;
using node = tuple<pi, pi, pi, int>;

struct T {
  int n;

  vector<int> len;
  vector<int> lon[2];
  vector<int> llon[2];
  vector<int> rlon[2];
  vector<int> nstar, fliped, isset;

  T(int n) : n(n), len(4 * n), nstar(4 * n), fliped(4 * n), isset(4 * n) {
    for (int i = 0; i < 2; i++) {
      lon[i].resize(4 * n);
      llon[i].resize(4 * n);
      rlon[i].resize(4 * n);
    }
  }

  void build(int x, int l, int r, vector<int>& a) {
    isset[x] = 2;
    fliped[x] = 0;
    len[x] = r - l + 1;
    if (l == r) {
      lon[a[l]][x] = 1;
      llon[a[l]][x] = 1;
      rlon[a[l]][x] = 1;
      nstar[x] = a[l];

      dbg(l, r, mk_node(x));

      return;
    }

    int mid = (l + r) / 2;
    build(2 * x, l, mid, a);
    build(2 * x + 1, mid + 1, r, a);
    combine(x, l, r);

    dbg(l, r, mk_node(x));
  }

  void combine(int x, int l, int r) {
    llon[0][x] = llon[0][2 * x];
    if (nstar[2 * x] == 0)
      llon[0][x] += llon[0][2 * x + 1];
    llon[1][x] = llon[1][2 * x];
    if (nstar[2 * x] == len[2 * x])
      llon[1][x] += llon[1][2 * x + 1];

    rlon[0][x] = rlon[0][2 * x + 1];
    if (nstar[2 * x + 1] == 0)
      rlon[0][x] += rlon[0][2 * x];
    rlon[1][x] = rlon[1][2 * x + 1];
    if (nstar[2 * x + 1] == len[2 * x + 1])
      rlon[1][x] += rlon[1][2 * x];

    nstar[x] = nstar[2 * x] + nstar[2 * x + 1];

    lon[0][x] = max(llon[0][x], rlon[0][x]);
    lon[0][x] = max(lon[0][x], lon[0][2 * x]);
    lon[0][x] = max(lon[0][x], lon[0][2 * x + 1]);
    lon[0][x] = max(lon[0][x], rlon[0][2 * x] + llon[0][2 * x + 1]);

    lon[1][x] = max(llon[1][x], rlon[1][x]);
    lon[1][x] = max(lon[1][x], lon[1][2 * x]);
    lon[1][x] = max(lon[1][x], lon[1][2 * x + 1]);
    lon[1][x] = max(lon[1][x], rlon[1][2 * x] + llon[1][2 * x + 1]);
  }

  node comb2(node l_node, node r_node, int len_l, int len_r) {
    pi res_llon, res_rlon, res_lon;
    int res_nstar;

    int l_llon0 = get<0>(l_node).first;
    int l_llon1 = get<0>(l_node).second;
    int l_rlon0 = get<1>(l_node).first;
    int l_rlon1 = get<1>(l_node).second;
    int l_lon0 = get<2>(l_node).first;
    int l_lon1 = get<2>(l_node).second;
    int l_nstar = get<3>(l_node);

    int r_llon0 = get<0>(r_node).first;
    int r_llon1 = get<0>(r_node).second;
    int r_rlon0 = get<1>(r_node).first;
    int r_rlon1 = get<1>(r_node).second;
    int r_lon0 = get<2>(r_node).first;
    int r_lon1 = get<2>(r_node).second;
    int r_nstar = get<3>(r_node);

    res_nstar = l_nstar + r_nstar;

    res_llon.first = l_llon0;
    if (l_nstar == 0) {
      res_llon.first += r_llon0;
    }
    res_llon.second = l_llon1;
    if (l_nstar == len_l) {
      res_llon.second += r_llon1;
    }

    res_rlon.first = r_rlon0;
    if (r_nstar == 0) {
      res_rlon.first += l_rlon0;
    }
    res_rlon.second = r_rlon1;
    if (r_nstar == len_r) {
      res_rlon.second += l_rlon1;
    }

    res_lon.first = max({l_lon0, r_lon0, l_rlon0 + r_llon0});
    res_lon.second = max({l_lon1, r_lon1, l_rlon1 + r_llon1});

    res_lon.first = max({res_lon.first, res_llon.first, res_rlon.first});
    res_lon.second = max({res_lon.second, res_llon.second, res_rlon.second});

    return make_tuple(res_llon, res_rlon, res_lon, res_nstar);
  }

  void push(int x, int l, int r) {
    int mid = (l + r) / 2;
    if (isset[x] != 2) {
      put_set(2 * x, l, mid, isset[x]);
      put_set(2 * x + 1, mid + 1, r, isset[x]);
      isset[x] = 2;
      fliped[x] = 0;
      return;
    }

    if (fliped[x] != 0) {
      put_flip(2 * x, l, mid, fliped[x]);
      put_flip(2 * x + 1, mid + 1, r, fliped[x]);
      fliped[x] = 0;
      return;
    }
  }

  void put_set(int x, int l, int r, int v) {
    if (v == 2)
      return;

    lon[v][x] = len[x];
    lon[1 - v][x] = 0;

    llon[v][x] = len[x];
    llon[1 - v][x] = 0;

    rlon[v][x] = len[x];
    rlon[1 - v][x] = 0;

    nstar[x] = v == 1 ? len[x] : 0;

    isset[x] = v;
    fliped[x] = 0;
  }

  void put_flip(int x, int l, int r, int v) {
    if (!v)
      return;

    swap(lon[0][x], lon[1][x]);
    swap(llon[0][x], llon[1][x]);
    swap(rlon[0][x], rlon[1][x]);
    nstar[x] = len[x] - nstar[x];

    if (isset[x] != 2) {
      isset[x] = 1 - isset[x];
      fliped[x] = 0;
    } else {
      fliped[x] = 1 - fliped[x];
    }
  }

  void flip(int x, int l, int r, int ql, int qr) {
    if (l > qr || r < ql)
      return;
    if (l >= ql && r <= qr) {
      put_flip(x, l, r, 1);
      return;
    }

    push(x, l, r);
    int mid = (l + r) / 2;
    flip(2 * x, l, mid, ql, qr);
    flip(2 * x + 1, mid + 1, r, ql, qr);
    combine(x, l, r);
  }

  void set(int x, int l, int r, int ql, int qr, int v) {
    if (l > qr || r < ql)
      return;
    if (l >= ql && r <= qr) {
      put_set(x, l, r, v);
      return;
    }

    push(x, l, r);
    int mid = (l + r) / 2;
    set(2 * x, l, mid, ql, qr, v);
    set(2 * x + 1, mid + 1, r, ql, qr, v);
    combine(x, l, r);
  }

  void sort(int l, int r) {
    dbg(l, r);
    int stars = query_stars(1, 0, n - 1, l, r);
    int nonstars = r - l + 1 - stars;
    dbg(stars, nonstars);
    if (nonstars)
      set(1, 0, n - 1, l, l + nonstars - 1, 0);
    if (stars)
      set(1, 0, n - 1, l + nonstars, r, 1);
    dbg(query_stars(1, 0, n - 1, l, r));
  }

  int query_stars(int x, int l, int r, int ql, int qr) {
    if (l > qr || r < ql)
      return 0;
    if (l >= ql && r <= qr)
      return nstar[x];

    push(x, l, r);
    int mid = (l + r) / 2;
    return query_stars(2 * x, l, mid, ql, qr) +
           query_stars(2 * x + 1, mid + 1, r, ql, qr);
  }

  // int query_len(int x, int l, int r, int ql, int qr) {
  //   if (l > qr || r < ql) return 0;
  //   if (l >= ql && r <= qr) return {lon[0][x], lon[1][x]};
  // }

  int get_lon() {
    push(1, 0, n - 1);
    combine(1, 0, n - 1);
    return max(lon[0][1], lon[1][1]);
  }

  node mk_node(int x) {
    return {
        {llon[0][x], llon[1][x]},
        {rlon[0][x], rlon[1][x]},
        {lon[0][x], lon[1][x]},
        nstar[x]
    };
  }

  node query_len(int x, int l, int r, int ql, int qr) {
    if (l > qr || r < ql)
      return {{0, 0}, {0, 0}, {0, 0}, 0};
    if (l >= ql && r <= qr)
      return mk_node(x);

    push(x, l, r);
    int mid = l + (r - l) / 2;
    return comb2(
        query_len(2 * x, l, mid, ql, qr),
        query_len(2 * x + 1, mid + 1, r, ql, qr),
        mid - l + 1,
        r - mid
    );
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, q;
  cin >> n >> q;
  vector<int> a(n);
  {
    string s;
    cin >> s;
    for (int i = 0; i < n; i++)
      a[i] = s[i] == '1';
  }

  dbg(a);

  T t(n);
  t.build(1, 0, n - 1, a);

  dbg(t.query_len(1, 0, n - 1, 0, n - 1));

  for (int i = 0; i < q; i++) {
    int op, l, r;
    cin >> op >> l >> r;

    if (op == 1) {
      t.flip(1, 0, n - 1, l, r);
    } else {
      t.sort(l, r);
    }

    // node res = t.query_len(1, 0, n - 1, 0, n - 1);
    // int ans = max(get<2>(res).first, get<2>(res).second);
    // cout << ans << '\n';
    cout << t.get_lon() << '\n';
  }
}
