#include <bits/stdc++.h>
using namespace std;

// dbg
#ifdef LOCAL
  #include "dbg.h"
#else
  #define dbg(...)
#endif

// typedefs
using ll = long long;
#define int ll
const int inf = int(1e18);

using vi = vector<int>;
using vvi = vector<vi>;
using p2 = pair<int, int>;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (int i = high - 1; i >= 0; i--)
#define perr(i, high, low) for (int i = high - 1; i >= low; i--)

#define clz(x) __builtin_clz(x)
#define popcount(x) __builtin_popcountll(x)

inline void fast() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
}

#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define setcontains(set, x) (set.find(x) != set.end())
#define sz(container) ((int)container.size())
vector<p2> dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

// time and rng
auto Start = chrono::high_resolution_clock::now();
void resettimer() {
  Start = chrono::high_resolution_clock::now();
}
int elapsedmillis() {
  return chrono::duration_cast<chrono::milliseconds>(
             chrono::high_resolution_clock::now() - Start
  )
      .count();
}

random_device rd;
mt19937 rng(rd());
template <typename T, typename U>
inline int randint(T lo, U hi) {
  return uniform_int_distribution<int>((int)lo, (int)hi)(rng);
}  // [lo,hi]

template <typename T>
inline T randel(vector<T>& v) {
  return v[uniform_int_distribution<int>(int(0), int(v.size()) - int(1))(rng)];
}  // [lo,hi]

int dp[10][10][20][2];
string num;

int dpf(int l1, int l2, int idx, bool e = true) {
  if (idx >= sz(num))
    return 1;
  if (dp[l1][l2][idx][e] != -1)
    return dp[l1][l2][idx][e];

  int ans = 0;
  if (e) {
    rep(n, 10) if (n != l1 && n != l2) ans += dpf(l2, n, idx + 1, true);
  } else {
    int limit = num[idx] - '0';

    rep(n, limit) {
      if (n != l1 && n != l2)
        ans += dpf(l2, n, idx + 1, true);
    }

    if (limit != l1 && limit != l2)
      ans += dpf(l2, limit, idx + 1, false);
  }

  dp[l1][l2][idx][e] = ans;
  return dp[l1][l2][idx][e];
}

int solve(int n) {
  if (n < 0)
    return 0;
  dbg(n);
  memset(dp, -1, sizeof(dp));

  num = to_string(n);

  int l1 = num[0] - '0';

  int ans = 1;
  repp(i, 1, l1) {
    ans += dpf(i, i, 1);
  }
  ans += dpf(l1, l1, 1, false);

  dbg(ans);

  repp(len, 2, sz(num) + 1) {
    repp(i, 1, 10) {
      ans += dpf(i, i, len);
    }
  }

  return ans;
}

bool isPalindrome(string s) {
  rep(i, sz(s)) {
    if ((i + 1 < sz(s) && s[i] == s[i + 1]) or
        (i + 2 < sz(s) && s[i] == s[i + 2])) {
      return true;
    }
  }
  return false;
}

signed main() {
  fast();

  int lo, hi;  // [lo, hi]
  cin >> lo >> hi;

  if (hi - lo <= 1e5) {
    int ans = 0;
    repp(i, lo, hi + 1) {
      ans += 1 - isPalindrome(to_string(i));
    }
    cout << ans;
    return 0;
  }

  int hh = solve(hi);
  int ll = solve(lo - 1);

  cout << hh - ll;

  return 0;
}
