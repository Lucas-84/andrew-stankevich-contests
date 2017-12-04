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

const lli inf = 1ll << 52;
const int maxn = 1500, maxm = 300 * 1000;

lli ans[maxm];
lli cap[maxn][maxn];
lli icap[maxn], ocap[maxn];
int id[maxn][maxn];
bool seen[maxn];
int lev[maxn];
vi nlev[maxn];
int pr[maxn], ne[maxn];
int n, m, l;
int s, t;

int main() {
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
    scanf("%d%d%d", &n, &m, &l);
    vi cnt(l);
    rep(i, n) {
        scanf("%d", &lev[i]);
        lev[i]--;
        if (lev[i] == 0) s = i;
        if (lev[i] == l - 1) t = i;
        nlev[lev[i]].pb(i);
    }
    rep(i, m) {
        int u, v; lli c;
        scanf("%d%d%lld", &u, &v, &c);
        u--;
        v--;
        cap[u][v] = c;
        id[u][v] = i;
        ocap[u] += c;
        icap[v] += c;
        if (u == s && v == t) ans[i] = c;
    }
    seen[s] = seen[t] = true;
    rep(step, n - 2) {
        int ubest = -1;
        lli df = inf;
        rep(u, n) if (!seen[u]) {
            lli curr = min(icap[u], ocap[u]);
            if (curr < df) {
                df = curr;
                ubest = u;
            }
        }
        vector<lli> flow(n);
        flow[ubest] = df;
        seen[ubest] = true;
        repu(i, lev[ubest], l) for (int u: nlev[i]) {
            lli s = flow[u];
            while (s > 0 && ne[u] < n) {
                lli f = min(s, cap[u][ne[u]]);
                s -= f;
                cap[u][ne[u]] -= f; ocap[u] -= f; icap[ne[u]] -= f;
                ans[id[u][ne[u]]] += f;
                flow[ne[u]] += f;
                if (cap[u][ne[u]] == 0)
                    ne[u]++;
            }
        }
        repd(i, 0, lev[ubest] + 1) for (int u: nlev[i]) {
            lli s = flow[u];
            while (s > 0 && pr[u] < n) {
                lli f = min(s, cap[pr[u]][u]);
                s -= f;
                cap[pr[u]][u] -= f; ocap[pr[u]] -= f; icap[u] -= f;
                ans[id[pr[u]][u]] += f;
                flow[pr[u]] += f;
                if (cap[pr[u]][u] == 0)
                    pr[u]++;
            }
        }
    }
    rep(i, m) printf("%lld\n", ans[i]);
}
