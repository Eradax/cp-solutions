#include <bits/extc++.h>
#include <bits/stdc++.h>
using namespace std;

#pragma Ofast

typedef long long ll;

#define gc() getchar_unlocked()
inline void read(int& v) {
  v = 0;
  char c = gc();
  v += c - '0';
  while ((c = gc()) && c != ' ' && c != '\n') {
    v *= 10;
    v += c - '0';
  }
}

#define pc(x) putchar_unlocked(x)
inline void write(int& v) {
  char dig[20];
  char n = 0;
  while (v) {
    dig[n++] = v % 10;
    v /= 10;
  }
  while (n) {
    pc(dig[--n] + '0');
  }
}
inline void write(ll& v) {
  char dig[20];
  char n = 0;
  while (v) {
    dig[n++] = v % 10;
    v /= 10;
  }
  while (n) {
    pc(dig[--n] + '0');
  }
}

// const int RANDOM =
// chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash {  // To use most bits rather than just the lowest ones:
  const uint64_t C = ll(4e18 * acos(0)) | 71;  // large odd number
  ll operator()(ll x) const { return __builtin_bswap64((x)*C); }
};

__gnu_pbds::gp_hash_table<int, long long, chash>
    elems({}, {}, {}, {}, {1 << 20});

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (int i = high - 1; i >= 0; i--)

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  int n;
  read(n);

  rep(i, n) {
    char c = gc();
    gc();
    int T, K;
    read(T);
    read(K);

    if (c == '1') {
      elems[T] += K;
    } else {
      elems[K] += elems[T];
      elems[T] = 0;
    }
  }

  /*
  int keys[1000000];
  int key = 0;
  repe(i, elems) {
      keys[key] = i.first;
      key++;
  }

  sort(keys, keys+key);

  rep(j, key) {
      int i = keys[j];
      if (elems[i])
          cout << i << " " << elems[i] << "\n";
  }
  */

  vector<pair<int, ll>> vals;
  vals.reserve(1000000);
  repe(i, elems) {
    if (i.second)
      vals.push_back(i);
  }

  sort(vals.begin(), vals.end());

  repe(i, vals) {
    // cout << i.first << " " << i.second << "\n";
    write(i.first);
    pc(' ');
    write(i.second);
    pc('\n');
  }

  return 0;
}
