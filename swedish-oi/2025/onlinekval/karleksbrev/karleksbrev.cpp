#include <bits/stdc++.h>
#include <random>
#include <string>

#ifdef DBG
    #include "../../../../../dbg.h"
#else
    #define dbg(...)
#endif

using namespace std;

using ld = long double;

using ll = long long;
#define int ll

#define rep(i, n) for (int i = 0; i < (n); i++)
#define repp(i, s, n) for (int i = s; i < (n); i++)
#define perr(i, s, n) for (int i = s-1; i >= (n); i--)

#define sz(c) ((int)c.size())


const int STRLEN = 100;
const int HASHLEN = 50;
const uint64_t HASHMOD = 1ULL << HASHLEN;
const int TOTLEN = STRLEN + HASHLEN;
const uint64_t PRIME = 64124849;

// PRIMEPOWS = {p, p**2 % HASHMOD, p**3 % HASHMOD ...}
array<uint64_t, STRLEN> PRIMEPOWS = []() -> array<uint64_t, STRLEN> {
    array<uint64_t, STRLEN> ret;
    uint64_t hp = PRIME % HASHMOD;
    rep(i, STRLEN) {
        ret[i] = hp;
        hp *= PRIME;
        hp %= HASHMOD;
    }

    return ret;
}();

using bs = bitset<STRLEN>;
using bt = bitset<TOTLEN>;


bt flip(bt& bset, int l, int r) {
    l = max(0LL, min(TOTLEN - 1, l));
    r = max(0LL, min(TOTLEN - 1, r));

    rep(i, TOTLEN) {
        if (l <= i && i <= r) bset.flip(i);
    }
    return bset;
}


string encode(string s) {
    bs bset(s);
    bt ret;

    uint64_t h = 0;
    rep(i, STRLEN) {
        ret[i] = bset[i];
        h += PRIMEPOWS[i] * bset[i];
        h %= HASHMOD;
    }

    rep(i, HASHLEN) {
        ret[STRLEN + i] = h % 2;
        h /= 2;
    }

    return ret.to_string();
}


string decode(string e) {
    bt bset(e);

    uint64_t h = 0;
    rep(i, STRLEN) {
        h += PRIMEPOWS[i] * bset[i];
        h %= HASHMOD;
    }

    uint64_t ch = 0;
    rep(i, HASHLEN) {
        ch += bset[STRLEN + i] * (1ULL << i);
    }


    int l2 = -1;
    int r2 = -1;

    rep(l, TOTLEN) { // Technically we only need to search through [0, STRLEN)
        uint64_t mh, mch;
        mh = h;
        mch = ch;

        repp(r, l, TOTLEN) {
            if (r < STRLEN) {
                mh += (bset[r] ? -1 : 1) * PRIMEPOWS[r];
                if (mh < 0) h += HASHMOD;
                mh %= HASHMOD;
            } else {
                uint64_t pmch = mch;
                if (bset[r]) {
                    mch -= (1ULL << (r - STRLEN));
                } else {
                    mch += 1ULL << (r - STRLEN);
                }
                
                if (bset[r]) {
                    if (!(pmch > mch)) {
                        dbg(pmch, mch, l, r, bset[r]);
                    }

                    assert(pmch > mch);
                } else {
                    if (!(pmch < mch)) {
                        dbg(pmch, mch, l, r, bset[r]);
                    }

                    assert(pmch < mch);
                }
            }

            if (mh == mch) {
                l2 = l;
                r2 = r;
                break;
            }
        }
    }

    if (l2 == -1 || r2 == -1) {
        return "Fuck";
    }

    flip(bset, l2, r2);

    string res = bset.to_string();    
    return res.substr(HASHLEN, STRLEN);
}

random_device rd;
mt19937 rng(rd());
uniform_int_distribution<> dis(0, 1);

string getStr(int l) {
    string str(l, '0');
    rep(i, l) {
        if (dis(rng)) {
            str[i] = '1';
        } else {
            str[i] = '0';
        }
    }

    return str;
}

int randint(int l, int h) {
    uniform_int_distribution<> u(l, h);

    return u(rng);
}

signed main() {
    dbg(TOTLEN, STRLEN, HASHLEN, HASHMOD, PRIME, PRIMEPOWS);

    int total = 0;
    int failed = 0;

    while (total < 1e6) {
        string s = getStr(STRLEN);
        string e = encode(s);

        int l = randint(0, sz(e) - 1);
        int r = randint(l, sz(e) - 1);

        bt be(e);
        be = flip(be, l, r);
        string mode = be.to_string();

        string m = decode(mode);

        if (m != s) {
            failed++;
            dbg("------", s, m, l, r);
        }
        total++;
    }

    dbg(total, failed, ((ld)failed / (ld)total) * 100);
}
