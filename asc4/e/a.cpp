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

const int maxn = 2000, maxl = 111;
const int miny = 1870, maxy = 2005;
const int totc = 5;
char name[maxn][maxl + 1];
int dp[maxy + 1][totc + 1][totc];
pair<pii, int> how[maxy + 1][totc + 1][totc];
vector<pair<int, int>> year[maxy];
int cnt[maxy][1 << totc];
int n;

int main() {
    freopen("dvd.in", "r", stdin);
    freopen("dvd.out", "w", stdout);
    scanf("%d", &n);
    rep(i, n) {
        int y, r;
        scanf(" \"%[^\"]\"%d%d", name[i], &y, &r);
        r--;
        year[y].pb({i, r});
    }
    repu(y, miny, maxy) rep(mask, 1 << totc) for (pii movie: year[y]) cnt[y][mask] += ((mask >> movie.snd) & 1);
    /*
    repu(y, miny, maxy) if (!year[y].empty()) {
        printf("%d: ", y);
        rep(mask, 1 << totc) printf("%d ", cnt[y][mask]);
        puts("");
    }
    */
    repu(y, miny, maxy) rep(remc, totc + 1) rep(inc, totc) how[y][remc][inc] = {{-1, -1}, -1};
    repu(y, miny, maxy) rep(remc, totc + 1) rep(inc, totc) rep(mask, 1 << totc) rep(outc, totc) {
        if (!((mask >> inc) & 1)) continue;
        if (!((mask >> outc) & 1)) continue;
        int nbc = __builtin_popcount(mask) - 1;
        if (nbc != 0 && inc == outc) nbc++;
        if (nbc < 0 || nbc > remc) continue;
        if (dp[y][remc][inc] + cnt[y][mask] > dp[y + 1][remc - nbc][outc]) {
            dp[y + 1][remc - nbc][outc] = dp[y][remc][inc] + cnt[y][mask];
            how[y + 1][remc - nbc][outc] = {{remc, inc}, mask};
        }
    }
    vi ans;
    int y = maxy, remc = 0, currc = 0;
    repu(y, miny, maxy) {
        rep(tremc, totc + 1) rep(tcurrc, totc) {
            if (dp[y][tremc][tcurrc] > dp[y][remc][currc]) {
                remc = tremc;
                currc = tcurrc;
            }
        }
    }
    printf("%d\n", dp[y][remc][currc]);
    while (y > miny) {
        int nremc = how[y][remc][currc].fst.fst, ncurrc = how[y][remc][currc].fst.snd;
        int mask = how[y][remc][currc].snd; 
        if (nremc == -1) break;
        vi bits;
        bits.pb(currc);
        if (mask != (1 << currc)) {
            rep(i, totc) if (((mask >> i) & 1) && i != ncurrc && i != currc) bits.pb(i);
            if (currc != ncurrc) bits.pb(ncurrc);
        }
        for (int b: bits) for (pii movie: year[y - 1]) if (movie.snd == b) {
            ans.pb(movie.fst);
        }
        currc = ncurrc; remc = nremc; y--;
    }
    reverse(all(ans));
    for (int x: ans) printf("\"%s\"\n", name[x]);
}
