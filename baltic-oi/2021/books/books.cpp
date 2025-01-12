#include "books.h"
#include <bits/stdc++.h>

namespace sol {
/*
Either the answer is K consecutive numbers or
the first K-1 numbers and then the first number >= A

if all values are < A, the sum when moving one value can never change by any
value >= A. Therefore the solution can be found by moving from left to right and
taking the smallest value to the largest.
*/

#define setcontains(c, x) (c.find(x) != c.end())

unordered_map<int, ll> q;
ll mskim(int a) {
  a++;

  if (setcontains(q, a)) {
    return q[a];
  }

  return q[a] = skim(a);
}

void solve(int N, int K, ll A, int S) {
  q.clear();

  int f = 0;
  ll sum = 0;

  {
    int lo = 0;
    int hi = N - 1;
    while (lo < hi) {
      int mi = lo + (hi - lo) / 2;

      ll v = mskim(mi);

      if (v < A) {
        lo = mi + 1;
      } else {
        hi = mi;
      }
    }

    if (mskim(lo) >= A) {
      f = lo;
    } else {
      f = N;
    }
  }

  rep(i, K - 1) {
    sum += mskim(i);
  }

  if (f < N) {
    sum += mskim(f);

    if (A <= sum && sum <= 2 * A) {
      vi ans(K);
      rep(i, K - 1) ans[i] = i + 1;
      ans[K - 1] = f + 1;

      answer(ans);
      return;
    }

    sum -= mskim(f);
  }

  sum += mskim(K - 1);

  if (A <= sum && sum <= 2 * A) {
    vi ans(K);
    rep(i, K) ans[i] = i + 1;

    answer(ans);
    return;
  }

  int i = 0;
  while (i < K && f - 1 - i >= K) {
    sum -= mskim(i);
    sum += mskim(f - i - 1);

    if (A <= sum && sum <= 2 * A) {
      vi ans(K);
      rep(j, K - i - 1) { ans[j] = i + 1 + j + 1; }
      rep(j, i + 1) { ans[K - i - 1 + j] = f - i + j; }

      answer(ans);
      return;
    }

    i++;
  }

  impossible();
  return;
}
} // namespace sol
