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

const int maxn = 888, maxm = 888;
char grid[maxn][maxm];
const int dirx[4] = {0, 1, 0, -1};
const int diry[4] = {1, 0, -1, 0};
const char *dirc = "NESW";
int dist[maxn][maxm];
int n, m;

bool ingrid(int x, int y) {
    return x >= 0 && x < m && y >= 0 && y < n && grid[y][x] != ' ';
}

int nxtdir(int x, int y, int d) {
    int nd = -2;
    rep(td, 4) {
        int dx = x + dirx[td], dy = y + diry[td];
        if (ingrid(dx, dy) && dist[dy][dx] == dist[y][x] - 1 && nd != d)
            nd = td;
    }
    return nd;
}

int main() {
    freopen("straight.in", "r", stdin);
    freopen("straight.out", "w", stdout);
    scanf("%d%d", &n, &m); n = 2 * n - 1; m = 2 * m - 1;
    rep(i, n) {
        getchar();
        rep(j, m) scanf("%c", &grid[n - i - 1][j]);
    }
    rep(i, n) rep(j, m) dist[i][j] = -1;
    queue<pii> q; q.push({m - 1, n - 1});
    dist[n - 1][m - 1] = 0;
    while (!q.empty()) {
        int x = q.front().fst, y = q.front().snd;
        q.pop();
        rep(d, 4) {
            int dx = x + dirx[d], dy = y + diry[d];
            if (ingrid(dx, dy) && dist[dy][dx] == -1) {
                dist[dy][dx] = dist[y][x] + 1;
                q.push({dx, dy}); 
            }
        }
    }
    /*
    rep(i, n) {
        rep(j, m) printf("%c ", grid[n - i - 1][j]);
        puts("");
    }
    rep(i, n) {
        rep(j, m) printf("%2d ", dist[n - i - 1][j]);
        puts("");
    }
    */
    int x = 0, y = 0, d = -1;
    // init d
    while (x != m - 1 || y != n - 1) {
        //printf("%d %d %d\n", x, y, d);
        if (grid[y][x] == '+') {
            int nd = nxtdir(x, y, d);
            if (x == 0 && y == 0) printf("%c\n", dirc[nd]);
            else if (nd == d) printf("F");
            else if (nd == (d + 1) % 4) printf("R");
            else printf("L");
            d = nd;
        }
        x += dirx[d]; y += diry[d];
        assert(ingrid(x, y));
    }
    puts("");
}
