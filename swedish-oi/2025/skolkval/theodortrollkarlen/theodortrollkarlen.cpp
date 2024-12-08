#include <bits/stdc++.h>

#ifdef DBG
    #include "../../../../dbg.h"
#else
    #define dbg(...)
#endif

using namespace std;

using ll = long long;

#define rep(i, n) for (int i = 0; i < (n); i++)

constexpr ll MOD = 1e9 + 7;
constexpr int MAXN = 2e5 + 1;

struct MINT {
    ll v;
    MINT() : v(0) {}
    MINT(ll v) : v(v % MOD) {}

    MINT operator+(MINT o) {
        return MINT(o.v + v);
    }


    MINT operator*(MINT o) {
        return MINT(o.v * v);
    }

    MINT operator*=(MINT o) {
        v *= o.v;
        v %= MOD;

        return v;
    }

    MINT operator+=(MINT o) {
        v += o.v;
        v %= MOD;

        return v;
    }

    MINT operator-=(MINT o) {
        v -= o.v;
        if (v < 0) v += MOD;

        return v;
    }
};


auto fac{[]() constexpr{    
    array<ll, MAXN> res{};
    rep(i, MAXN) {
        if (i == 0) {
            res[i] = 1;
        } else {
            res[i] = (res[i - 1] * i) % MOD;
        }
    }
    return res;
}()};


auto inv{[]() constexpr{    
    array<ll, MAXN> res{};
    rep(i, MAXN) {
        if (i < 2) {
            res[i] = 1;
        } else {
            res[i] = (res[MOD % i] * (MOD - MOD / i)) % MOD;
        }
    }
    return res;
}()};


auto invfac{[]() constexpr{    
    array<ll, MAXN> res{};
    rep(i, MAXN) {
        if (i < 2) {
            res[i] = 1;
        } else {
            res[i] = (res[i - 1] * inv[i]) % MOD;
        }
    }
    return res;
}()};


MINT ncr(ll n, ll k) {
    MINT ans = 0;
    if (!(n >= 0 && k >= 0 && n >= k)) {
        ans = 0;
    } else {
        ans = (MINT)fac[n] * (MINT)invfac[k] * (MINT)invfac[n - k];
    }

    dbg(ans);

    return ans;
}


void calcPows(array<MINT, MAXN>& a, MINT p) {
    MINT e = 1;
    rep(i, MAXN) {
        a[i] = e;
        e *= p;
    }
}


array<MINT, MAXN> spow;
array<array< MINT, MAXN>, 2> akpow;


MINT solve(int nn, int kk, int ind) {
    MINT ans = 0;
    rep(i, nn + 1) {
        MINT add = 1;
        add *= akpow[ind][i];
        add *= spow[nn - i];
        add *= ncr(nn, i);
        add *= ncr(kk, nn - i);

        dbg(add);

        ans += add;
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    dbg(fac, inv, invfac);

    ll n, k, s, a;
    cin >> n >> k >> s >> a;

    calcPows(spow, s);
    calcPows(akpow[1], a * k);
    calcPows(akpow[0], a * (k - 1));

    dbg(spow, akpow[0], akpow[1]);



    MINT ans = 0;
    ans += solve(n, k, 1);
    ans -= solve(n, k - 1, 0);

    cout << ans.v << endl;
}

