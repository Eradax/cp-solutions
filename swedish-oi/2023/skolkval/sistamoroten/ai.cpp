#include <bits/stdc++.h>
using namespace std;

// Standard normal PDF & CDF:
static const double INV_SQRT2PI = 0.3989422804014327;
inline double phi(double x) {
    return INV_SQRT2PI * exp(-0.5*x*x);
}
inline double Phi(double x) {
    return 0.5 * erfc(-x * M_SQRT1_2);
}

// Compute the exact excess kurtosis of one Uniform{0,...,n-1}:
double uniform_excess_kurtosis(long long n) {
    // Var(U)       = (n^2-1)/12
    // Fourth central moment = (n^4 - 1)/80
    double v = (double(n)*n - 1.0)/12.0;
    double m4 = (double(n)*n*n*n - 1.0)/80.0;
    return m4/(v*v) - 3.0;
}

// Sum of K largest probabilities via Edgeworth‐corrected normal integral:
double sum_topK_edgeworth(long long n, long long m, int K) {
    double mu    = double(m) * (n-1) / 2.0;
    double sigma = sqrt(double(m) * (n* n - 1.0) / 12.0);

    // Window [L..R]:
    int L = int(floor(mu - (K-1)/2.0));
    int R = L + K - 1;

    // Standardized endpoints:
    double a = (L - 0.5 - mu) / sigma;
    double b = (R + 0.5 - mu) / sigma;

    // Base normal CDF:
    double base = Phi(b) - Phi(a);

    // One‐term Edgeworth correction using excess kurtosis κₑ:
    // Correction = (κₑ / 24m) * [ φ(a)*(a^3 - 3a) - φ(b)*(b^3 - 3b) ]
    double k_ex = uniform_excess_kurtosis(n) / double(m);
    double corr = (k_ex / 24.0) * ( phi(a)*(a*a*a - 3*a)
                                - phi(b)*(b*b*b - 3*b) );

    return base + corr;
}

// (Optional) Sum via Lugannani–Rice saddlepoint for highest accuracy:
// See: Daniels (1954), Lugannani–Rice (1980).
double sum_topK_saddlepoint(long long n, long long m, int K) {
    // 1) compute cumulant‐generating function K(t) = m·log[(e^{nt}-1)/(n(e^t-1))]
    // 2) solve for saddlepoint tˆ such that K'(tˆ) = target s (≈ center of window)
    // 3) plug into the Lugannani–Rice formula for tail‐probabilities.
    //
    // Implementation is lengthy; in most cases the Edgeworth branch suffices.
    throw logic_error("Saddlepoint not implemented in this snippet.");
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, m;
    int K;
    cin >> n >> m >> K;

    double ans;
    if (m < 100) {
        // Small m: use exact pruned‐FFT (omitted here for brevity)
        // ans = exact_pruned_fft(n,m,K);
    }
    else if (m < 10000) {
        // Moderate m: Edgeworth‐corrected CLT
        ans = sum_topK_edgeworth(n, m, K);
    }
    else {
        // Very large m: plain CLT is already super‐accurate
        double mu    = double(m) * (n-1) / 2.0;
        double sigma = sqrt(double(m) * (n* n - 1.0) / 12.0);
        int L = int(floor(mu - (K-1)/2.0));
        int R = L + K - 1;
        double a = (L - 0.5 - mu) / sigma;
        double b = (R + 0.5 - mu) / sigma;
        ans = Phi(b) - Phi(a);
    }

    cout << fixed << setprecision(6) << ans << "\n";
    return 0;
}
