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
double b1, t1, b2, t2, l, ds, df, g;

double get_speed_h(double h, double xw, double xe) {
    return xw * (xe - xw) / h + xe * xe * h / xw / (xe - xw);
}

double get_speed_d(double xw, double xe, double b, double t) {
    double h = xw * (xe - xw) / xe;
    if (h < b) h = b;
    if (h > t) h = t;
    /*
    double low = b, up = t; 
    rep(it, 60) {
        double m1 = low + (up - low) / 3, m2 = up - (up - low) / 3;
        if (get_speed_h(m1, xw, xe) < get_speed_h(m2, xw, xe)) up = m2;
        else low = m1;
    }
    return get_speed_h((low + up) / 2, xw, xe);
    */
    return get_speed_h(h, xw, xe);
}

double get_speed(double d) {
    return max(get_speed_d(ds, ds + d, b1, t1), get_speed_d(l - d, l - d + df, b2, t2));
}

int main() {
    freopen("jumper.in", "r", stdin);
    freopen("jumper.out", "w", stdout);
    while (scanf("%Lf%Lf%Lf%Lf%Lf%Lf%Lf%Lf", &b1, &t1, &b2, &t2, &l, &ds, &df, &g) == 8) {
        double low = 0, up = l;
        rep(it, 60) {
            double m1 = low + (up - low) / 3, m2 = up - (up - low) / 3;
            if (get_speed(m1) < get_speed(m2)) up = m2;
            else low = m1;
        }
        printf("%.9Lf\n", sqrt(g / 2 * get_speed((low + up) / 2)));
    }
}
