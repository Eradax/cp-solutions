#include <bits/stdc++.h>
using namespace std;

struct UF {
  vector<int> e;
  UF(int n) : e(n, -1) {}
  int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
  bool join(int a, int b) {
    a = find(a);
    b = find(b);

    if (a == b)
      return 0;

    if (e[a] > e[b])
      swap(a, b);
    e[a] += e[b];
    e[b] = a;
    return 1;
  }
};

struct P {
  int x, y, id;
};

struct Node {
  P pt;
  int dim;
  Node *l, *r;
  Node(const P& p, int d) : pt(p), dim(d), l(nullptr), r(nullptr) {}
};

double sqr(double x) {
  return x * x;
}

Node* build(vector<P>& pts, int l, int r, int dep) {
  if (l >= r)
    return nullptr;
  int d = dep % 2;
  int m = (l + r) >> 1;
  nth_element(
      pts.begin() + l,
      pts.begin() + m,
      pts.begin() + r,
      [d](auto& a, auto& b) { return d == 0 ? a.x < b.x : a.y < b.y; }
  );
  Node* nd = new Node(pts[m], d);
  nd->l = build(pts, l, m, dep + 1);
  nd->r = build(pts, m + 1, r, dep + 1);
  return nd;
}

void knn(Node* nd, const P& q, int K, priority_queue<pair<double, int>>& pq) {
  if (!nd)
    return;
  double dist = sqrt(sqr(nd->pt.x - q.x) + sqr(nd->pt.y - q.y));
  if (pq.size() < K || dist < pq.top().first) {
    pq.emplace(dist, nd->pt.id);
    if (pq.size() > K)
      pq.pop();
  }

  int d = nd->dim;
  double diff = d == 0 ? q.x - nd->pt.x : q.y - nd->pt.y;
  Node* first = diff < 0 ? nd->l : nd->r;
  Node* second = diff < 0 ? nd->r : nd->l;
  knn(first, q, K, pq);
  if (pq.size() < K || fabs(diff) < pq.top().first)
    knn(second, q, K, pq);
}

int main() {
  cin.tie(0)->sync_with_stdio();

  int n;
  cin >> n;
  vector<P> pts(n);
  for (int i = 0; i < n; i++) {
    cin >> pts[i].x >> pts[i].y;
    pts[i].id = i;
  }

  vector<P> tmp = pts;
  Node* root = build(tmp, 0, n, 0);

  const int K = 300;
  struct Edg {
    int u, v;
    double d;
  };
  vector<Edg> edgs;
  edgs.reserve((long long)n * K);

  for (int i = 0; i < n; i++) {
    priority_queue<pair<double, int>> pq;
    knn(root, pts[i], K + 1, pq);

    while (!pq.empty()) {
      auto [dist, idx] = pq.top();
      pq.pop();
      if (idx == i)
        continue;
      edgs.push_back({i, idx, dist});
    }
  }

  sort(edgs.begin(), edgs.end(), [](auto& a, auto& b) { return a.d < b.d; });

  UF uf(n);
  double total = 0;
  for (auto& e : edgs) {
    if (uf.join(e.u, e.v)) {
      total += e.d;
    }
  }

  cout << fixed << setprecision(2) << total << "\n";
}
