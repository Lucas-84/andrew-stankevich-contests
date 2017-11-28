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

const int maxm = 5;
const int maxl = 111;
lli tmp[1 << maxm][1 << maxm];
int mod;
int repn[maxl], lenn;
int m;

void mul(vvi& a, vvi b) {
    FOR(i, 1 << m) FOR(j, 1 << m) {
        tmp[i][j] = 0;
        FOR(k, 1 << m) tmp[i][j] = (tmp[i][j] + (a[i][k] * b[k][j] % mod)) % mod;
    }
    FOR(i, 1 << m) FOR(j, 1 << m) a[i][j] = tmp[i][j];
}

void div2() {
    int c = 0;
    FOR(i, lenn) {
        repn[i] += c;
        if (repn[i] % 2 != 0) c = 10;
        else c = 0;
        repn[i] /= 2;
    }
}

vvi expo(vvi x) {
    vvi ans(1 << m, vi(1 << m)); 
    FOR(i, 1 << m) ans[i][i] = 1;
    FOR(step, 400) {
        if (repn[lenn - 1] % 2) mul(ans, x);
        mul(x, x);
        div2();
    }
    return ans;
}

vvi expo2(vvi x, int n) {
    vvi ans(1 << m, vi(1 << m)); 
    FOR(i, 1 << m) ans[i][i] = 1;
    while (n > 0) {
        if (n % 2) mul(ans, x);
        mul(x, x);
        n /= 2;
    }
    return ans;
}

//int n;
void readn() {
    char buf[128]; scanf("%s", buf);
    lenn = strlen(buf);
    FOR(i, lenn) repn[i] = buf[i] - '0';
    //n = 0;
    //FOR(i, lenn) n = n * 10 + repn[i];
    FORD(i, 0, lenn) {
        if (repn[i] != 0) {
            repn[i]--;
            break;
        }
        repn[i] = 9;
    }
    //FOR(i, lenn) printf("%d ", repn[i]); puts("");
}

int main() {
    freopen("nice.in", "r", stdin);
    freopen("nice.out", "w", stdout);
    readn(); 
    scanf("%d%d", &m, &mod);
    vvi mat(1 << m, vi(1 << m));
    FOR(i, 1 << m) FOR(j, 1 << m) {
        bool ok = true;
        FORU(k, 1, m) {
            int b1 = (i >> k) & 1, b2 = (j >> k) & 1, b3 = (i >> (k - 1)) & 1, b4 = (j >> (k - 1)) & 1;
            if (b1 == b2 && b2 == b3 && b3 == b4) ok = false;
        }
        if (ok) mat[i][j] = (mat[i][j] + 1) % mod;
    }
    /*
    FOR(i, 1 << m) {
        FOR(j, 1 << m) printf("%lld ", mat[i][j]);
        puts("");
    }
    */
    vvi mans = expo(mat);
    //assert(mans == expo2(mat, n - 1));
    lli ans = 0;
    FOR(i, 1 << m) FOR(j, 1 << m) ans = (ans + mans[i][j]) % mod;
    printf("%lld\n", ans);
}
