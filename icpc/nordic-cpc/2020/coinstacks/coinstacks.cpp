#include <bits/stdc++.h>

#ifdef DBG
#include "../../../../dbg.h"
#else
#define dbg(...)
#endif

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  priority_queue<pair<int, int>> pq;
  vector<pair<int, int>> d;

  rep(i, n) {
    int tmp;
    cin >> tmp;

    if (tmp) {
      pq.emplace(tmp, i + 1);
    }
  }

  dbg(pq);

  while (pq.size() >= 2) {
    pair<int, int> a = pq.top();
    pq.pop();
    pair<int, int> b = pq.top();
    pq.pop();

    dbg(a, b, pq);

    a.first--;
    b.first--;

    d.emplace_back(a.second, b.second);

    if (a.first) {
      pq.push(a);
    }

    if (b.first) {
      pq.push(b);
    }
  }

  dbg(pq);
  dbg(d);

  bool flag = pq.empty();

  if (flag) {
    cout << "yes" << '\n';
    for (auto [a, b] : d) {
      cout << a << " " << b << '\n';
    }
  } else {
    cout << "no" << '\n';
  }
}
