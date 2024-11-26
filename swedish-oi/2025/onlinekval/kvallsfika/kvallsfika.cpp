#pragma GCC optimize("Ofast,inline,unroll-loops")
#pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma,tune=native")

#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int (i)=0; (i)<(n); i++)

#define gc() getchar_unlocked()
inline void read(long long& i) {
    int v=0;
    char c = gc();
    v += c - '0';
    while ((c = gc()) && c != ' ' && c != '\n') {
        v *= 10;
        v += c - '0';
    }
    i+=v;
}

inline void read(int& v) {
    v = 0;
    int sign = 1;
    char c = gc();
    if (c == '-') {
        sign = -1;
    } else {
        v += c - '0';
    }
    while ((c = gc()) && c != ' ' && c != '\n') {
        if (c == EOF) {
            v = -1;
            return;
        }
        v *= 10;
        v += c - '0';
    }
    v *= sign;
}

const int N = 1e5;

int main() {
    int n, p, k;
    read(n);
    read(p);
    read(k);

    long long c[N];
    rep(i, n) {
        c[i]=0;
        read(c[i]);
        c[i]<<=32;
    }

    rep(i, n) {
        read(c[i]);
        c[i]--;
    }

    sort(c, c+n);

    int a = 0;
    int idx = 0;
    int b[N];
    while (p > 0 && idx < n) { 
        long long t = c[idx++];

        
        if ((t>>32) > p) {break;}
        if (b[(int)t]++ >= k) {continue;}

        p -= (t>>32);
        a++;
    }

    printf("%d", a);
}
