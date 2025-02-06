#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int g;
  cin >> g;
  g--;

  int n;
  cin >> n;

  int ball = 1;
  rep(i, n) {
    int a, b;
    cin >> a >> b;
    a--;
    b--;

    if (a == ball) {
      ball = b;
    } else if (b == ball) {
      ball = a;
    }
  }

  int a, b;

  if (g == ball) {
    a = (ball - 1) % 3;
    b = (ball + 1) % 3;
  } else {
    a = ball;
    b = g;
  }

  if (a < 0) a+=3;
  if (b < 0) b+=3;

  cout << a+1 << " " << b+1 << endl;
}
