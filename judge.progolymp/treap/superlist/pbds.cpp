#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;

#define sz(c) ((int)c.size())

using pi = pair<long double, int>;
struct comp {
  bool operator()(const pi& a, const pi& b) const { return a.first < b.first; }
};

using ord_set =
    tree<pi, null_type, comp, rb_tree_tag, tree_order_statistics_node_update>;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  ord_set s;

  int q;
  cin >> q;
  while (q--) {
    int t, x, y;
    cin >> t >> x;
    if (t == 0) {
      cin >> y;

      if (s.empty()) {
        s.insert({0.0L, y});
      } else if (x == 0) {
        s.insert({s.find_by_order(0)->first - 1.0L, y});
      } else if (x == sz(s)) {
        s.insert({s.find_by_order(sz(s) - 1)->first + 1.0L, y});
      } else {
        auto l = s.find_by_order(x - 1)->first;
        auto r = s.find_by_order(x)->first;
        s.insert({(l + r) / 2.0L, y});
      }
    } else if (t == 1) {
      s.erase(s.find_by_order(x));
    } else if (t == 2) {
      cout << s.find_by_order(x)->second << '\n';
    }
  }
}
