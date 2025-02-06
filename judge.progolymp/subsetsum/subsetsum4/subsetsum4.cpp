#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll

const int inf = (int)1e18;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (int i = high - 1; i >= 0; i--)

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

signed main() {
  fast();

  int m, t, sum = 0;
  cin >> m >> t;

  vi vals(m + 1);
  vi sub_vals(m + 1);
  rep(i, m + 1) {
    cin >> vals[i];
    sum += i * vals[i];
  }

  if (sum < t) {
    cout << "NO";
    return 0;
  }

  repp(i, 1, m + 1) {
    if (i * vals[i] < t) {
      t -= i * vals[i];
      sub_vals[i] = vals[i];
      vals[i] = 0;
    } else {
      int sub = t / i;
      t -= i * sub;
      sub_vals[i] = sub;
      vals[i] -= sub;
    }
  }

  int dp_size = 600000;
  vi dp(dp_size, inf);
  dp[dp_size / 2] = 0;

  repp(i, 1, m + 1) {
    if (vals[i] > 0) {
      repp(j, i, dp_size) {
        if (dp[j] > dp[j - i] + 1)
          dp[j] = dp[j - i] + 1;
      }

      rep(j, dp_size) {
        if (dp[j] > vals[i])
          dp[j] = inf;
        else
          dp[j] = 0;
      }
    }
    if (sub_vals[i] > 0) {
      per(j, dp_size - i) {
        if (dp[j] > dp[j + i] + 1)
          dp[j] = dp[j + i] + 1;
      }

      rep(j, dp_size) {
        if (dp[j] > sub_vals[i])
          dp[j] = inf;
        else
          dp[j] = 0;
      }
    }
  }

  cout << ((dp[dp_size / 2 + t] == 0) ? "YES" : "NO");

  return 0;
}
