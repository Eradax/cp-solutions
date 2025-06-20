#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

#ifdef DBG
  #define dbg(expr)                                                           \
    if (true) {                                                               \
      cerr << "[" << __FUNCTION__ << "," << __LINE__ << "] " << #expr << ": " \
           << expr << endl;                                                   \
    }
#else
  #define dbg(...)
#endif

using namespace std;

using ll = long long;

const ll MOD = 1e9 + 7;
const ll P = 65537;
const ll Pi = 743534192;

const ll P2 = 102001;
const ll Pi2 = 578749232;

// const ll MOD = 10;
// const ll P = 3;
// const ll Pi = 7;
//
// const ll P2 = 3;
// const ll Pi2 = 7;

inline ll modpow(ll b, int e) {
  e %= MOD;
  ll ans = 1;
  while (e) {
    if (e & 1)
      ans = (ans * b) % MOD;
    b = (b * b) % MOD;
    e /= 2;
  }

  return ans;
}

template <typename T>
ostream& operator<<(ostream& o, vector<T> t) {
  o << "{ ";
  for (auto& i : t)
    o << i << ", ";
  o << "}" << '\n';
  return o;
}

int main() {
  cin.tie(0)->sync_with_stdio();

  int n;
  cin >> n;

  vector<ll> h(n);
  vector<ll> h2(n);
  vector<int> freq('Z' - 'A' + 1);

  string s;
  cin >> s;
  ll Pp = 1;
  ll Pp2 = 1;
  for (int i = 0; i < n; i++) {
    freq[s[i] - 'A']++;
    h[i] = (i ? h[i - 1] : 0) + (s[i] - 'A') * Pp;
    h[i] %= MOD;

    h2[i] = (i ? h2[i - 1] : 0) + (s[i] - 'A') * Pp2;
    h2[i] %= MOD;

    Pp *= P;
    Pp %= MOD;

    Pp2 *= P2;
    Pp2 %= MOD;
  }

  dbg(h);
  dbg(h2);

  int pos = -1;
  {
    int cnt = 0;
    for (int i = 25; i >= 0; i--)
      if (freq[i] % 2)
        pos = i, cnt++;

    if (cnt != 1) {
      cout << "NOT POSSIBLE" << '\n';
      return 0;
    }

    dbg(cnt);
    dbg(pos);
    dbg(char(pos + 'A'));
  }

  assert(pos != -1);

  int cnt = 0;
  int pos2 = -1;

  ll rr1 = -1, rr2 = -1, ll1 = -1, ll2 = -1;

  ll mpd1 = modpow(Pi, n / 2);
  ll mpd2 = modpow(Pi2, n / 2);

  for (int i = 0; i < n; i++) {
    if (s[i] != pos + 'A')
      continue;

    dbg(i);

    ll left = 0, right = 0;
    ll left2 = 0, right2 = 0;
    if (i <= n / 2) {
      dbg("i in left");
      if (i) {
        left += h[i - 1];
        left2 += h2[i - 1];
      }

      ll tmp = (h[n / 2] - h[i]) % MOD;
      if (tmp < 0)
        tmp += MOD;
      left += tmp * Pi;
      left %= MOD;

      ll tmp2 = (h2[n / 2] - h2[i]) % MOD;
      if (tmp2 < 0)
        tmp2 += MOD;
      left2 += tmp2 * Pi2;
      left2 %= MOD;

      ll tmp3 = (h[n - 1] - h[n / 2]) % MOD;
      if (tmp3 < 0)
        tmp3 += MOD;
      right += tmp3 * (mpd1 * Pi % MOD);
      right %= MOD;

      ll tmp4 = (h2[n - 1] - h2[n / 2]) % MOD;
      if (tmp4 < 0)
        tmp4 += MOD;
      right2 += tmp4 * (mpd2 * Pi2 % MOD);
      right2 %= MOD;
    } else {
      dbg("i in right");
      left += h[n / 2 - 1];
      left %= MOD;

      left2 += h2[n / 2 - 1];
      left2 %= MOD;

      ll tmp = (h[i - 1] - h[n / 2 - 1]) % MOD;
      if (tmp < 0)
        tmp += MOD;
      right += tmp * mpd1;
      right %= MOD;

      ll tmp2 = (h2[i - 1] - h2[n / 2 - 1]) % MOD;
      if (tmp2 < 0)
        tmp2 += MOD;
      right2 += tmp2 * mpd2;
      right2 %= MOD;

      dbg(right);

      ll tmp3 = (h[n - 1] - h[i]) % MOD;
      if (tmp3 < 0)
        tmp3 += MOD;
      dbg(tmp3);
      right += tmp3 * (mpd1 * Pi % MOD);
      right %= MOD;

      ll tmp4 = (h2[n - 1] - h2[i]) % MOD;
      if (tmp4 < 0)
        tmp4 += MOD;
      right2 += tmp4 * (mpd2 * Pi2 % MOD);
      right2 %= MOD;
    }

    dbg(left);
    dbg(right);

    dbg(left2);
    dbg(right2);

    if (right == left && right2 == left2) {
      if (rr1 == right && rr2 == right2 && ll1 == left && ll2 == left2) {
      } else {
        cnt++;
        pos2 = i;
        rr1 = right;
        rr2 = right2;
        ll1 = left;
        ll2 = left2;
      }
    }
  }

  dbg(cnt);
  dbg(pos2);

  if (cnt == 0) {
    cout << "NOT POSSIBLE" << '\n';
  } else if (cnt > 1) {
    cout << "NOT UNIQUE" << '\n';
  } else {
    string res;

    if (pos2 >= n / 2) {
      res = s.substr(0, n / 2);
    } else {
      res = s.substr(n / 2 + 1, n / 2);
    }

    cout << res << '\n';
  }
}
