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

const int maxn = 200 * 1000;
lli a[maxn + 1];
lli minl[maxn + 1], minr[maxn + 1];

int main() {
    freopen("positive.in", "r", stdin);
    freopen("positive.out", "w", stdout);
    int n;
    scanf("%d", &n);
    rep(i, n) {
        scanf("%lld", &a[i + 1]);
        a[i + 1] += a[i];
    }
    minl[0] = a[0];
    repu(i, 1, n) minl[i] = min(minl[i - 1], a[i]);
    minr[n - 1] = a[n];
    repd(i, 0, n - 1) minr[i] = min(minr[i + 1], a[i + 1]);
    int ans = 0;
    rep(i, n) if (a[i] < minl[i] + a[n] && a[i] < minr[i]) ans++;
    printf("%d\n", ans);
}
