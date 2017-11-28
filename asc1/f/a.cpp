#include <bits/stdc++.h>

#define FOR(i, n) for(lli i = 0; i < (lli)(n); ++i)
#define FORU(i, a, b) for(lli i = (lli)(a); i < (lli)(b); ++i)
#define FORD(i, a, b) for(lli i = (lli)(b)-1; i >= (lli)(a); --i)
#define ALL(x) (x).begin(), (x).end()

#define X(A) get<0>(A)
#define Y(A) get<1>(A)
#define Z(A) get<2>(A)
#define W(A) get<3>(A)
#define SZ(a) lli(a.size())

#define mt make_tuple
#define mp make_pair
#define pb push_back
#define fst first
#define snd second



using namespace std;
using lli = long long int;
using ll = lli;
using llu = unsigned long long int;

using pii   = tuple<lli, lli>;
using piii  = tuple<lli, lli, lli>;
using vi    = vector<lli>;
using vii   = vector<pii>;
using viii  = vector<piii>;
using vvi   = vector<vi>;
using vvii  = vector<vii>;
using vviii = vector<viii>;
using vb    = vector<bool>;
using vvb   = vector<vb>;

#define double long double
const double eps = 1e-10;
struct pt {
    double x, y;
    pt() {}
    pt(double x, double y) : x(x), y(y) {}
    void read() { scanf("%Lf%Lf", &x, &y); }
    pt operator - (pt a) { return pt(x - a.x, y - a.y); }
    bool operator == (pt a) { return fabs(a.x - x) + fabs(a.y - y) < eps; }
};

double cross(pt a, pt b) { return a.x * b.y - a.y * b.x; }
double dot(pt a, pt b) { return a.x * b.x + a.y * b.y; }
double dist(pt a, pt b) { return sqrt(dot(b - a, b - a)); }

const double pi = acos(-1);
const int maxn = 300;
const int none = 0, curr = 1, done = 2;
vi adj[maxn];
pt centers[maxn];
double radius[maxn];
pt start;
double ang[maxn];
int seen[maxn];

double angle(pt a, pt b) {
    if (a == b) return 0;
    a = a - start; b = b - start;
    return atan2(cross(a, b), dot(a, b));
}

bool dfs(int u, int p = -1, double s = 0) {
    if (seen[u] == done) return false;
    if (seen[u] == curr) return fabs(s - ang[u]) > 2 * pi - eps;
    ang[u] = s;
    int ans = 0;
    seen[u] = curr;
    for (int v: adj[u]) if (v != p) ans |= dfs(v, u, s + angle(centers[u], centers[v]));
    seen[u] = done;
    return ans;
}

int main() {
    freopen("out.in", "r", stdin);
    freopen("out.out", "w", stdout);
    int n; scanf("%d", &n);
    FOR(i, n) {
        centers[i].read();
        scanf("%Lf", &radius[i]);
    }
    start.read();
    double r; scanf("%Lf", &r);
    FOR(i, n) radius[i] += r;
    FOR(i, n) FOR(j, n) if (i != j && dist(centers[i], centers[j]) < radius[i] + radius[j] - eps) adj[i].pb(j);
    int ans = 0;
    FOR(i, n) if (!seen[i]) ans |= dfs(i);
    puts(ans ? "NO" : "YES");
}
