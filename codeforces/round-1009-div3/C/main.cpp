#include <bits/stdc++.h>

using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    int x;
    cin >> x;

    int l = __bit_width(x);

    int y = 0;

    for (int i = 0; i <= l; i++) {
      if (((x >> i)&1) == 0){
        y += 1 << i;
        break;
      }
    }

    for (int i = 0; i <= l; i++) {
      if ((x >> i) & 1) {
        y += 1 << i;
        break;
      } 
    }

    if (!(x + y > (x^y) && x + (x^y) > y && y + (x^y) > x && (y < x)))
      y = -1;

    cout << y << '\n';
  }
}
