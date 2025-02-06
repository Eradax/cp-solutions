#include <bits/stdc++.h>
#include <algorithm>
#include <fstream>
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

int pisinger_main(int n, int t, vi& vals) {
  int a = 0, b = 0, x;
  while (b < sz(vals) && a + vals[b] <= t)
    a += vals[b++];
  if (b == sz(vals))
    return a;
  int m = *max_element(all(vals));
  vi u, v(2 * m, -1);
  v[a + m - t] = b;
  repp(i, b, sz(vals)) {
    u = v;
    repp(x, 0, m) v[x + vals[i]] = max(v[x + vals[i]], u[x]);
    for (x = 2 * m; --x > m;)
      repp(j, u[x] > 0 ? u[x] : 0, v[x])
          v[x - vals[j]] = max(v[x - vals[j]], j);
  }
  for (a = t; v[a + m - t] < 0; a--)
    ;
  return a;
}

int rnd_walk_main(int n, int t, vi& vals) {
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

  return sum + correct;
}

signed main() {
  fast();

  int pisinger = -1;
  int rnd_walk = -1;

  const int N = 1e5;
  vi vals(N);
  int t;
  int i = 0;
  while (pisinger == rnd_walk) {
    i++;
    if ((i % (1 << 8)) == 0)
      cout << "---------- " << i << " ----------\n";
    t = randint(500 * N, 1000 * N);
    rep(i, N) {
      vals[i] = randint(500, 1000);
    }
    pisinger = pisinger_main(N, t, vals);
    rnd_walk = rnd_walk_main(N, t, vals);
  }

  ofstream out;
  out.open("in.txt");
  out << N << " " << t << '\n';
  rep(i, N - 1) out << vals[i];
  out << vals[N - 1] << '\n';
}
