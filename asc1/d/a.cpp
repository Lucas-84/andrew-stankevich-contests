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

int main() {
    freopen("matrix.in", "r", stdin);
    freopen("matrix.out", "w", stdout);
    int n, m; scanf("%d%d", &n, &m);
    vi deg(n);
    FOR(i, m) {
        int u, v; scanf("%d%d", &u, &v); u--; v--;
        deg[u]++; deg[v]++;
    }
    lli ans = 0;
    FOR(i, n) ans += deg[i] * deg[i];
    printf("%lld\n", ans);
}
