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

const int maxt = 111, maxm = 111, ub = 1000;
int mat[maxt][maxm];
int t, m;
vi primes;

bool isprime(int n) { FORU(i, 2, n) if (n % i == 0) return false; return true; }
void genp() {
    int i = 2, np = 0;
    while (np < t) {
        if (isprime(i)) {
            primes.pb(i);
            np++;
        }
        i++;
    }
}

int getrank() {
    int r = 0;
    FOR(j, m) {
        int iref = -1;
        FORU(i, r, t) if (mat[i][j] != 0) iref = i;
        if (iref == -1) continue;
        FOR(k, m) swap(mat[iref][k], mat[r][k]);
        FOR(i, t) if (i != r && mat[i][j]) FOR(k, m) mat[i][k] ^= mat[r][k];
        r++;
    }
    return r;
}

const int maxl = 100;
int repans[maxl];

void mul2() {
    int c = 0;
    FORD(i, 0, maxl) {
        int v = 2 * repans[i] + c;
        repans[i] = v % 10;
        c = v / 10;
    }
}

void sub1() {
    FORD(i, 0, maxl) {
        if (repans[i] > 0) {
            repans[i]--;
            break;
        }
        repans[i] = 9;
    }
}

int main() {
    freopen("rsa.in", "r", stdin);
    freopen("rsa.out", "w", stdout);
    scanf("%d%d", &t, &m);
    genp();
    //assert(primes.size() == t);
    FOR(i, m) {
        int b; scanf("%d", &b); 
        FOR(j, t) {
            int p = 0;
            while (b % primes[j] == 0) {
                p ^= 1;
                b /= primes[j];
            }
            mat[j][i] = p;
        }
    }
    /*
    FOR(i, t) {
        FOR(j, m) printf("%d ", mat[i][j]);
        puts("");
    }
    */
    repans[maxl - 1] = 1;
    int r = getrank();
    FOR(i, m - r) mul2();
    sub1();
    int i = 0;
    while (i < maxl && repans[i] == 0) i++;
    if (i == maxl) puts("0");
    while (i < maxl) printf("%d", repans[i++]);
    puts("");
    //printf("%lld\n", (1ll << (m - getrank())) - 1);
    /*
    printf("%d\n",  getrank());
    FOR(i, t) {
        FOR(j, m) printf("%d ", mat[i][j]);
        puts("");
    }
    */
}
