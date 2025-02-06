#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (int i = high - 1; i >= 0; i--)

#define clz(x) __builtin_clz(x)
#define deb ;
#define popcount(x) __builtin_popcountll(x)

inline void fast() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
}

#ifdef _DEBUG
  #define debassert(expr) \
    if (!(expr))          \
      deb;
#else
  #define debassert(expr) ;
#endif

#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define setcontains(set, x) (set.find(x) != set.end())
#define sz(container) ((int)container.size())

signed main() {
  fast();

  int n;
  cin >> n;

  int sum = 1, ans = 1;
  while (sum <= n) {
    ans++;
    sum += (ans * 2 - 1) * (ans * 2 - 1);
  }
  cout << --ans;
  return 0;
}