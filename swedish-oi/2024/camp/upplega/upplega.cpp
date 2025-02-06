#include <bits/stdc++.h>
using namespace std;

// Ints
typedef long long int ll;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<vvll> vvvll;

// Floats
typedef long double ld;
typedef vector<ld> vld;
typedef vector<vld> vvld;
typedef vector<vvld> vvvld;

constexpr ll INF = LLONG_MAX;

istream& operator>>(istream& in, vll& arr) {
  for (ll i = 0; i < arr.size(); i++) {
    ll inp;
    cin >> inp;
    arr[i] = inp;
  }
  return in;
}

int n;
vll lDrop, rDrop, totDrop;
vvvld memo;

vld dp(int i, ld cost, bool isLastSaved) {
  if (i == n) {
    vld ans = {0, 0};
    return ans;
  }
  if (memo[i][isLastSaved][0] != -1) {
    return memo[i][isLastSaved];
  }
  ld save, ignore, saveMoves, ignoreMoves;

  vld tmp;
  tmp = dp(i + 1, cost, false);
  save = tmp[0], saveMoves = tmp[1];
  save += isLastSaved * (totDrop[i] - lDrop[i]) + (1 - isLastSaved) * rDrop[i] +
          totDrop[i + 1] - rDrop[i + 1] - cost;
  saveMoves += 1;

  tmp = dp(i + 1, cost, true);
  ignore = tmp[0], ignoreMoves = tmp[1];

  if (save > ignore) {
    memo[i][isLastSaved] = {save, saveMoves};
  } else {
    memo[i][isLastSaved] = {ignore, ignoreMoves};
  }
  return memo[i][isLastSaved];
}

vvvll getGaps(int n, vll numOfBranches) {
  vvvll gaps(n + 1);

  for (int i = 0; i < n; i++) {
    vll heights(numOfBranches[i]);
    vll lengths(numOfBranches[i]);
    cin >> heights;
    cin >> lengths;

    for (int j = 0; j < numOfBranches[i]; j++) {
      ll height, length;
      height = heights[j], length = lengths[j];
      vll branch = {height, length};
      if (length < 0) {
        gaps[i].push_back(branch);
      } else {
        gaps[i + 1].push_back(branch);
      }
    }
  }
  return gaps;
}

vvll getDrops(vvvll gaps, vll gapsSize) {
  vll lDrop(n + 1, 0);
  vll rDrop(n + 1, 0);
  vll totDrop(n + 1, 0);

  for (int i = 0; i < n + 1; i++) {
    ll lmax = 0, rmax = 0;
    vvll gap = gaps[i];
    sort(gap.begin(), gap.end());

    for (vll branch : gap) {
      ll length = branch[1];
      if (length < 0) {
        length = -length;
        totDrop[i] += length;
        rDrop[i] += min(gapsSize[i] - lmax, length);
        rmax = max(rmax, length);
      } else {
        totDrop[i] += length;
        lDrop[i] += min(gapsSize[i] - rmax, length);
        lmax = max(lmax, length);
      }
    }
  }
  return {lDrop, rDrop, totDrop};
}

int main() {
  // n: number of trees
  // k: number of trees to save
  int k;

  cin >> n >> k;
  vll roots(n);
  cin >> roots;

  vll gapsSize = {roots[0]};
  for (int i = 1; i < n; i++) {
    gapsSize.push_back(roots[i] - roots[i - 1] - 1);
  }
  gapsSize.push_back(INF);

  vll numOfBranches(n);
  cin >> numOfBranches;

  vvvll gaps = getGaps(n, numOfBranches);

  vvll tmp = getDrops(gaps, gapsSize);
  lDrop = tmp[0];
  rDrop = tmp[1];
  totDrop = tmp[2];

  for (int i = 0; i < n; i++) {
    memo.push_back({{-1, -1}, {-1, -1}});
  }

  // Binary search
  ld lo = 0, hi = 1e9;
  for (int i = 0; i < 50; i++) {
    ld mi = lo + (hi - lo) / 2;

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < 2; j++) {
        for (int k = 0; k < 2; k++) {
          memo[i][j][k] = -1;
        }
      }
    }

    vld tmp = dp(0, mi, false);
    ll ansK = ll(tmp[1]);
    if (ansK == k) {
      hi = mi;
      break;
    } else if (ansK > k) {
      lo = mi;
    } else {
      hi = mi;
    }
  }
  cout << ll(round(dp(0, hi, false)[0] + hi * k)) << endl;
}
