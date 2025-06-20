#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <tuple>
#include <limits> // Required for numeric_limits

// Using standard types is generally better unless specific reasons dictate otherwise.
// For competitive programming, people often use short aliases.
using namespace std;

// Type aliases
using ll = long long;
using ull = unsigned long long;
// Use unsigned long long for penalty if it can exceed 2^32-1.
// Max penalty can be ~ 2 * T / min_item_val. If T=10^9, min=1, penalty ~ 2*10^9 -> fits unsigned int.
// If T can be much larger, unsigned long long might be needed. Let's use unsigned int for now.
using ui = unsigned int; // penalty type

// Pair: {value, index_with_flag}
// Assuming item values fit in int based on typical constraints (e.g., <= 10^9).
// If item values can exceed INT_MAX, change first element to long long.
using piui = pair<int, ui>;
using vui = vector<ui>;
using vi = vector<int>;
using vpiui = vector<piui>;

// Use a large enough INF value for penalty type ui.
// Use half of max value to allow addition without immediate overflow.
static constexpr ui INF = numeric_limits<ui>::max() / 2;

// Macros for loops (optional, standard loops are fine)
#define repp(i, s, n) for (int i = s; i < n; i++)
#define rep(i, n) repp(i, 0, n)
#define all(c) c.begin(), c.end()

// Debug macro setup (conditional compilation)
#ifdef DBG
  #include "../../../../dbg.h" // Adjust path as needed for local debugging
#else
  #define dbg(...) // Empty definition when not debugging
#endif


