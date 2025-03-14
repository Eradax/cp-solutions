#pragma once

#include <bits/stdc++.h>

// #define DBG
#ifdef DBG
#include "../../../dbg.h"
#else
#define dbg(...)
#endif

using namespace std;

using ll = long long;

using vi = vector<int>;
using vl = vector<ll>;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define sz(c) ((int)c.size())
#define all(c) c.begin(), c.end()

/**
 * skims through the i-th book and returns its difficulty x_i (1 <= i <= N).
 */
long long skim(int);

/**
 * buys your selection of books. This function has to be called with
 * v = {i_1, ..., i_K} (1 <= i_1, ..., i_K <= N) where the i_j's are pairwise
 * distinct and satisfy A <= x_{i_1} + ... + x_{i_K} <= 2 A.
 */
void answer(std::vector<int>);

/**
 * states that it is impossible to buy a set of K books with the desired difficulty.
 */
void impossible();

void solve(int, int, long long, int);
