#include <bits/stdc++.h>
using namespace std;

// dbg
#ifdef LOCAL
  #include "../dbg.h"
#else
  #define dbg(...)
#endif

// typedefs
using ll = long long;
#define LONG_LONGS
#ifdef LONG_LONGS
  #define int ll
const int inf = (int)1e18;
#else
const int inf = int(1e9);
#endif

using vi = vector<int>;
using vvi = vector<vi>;

using p2 = pair<int, int>;
using vp2 = vector<p2>;
using vvp2 = vector<vp2>;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (int i = high - 1; i >= 0; i--)
#define perr(i, high, low) for (int i = high - 1; i >= low; i--)

// Builtins
#define clz(x) __builtin_clz(x)
#define popcount(x) __builtin_popcountll(x)

// Fast I/O
inline void fast() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
}
void readinput() {}  // Recursion base case
template <typename T, typename... Args>
void readinput(T& arg, Args&... args) {
  read(arg);
  readinput(args...);
}
#define dread(type, ...) \
  type __VA_ARGS__;      \
  readinput(__VA_ARGS__);
template <typename T>
istream& operator>>(istream& is, vector<T>& v) {
  repe(u, v) read(u);
  return is;
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

  int m, q;
  cin >> m >> q;

  vi primes(m);
  repe(prime, primes) cin >> prime;

  int maxm = 1;
  repe(prime, primes) {
    if (maxm > 1e7)
      break;
    maxm *= prime;
  }

  dbg(primes);
  dbg(maxm);

  rep(i, q) {
    int qq;
    cin >> qq;
    dbg(qq);

    if (qq >= maxm) {
      cout << "oo\n";
      continue;
    }

    int moves = 0;
    while (qq > 0) {
      moves++;
      int rm = 0;
      per(i, m) {
        if (rm >= primes[i])
          break;
        rm = (rm >= (qq % primes[i]) ? rm : (qq % primes[i]));
      }
      dbg(rm);
      qq -= rm;
    }

    cout << moves << '\n';
  }

  return 0;
}
