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

const int maxl = 2000;
int rep[maxl];
int len;

void div2() {
    int c = 0;
    FOR(i, len) {
        int v = rep[i] + 10 * c;
        c = v % 2;
        rep[i] = v / 2;
    }
}

void sub1() {
    FORD(i, 0, len) {
        if (rep[i] > 0) {
            rep[i]--;
            break;
        }
        rep[i] = 9;
    }
}

void print() {
    int i = 0;
    while (i < len && rep[i] == 0) i++;
    while (i < len) printf("%d", rep[i++]); puts("");
}

bool even() { return rep[len - 1] % 2 == 0; }

int main() {
    //freopen("china.in", "r", stdin);
    //freopen("china.out", "w", stdout);
    int b;
    while (scanf("%1d", &b) == 1) rep[len++] = b;
    if (even()) {
        div2();
        sub1();
        if (even()) sub1();
    } else {
        div2();
    }
    print();
}
