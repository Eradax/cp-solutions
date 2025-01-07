#include <bits/stdc++.h>

#ifdef DBG
#include "../../../../dbg.h"
#else
#define dbg(...)
#endif

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define set_in(c, a) (c.find(a) != c.end())

int main() {
  int s, e;
  cin >> s >> e;

  unordered_set<string> so;

  rep(i, s) {
    string word;
    cin >> word;
    so.insert(word);
  }

  rep(i, e) {
    string word;
    cin >> word;
    s -= set_in(so, word);
  }

  cout << max(s, 0) << endl;
}
