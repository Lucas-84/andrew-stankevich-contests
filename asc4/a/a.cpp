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

struct Edge {
    int from, to;
    lli f, c;
};

struct Dinic {
    vector<Edge> E;
    vector<vi> adj;
    vi d, w;
    int s, t;

    Dinic(int n, int s, int t) : E(), adj(n), s(s), t(t) {}

    void add(int u, int v, lli c) {
        adj[u].pb(sz(E)); E.pb({u, v, 0, c});
        adj[v].pb(sz(E)); E.pb({v, u, 0, 0});
    }
    
    lli dfs(int u, lli f) {
        if (u == t || f == 0) return f;
        for (; w[u] < sz(adj[u]); ++w[u]) {
            int e = adj[u][w[u]];
            Edge& ed = E[e];
            if (ed.c > ed.f && d[ed.to] == d[u] + 1)
                if (lli df = dfs(ed.to, min(f, ed.c - ed.f))) {
                    ed.f += df;
                    E[e ^ 1].f -= df;
                    return df;
                }
        }
        return 0;
    }
    
    lli operator () () {
        lli f = 0;
        int n = adj.size();
        while (true) {
            d.assign(n, -1);
            queue<int> q; q.push(s); d[s] = 0;
            while (!q.empty()) {
                int u = q.front(); q.pop();
                if (u == t) break;
                for (int e: adj[u]) {
                    Edge ed = E[e];
                    if (ed.c > ed.f && d[ed.to] == -1) {
                        d[ed.to] = d[u] + 1;
                        q.push(ed.to);
                    }
                }
            }
            if (d[t] == -1) break;
            w.assign(n, 0);
            while (lli df = dfs(s, 1ll << 62)) f += df;
        }
        return f;
    }
};

const int maxn = 888;
vi adj[maxn], tadj[maxn];
bool seen[maxn];

void dfs(int u, bool rev) {
    if (seen[u]) return;
    seen[u] = true;
    for (int v: (rev ? tadj : adj)[u]) dfs(v, rev);
}

int main() {
    freopen("attack.in", "r", stdin);
    freopen("attack.out", "w", stdout);
    int n, m, s, t;
    scanf("%d%d%d%d", &n, &m, &s, &t);
    s--;
    t--;
    Dinic dinic(n, s, t);
    rep(i, m) {
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        u--;
        v--;
        dinic.add(u, v, c);
        dinic.add(v, u, c);
    }
    lli f = dinic();
    //printf("debug: f = %lld\n", f);
    rep(i, 4 * m) {
        int u = dinic.E[i].from, v = dinic.E[i].to;
        if (dinic.E[i].c > dinic.E[i].f) {
            adj[u].pb(v);
            tadj[v].pb(u);
        }
    }
    /*
    rep(i, n) {
        printf("%d: ", i+1);
        for (int v: adj[i]) printf("%d ", v+1); puts("");
    }
    */
    dfs(s, false); dfs(t, true);
    rep(i, n) if (!seen[i]) {
        puts("AMBIGUOUS");
        return 0;
    }
    puts("UNIQUE");
}
