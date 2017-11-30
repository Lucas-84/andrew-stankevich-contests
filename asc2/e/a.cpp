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

const int inf = 2e9;
const int maxn = 1000;
const int maxs = 128;
int levels[maxs][maxs];
int x[maxn];
pair<int, pii> dp[maxn + 1][maxs];
int n, m, s;

int main() {
    freopen("quant.in", "r", stdin);
    freopen("quant.out", "w", stdout);
    scanf("%d", &n);
    rep(i, n) scanf("%d", &x[i]);
    scanf("%d%d", &m, &s);
    rep(i, m) rep(j, s) scanf("%d", &levels[i][j]);
    rep(i, n + 1) rep(j, m) dp[i][j] = {inf, {-1, -1}};
    dp[0][0].fst = 0; 
    rep(i, n) rep(j, m) rep(k, s) {
        int ne = k & (m - 1);
        dp[i + 1][ne] = min(dp[i + 1][ne], mp(dp[i][j].fst + abs(x[i] - levels[j][k]), mp(j, k)));
    }
    pair<int, pii> ans = {inf, {-1, -1}};
    rep(j, m) ans = min(ans, dp[n][j]);
    printf("%d\n", ans.fst);
    vi vans;
    repd(i, 0, n) {
        vans.pb(ans.snd.snd);
        ans = dp[i][ans.snd.fst];
    }
    reverse(all(vans));
    for (int x: vans) printf("%d ", x);
    puts("");
}
