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

struct pt {
    double x, y;
    pt() {}
    pt(double x, double y) : x(x), y(y) {}
    pt operator - (pt a) { return pt(x - a.x, y - a.y); }
    pt operator + (pt a) { return pt(x + a.x, y + a.y); }
    pt operator * (double a) { return pt(a * x, a * y); }
    void read() { scanf("%Lf%Lf", &x, &y); }
    bool operator == (pt a) const { return fabs(x - a.x) < eps && fabs(y - a.y) < eps; }
    bool operator < (pt a) const {
        if (fabs(x - a.x) > eps) return x < a.x;
        return y < a.y - eps;
    }
    void print() {
        printf("(%Lf, %Lf)\n", x, y);
    }
};

double dot(pt a, pt b) { return a.x * b.x + a.y * b.y; }
double cross(pt a, pt b) { return a.x * b.y - a.y * b.x; }
double angle(pt a, pt b) { return atan2(cross(a, b), dot(a, b)); }

bool dointer(pt a, pt b, pt c, pt d) {
    return fabs(cross(b - a, d - c)) > eps; 
}

double inter(pt a, pt b, pt c, pt d) {
    return cross(d - c, c - a) / cross(d - c, b - a);
}

double area(vector<pt> v) {
    double ans = 0;
    rep(i, sz(v)) ans += cross(v[i], v[(i + 1) % sz(v)]);
    return fabs(ans / 2);
}

const double inf = 1e100;
const int maxm = 81;
pair<pt, pt> lines[maxm];
bool seen[maxm * maxm][maxm * maxm];
vi adj[maxm * maxm];
int n, m;
vector<pt> poly;
vector<pt> lpts;

bool dfs(int u, int p) {
    if (lpts[u] == poly[0]) return true;
    seen[p][u] = true;
    poly.pb(lpts[u]);
    int bestv = -1;
    double besta = inf;
    for (int v: adj[u]) if (v != p && !seen[u][v]) {
        double curra = angle(lpts[p] - lpts[u], lpts[v] - lpts[u]);
        if (cross(lpts[p] - lpts[u], lpts[v] - lpts[u]) > eps && curra < besta) {
            besta = curra;
            bestv = v;
        }
    }
    if (bestv == -1) return false;
    return dfs(bestv, u);
}

int main() {
    freopen("areas.in", "r", stdin);
    freopen("areas.out", "w", stdout);
    scanf("%d", &m);
    rep(i, m) {
        lines[i].fst.read();
        lines[i].snd.read();
    } 
    rep(i, m) rep(j, m) if (i != j) {
        pt a = lines[i].fst, b = lines[i].snd, c = lines[j].fst, d = lines[j].snd;
        if (dointer(a, b, c, d))
            lpts.pb(a + (b - a) * inter(a, b, c, d));
    }
    sort(all(lpts));
    lpts.resize(unique(all(lpts)) - lpts.begin());
    n = sz(lpts);
    rep(i, m) {
        vector<pair<double, int>> v;
        rep(j, m) if (i != j) {
            pt a = lines[i].fst, b = lines[i].snd, c = lines[j].fst, d = lines[j].snd;
            if (dointer(a, b, c, d)) {
                double t = inter(a, b, c, d);
                pt p = a + (b - a) * t;
                v.pb({t, lower_bound(all(lpts), p) - lpts.begin()});
            }
        }
        sort(all(v));
        rep(i, sz(v)) {
            if (i > 0 && v[i].snd != v[i - 1].snd) adj[v[i].snd].pb(v[i - 1].snd); 
            if (i < sz(v) - 1 && v[i].snd != v[i + 1].snd) adj[v[i].snd].pb(v[i + 1].snd); 
        }
    }
    /*
    rep(i, n) {
        printf("%d: %f %f\n", i, lpts[i].x, lpts[i].y);
        printf("adj: ");
        for (int v: adj[i]) printf("%d ", v); puts("");
    }
    */
    vector<double> ans;
    rep(i, n) for (int v: adj[i]) if (!seen[i][v]) {
        poly.clear();
        poly.pb(lpts[i]);
        if (dfs(v, i)) {
            double a = area(poly);
            if (a >= 1e-8) ans.pb(a);
        }
    }
    sort(all(ans));
    printf("%d\n", sz(ans));
    for (auto x: ans) printf("%.12Lf\n", x);
}
