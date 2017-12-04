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

const int maxn = 10000;
int idc[maxn], head[maxn];
vi adj[maxn];
vi vnew;
int nbc;
int n, b;

int dfs(int u, int p = -1) {
    int s = 0;
    for (int v: adj[u]) if (v != p) {
        s += dfs(v, u);
        if (s >= b) {
            head[nbc] = u;
            rep(i, s) {
                idc[vnew.back()] = nbc;
                vnew.pop_back();
            }
            s = 0;
            nbc++;
        }
    }
    vnew.pb(u);
    return 1 + s;
}

int main() {
    freopen("royal.in", "r", stdin);
    freopen("royal.out", "w", stdout);
    scanf("%d%d", &n, &b);
    rep(i, n - 1) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--; v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    fill(idc, idc + n, -1);
    dfs(0);
    if (nbc == 0) nbc++;
    printf("%d\n", nbc);  
    rep(i, n) printf("%d ", idc[i] == -1 ? nbc : idc[i] + 1); puts("");
    rep(i, nbc) printf("%d ", head[i] + 1); puts("");
}
