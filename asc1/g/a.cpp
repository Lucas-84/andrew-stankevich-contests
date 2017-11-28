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

const int maxn = 1e5;

struct pt {
    int x, y;
    int id;
    void read() { scanf("%d%d", &x, &y); }
    bool operator < (pt a) const {
        if (x != a.x) return x < a.x;
        return y > a.y;
    }
};

struct node {
    int l, r;
    pair<int, int> v;
} tree[4 * maxn];

pt pts[maxn];
int n;

void build(int u, int l = 0, int r = n - 1) {
    tree[u].l = l; tree[u].r = r;
    tree[u].v = mp(0, -1);
    if (l == r) return;
    int m = l + (r - l) / 2;
    build(2 * u, l, m); build(2 * u + 1, m + 1, r);
}

pair<int, int> getmax(int ql, int qr, int u = 1) {
    if (tree[u].r < ql || qr < tree[u].l) return mp(0, -1);
    if (ql <= tree[u].l && tree[u].r <= qr) return tree[u].v;
    return max(getmax(ql, qr, 2 * u), getmax(ql, qr, 2 * u + 1));
}

void update(int q, pair<int, int> v, int u = 1) {
    if (tree[u].r < q || q < tree[u].l) return;
    if (tree[u].l == tree[u].r) {
        tree[u].v = max(tree[u].v, v);
        return;
    }
    update(q, v, 2 * u); update(q, v, 2 * u + 1);
    tree[u].v = max(tree[2 * u].v, tree[2 * u + 1].v);
}

int main() {
    freopen("people.in", "r", stdin);
    freopen("people.out", "w", stdout);
    scanf("%d", &n);
    vi ylist;
    FOR(i, n) {
        pts[i].read();
        pts[i].id = i + 1;
        ylist.pb(pts[i].y);
    }
    sort(ALL(ylist)); ylist.resize(unique(ALL(ylist)) - ylist.begin());
    FOR(i, n) pts[i].y = lower_bound(ALL(ylist), pts[i].y) - ylist.begin();
    sort(pts, pts + n);
    build(1);
    vector<pair<int, int>> dp(n);
    pair<int, int> ans(0, -1);
    FORD(i, 0, n) {
        dp[i] = getmax(pts[i].y + 1, n - 1);
        dp[i].fst++;
        update(pts[i].y, {dp[i].fst, i});
        ans = max(ans, {dp[i].fst, i});
    }
    printf("%d\n", ans.fst);
    while (ans.snd != -1) {
        printf("%d ", pts[ans.snd].id);
        ans = dp[ans.snd];
    }
    puts("");
}
