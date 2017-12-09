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

#define double long double
const int maxn = 111, maxl = 111;
const int maxm = 22;
char name[maxn][maxl + 1];
int C[maxn];

int main() {
    freopen("ranking.in", "r", stdin);
    freopen("ranking.out", "w", stdout);
    int n, m;
    scanf("%d", &n);
    rep(i, n) {
        getchar();
        scanf("%[^\n]", name[i]);
        assert(strlen(name[i]) <= 100);
    }
    scanf("%d", &m);
    vector<pair<double, int>> score(n);
    rep(i, n) score[i].snd = i;
    while (m--) {
        int K;
        scanf("%d", &K);
        vi nsolved(n), pen(n), part(n);
        rep(j, K) {
            int id;
            scanf("%d", &id);
            id--;
            C[id]++;
            part[id] = 1;
        }
        int pn, rn;
        scanf("%d%d", &pn, &rn);
        vector<vi> did(n, vi(pn)), tries(n, vi(pn));
        rep(j, rn) {
            int idt, t;
            char cidp, acc;
            scanf("%d %c%d %c", &idt, &cidp, &t, &acc);
            idt--;
            if (!part[idt]) continue;
            int idp = cidp - 'A';
            if (did[idt][idp]) continue;
            if (acc == '+') {
                did[idt][idp] = 1;
                nsolved[idt]++;
                pen[idt] += t + tries[idt][idp] * 20;
            } else {
                tries[idt][idp]++;
            }
        }
        vi teams(n); rep(i, n) teams[i] = i;
        auto f = [&](int a, int b) {
            if (nsolved[a] != nsolved[b]) return nsolved[a] > nsolved[b];
            return pen[a] < pen[b];
        };
        int pm = 0;
        rep(i, n) pm = max(pm, nsolved[i]);
        sort(all(teams), f);
        int last = 1;
        rep(i, n) {
            if (i > 0 && f(teams[i - 1], teams[i])) {
                last = i + 1;
            }
            if (!part[teams[i]]) continue;
            int A = 2 * K - 2;
            int B = K - 2;
            if (pm) {
                double raw = 1. * nsolved[teams[i]] / pm;
                score[teams[i]].fst += raw * A / (last + B);
            }
        }
    }
    rep(i, n) if (C[i]) score[i].fst /= C[i];
    sort(all(score)); reverse(all(score));
    int maxlen = 0;
    rep(i, n) maxlen = max(maxlen, (int)strlen(name[i]) + 1);
    rep(i, n) {
        int id = score[i].snd;
        printf("%s", name[id]);
        rep(i, maxlen - (int)strlen(name[id])) putchar(' ');
        printf("%.4Lf\n", score[i].fst);
    }
}
