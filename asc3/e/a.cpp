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

const int maxn = 400;
vector<pii> adj[maxn];
vi ldist[maxn];

int main() {
    freopen("defence.in", "r", stdin);
    freopen("defence.out", "w", stdout);
    int n, m, s, t;
    scanf("%d%d%d%d", &n, &m, &s, &t);
    s--;
    t--;
    rep(i, m) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--;
        v--;
        adj[u].pb({i, v});
        adj[v].pb({i, u});
    }
    vi seen(m);
    vi dist(n, -1);
    queue<int> q; q.push(s); dist[s] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (u == t) break;
        for (pii ne: adj[u]) {
            int e = ne.fst, v = ne.snd;
            if (!seen[e]) {
                seen[e] = true;
                ldist[dist[u]].pb(e);
            }
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    printf("%d\n", dist[t]);
    rep(i, dist[t]) {
        printf("%d ", sz(ldist[i]));
        for (int e: ldist[i]) printf("%d ", e + 1);
        puts("");
    }
}
