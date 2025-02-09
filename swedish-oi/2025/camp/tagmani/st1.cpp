#include <bits/stdc++.h>

#ifdef DBG
  #include "../../../../dbg.h"
#else
  #define dbg(...)
#endif

using namespace std;

#define rep(i, n) for (int i = 0; i < n; i++)

static constexpr int INF = 1e9;

struct Train {
  int u, v;
  int t, d;
};

int solve(
    int u,
    int current_time,
    int n,
    int k,
    const vector<vector<int>>& scooter_times,
    const vector<Train>& trains,
    vector<vector<int>>& dp
) {
  if (dp[u][current_time] != -1) {
    return dp[u][current_time];
  }

  int max_trains = 0;

  rep(v, n) {
    if (u != v && scooter_times[u][v] != -1) {
      int travel_time = scooter_times[u][v];
      if (current_time + travel_time <= 400) {
        max_trains = max(
            max_trains,
            solve(
                v, current_time + travel_time, n, k, scooter_times, trains, dp
            )
        );
      }
    }
  }

  for (const auto& train : trains) {
    if (train.u == u) {
      if (train.t >= current_time && train.t <= 400) {
        if (train.t + train.d <= 400) {
          max_trains = max(
              max_trains,
              1 + solve(
                      train.v,
                      train.t + train.d,
                      n,
                      k,
                      scooter_times,
                      trains,
                      dp
                  )
          );
        }
      }
    }
  }

  return dp[u][current_time] = max_trains;
}

int main() {
  int n, k;
  cin >> n >> k;

  vector<vector<int>> scooter_times(n, vector<int>(n, -1));
  for (int i = 0; i < n; ++i) {
    scooter_times[i][i] = 0;
  }

  for (int i = 0; i < n - 1; ++i) {
    int u, v, s;
    cin >> u >> v >> s;
    --u;
    --v;
    scooter_times[u][v] = s;
    scooter_times[v][u] = s;
  }

  vector<Train> trains(k);
  for (int i = 0; i < k; ++i) {
    cin >> trains[i].u >> trains[i].v >> trains[i].t >> trains[i].d;
    --trains[i].u;
    --trains[i].v;
  }

  for (int start_station = 0; start_station < n; ++start_station) {
    vector<vector<int>> dp(n, vector<int>(401, -1));
    cout << solve(start_station, 0, n, k, scooter_times, trains, dp)
         << (start_station == n - 1 ? "" : " ");
  }
  cout << endl;
}