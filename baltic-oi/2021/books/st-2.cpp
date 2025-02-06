#include <bits/stdc++.h>
#include "books.h"

namespace sol {
/*
Either the answer is K consecutive numbers or
the first K-1 numbers and then the first number >= A
*/
void solve(int N, int K, ll A, int S) {
  vl vals(N);

  rep(i, N) {
    vals[i] = skim(i + 1);
    S--;
  }

  ll sum = 0;
  int l = 0, r = K;
  rep(i, K) {
    sum += vals[i];
  }

  while (r < N) {
    if (A <= sum && sum <= 2 * A) {
      break;
    }

    if (sum < A) {
      sum += vals[r++];
      sum -= vals[l++];
    } else {
      break;
    }
  }

  if (A <= sum && sum <= 2 * A) {
    vi ans(K);
    rep(i, K) {
      ans[i] = l + i + 1;
    }

    answer(ans);
    return;
  } else {
    int i = 0;
    while (i < N && vals[i] < A)
      i++;
    if (K <= i && i < N) {
      ll sum = 0;
      rep(j, K - 1) {
        sum += vals[j];
      }
      sum += vals[i];

      if (A <= sum && sum <= 2 * A) {
        vi ans(K);
        rep(j, K - 1) {
          ans[j] = j + 1;
        }
        ans[K - 1] = i + 1;

        answer(ans);
        return;
      }
    }

    impossible();
  }
}
}  // namespace sol
