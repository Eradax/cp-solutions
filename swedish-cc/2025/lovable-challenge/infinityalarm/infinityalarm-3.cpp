#include <bits/stdc++.h>
using namespace std;

const uint32_t P = 16777619;
const uint32_t B = 2166136261;
uint32_t ha(uint32_t v) {
  uint32_t h = B;

  h ^= v & 0xff;
  h *= P;

  h ^= (v >> 8) & 0xff;
  h *= P;

  h ^= (v >> 16) & 0xff;
  h *= P;

  h ^= (v >> 24) & 0xff;
  h *= P;

  return h;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  vector<uint32_t> s(n);
  for (auto& i : s) {
    cin >> i;
    i--;
  }

  uint32_t ans = 0;
  for (int i = 31; i >= 0; i--) {
    uint32_t h = 0;
    for (auto j : s)
      h ^= ha(j & ((1u << i) - 1));

    if (h == 0) {
      ans |= 1u << i;

      s.erase(remove_if(s.begin(), s.end(), [&](const auto& j){
        return ((j >> i) & 1) ^ 1;
      }), s.end());
    }
  }

  cout << ans + 1 << endl;
}
