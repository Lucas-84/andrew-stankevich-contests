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

const int inf = 1e8;
const int maxn = 66;
const int maxm = 444;
int a[maxm + 1][maxm + 1];
int u[maxm + 1], v[maxm + 1];
int l, r;

void hungarian() {
    vi p(r + 1), way(r + 1);
    repu(i, 1, l + 1) {
        p[0] = i;
        int j0 = 0;
        vi minv(r + 1, inf), used(r + 1, false);
        do {
            used[j0] = true;
            int i0 = p[j0], delta = inf, j1;
            repu(j, 1, r + 1) if (!used[j]) {
                int cur = a[i0][j] - u[i0] - v[j];
                if (cur < minv[j]) {
                    minv[j] = cur;
                    way[j] = j0;
                }
                if (minv[j] < delta) {
                    delta = minv[j];
                    j1 = j;
                }
            }
            rep(j, r + 1) {
                if (used[j]) {
                    u[p[j]] += delta;
                    v[j] -= delta;
                } else
                    minv[j] -= delta;
            }
            j0 = j1;
        } while (p[j0] != 0);
        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }
}

struct Edge { int u, v, w; void read() { scanf("%d%d%d", &u, &v, &w); u--; v--; } };
Edge edges[maxm];
vi adj[maxn];
vi lseen;

bool dfs(int u, int s, int p = -1) {
    if (u == s) return true;
    for (int e: adj[u]) {
        int v = edges[e].u ^ edges[e].v ^ u;
        if (v != p && dfs(v, s, u)) {
            lseen.pb(e);
            return true;
        }
    }
    return false;
}

int main() {
    freopen("roads.in", "r", stdin);
    freopen("roads.out", "w", stdout);
    int n, m;
    scanf("%d%d", &n, &m);
    rep(i, n - 1) {
        edges[i].read();
        adj[edges[i].u].pb(i);
        adj[edges[i].v].pb(i);
    }
    l = n - 1;
    r = max(n - 1, m - n + 1);
    repu(i, n - 1, m) {
        edges[i].read();
        lseen.clear();
        dfs(edges[i].u, edges[i].v);
        for (int e: lseen) a[1 + e][i - n + 2] = edges[i].w - edges[e].w;
    }
    hungarian();
    rep(i, n - 1) printf("%d\n", edges[i].w + u[i + 1]); 
    repu(i, n - 1, m) printf("%d\n", edges[i].w - v[i - n + 2]);
}
