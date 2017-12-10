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

const int maxn = 13;

vi comp(vi v) {
    vi ans(sz(v));
    rep(i, sz(v)) ans[i] = 1 - v[i];
    return ans;
}

int dist(vi a, vi b) {
    assert(sz(a) == sz(b));
    int ans = 0;
    rep(i, sz(a)) ans += (a[i] != b[i]);
    return ans;
}

void prt(vi v) {
    for (int x: v) printf("%d", x); puts("");
}

int main() {
    freopen("code.in", "r", stdin);
    freopen("code.out", "w", stdout);
    vector<vector<vi>> grey(maxn), yellow(maxn);    
    grey[1] = yellow[0] = {{0}, {1}};
    repu(i, 2, maxn) {
        vector<vi> a = grey[i - 1];
        rep(j, 1 << (i - 1)) {
            grey[i].pb(a[j]);
            grey[i][j].pb(0);
        }
        reverse(all(a));
        rep(j, 1 << (i - 1)) {
            grey[i].pb(a[j]);
            grey[i][j + (1 << (i - 1))].pb(1);
        }
        reverse(all(a));
        rep(j, 1 << (i - 1)) {
            yellow[i].pb(a[j]);
            yellow[i][2 * j].pb(0);
            yellow[i].pb(comp(a[j]));
            yellow[i][2 * j + 1].pb(1);
            assert(dist(yellow[i][2 * j], yellow[i][2 * j + 1]) >= i / 2);
        }
        assert(dist(yellow[i][0], yellow[i].back()) >= i / 2);
    }
    int n;
    scanf("%d", &n);
    for (auto v: yellow[n]) prt(v);
}
