#include <bits/stdc++.h>
#include <deque>

using namespace std;

using vi = vector<int>;

#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, x;
  cin >> n >> x;

  queue<int> oats;

  rep(i, n) {
    string line;
    cin >> line;

    if (line == "ADD") {
      oats.push(i);
    } else if (line == "EAT") {
      int l = oats.front();
      oats.pop();

      if (i - l > x) {
        cout << "ono.." << endl;
        return 0;
      }
    }else if (line == "PASS") {

    }
  }

  cout << "yay!" << endl;
}
