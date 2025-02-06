#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
constexpr auto mod = ll(1e9 + 7);

struct Mod {
  ll x;
  Mod() : x(0) {}
  Mod(ll xx) : x(xx) {}
  Mod operator+(Mod b) { return Mod((x + b.x) % mod); }
  Mod operator-(Mod b) { return Mod((x - b.x + mod) % mod); }
  Mod operator*(Mod b) { return Mod((x * b.x) % mod); }

  Mod operator^(ll e) {
    if (!e)
      return Mod(1);
    Mod r = *this ^ (e / 2);
    r = r * r;
    return e & 1 ? *this * r : r;
  }
};

typedef vector<Mod> vll;
typedef vector<vll> vvll;

vvll matMul(vvll A, vvll B) {
  // std::cout << "MatMul 1" << std::endl;
  int rowsA = A.size();
  int colsA = A[0].size();
  // int rowsB = B.size();
  int colsB = B[0].size();

  vvll res(rowsA, vll(colsB));
  for (int i = 0; i < rowsA; i++) {
    // std::cout << "MatMul 2" << std::endl;
    for (int j = 0; j < colsB; j++) {
      // std::cout << "MatMul 3" << std::endl;
      Mod v = 0;
      for (int k = 0; k < colsA; k++) {
        // std::cout << "MatMul 4" << std::endl;
        v = v + A[i][k] * B[k][j];
      }
      res[i][j] = v;
    }
  }
  return res;
}

vvll matPow(vvll A, long long n) {
  if (n == 1) {
    return A;
  } else if (n == 2) {
    return matMul(A, A);
  } else {
    // std::cout << "MatPow" << std::endl;
    vvll t(A);
    n--;
    while (n > 1) {
      if (n & 1) {
        t = matMul(A, t);
      }
      A = matMul(A, A);
      n >>= 1;
    }
    return matMul(A, t);
  }
}

int main() {
  long long n;
  std::cin >> n;

  vvll F = {{0}, {1}, {1}};
  vvll T = {{0, 1, 0}, {1, 1, 1}, {0, 0, 1}};

  vvll nT = matPow(T, n);

  Mod Fn = matMul(nT, F)[0][0];
  std::cout << Fn.x << std::endl;
}