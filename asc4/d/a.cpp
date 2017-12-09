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

const int maxn = 111, maxm = 111;
int A[maxn][maxm];
char buf[64];
int n, m;

vi readops() {
    vi ans(n);
    while (true) {
        int coeff = 1;
        if (scanf(" %[-+0123456789]", buf) == 1) {
            int len = strlen(buf);
            if (!isdigit(buf[len - 1])) {
                buf[len++] = '1';
                buf[len] = 0;
            }
            coeff = atoi(buf);
        }
        int id;
        if (scanf("x%d", &id) == 1) {
            ans[id - 1] = coeff;
        }
        int c = getchar();
        ungetc(c, stdin);
        if (c == '\n' || c == '<' || c == '>' || c == '=') break;
    }
    return ans;
}

void printops(vi v) {
    bool did = false;
    rep(i, sz(v)) if (v[i] != 0) {
        if (v[i] > 0) {
            if (did) printf("+");
        } else
            printf("-");
        if (abs(v[i]) != 1) printf("%d", abs(v[i]));
        printf("y%d", i + 1);
        did = true;
    }
    if (!did) printf("0");
}

int main() {
    freopen("dual.in", "r", stdin);
    freopen("dual.out", "w", stdout);
    scanf("%d%d", &n, &m);
    scanf(" %s ", buf);
    int ismin = strcmp(buf, "min") == 0;
    vi vb = readops();
    scanf(" with ");    
    vi vsign(n);
    rep(i, n) {
        int id;
        char c;
        scanf(" x%d%c", &id, &c);
        assert(i == id - 1);
        if (c == '>') vsign[i] = +1;
        else if (c == '<') vsign[i] = -1;
        scanf("%*[^\n]");
        if (ismin) vsign[i] = -vsign[i];
    }
    scanf(" under ");
    vi csign(m), vc(m);
    rep(i, m) {
        vi l = readops();
        rep(j, n) A[j][i] = l[j];
        char c;
        scanf(" %c", &c);
        if (c == '>') {
            csign[i] = +1;
            scanf("=%d", &vc[i]);
        } else if (c == '<') {
            csign[i] = -1;
            scanf("=%d", &vc[i]);
        } else {
            assert(c == '=');
            scanf("%d", &vc[i]);
        }
        if (!ismin) csign[i] = -csign[i];
    }
    /*
    rep(i, n) {
        rep(j, m) {
            printf("%d ", A[i][j]);
        }
        puts("");
    }
    */
    printf("%d %d\n", m, n);
    printf("%s ", ismin ? "max" : "min");
    printops(vc);
    puts("\nwith");
    rep(i, m) {
        printf("y%d", i + 1);
        if (csign[i] == +1) puts(">=0");
        else if (csign[i] == -1) puts("<=0");
        else puts(" arbitary");
    }
    puts("under");
    rep(i, n) {
        vi l(m);
        rep(j, m) l[j] = A[i][j];
        printops(l);
        if (vsign[i] == +1) printf(">=");
        else if (vsign[i] == -1) printf("<=");
        else printf("=");
        printf("%d\n", vb[i]);
    }
}
