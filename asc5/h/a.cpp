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

const int maxu = 111, maxs = 111;

struct Trans {
    int to, c, d;

    void read() {
        scanf("%d%d%d", &to, &c, &d);
        to--; c--;
    }
} adj[maxu][maxs];

bool seen[maxu][maxs][2];
int n, s;

bool dfs(int u, int c, int b) {
    if (seen[u][c][b]) return false;
    if (u == n - 1) return false;
    seen[u][c][b] = true;
    auto t = adj[u][c];
    if (t.d == -1) return true;
    if (t.d == 0) return dfs(t.to, t.c, b);
    if (b) return dfs(t.to, s - 1, true);
    int ans = 0;
    rep(i, s) ans |= dfs(t.to, i, i == s - 1);
    return ans;
}

int main() {
    freopen("left.in", "r", stdin);
    freopen("left.out", "w", stdout);
    scanf("%d%d", &n, &s);
    rep(u, n - 1) rep(j, s) adj[u][j].read();
    int ans = 0;
    rep(i, s) ans |= dfs(0, i, i == s - 1);
    puts(ans ? "NO" : "YES");
}