int main() {
  // Faster I/O
  cin.tie(0)->sync_with_stdio(0);

  int n;
  ll t; // Target value can be large, use long long.
  cin >> n >> t;
  dbg(n, t); // Debug output for n and t

  // Vector to store items: {value, original_index | derived_flag}
  vpiui v(2 * n);
  int max_v_first = 0; // Track maximum item value for DP array sizing

  // Constants for bit manipulation
  const ui DERIVED_FLAG = (1U << 31); // Use unsigned literal for the flag bit (MSB)
  const ui INDEX_MASK = DERIVED_FLAG - 1; // Mask to extract the original index (lower 31 bits)

  for (int i = 0; i < n; ++i) {
    int base_val;
    cin >> base_val;
    // Basic validation: Assume positive base_val based on typical problems.
    // If base_val can be <= 0, specific handling might be needed.
    if (base_val <= 0) {
         // Handle non-positive input if required by problem rules.
         // For now, we store it; the DP loop skips non-positive items.
    }

    // Store base item
    v[2 * i].first = base_val;
    v[2 * i].second = (ui)i; // Index i, flag bit is 0

    // Calculate and store derived item
    ll derived_val_ll = (3LL * base_val) / 2; // Use long long for intermediate calculation
    // Check if derived value fits in int. Assume it does.
    if (derived_val_ll > numeric_limits<int>::max()) {
        cerr << "Warning: Derived value exceeds integer limits for item " << i << endl;
        // Consider changing v[].first to long long if necessary.
    }
    v[2 * i + 1].first = (int)derived_val_ll;
    v[2 * i + 1].second = DERIVED_FLAG | (ui)i; // Index i, flag bit is 1

    // Update maximum item value seen (only consider positive values)
    if (v[2*i].first > 0) max_v_first = max(max_v_first, v[2*i].first);
    if (v[2*i+1].first > 0) max_v_first = max(max_v_first, v[2*i+1].first);
  }
  dbg(v); // Debug output for the item vector

  // Sort items primarily by value. Helps ensure deterministic reconstruction if multiple items work.
  sort(all(v));
  dbg(v); // Debug output after sorting

  // Handle t <= 0 edge case: Goal is >= t. If t<=0, goal is >=0.
  // The optimal solution is value 0 with penalty 0 (using no items).
  if (t <= 0) {
       cout << 0 << " " << 0 << '\n';
       vi ans(n, 0); // Create result vector of zeros
       rep(i, n) cout << ans[i] << (i == n - 1 ? "" : " "); // Print zero contributions
       cout << '\n';
       return 0;
  }

  // Determine DP array size. Need states up to index t + max_v_first - 1.
  // Size should be t + max_v_first.
  size_t max_k; // Use size_t for array size and indices
  ll max_k_ll = t + max_v_first; // Calculate max value needed using long long

  // Check for potential overflow or unreasonable size
  if (t < 0 || max_v_first < 0 || max_k_ll < t || (unsigned ll)max_k_ll >= numeric_limits<size_t>::max() / sizeof(ui) ) { // Check against memory limits or size_t max
      cerr << "Error: DP state space calculation results in overflow or excessive size." << endl;
       // Output default/error state as required by problem (e.g., 0 0)
       cout << 0 << " " << 0 << '\n';
       vi ans(n, 0);
       rep(i, n) cout << ans[i] << (i == n - 1 ? "" : " "); cout << '\n';
      return 1; // Indicate error
  }
  // Set DP array size. It needs to cover indices from 0 up to max_k_ll - 1.
  max_k = (size_t)max_k_ll;
  if (max_k == 0) max_k = 1; // Ensure size is at least 1


  // Allocate DP array `w`, initialized with INF penalty.
  // w[k] stores the minimum penalty to achieve exactly value k.
  vui w(max_k, INF);
  w[0] = 0; // Base case: value 0 requires 0 penalty.

  // DP calculation: Unbounded Knapsack variation
  // Iterate through each item type (base and derived)
  rep(i, 2 * n) {
    int item_val = v[i].first;
    // Skip items with non-positive value as they don't contribute positively or cause issues.
    if (item_val <= 0) continue;

    // Ensure item value can be cast safely to size_t for indexing.
    size_t item_val_sz = (size_t)item_val;

    // Determine penalty for this item: 1 for base (flag=0), 2 for derived (flag=1)
    ui item_penalty_contrib = 1 + ((v[i].second & DERIVED_FLAG) ? 1 : 0);

    // Update DP states. Iterate `k` from `item_val` up to `max_k - 1`.
    // For each `k`, check if we can reach it with lower penalty via `k - item_val`.
    for (size_t k = item_val_sz; k < max_k; ++k) {
        size_t prev_k = k - item_val_sz;
        // If the previous state `w[prev_k]` is reachable (not INF)
        if (w[prev_k] != INF) {
            // Check for potential penalty overflow before adding
             if (w[prev_k] <= INF - item_penalty_contrib) {
                 // Update w[k] if the path through prev_k is better
                 w[k] = min(w[k], w[prev_k] + item_penalty_contrib);
             }
             // If adding would overflow INF, w[k] remains unchanged or keeps its current INF value, which is correct.
        }
    }
  }
  // Optional: dbg(w); // Debug the DP table (can be very large)

  // Find the best result: minimum value k >= t with minimum penalty.
  ll best_val = -1; // Initialize best value found to -1 (not found)
  ui min_penalty = INF; // Initialize minimum penalty found to INF

  // Step 1: Find the minimum penalty among all reachable states k >= t.
  size_t start_k = (size_t)t; // Start searching from target t
  // Ensure start_k is within the bounds of the DP table
  if (start_k >= max_k) {
      // Target t is beyond the calculated DP range, implies unreachable.
      min_penalty = INF; // Keep min_penalty as INF
  } else {
      // Iterate from t up to the maximum calculated state
      for (size_t k = start_k; k < max_k; ++k) {
          if (w[k] != INF) { // If state k is reachable
              min_penalty = min(min_penalty, w[k]); // Update minimum penalty found
          }
      }
  }
  dbg(min_penalty); // Debug the minimum penalty found

  // Step 2: Find the smallest value k >= t that achieves this minimum penalty.
  if (min_penalty != INF) { // If any state >= t was reachable
      for (size_t k = start_k; k < max_k; ++k) {
          if (w[k] == min_penalty) { // Found a state k with the minimum penalty
              best_val = (ll)k; // Store this k as the best value
              break; // Stop searching, as we want the *smallest* k
          }
      }
  }
  dbg(best_val); // Debug the best value found

  // Output the final result (best value >= t and its minimum penalty)
  if (best_val == -1) {
      // Target t is unreachable or no solution found within calculated range.
      // Output 0 0 as per typical contest problem behavior for unreachable states.
      cout << 0 << " " << 0 << '\n';
      vi ans(n, 0); // Output contribution vector of zeros
      rep(i, n) cout << ans[i] << (i == n - 1 ? "" : " ");
      cout << '\n';
      return 0; // Exit
  }

  // Output the best value and minimum penalty found
  cout << best_val << " " << min_penalty << '\n';

  // Path reconstruction: Determine which items were used to achieve best_val with min_penalty.
  vi ans(n, 0); // Stores total value contributed by each original item index i
  ll current_val_ll = best_val; // Start backtracking from the best value found

  // Backtrack until value becomes 0
  while (current_val_ll > 0) {
      bool found_prev = false; // Flag to check if a valid previous step was found

      // Ensure current value is a valid index before accessing w[]
      if (current_val_ll < 0 || (unsigned ll)current_val_ll >= max_k) {
          cerr << "Reconstruction error: current value " << current_val_ll << " out of bounds [0, " << max_k << ")" << endl;
          break; // Abort reconstruction if state is invalid
      }
      size_t current_val_idx = (size_t)current_val_ll;

      // Iterate through all possible items (ip = 0 to 2n-1)
      // The order matters for reproducibility if multiple items satisfy the condition.
      // Iterating 0 to 2n-1 uses the sorted order (typically smallest value first).
      rep(ip, 2 * n) {
          int item_val = v[ip].first;
          // Skip invalid items (non-positive value)
          if (item_val <= 0) continue;

          // Calculate penalty contribution and original index for this item
          ui item_penalty_contrib = 1 + ((v[ip].second & DERIVED_FLAG) ? 1 : 0);
          ui original_idx = v[ip].second & INDEX_MASK;

          // Basic check on original index validity (paranoid check)
          if (original_idx >= (ui)n) {
              cerr << "Reconstruction error: invalid original index " << original_idx << endl;
              continue; // Skip this potentially corrupted item data
          }

          // Check if current state could have been reached from a previous state using this item
          if (current_val_ll >= item_val) { // Ensure prev_val is non-negative
              ll prev_val_ll = current_val_ll - item_val;
              // Ensure previous value is a valid index
               if (prev_val_ll < 0 || (unsigned ll)prev_val_ll >= max_k) continue; // Skip if prev index out of bounds
              size_t prev_val_idx = (size_t)prev_val_ll;

              // Check if the previous state was reachable
              if (w[prev_val_idx] != INF) {
                 // Verify the DP transition condition: w[current] == w[previous] + penalty(item)
                 // Check for potential underflow if w[current] < penalty (should not happen on valid path)
                 if (w[current_val_idx] >= item_penalty_contrib && w[current_val_idx] == w[prev_val_idx] + item_penalty_contrib) {
                    // Found the item `ip` used in the last step to reach `current_val`.
                    ans[original_idx] += item_val; // Add item's value to the total for its original index
                    current_val_ll = prev_val_ll; // Move to the previous state value
                    found_prev = true; // Mark that we successfully backtracked one step
                    dbg("Recon step: used item", ip, "val", item_val, "orig_idx", original_idx, "new_val", current_val_ll);
                    break; // Stop checking other items for this step; move to reconstruct the previous state.
                 }
              }
          }
      }
      // Safety check: If no valid previous step was found, the DP table or logic might be inconsistent.
      if (!found_prev) {
          cerr << "Error during path reconstruction at value " << current_val_ll << ". Could not find valid previous state." << endl;
          break; // Abort reconstruction
      }
  }
  dbg(ans); // Debug the final contribution vector

  // Output the total values contributed by each original item index
  rep(i, n) {
      cout << ans[i] << (i == n - 1 ? "" : " "); // Print space-separated values
  }
  cout << '\n'; // Print newline at the end

  return 0; // Indicate successful execution
}
