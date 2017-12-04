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
bool seen[maxn];
vi adj[maxn];
int a[maxn];
int p[maxn];
int n;

bool kuhn(int u) {
    if (seen[u]) return false;
    seen[u] = true;
    for (int v: adj[u]) if (p[v] == -1 || kuhn(p[v])) {
        p[v] = u;
        return true;
    }
    return false;
}

int main() {
    freopen("beloved.in", "r", stdin);
    freopen("beloved.out", "w", stdout);
    scanf("%d", &n);
    vector<pii> order;
    rep(i, n) {
        scanf("%d", &a[i]);
        order.pb({a[i], i});
    }
    rep(i, n) {
        int s;
        scanf("%d", &s);
        adj[i].resize(s);
        rep(j, s) {
            int v;
            scanf("%d", &v);
            adj[i][j] = v - 1;
        }
    }
    fill(p, p + n, -1);
    sort(all(order)); reverse(all(order));
    for (auto it: order) {
        fill(seen, seen + n, false);
        kuhn(it.snd);
    }
    vi ans(n);
    rep(i, n) if (p[i] != -1) ans[p[i]] = i + 1;
    rep(i, n) printf("%d ", ans[i]); puts("");
}
