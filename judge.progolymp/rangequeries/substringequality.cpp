#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (int i = high-1; i >= 0; i--)
#define perr(i, high, low) for (int i = high-1; i >= low; i--)

#define clz(x) __builtin_clz(x)
#define popcount(x) __builtin_popcountll(x)

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }


#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
#define setcontains(set, x) (set.find(x) != set.end())
#define sz(container) ((int)container.size())
vector<p2> dirs = { {0,1},{0,-1},{1,0},{-1,0} };

// time and rng
auto Start = chrono::high_resolution_clock::now();
void resettimer() { Start = chrono::high_resolution_clock::now(); }
int elapsedmillis() { return chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - Start).count(); }
random_device rd;
mt19937 rng(rd());
template<typename T, typename U> inline int randint(T lo, U hi) { return uniform_int_distribution<int>((int)lo, (int)hi)(rng); } // [lo,hi]
template<typename T> inline T randel(vector<T>& v) { return v[uniform_int_distribution<int>(int(0), int(v.size()) - int(1))(rng)]; } // [lo,hi]

// dbg
int recur_depth = 0;
// #define dbg(x) {++recur_depth; auto x_=x; --recur_depth; cerr<<string(recur_depth, '\t')<<"\e[91m"<<__func__<<":"<<__LINE__<<"\t"<<#x<<" = "<<x_<<"\e[39m"<<endl;}
#define dbg(x) 

const int N = 1e5;
const int M = 1e9 + 7;
const int P1 = 31;
const int P2 = 127;
const int P3 = 131;
const int P4 = 137;

vvi pows(4, vi(N));
void calc_pows() {
    pows[0][0] = 1;
    pows[1][0] = 1;
    pows[2][0] = 1;
    pows[3][0] = 1;
    repp(i, 1, N) {
        pows[0][i] = pows[0][i-1] * P1 % M;
        pows[1][i] = pows[1][i-1] * P2 % M;
        pows[2][i] = pows[2][i-1] * P3 % M;
        pows[3][i] = pows[3][i-1] * P4 % M;
    }
}

int chash(char c, int i, int P) {
    return ((c - 'a' + 1) * pows[P][i]) % M;
    // return pows[i];
}
struct Chash {
    int h1, h2, h3, h4;

    Chash() : h1(0), h2(0), h3(0), h4(0) {}
    Chash(char c, int i) : h1(chash(c, i, 0)), h2(chash(c, i, 1)), h3(chash(c, i, 2)), h4(chash(c, i, 3)) {}
    Chash(int h1, int h2, int h3, int h4) : h1(h1), h2(h2), h3(h3), h4(h4) {}
    
    Chash operator+(Chash o) {
        return Chash(
            h1 + o.h1 % M,
            h2 + o.h2 % M,
            h3 + o.h3 % M,
            h4 + o.h4 % M
        );
    }

    Chash operator*(int o) {
        return Chash(
            h1 * pows[0][o] % M,
            h2 * pows[1][o] % M,
            h3 * pows[2][o] % M,
            h4 * pows[3][o] % M
        );
    }

    bool operator==(Chash o) {
        return (
            h1 == o.h1 &&
            h2 == o.h2 &&
            h3 == o.h3 &&
            h4 == o.h4
        );
    }
};

typedef Chash T;

T t[2*N];

inline T merge(T a, T b) {
    return a + b;
}

void build() {
    perr(i, N, 1) {
        t[i] = merge(t[2 * i], t[2 * i + 1]);
    }
}

void sset(int p, T v) {
    t[p+=N] = v;
    for (p/=2; p>0; p/=2) {
        t[p] = t[2 * p] + t[2 * p + 1];
    }
}

T query(int l, int r) { // query [l, r)
    T res;
    for (l+=N, r+=N; l < r; l/=2, r/=2) {
        if (l&1) res = merge(res, t[l++]);
        if (r&1) res = merge(res, t[--r]);
    }
    return res;
}



#define gc() getchar_unlocked()
signed main() {
    //fast();
    calc_pows();

    int i = 0;
    char c;
    while ((c = gc()) != '\n') {
        t[N + i] = Chash(c, i);
        i++;
    }
    build();

    rep(j, i) {
        dbg(t[j+N]);
    }

    int q;
    cin >> q;
    rep(i, q) {
        int T;
        cin >> T;
        if (T == 0) {
            int l, r;
            int v, h;
            cin >> l >> r;
            cin >> v >> h;

            Chash h1 = (query(l, r+1) * v);
            Chash h2 = (query(v, h+1) * l);

            dbg(h1);
            dbg(h2);

            //cerr << h1.h1 << " " << h2.h1 << endl;
            cout << ((h1 == h2) ? "Ja" : "Nej") << '\n'; 


        } else {
            int i;
            char c;
            cin >> i >> c;
            sset(i, Chash(c, i));
        }
    }

    return 0;
}
