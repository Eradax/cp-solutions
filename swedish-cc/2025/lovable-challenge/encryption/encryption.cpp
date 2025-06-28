#include <bits/stdc++.h>
using namespace std;

#define sz(c) ((int)c.size())

int main() {
  cin.tie(0)->sync_with_stdio(0); 

  string s, d, lcs;
  cin >> s >> d >> lcs;

  int i = 0;
  int j = 0;
  int k = 0;

  string res;

  while (i < sz(s) || j < sz(d)) {
    if (i >= sz(s)) {
      res += d[j];
      j++;
      continue;
    }

    if (j >= sz(d)) {
      res += s[i];
      i++;
      continue;
    }

    if (k >= sz(lcs)) {
      res += s[i];
      i++;
      continue;
    }

    if (lcs[k] == s[i] && lcs[k] == d[j]) {
      res += lcs[k];
      k++;
      i++;
      j++;
      continue;
    }

    if (lcs[k] == s[i]) {
      res += d[j];
      j++;
      continue;
    }

    res += s[i];
    i++;
  }

  cout << res;
}
