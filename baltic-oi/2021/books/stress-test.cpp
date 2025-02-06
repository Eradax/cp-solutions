/*
SAMPLE GRADER for task BOOKS

USAGE:
place together with your solution and books.h in the same directory, then:
g++ <flags> sample_grader.cpp <solution_file>
e.g.:
g++ -std=c++17 sample_grader.cpp books.cpp

INPUT/OUTPUT:
The sample grader expects on standard input two lines. The first line should
contain the four integers N, K, A and S. The second line should contain a list
of N integers, the sequence of difficulties x_1 x_2 ... x_N which has to be
strictly increasing. Then, the grader writes to standard output a protocol of
all grader functions called by your program.
At the end, the grader prints your verdict.
*/

#include <bits/stdc++.h>

#include "books.cpp"
#include "brute.cpp"

namespace {
int N, K, S, sUsed;
long long A;
vector<long long> seq;

/*
 * 0 : failed
 * 1 : impossible
 * 2 : possible
 */
int ret = 2;
}  // namespace

void impossible() {
  if (ret != 0)
    ret = 1;
}

long long skim(int pos) {
  if (pos < 1 || pos > N) {
    ret = 0;
    return 0;
  }
  sUsed++;
  if (sUsed > S)
    ret = 0;
  return seq[pos];
}

void answer(vector<int> v) {
  if ((int)v.size() != K)
    ret = 0;
  ll sum = 0;
  for (auto x : v) {
    if (x < 1 || x > N)
      ret = 0;
    sum += seq[x];
  }
  if (sum < A || 2 * A < sum)
    ret = 0;

  if (ret != 0)
    ret = 2;
}

bool validate() {
  if (sUsed != 0) {
    return false;
  }

  if (ret != 2) {
    return false;
  }

  if (3 > N || N > 1e5) {
    return false;
  }

  if (3 > K || 10 < K || K > N) {
    return false;
  }

  if (1 > S || S > 1e5) {
    return false;
  }

  if (1 > A || A > 1e17) {
    return false;
  }

  if (sz(seq) != N + 1) {
    return false;
  }

  ll prev = 0;
  rep(i, N) {
    if (prev >= seq[i + 1]) {
      return false;
    }

    if (1 > seq[i + 1] || seq[i + 1] > 1e17) {
      return false;
    }

    prev = seq[i + 1];
  }

  return true;
}

void clear(int NN, int KK, ll AA, int SS, vl v) {
  N = NN;
  K = KK;
  A = AA;
  S = SS;
  sUsed = 0;
  ret = 2;

  seq = v;
}

bool init(int NN, int KK, ll AA, int SS, vl v) {
  int ansret = 0, solret = 0;

  clear(NN, KK, AA, SS, v);
  if (!validate()) {
    return 1;
  }

  // dbg(N, K, A, S, seq);

  ans::solve(N, K, A, S);

  ansret = ret;

  // dbg(ansret);

  clear(NN, KK, AA, SS, v);
  S = 40;
  if (!validate()) {
    return 1;
  }
  sol::solve(N, K, A, S);

  solret = ret;

  // dbg(solret);

  if (solret != ansret)
    dbg(ansret, solret);

  return ansret == solret;
}

random_device rd;
mt19937 rng(rd());

template <typename R, typename T, typename U>
inline R randint(T lo, U hi) {
  return uniform_int_distribution<R>((R)lo, (R)hi)(rng);
}

const int MAX_N = 170;
const int MAX_K = 170;
const ll MAX_A = 1e17;
const int MAX_S = 170;
const ll MAX_V = 1e17;

int main() {
  int NN, KK, SS;
  ll AA;
  vl vals;

  int iter = 0;

  while (1) {
    if (++iter % 10000 == 0)
      dbg(iter);

    NN = randint<int>(3, MAX_N);
    KK = randint<int>(3, min(NN, MAX_K));
    AA = randint<ll>(1, MAX_A);
    // SS = randint<int>(40, MAX_N);
    SS = NN;

    vals.clear();
    vals.reserve(NN + 1);
    vals.push_back(-1);

    ll prev = 0;
    rep(i, NN) {
      vals.push_back(randint<ll>(prev + 1, MAX_V - (NN - i - 1)));
      prev = vals[i + 1];
    }

    if (!init(NN, KK, AA, SS, vals)) {
      cout << "Found difference:" << endl;
      dbg(N, K, A, S);
      dbg(seq);

      return 0;
    }
  }
}
