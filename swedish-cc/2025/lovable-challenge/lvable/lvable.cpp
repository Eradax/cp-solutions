#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0); 

  int n;
  cin >> n;

  string s;
  cin >> s;

  if (s.find("lv") < n)
      cout << 0;
  else if (s.find('l') < n || s.find('v') < n)
      cout << 1;
  else
      cout << 2;
}
