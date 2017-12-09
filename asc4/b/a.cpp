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

const int maxn = 1e4, maxm = 1e5;
struct Edge { int u, v, is; };
Edge E[maxm];
vi adj[maxn];
int depth[maxn];
int n, m;

int dfs(int u, int p = -1, int d = 0) {
    depth[u] = d; 
    int ans = d;
    for (int e: adj[u]) if (e != p) {
        int v = E[e].u ^ E[e].v ^ u;
        if (depth[v] == -1) {
            int dcurr = dfs(v, e, d + 1);
            E[e].is = dcurr > depth[u];
            ans = min(ans, dcurr);
        } else {
            ans = min(ans, depth[v]);
        }
    }
    return ans;
}

int main() {
    freopen("bridges.in", "r", stdin);
    freopen("bridges.out", "w", stdout);
    scanf("%d%d", &n, &m);
    rep(i, m) {
        scanf("%d%d", &E[i].u, &E[i].v);
        E[i].u--;
        E[i].v--;
        adj[E[i].u].pb(i);
        adj[E[i].v].pb(i);
    }
    fill(depth, depth + n, -1);
    dfs(0);
    vi ans;
    rep(i, m) if (E[i].is) ans.pb(i);
    printf("%d\n", sz(ans));
    for (int x: ans) printf("%d ", 1 + x); puts("");
}
