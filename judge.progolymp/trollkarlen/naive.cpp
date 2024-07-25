#include <iostream>
using namespace std;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (int i = high-1; i >= 0; i--)

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }
int elems[1000000000];
int main() {
    fast();
    int n;
    cin >> n;

    rep(i, n) {
        int opt, T, K;
        cin >> opt >> T >> K;

        if (opt == 1) {
            elems[T-1] += K;
        } else {
            elems[K-1] += elems[T-1];
            elems[T-1] = 0;
        }
    }

    rep(i, 1000000000) {
        int elem = elems[i];
        if (elem != 0) {
            cout << i+1 << " " << elem << "\n";
        }
    }

    return 0;
}