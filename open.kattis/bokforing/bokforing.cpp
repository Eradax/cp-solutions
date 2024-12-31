#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  cin >> n >> q;

  vector<int> vals(n), epochs(n);
  int epoch = 0;
  int def = 0;

  rep(i, q) {
    string action;
    cin >> action;

    if (action == "PRINT") {
      int a;
      cin >> a;

      if (epochs[a - 1] == epoch) {
        cout << vals[a - 1] << '\n';
      } else {
        cout << def << '\n';
      }
    } else if (action == "RESTART") {
      epoch++;
      cin >> def;
    } else if (action == "SET") {
      int a, b;
      cin >> a >> b;
      vals[a - 1] = b;
      epochs[a - 1] = epoch;
    }
  }
}
