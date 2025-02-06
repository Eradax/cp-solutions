#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  rep(i, 3) {
    int v;
    cin >> v;

    if (v > 90) {
      cout << "Trubbig Triangel" << endl;
      return 0;
    } else if (v == 90) {
      cout << "Ratvinklig Triangel" << endl;
      return 0;
    }
  }

  cout << "Spetsig Triangel" << endl;
}
