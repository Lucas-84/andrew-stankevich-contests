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
const double eps = 1e-8;
const double pi = acosl(-1);

struct pt {
    lli x, y;
    pt() {}
    pt(lli x, lli y) : x(x), y(y) {}
    void read() { scanf("%lld%lld", &x, &y); }
    pt operator - (pt a) { return pt(x - a.x, y - a.y); }
};

double inv(double a) {
    if (fabsl(a) < eps) return 0;
    return 2 * pi - a;
}

int main() {
    freopen("angle.in", "r", stdin);
    freopen("angle.out", "w", stdout);
    int n;
    int t = 0;
    while (scanf("%d", &n) == 1 && n) {
        if (t++ != 0) puts("");
        vector<pt> pts(n);
        rep(i, n) pts[i].read();
        double a = 0;
        rep(i, n - 1) {
            pt d = pts[i + 1] - pts[i];
            a += atan2(d.y, d.x) / (n - 1);
        }
        while (a > 2 * pi) a -= 2 * pi;
        while (a < 0) a += 2 * pi;
        a = inv(a);
        assert(a >= -eps);
        printf("%.12Lf\n%.12Lf\n", 0.L, a);
        rep(i, n) {
            pt t = pts[i];
            printf("%.12Lf %.12Lf\n", t.x * cosl(a) - t.y * sinl(a), t.x * sinl(a) + t.y * cosl(a));
        }
    }
}
