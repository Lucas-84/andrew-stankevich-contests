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
    freopen("railsort.in", "r", stdin);
    freopen("railsort.out", "w", stdout);
    int n;
    scanf("%d", &n);
    vi a(1 << n);
    rep(i, 1 << n) {
        scanf("%d", &a[i]);
        a[i]--;
    }
    vector<vi> lg = {a};
    repd(i, 0, n) {
        vector<vi> nlg;
        for (vi g: lg) {
            vi ng1, ng2;
            for (int x: g) {
                printf("%d ", 1 + x);
                if ((x >> i) & 1) {
                    ng2.pb(x);
                } else {
                    printf("%d ", 1 + x);
                    ng1.pb(x);
                }
            }
            reverse(all(ng2));
            for (int x: ng2) printf("%d ", 1 + x);
            nlg.pb(ng1);
            nlg.pb(ng2);
        }
        lg = nlg;
    }
}
