#include <bits/stdc++.h>

#define FOR(i, n) for(lli i = 0; i < (lli)(n); ++i)
#define FORU(i, a, b) for(lli i = (lli)(a); i < (lli)(b); ++i)
#define FORD(i, a, b) for(lli i = (lli)(b)-1; i >= (lli)(a); --i)
#define ALL(x) (x).begin(), (x).end()

#define X(A) get<0>(A)
#define Y(A) get<1>(A)
#define Z(A) get<2>(A)
#define W(A) get<3>(A)
#define SZ(a) lli(a.size())

#define mt make_tuple
#define mp make_pair
#define pb push_back
#define fst first
#define snd second



using namespace std;
using lli = long long int;
using ll = lli;
using llu = unsigned long long int;

using pii   = tuple<lli, lli>;
using piii  = tuple<lli, lli, lli>;
using vi    = vector<lli>;
using vii   = vector<pii>;
using viii  = vector<piii>;
using vvi   = vector<vi>;
using vvii  = vector<vii>;
using vviii = vector<viii>;
using vb    = vector<bool>;
using vvb   = vector<vb>;

struct Edge { int to; lli f, c; };
struct Dinic {
    vector<Edge> E;
    vvi adj;
    vi d, w;
    int s, t;

    Dinic(int n, int s, int t) : E(), adj(n), s(s), t(t) {}
    
    int add(int u, int v, lli c) {
        adj[u].pb(E.size()); E.pb({v, 0, c});
        adj[v].pb(E.size()); E.pb({u, 0, 0});
        return E.size() - 2;
    }

    lli dfs(int u, lli f) {
        if (u == t || f == 0) return f;
        for (; w[u] < int(adj[u].size()); ++w[u]) {
            int ide = adj[u][w[u]];
            Edge& e = E[ide];
            if (e.c > e.f && d[e.to] == d[u] + 1)
                if (lli df = dfs(e.to, min(f, e.c - e.f))) {
                    e.f += df;
                    E[ide ^ 1].f -= df;
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
                for (int ide: adj[u]) {
                    Edge e = E[ide];
                    if (e.c > e.f && d[e.to] == -1) {
                        d[e.to] = d[u] + 1;
                        q.push(e.to);
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

int main() {
    freopen("cooling.in", "r", stdin);
    freopen("cooling.out", "w", stdout);
    int n, m; scanf("%d%d", &n, &m);
    Dinic flow(2 + m, 0, 1 + m);
    vi id(m), low(m);
    lli s = 0;
    FOR(i, m) {
        int u, v, l, c; scanf("%d%d%d%d", &u, &v, &l, &c); u--; v--;
        id[i] = flow.add(1 + u, 1 + v, c - l);
        low[i] = l;
        flow.add(1 + u, 1 + m, l);
        flow.add(0, 1 + v, l);
        s += l;
    }
    lli f = flow();
    if (f == s) {
        puts("YES");
        FOR(i, m) printf("%lld\n", low[i] + flow.E[id[i]].f);
    } else
        puts("NO");
}
