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

const int maxl = 2000;
const int maxs = 256;
const int LEFT = 0, RIGHT = 1, BOTH = 2;
char lambda[maxl + 1], mu[maxl + 1];
int n, m;
char alpha[maxs];
int a[maxl], b[maxl];
lli cost[maxs][maxs];
int best[maxs], tbest[maxs];
lli dp[maxl + 1][maxl + 1];
int how[maxl + 1][maxl + 1];
const lli inf = LLONG_MAX;

void relax(int i, int j, lli v, int h) {
    if (v < dp[i][j]) {
        dp[i][j] = v;
        how[i][j] = h; 
    }
}

int main() {
    freopen("dissim.in", "r", stdin);
    freopen("dissim.out", "w", stdout);
    scanf("%s", alpha); 
    int s = strlen(alpha);
    scanf(" %s %s", lambda, mu);
    n = strlen(lambda), m = strlen(mu);
    rep(i, n) a[i] = strchr(alpha, lambda[i]) - alpha;
    rep(i, m) b[i] = strchr(alpha, mu[i]) - alpha;
    rep(i, s) rep(j, s) scanf("%lld", &cost[i][j]);
    rep(i, s) rep(j, s) if (cost[i][j] < cost[i][best[i]]) best[i] = j;
    rep(i, s) rep(j, s) if (cost[i][j] < cost[tbest[j]][j]) tbest[j] = i;
    rep(i, n + 1) rep(j, m + 1) dp[i][j] = inf;
    dp[0][0] = 0;
    rep(i, n + 1) rep(j, m + 1) if (dp[i][j] != inf) {
        if (i < n && j < m) relax(i + 1, j + 1, dp[i][j] + cost[a[i]][b[j]], BOTH);
        if (i < n) relax(i + 1, j, dp[i][j] + cost[a[i]][best[a[i]]], LEFT);
        if (j < m) relax(i, j + 1, dp[i][j] + cost[tbest[b[j]]][b[j]], RIGHT);
    }
    printf("%lld\n", dp[n][m]);
    vi ansa, ansb;
    int i = n, j = m;
    while (i != 0 || j != 0) {
        if (how[i][j] == BOTH) {
            ansa.pb(a[i - 1]);
            ansb.pb(b[j - 1]);
            i--;
            j--;
        } else if (how[i][j] == LEFT) {
            ansa.pb(a[i - 1]);
            ansb.pb(best[a[i - 1]]);
            i--;
        } else if (how[i][j] == RIGHT) {
            ansa.pb(tbest[b[j - 1]]);
            ansb.pb(b[j - 1]);
            j--;
        } else {
            assert(0);
        }
    }
    reverse(all(ansa)); reverse(all(ansb));
    for (int c: ansa) printf("%c", alpha[c]); puts("");
    for (int c: ansb) printf("%c", alpha[c]); puts("");
}

