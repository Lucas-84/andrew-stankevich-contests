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

const double inf = 1e100, eps = 1e-8;
const int maxn = 1000;
const int maxm = 10 * 1000;
int ans[maxn];
double val[maxn];
int n, m, y;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    scanf("%d%d%d", &n, &m, &y);
    int s = 0;
    rep(i, n) {
        int x;
        scanf("%d", &x); 
        val[i] = 1. * m * x / y;
        ans[i] = round(val[i]);
        s += ans[i];
    }
    while (s != m) {
        double best = -inf;
        int ibest = -1;
        rep(i, n) if ((s > m && ans[i] > val[i] + eps) || (s < m && ans[i] < val[i] - eps)) {
            double curr = fabs(ans[i] - val[i]);
            if (curr > best) {
                best = curr;
                ibest = i;
            }
        }
        assert(ibest != -1);
        if (s > m) {
            ans[ibest]--;
            s--;
        } else {
            ans[ibest]++;
            s++;
        }
    }
    rep(i, n) printf("%d ", ans[i]); puts("");
}
