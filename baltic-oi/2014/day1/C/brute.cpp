#include <bits/stdc++.h>

#ifdef DBG
  #define dbg(expr)                                                            \
    if (true) {                                                                \
      cerr << "[" << __FUNCTION__ << ", " << __LINE__ << "] " << #expr << ": " \
           << expr << endl;                                                    \
    }
#else
  #define dbg(...)
#endif

using namespace std;

template <typename T>
ostream& operator<<(ostream& o, vector<T> t) {
  o << "{ ";
  for (auto& i : t)
    o << i << ", ";
  o << "}";
  return o;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int k;
  cin >> k;

  vector<int> b(k);
  for (auto& i : b)
    cin >> i;

  auto check = [&](int s) -> bool {
    vector<int> cnts(10);

    {
      int it = s;
      while (it) {
        cnts[it % 10]++;
        it /= 10;
      }
    }

    dbg(s);
    dbg(cnts);

    for (int i = s; i < s + k; i++) {
      if (!cnts[b[i - s]])
        return 0;

      if (i % 10 == 9) {
        int it = i;
        while (it % 10 == 9) {
          cnts[9]--;
          cnts[0]++;
          it /= 10;
        }
        if (it) {
          cnts[it % 10]--;
          cnts[(it + 1) % 10]++;
        } else {
          cnts[1]++;
        }
      } else {
        cnts[i % 10]--;
        cnts[(i + 1) % 10]++;
      }

      dbg(i);
      dbg(i + 1);
      dbg(cnts);
    }

    return 1;
  };

  int i = 0;
  while (++i) {
    if (check(i)) {
      cout << i << '\n';
      return 0;
    }
  }
}
