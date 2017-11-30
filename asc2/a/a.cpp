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

const int none = -2, curr = -1;
const int maxk = 1000;
const int maxn = 60;
char alpha[26];
bool term[maxk];
int adj[26][maxk];
int typeadj[26][maxk];
int nxt[26][maxk];
int k, s, l, n;
vi lseen;

int dfs(int c, int u) {
    if (nxt[c][u] == none) {
        nxt[c][u] = curr;
        if (!typeadj[c][u]) return nxt[c][u] = adj[c][u];
        return nxt[c][u] = dfs(c, adj[c][u]);
    }
    return nxt[c][u];
}

const int maxl = 200;
const int base = 1e9;
struct bigint {
    int d[maxl], len;

    bigint(int x = 0) {
        fill(d, d + maxl, 0);
        len = 1;
        d[0] = x;
    }

    void add(const bigint& rhs) {
        int m = max(len, rhs.len);
        rep(i, m) d[i] += rhs.d[i];
        rep(i, m) d[i + 1] += d[i] / base, d[i] %= base;
        for (len = m; d[len] >= base; ++len) d[len + 1] += d[len] / base, d[len] %= base;
        while (d[len]) len++;
    }

    void out() {
        printf("%d", d[len - 1]);
        repd(i, 0, len - 1) printf("%09d", d[i]);
        puts("");
    }
};

bigint dp[maxn + 1][maxk];

int main() {
    freopen("dfa.in", "r", stdin);
    freopen("dfa.out", "w", stdout);
    scanf("%s", alpha);
    int sigma = strlen(alpha);
    scanf("%d%d%d", &k, &s, &l);
    s--;
    rep(i, l) {
	int u;
	scanf("%d", &u);
	term[u - 1] = true;
    }
    rep(u, k) rep(c, sigma) {
	int v;
	scanf("%d", &v);
	adj[c][u] = v - 1;
    }
    rep(u, k) rep(c, sigma) {
	int t;
	scanf("%d", &t);
	typeadj[c][u] = t;
    }
    rep(c, sigma) rep(u, k) nxt[c][u] = none;
    rep(c, sigma) rep(u, k) dfs(c, u);
    scanf("%d", &n);
    dp[0][s] = bigint(1);
    repu(i, 1, n + 1) rep(u, k) rep(c, sigma) if (nxt[c][u] != curr)
        dp[i][nxt[c][u]].add(dp[i - 1][u]);
    bigint ans(0);
    rep(u, k) if (term[u]) ans.add(dp[n][u]);
    ans.out();
}
