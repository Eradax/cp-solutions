#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int m = 0;

  int n;
  cin >> n;

  rep(i, n) {
    string l;
    int c;
    cin >> l >> c;
    m += c;
  }

  if (m == 0) {
    cout << "Lagom";
  } else if (m > 0) {
    cout << "Usch, vinst";
  } else {
    cout << "Nekad";
  }

  cout << endl;
}
