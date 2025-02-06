#include <bits/stdc++.h>
#include "books.h"

namespace ans {
vl vals;
int N, K, S;
ll A;

const ll INF = 1e18;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define repp(i, s, n) for (int i = s; i < (n); i++)
#define all(c) c.begin(), c.end()

pair<vi, ll> rec(int i, int prev, ll sum) {
  // dbg(i, sum);
  // dbg(N, K, S, A);

  if (i == K) {
    return {vi(0, -1), sum};
  }

  // dbg(prev, N - (K - i - 1));

  repp(j, prev + 1, N - (K - i - 1)) {
    ll sumtmp = sum;
    sumtmp += vals[j];
    if (sum > 2 * A)
      continue;

    auto tmp = rec(i + 1, j, sumtmp);
    if (A <= tmp.second && tmp.second <= 2 * A) {
      tmp.first.push_back(j);
      return tmp;
    }
  }

  return {vi(K, -1), INF};
}

void solve(int NN, int KK, ll AA, int SS) {
  N = NN;
  K = KK;
  A = AA;
  S = SS;

  vals.resize(N);

  rep(i, N) {
    vals[i] = skim(i + 1);
    S--;
  }

  auto [ans, sum] = rec(0, -1, 0);
  rep(i, K) {
    ans[i]++;
  }

  reverse(all(ans));

  // dbg(ans, sum);

  if (A <= sum && sum <= 2 * A) {
    answer(ans);
  } else {
    impossible();
  }
}
}  // namespace ans
