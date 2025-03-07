#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
    #include "../../../../pp.h"
    #define pp_grid(g) pp::grid(g)
    #
    #include "../../../../dbg.h"
#else
    #define dbg(...)
    #define pp_grid(g)
#endif

// #define int unsigned long long
#define int ull
// #define int ll

// typedefs
using ull = unsigned long long;
using ll = long long;
const int INF = (int)1e18;

using vi = vector<int>;
using vvi = vector<vi>;

using pi = pair<int, int>;
using vpi = vector<pair<int, int>>;

using vb = vector<bool>;
using vvb = vector<vb>;

// time and rng
auto Start = chrono::high_resolution_clock::now();
void resettimer() {
    Start = chrono::high_resolution_clock::now();
}
int elapsedmillis() {
    return chrono::duration_cast<chrono::milliseconds>(
               chrono::high_resolution_clock::now() - Start
    )
        .count();
}
random_device rd;
mt19937 rng(rd());
template <typename T, typename U>
inline int randint(T lo, U hi) {
    return uniform_int_distribution<int>((int)lo, (int)hi)(rng);
}  // [lo,hi]
template <typename T>
inline T randel(vector<T>& v) {
    return v[uniform_int_distribution<int>(int(0), int(v.size()) - int(1))(rng
    )];
}  // [lo,hi]

// pairs
template <typename T, typename U>
inline pair<T, U> operator+(const pair<T, U> l, const pair<T, U> r) {
    return {l.first + r.first, l.second + r.second};
}
template <typename T, typename U>
inline pair<T, U> operator-(const pair<T, U> l, const pair<T, U> r) {
    return {l.first - r.first, l.second - r.second};
}
template <typename T, typename U>
inline pair<T, U> operator*(const pair<T, U> l, const int m) {
    return {l.first * m, l.second * m};
}
template <typename T, typename U>
inline void operator+=(pair<T, U>& l, const pair<T, U>& r) {
    l = l + r;
}
template <typename T, typename U>
inline void operator-=(pair<T, U>& l, const pair<T, U>& r) {
    l = l - r;
}
template <typename T, typename U>
inline void operator*=(pair<T, U>& l, const int m) {
    l = l * m;
}

vector<pi> dir4 = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
vector<pi> dir8 =
    {{-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}};
// vector<pi> dir8 = {{-1, -1}, {-1, 1}, {1, 1}, {1, -1}};
// dir8.insert(dir8.end(), dir4.start(), dir4.end());

// fast io
inline void fast() {
    cin.tie(0)->sync_with_stdio(0);
}

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define per(i, high) for (int i = high - 1; i >= 0; i--)
#define perr(i, low, high) for (int i = high - 1; i >= low; i--)

#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()

#define clz(x) __builtin_clz(x)
#define popcount(x) __builtin_popcountll(x)

#define setcontains(set, x) (set.find(x) != set.end())
#define sz(container) ((int)container.size())
#define beti(a, x, b) (a <= x && x <= b)

template <class T, int N>
struct Vec {
    array<T, N> d{};
    Vec operator+(const Vec& v) const {
        Vec res{};
        for (int i = 0; i < N; i++) {
            res.d[i] = d[i] + v.d[i];
        }
        return res;
    }
};

template <class T, int N>
struct Matrix {
    array<array<T, N>, N> d{};
    Matrix operator*(const Matrix& m) const {
        Matrix a{};
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                for (int k = 0; k < N; k++)
                    a.d[i][j] += d[i][k] * m.d[k][j];
            }
        }
        return a;
    }
    Vec<T, N> operator*(const Vec<T, N>& vec) const {
        Vec<T, N> ret{};
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                ret.d[i] += d[i][j] * vec.d[j];
        return ret;
    }
};

const int V = 10;

struct MatVec {
    Matrix<ull, V> first;
    Vec<ull, V> second;
};

MatVec operator+(MatVec& L, MatVec& R) {
    MatVec res;

    res.first = R.first * L.first;
    res.second = R.first * L.second + R.second;

    return res;
}

struct SegTree {
    int n;
    MatVec ID;
    vector<MatVec> data;

    SegTree(int size) {
        n = 1 << (int)ceil(log2(size));

        rep(i, V) ID.first.d[i][i] = 1;

        data.resize(2*n, ID);
    };

    void set_val(int i, MatVec val) {
        // reorder the data so that the data starts to the left
        // in the resulting seg tree 
        // 
        // |   1   |
        // | 2 | 3 |
        // |4|5| 
        //
        // we place the values like this
        //     | 3 |
        // |1|2| 
        // 
        // instead of 
        //     | 1 |
        // |2|3| 
        // i = (__bit_ceil(n) + i) % n + n;
        i += n;

        data[i] = val;

        for (i /= 2; i > 0; i /= 2)
            data[i] = data[i * 2] + data[i * 2 + 1];
    }
};

MatVec gen_mat(int index) {
    MatVec x;

    rep(i, V) {
        x.first.d[index][i] = 1;
        x.first.d[i][i] = 1;
    }
    x.second.d[index] = 1;

    return x;
}

void test(int i) {
    int n = 3;
    dbg((__bit_ceil(n) + i) % n + n);
}

signed main() {
    fast();

    int n_days, n_changes;
    cin >> n_days >> n_changes;

    vi arr(n_days);
    rep(i, n_days) {
        int color;
        cin >> color;
        arr[i] = color;
    }

    SegTree st(n_days);

    rep(i, n_days) {
        st.set_val(i, gen_mat(arr[i]));
    }

    // she never want to chose the same color twice in a row
    rep(i, n_changes + 1) {
        MatVec res = st.data[1];
        int sum = 0;
        rep(i, V) {
            sum += res.second.d[i];
        }

        cout << sum + 1 << "\n";

        if (i != n_changes) {
            int c_day, c_col;
            cin >> c_day >> c_col;
            c_day--;
            arr[c_day] = c_col;

            st.set_val(c_day, gen_mat(arr[c_day]));
        }
    }
}
