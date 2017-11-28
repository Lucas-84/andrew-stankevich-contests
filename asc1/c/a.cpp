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

const int maxn = 5e5;
vi adj[maxn];
int dp[maxn][2], how[maxn][2];
int n;

int getdp(int u, int has) {
    int& r = dp[u][has];
    if (r != -1) return r;
    if (has) {
        r = 1;
        for (int v: adj[u]) r += getdp(v, 0);
        return r;
    }
    int s = 0;
    for (int v: adj[u]) s += getdp(v, 0);
    r = s;
    for (int v: adj[u]) {
        int c = s - getdp(v, 0) + getdp(v, 1);
        if (c > r) {
            how[u][has] = v;
            r = c;
        }
    }
    return r;
}

vi ans;

void gethow(int u, int has) {
    if (has) ans.pb(u);
    for (int v: adj[u]) if (v != how[u][has]) gethow(v, 0);
    if (how[u][has] != -1) gethow(how[u][has], 1);
}

int main() {
    freopen("grant.in", "r", stdin);
    freopen("grant.out", "w", stdout);
    scanf("%d", &n);
    FOR(i, n - 1) {
        int u; scanf("%d", &u); u--;
        adj[u].pb(i + 1);
    }
    FOR(i, n) FOR(j, 2) dp[i][j] = how[i][j] = -1;
    getdp(0, 0);
    gethow(0, 0);
    printf("%d\n", 1000 * (int)ans.size());
    sort(ALL(ans));
    for (int x: ans) printf("%d ", x + 1); puts("");
}
