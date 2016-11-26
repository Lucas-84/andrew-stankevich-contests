// Maximum flow with edge demands
// Add new source S' and sink T' 
// c(S', u) := sum(l(v, u), v in V)
// c(u, T') := sum(l(u, v), v in V)
// Then feasible flow in G iff. saturating flow in G'
#include <bits/stdc++.h>
using namespace std;
#define mp make_pair
#define pb push_back
#define fst first
#define snd second
#ifndef M_PI
#   define M_PI 3.14159265358979323846
#endif
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;
const int INF = 1000 * 1000 * 1000;
const ll LLINF = 1ll << 53;

const int MAXN = 200;

struct Dinic {
  struct Edge { int u, v; ll cap, flow; };

  vector<int> adj[MAXN];
  vector<Edge> edges;
  int dist[MAXN];
  int idnext[MAXN];
  int n;

  Dinic() {}
  Dinic(int n) : n(n) {}

  int add_edge(int u, int v, ll c) {
    int id = (int)edges.size();
    edges.push_back({u, v, c, 0});
    adj[u].push_back(id);
    edges.push_back({v, u, 0, 0});
    adj[v].push_back(id + 1);
    return id;
  }

  bool bfs(int s, int t) {
    queue<int> q; 
    fill(dist, dist + n, -1);
    dist[s] = 0;
    q.push(s);

    while (!q.empty()) {
      int u = q.front();
      q.pop();

      for (int e: adj[u]) {
        int v = edges[e].v;
        if (dist[v] == -1 && edges[e].flow < edges[e].cap) {
          dist[v] = dist[u] + 1;
          q.push(v);
        }
      }
    }

    return dist[t] != -1;
  }

  int dfs(int u, int t, ll flow) {
    if (flow == 0) return 0;
    if (u == t)    return flow;

    for (; idnext[u] < (int)adj[u].size(); ++idnext[u]) {
      int e = adj[u][idnext[u]];
      int v = edges[e].v;
      if (dist[v] != dist[u] + 1) continue;
      ll pushed = dfs(v, t, min(flow, edges[e].cap - edges[e].flow));
      if (pushed > 0) {
        edges[e].flow += pushed;
        edges[e ^ 1].flow -= pushed;
        return pushed;
      }
    }

    return 0;
  }

  ll maxflow(int s, int t) {
    ll ans = 0;
    while (bfs(s, t)) {
      fill(idnext, idnext + n, 0);
      ll pushed = 0;
      while ((pushed = dfs(s, t, LLINF)) > 0)
        ans += pushed;
    }
    return ans;
  }
};

int main() {
  freopen("cooling.in", "r", stdin);
  freopen("cooling.out", "w", stdout);
  int N, M;
  scanf("%d%d", &N, &M);
  vector<int> id(M), low(M);
  ll D = 0;
  Dinic d(N + 2);
  int Sp = 0, Tp = N + 1;
  for (int i = 0; i < M; ++i) {
    int u, v, upp;
    scanf("%d%d%d%d", &u, &v, &low[i], &upp);
    id[i] = d.add_edge(u, v, upp - low[i]);
    d.add_edge(Sp, v, low[i]);
    d.add_edge(u, Tp, low[i]);
    D += low[i];
  }
  ll flow = d.maxflow(Sp, Tp);
  if (flow == D) {
    puts("YES");
    for (int i = 0; i < M; ++i)
      printf("%lld\n", low[i] + d.edges[id[i]].flow);
  } else {
    puts("NO");
  }
  return 0;
}
