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
const double eps = 1e-5;
const double pi = acos(-1); 
struct pt {
    double x, y;
    pt() {}
    pt(double x, double y) : x(x), y(y) {}
    pt operator + (pt a) { return pt(x + a.x, y + a.y); }
    pt operator - (pt a) { return pt(x - a.x, y - a.y); }
    pt operator * (double a) { return pt(a * x, a * y); }
    pt operator / (double a) { return pt(x / a, y / a); }
    bool operator < (pt a) const {
        if (fabs(x - a.x) > eps) return x < a.x;
        return y < a.y - eps;
    }
    bool operator == (pt a) const { return fabs(x - a.x) < eps && fabs(y - a.y) < eps; }
    void read() { scanf("%Lf%Lf", &x, &y); }
};

pt rotate(pt p, double a) {
    return pt(p.x * cos(a) - p.y * sin(a), p.x * sin(a) + p.y * cos(a));
}

double dist2(pt a, pt b) {
    double dx = a.x - b.x, dy = a.y - b.y;
    return dx * dx + dy * dy;
}

vector<pt> circle_circle_inter(pt a, pt b, double r, double R) {
    vector<pt> ans;
    double d = sqrt(dist2(a, b));
    if (d > r + R + eps || d + min(r, R) < max(r, R) - eps) return ans;
    double x = (d * d - R * R + r * r) / 2 / d, y = sqrt(fabs(r * r - x * x));
    pt v = (b - a) / d;
    ans.pb(a + v * x + rotate(v, pi / 2) * y);
    if (y > eps) ans.pb(a + v * x - rotate(v, pi / 2) * y);
    return ans;
}

const int maxn = 80;
pt center[maxn];
double radius[maxn];
vi adj[maxn];
bool seen[maxn];
int n;

void dfs(int u) {
    seen[u] = true;
    for (int v: adj[u]) if (!seen[v]) dfs(v);
}

int main() {
    freopen("circles.in", "r", stdin);
    freopen("circles.out", "w", stdout);
    scanf("%d", &n);
    rep(i, n) {
        center[i].read();
        scanf("%Lf", &radius[i]);
    }
    int ans = 0;
    vector<pt> apts;
    rep(i, n) {
        vector<pt> ipts;
        rep(j, n) if (i != j) {
            vector<pt> inter = circle_circle_inter(center[i], center[j], radius[i], radius[j]);
            if (!inter.empty()) adj[i].pb(j);
            apts.insert(apts.end(), all(inter)); 
            ipts.insert(ipts.end(), all(inter)); 
        }
        sort(all(ipts)); ipts.resize(unique(all(ipts)) - ipts.begin());
        ans += sz(ipts);
    }
    sort(all(apts)); apts.resize(unique(all(apts)) - apts.begin());
    ans -= sz(apts);
    rep(u, n) if (!seen[u]) {
        dfs(u);
        ans++;
    }
    printf("%d\n", ans + 1);
}
