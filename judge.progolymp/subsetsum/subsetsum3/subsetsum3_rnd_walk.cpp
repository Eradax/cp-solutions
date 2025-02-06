#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

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

  int n, t;
  cin >> n >> t;

  vi vals(n);
  repe(i, vals) cin >> i;

  int sum = 0, index = 0;
  while (index < n && sum + vals[index] <= t) {
    sum += vals[index++];
  }

  rep(i, index) {
    vals[i] *= -1;
  }

  shuffle(all(vals), rng);

  const int bs = 2000;
  bitset<bs> dp;  // unsure of size requirements
  // we should never need to correct more than `D` so perhaps `2*D`.
  dp[bs / 2] = 1;

  repe(i, vals) {
    if (i > 0) {
      dp |= dp << i;
    } else {
      dp |= dp >> -i;
    }
  }

  int correct = 0;
  rep(i, bs / 2) {
    if (i + sum > t)
      break;
    if (dp[i + (int)(bs / 2)])
      correct = i;
  }

  cout << sum + correct;

  return 0;
}
