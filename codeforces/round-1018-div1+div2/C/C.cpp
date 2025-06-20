#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    vector<vector<int>> h(n, vector<int>(n));

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        cin >> h[i][j];
      }
    }

    vector<int> A(n), B(n);
    for (int i = 0; i < n; i++) {
      cin >> A[i];
    }
    for (int i = 0; i < n; i++) {
      cin >> B[i];
    }

    vector<pair<pair<int, int>, pair<int, int>>> blocky(n - 1);

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n - 1; j++) {
        int d = h[i][j + 1] - h[i][j];
        if (d == 0) {
          blocky[j].fi.fi = 1;
          blocky[j].se.se = 1;
        } else if (d == 1) {
          blocky[j].se.fi = 1;
        } else if (d == -1) {
          blocky[j].fi.se = 1;
        }
      }
    }

    vector<pair<pair<int, int>, pair<int, int>>> blockx(n - 1);

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n - 1; j++) {
        int d = h[j + 1][i] - h[j][i];
        if (d == 0) {
          blockx[j].fi.fi = 1;
          blockx[j].se.se = 1;
        } else if (d == 1) {
          blockx[j].se.fi = 1;
        } else if (d == -1) {
          blockx[j].fi.se = 1;
        }
      }
    }

    const long long INF = 1e18;
    vector<pair<long long, long long>> dpy(n, make_pair(INF, INF));
    vector<pair<long long, long long>> dpx(n, make_pair(INF, INF));

    dpy[0].fi = 0;
    dpy[0].se = B[0];
    for (int i = 0; i < n - 1; i++) {
      if (dpy[i].fi < INF) {
        if (!blocky[i].fi.fi) {
          long long c = dpy[i].fi;
          dpy[i + 1].fi = min(dpy[i + 1].fi, c);
        }

        if (!blocky[i].fi.se) {
          long long c = dpy[i].fi + B[i + 1];
          dpy[i + 1].se = min(dpy[i + 1].se, c);
        }
      }

      if (dpy[i].se < INF) {
        if (!blocky[i].se.fi) {
          long long c = dpy[i].se;
          dpy[i + 1].fi = min(dpy[i + 1].fi, c);
        }

        if (!blocky[i].se.se) {
          long long c = dpy[i].se + B[i + 1];
          dpy[i + 1].se = min(dpy[i + 1].se, c);
        }
      }
    }



    dpx[0].fi = 0;
    dpx[0].se = A[0];
    for (int i = 0; i < n - 1; i++) {
      if (dpx[i].fi < INF) {
        if (!blockx[i].fi.fi) {
          long long c = dpx[i].fi;
          dpx[i + 1].fi = min(dpx[i + 1].fi, c);
        }

        if (!blockx[i].fi.se) {
          long long c = dpx[i].fi + A[i + 1];
          dpx[i + 1].se = min(dpx[i + 1].se, c);
        }
      }

      if (dpx[i].se < INF) {
        if (!blockx[i].se.fi) {
          long long c = dpx[i].se;
          dpx[i + 1].fi = min(dpx[i + 1].fi, c);
        }

        if (!blockx[i].se.se) {
          long long c = dpx[i].se + A[i + 1];
          dpx[i + 1].se = min(dpx[i + 1].se, c);
        }
      }
    }

    long long ans = 0;
    ans += min(dpy[n-1].fi, dpy[n-1].se);
    ans += min(dpx[n-1].fi, dpx[n-1].se);
    if (ans >= INF) {
      cout << -1 << '\n';
    } else {
      cout << ans << '\n';
    }
  }
}
