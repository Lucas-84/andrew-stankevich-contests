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

const int inf = 1e7;
struct mcmf {
    vi last, curr, seen;
    vi pi;
    vi ne, adj;
    vi flow, cap, cost;
    int n, m;

    mcmf(int n) : n(n), m(0) {
        last = vi(n, -1);
        curr = seen = pi = vi(n);
    }

    int add(int u, int v, int c, int w) {
        adj.pb(v); flow.pb(0); cap.pb(c); cost.pb(+w); ne.pb(last[u]); last[u] = m++;
        adj.pb(u); flow.pb(0); cap.pb(0); cost.pb(-w); ne.pb(last[v]); last[v] = m++;
        return m - 2;
    }

    int dfs(int u, int t, int f) {
        if (u == t) return f;
        if (seen[u]) return 0;
        seen[u] = true;
        for (int e = curr[u]; e != -1; e = ne[e]) {
            int v = adj[e];
            if (flow[e] < cap[e] && pi[u] == pi[v] + cost[e])
                if (int df = dfs(v, t, min(f, cap[e] - flow[e]))) {
                    flow[e] += df;
                    flow[e ^ 1] -= df;
                    return df;
                }
        }
        return 0;
    }

    pii operator () (int s, int t) {
        int answ = 0, ansf = 0;
        pi.assign(n, inf);
        pi[t] = 0;
        bool done;
        do {
            done = true;
            rep(u, n) for (int e = last[u]; e != -1; e = ne[e])
                if (flow[e] < cap[e] && pi[adj[e]] + cost[e] < pi[u]) {
                    pi[u] = pi[adj[e]] + cost[e];
                    done = false;
                }
        } while (!done);
        while (true) {
            seen.assign(n, false);
            copy(all(last), curr.begin());
            while (int df = dfs(s, t, inf)) {
                answ += pi[s] * df;
                ansf += df;
                seen.assign(n, false);
            }
            int inc = inf;
            rep(u, n) if (seen[u]) for (int e = last[u]; e != -1; e = ne[e]) {
                int v = adj[e];
                if (flow[e] < cap[e] && !seen[v]) inc = min(inc, pi[v] + cost[e] - pi[u]);
            }
            if (inc == inf) break;
            rep(u, n) if (seen[u]) pi[u] += inc;
        }
        return mp(answ, ansf);
    }
};

int main() {
    freopen("keeper.in", "r", stdin);
    freopen("keeper.out", "w", stdout);
    int m, n;
    scanf("%d%d", &m, &n);
    vector<vi> adj(m);
    vector<vi> id(m);
    rep(i, m) {
        int k;
        scanf("%d", &k);
        adj[i].resize(k);
        rep(j, k) {
            scanf("%d", &adj[i][j]);
            adj[i][j]--;
        }
    }
    vi init(m);
    int nob = 0;
    rep(i, m) {
        scanf("%d", &init[i]);
        init[i]--;
        if (init[i] != -1) nob++;
    }
    mcmf mcmf(2 + m + n);
    rep(i, m) mcmf.add(0, 1 + i, 1, 0);
    rep(i, n) mcmf.add(1 + m + i, 1 + m + n, 1, 0);
    rep(i, m) for (int v: adj[i]) {
        id[i].pb(mcmf.add(1 + i, 1 + m + v, 1, init[i] != v));
    }
    pii ans = mcmf(0, 1 + m + n);
    printf("%d %d\n", ans.snd, ans.first - (ans.snd - nob));
    rep(i, m) {
        int c = -1;
        rep(j, sz(adj[i])) if (mcmf.flow[id[i][j]]) c = adj[i][j];
        printf("%d ", c + 1);
    }
    puts("");
}
