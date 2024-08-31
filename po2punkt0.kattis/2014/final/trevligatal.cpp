#include <bits/stdc++.h>
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
#define per(i, high) for (int i = high-1; i >= 0; i--)
#define perr(i, high, low) for (int i = high-1; i >= low; i--)

#define clz(x) __builtin_clz(x)
#define popcount(x) __builtin_popcountll(x)

inline void fast() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
}



#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define setcontains(set, x) (set.find(x) != set.end())
#define sz(container) ((int)container.size())
vector<p2> dirs = { {0,1},{0,-1},{1,0},{-1,0} };



const int maxN = 1e5;
const int maxM = 3;
 
// To store the states of DP
int dp[maxN + 1][maxM];

const int m = 3;
const int MOD = 1e9;

// Function to find the required count
int findCnt(vi &arr, int n){
    int zcnt = 0;
    rep(i, n) {
        rep(j, 3) dp[i + 1][j] = dp[i][j];
        rep(j, 3) dp[i + 1][(j + arr[i]) % 3] = (dp[i + 1][(j + arr[i]) % 3] + dp[i][j]) % MOD;
        if(arr[i] > 0) {
            dp[i+1][arr[i] % 3] = (dp[i + 1][arr[i] % 3] + 1) % MOD;
        } else {
            zcnt++;
        }
    }
    return (dp[n][0] + zcnt) % MOD;
}
 
//Driver Code
signed main()
{
    string line;
    cin >> line;

    int n = sz(line);
    int zcnt = 0;
    vi a(n);
    rep(i, n) {
        a[i] = (line[i] - '0');
    }

    // Function call
    cout << findCnt(a, n);
 
    return 0;
}
