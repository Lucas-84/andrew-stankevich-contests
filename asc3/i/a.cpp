#include <bits/stdc++.h>
using namespace std;
#define rep(i, n) for (int (i) = 0; (i) < n; ++(i))
#define repu(i, a, b) for (int (i) = (a); (i) < (b); ++(i))
#define repd(i, a, b) for (int (i) = (b) - 1; (i) >= (a); --(i))
#define all(x) (x).begin(), (x).end()
#define sz(x) int((x).size())
#define mp make_pair
#define pb push_back
#define fst first
#define snd second
using lli = long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vlli = vector<lli>;

#define double long double

double simpson(double a, double b, double fa, double fm, double fb) {
    return (fa + 4 * fm + fb) * (b - a) / 6;
}

double integrate_rec(double a, double b, double fa, double fm, double fb, double eps, auto f) {
    double m = (a + b) / 2;
    double fam = f((a + m) / 2), fmb = f((m + b) / 2);
    double l = simpson(a, m, fa, fam, fm), r = simpson(m, b, fm, fmb, fb), tot = simpson(a, b, fa, fm, fb);
    if (fabs(l + r - tot) < eps) return tot;
    return integrate_rec(a, m, fa, fam, fm, eps, f) + integrate_rec(m, b,fm, fmb, fb, eps, f);
}

double integrate(double a, double b, double eps, auto f) {
    return integrate_rec(a, b, f(a), f((a + b) / 2), f(b), eps, f);
}

int main() {
    freopen("twocyl.in", "r", stdin);
    freopen("twocyl.out", "w", stdout);
    double R1, R2;
    scanf("%Lf%Lf", &R1, &R2);
    auto f = [&](double u) {
        return integrate(0, R2, 1e-12, [&](double v) {
            return sqrt(min(R1 * R1 - u * u, R2 * R2 - v * v));
        });
    };
    printf("%.12Lf\n", 8 * integrate(0, R1, 1e-8, f));
    //printf("%.12f %.12f\n", integrate(0, acos(-1), [&](double x) {return sin(x); }), 2.);
}
