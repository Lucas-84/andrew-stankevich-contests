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

const lli inf = 1ll << 50;
const int maxn = 66, maxm = 66;
pair<lli, int> dp[maxn + 1][maxm + 1];
stack<int> S[maxn];
bool used[maxn];
int N;

int nxtfree(int s, int d) { int i = 0; while (i < N && (used[i] || i == s || i == d)) i++; assert(i < N); return i; }

void solve(int n, int m, int s, int d) {
    if (n == 1) {
        assert(!S[s].empty());
        printf("move %d from %d to %d", S[s].top(), 1 + s, 1 + d);
        if (!S[d].empty()) printf(" atop %d", S[d].top()); 
        puts("");
        S[d].push(S[s].top());
        S[s].pop();
        return;
    }
    int k = dp[n][m].snd;
    int i = nxtfree(s, d);
    solve(k, m, s, i);
    used[i] = true;
    solve(n - k, m - 1, s, d);
    used[i] = false;
    solve(k, m, i, d);
}

int main() {
    freopen("hanoi.in", "r", stdin);
    freopen("hanoi.out", "w", stdout);
    int n, m;
    scanf("%d%d", &n, &m); 
    rep(i, n + 1) rep(j, m + 1) dp[i][j] = {inf, -1};
    repu(j, 2, m + 1) dp[1][j] = {1, -1};
    repu(i, 2, n + 1) repu(j, 1, m + 1) repu(k, 1, i)
        dp[i][j] = min(dp[i][j], mp(2 * dp[k][j].fst + dp[i - k][j - 1].fst, k));
    /*
    repu(i, 0, n + 1) {
        repu(j, 0, m + 1) printf("%lld ", dp[i][j]);
        puts("");
    }
    */
    N = m;
    printf("%lld\n", dp[n][m].fst);
    repd(i, 1, n + 1) S[0].push(i);
    solve(n, m, 0, m - 1);
}
