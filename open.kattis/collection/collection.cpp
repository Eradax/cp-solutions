#include <bits/stdc++.h>

using namespace std;

#ifdef DBG
#define dbg(expr) cerr << "[" << __FUNCTION__ << ", " << __LINE__ << "] " << #expr << ": " << expr << endl
#else
#define dbg(expr)
#endif

#define sz(c) ((int)c.size())

const int INF = 1e9;

mt19937 rng;

struct Node {
  int val, prio;

  Node* l;
  Node* r;

  int size;
  int min, max;

  Node(int x) : val(x),
    prio(uniform_int_distribution<int>(0, 1e9)(rng)),
    l(nullptr),
    r(nullptr),
    size(1),
    min(x),
    max(x) {}
  Node(int x, Node* _l, Node* _r) : val(x),
    prio(uniform_int_distribution<int>(0, 1e9)(rng)),
    l(_l),
    r(_r),
    size(1),
    min(x),
    max(x) {}

  ~Node() {
    delete l;
    delete r;
  }
};

int _size(Node* p) {
  return p ? p->size : 0;
}
int _min(Node* p) {
  return p ? p->min : INF;
}
int _max(Node* p) {
  return p ? p->max : -INF;
}

int get(Node* p, int ind) {
  assert(0 <= ind && ind < _size(p));
  if (ind < _size(p->l))
    return get(p->l, ind);
  if (ind > _size(p->l))
    return get(p->r, ind - _size(p->l) - 1);
  return p->val;
}

void upd(Node* p) {
  if (!p)
    return;
  p->size = _size(p->l) + _size(p->r) + 1;
  p->min = min(p->val, min(_min(p->l), _min(p->r)));
  p->max = max(p->val, max(_max(p->l), _max(p->r)));
}

void split(Node* t, int key, Node*& t1, Node*& t2) {
  if (!t)
    t1 = t2 = nullptr;
  else if (t->val <= key)
    split(t->r, key, t->r, t2), t1 = t;
  else
    split(t->l, key, t1, t->l), t2 = t;
  
  upd(t);
}

void merge(Node*& t, Node* t1, Node* t2) {
  if (!t1 || !t2)
    t = t1 ? t1 : t2;
  else if (t1->prio > t2->prio)
    merge(t1->r, t1->r, t2), t = t1;
  else
    merge(t2->l, t1, t2->l), t = t2;
  
  upd(t);
}

void insert(Node*& t, Node* nt) {
  if (!t)
    return void(t = nt);

  if (t->prio > nt->prio)
    insert(t->val > nt->val ? t->l : t->r, nt);
  else
    split(t, nt->val, nt->l, nt->r), t = nt;

  upd(t);
}

Node* join(Node* t1, Node* t2) {
  if (!t1 || !t2)
    return t1 ? t1 : t2;
  if (t1->prio < t2->prio)
    swap(t1, t2);

  Node* tt1, *tt2;
  split(t2, t1->val, tt1, tt2);
  t1->l = join(t1->l, tt1);
  t1->r = join(t1->r, tt2);

  upd(t1);
  return t1;
}

// NOTE: This solves the problem not as described in the problemstatement
// but as is required for AC
// The items should be sorted within each group
int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, q;
  cin >> n >> q;

  vector<Node*> v(n + 1);
  for (int i = 0; i < n + 1; i++)
    v[i] = new Node(i);

  vector<int> tags;

  while (q--) {
    int op, i, j;
    cin >> op >> i >> j;

    assert(1 <= i && i <= n);

    if (op == 1) {
      assert(1 <= j && j <= v[i]->size);
      cout << get(v[i], j - 1) << '\n';
    } else if (op == 2) {
      assert(1 <= j && j <= n);
      if (_max(v[i]) < _min(v[j]))
        merge(v[i], v[i], v[j]);
      else if (_max(v[j]) < _min(v[i]))
        merge(v[i], v[j], v[i]);
      else
        v[i] = join(v[i], v[j]);
      v[j] = nullptr;
      tags.push_back(j);
    } else if (op == 3) {
      assert(1 <= j && j < v[i]->size);
      split(v[i], get(v[i], j - 1), v[i], v[tags.back()]);
      tags.pop_back();
    } else {
      assert(0);
    }
  }

  for (auto i : v)
    delete i;
}