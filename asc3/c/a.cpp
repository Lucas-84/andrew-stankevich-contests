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

int main() {
    freopen("counter.in", "r", stdin);
    freopen("counter.out", "w", stdout);
    int n;
    scanf("%d", &n);
    vi a(n), b(n);
    int m;
    scanf("%d", &m);
    while (m--) {
        int p;
        scanf("%d", &p);
        rep(i, n) b[i] = a[i];
        b[p]++;
        bool killme = false;
        if (b[p] == 2) {
            repu(i, p + 1, n) {
                if (b[i] == 0) killme = true;
                if (b[i] == 2) break;
            }
        } 
        if (b[p] == 3) {
            b[p + 1]++;
            b[p] %= 2;
        }
        if (killme) {
            b[p] = 0;
            b[p + 1]++;
        }
        repu(i, p + 1, n) if (b[i] == 2) {
            b[i] = 0;
            b[i + 1]++;
            break;
        }
        vector<pii> ans;
        rep(i, n) if (a[i] != b[i]) ans.pb({i, b[i]});
        printf("%d  ", sz(ans));
        for (pii p: ans) printf("%d %d ", p.fst, p.snd);
        puts("");
        rep(i, n) a[i] = b[i];
        rep(i, n) assert(b[i] <= 2);
    }
}
