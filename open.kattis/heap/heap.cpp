#include "heap.h"
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto &i : container)
#define per(i, high) for (int i = high - 1; i >= 0; i--)

#define clz(x) __builtin_clz(x)
#define popcount(x) __builtin_popcountll(x)

inline void fast() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
}

#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define setcontains(set, x) (set.find(x) != set.end())
#define sz(container) ((int)container.size())

vi bh(0);
int hsize = 0;

int getMax() { return bh[0]; }

int getSize() { return hsize; }

void insert(int element) {
  // repe(i, bh) {
  //   cout << i << " ";
  // } cout << endl;

  int idx = hsize, par = (idx - 1) / 2;
  bh.push_back(element);
  hsize++;

  while (!(bh[idx] <= bh[par])) {
    int tmp = bh[idx];
    bh[idx] = bh[par];
    bh[par] = tmp;

    idx = par;
    par = (par - 1) / 2;

    if (idx == 0)
      return;
  }
}

#define lchild 2 * idx + 1
#define rchild 2 * idx + 2
void removeMax() {
  //   repe(i, bh) {
  //   cout << i << " ";
  // } cout << endl;

  if (hsize <= 0)
    return;
  bh[0] = bh[hsize - 1];
  bh.pop_back();
  hsize--;

  int idx = 0;

  if (lchild >= hsize) {
    return;
  }else if (rchild >= hsize) {
    if (!(bh[idx] >= bh[lchild])) {
      int tmp = bh[lchild];
      bh[lchild] = bh[idx];
      bh[idx] = tmp;
    }
    return;
  }

  while (!((bh[idx] >= bh[lchild]) && (bh[idx] >= bh[rchild]))) {
    int max_child;
    if (bh[lchild] >= bh[rchild])
      max_child = lchild;
    else
      max_child = rchild;

    int tmp = bh[max_child];
    bh[max_child] = bh[idx];
    bh[idx] = tmp;
    
    idx = max_child;

    if (lchild >= hsize) {
      return;
    }else if (rchild >= hsize) {
      if (!(bh[idx] >= bh[lchild])) {
        int tmp = bh[lchild];
        bh[lchild] = bh[idx];
        bh[idx] = tmp;
      }
      return;
    }
  }
}
