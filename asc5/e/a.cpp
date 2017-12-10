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
using lli = unsigned long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vlli = vector<lli>;

const int maxl = 20, maxv = 9;
lli dp[maxl][maxv * maxl + 1][2];
lli n; vi sn;

vi tostring(lli x) {
    vi ans;
    while (x > 0) {
        ans.pb(x % 10);
        x /= 10;
    }
    return ans;
}

lli toint(vi v) {
    lli ans = 0;
    for (int x: v) ans = ans * 10 + x;
    return ans;
}

lli lesslex(lli k, int sum) {
    if (k == 0) return 0;
    vi sk = tostring(k);
    lli ans = 0;
    int equal = 1, greater = 0;
    int s = sum;
    rep(i, sz(sk)) {
        repu(v, i == 0, sk[sz(sk) - i - 1]) {
            if (v > s) break;
            repu(l, 0, sz(sn)) {
                int len = l + i + 1;
                if (len > sz(sn)) break;
                if (len == sz(sn) && (greater || (equal && v > sn[sz(sn) - i - 1]))) break;
                if (len == sz(sn)) ans += dp[l][s - v][equal && v == sn[sz(sn) - i - 1]];
                else ans += dp[l][s - v][0];
            }
        }
        greater |= equal && sk[sz(sk) - i - 1] > sn[sz(sn) - i - 1];
        equal &= sk[sz(sk) - i - 1] == sn[sz(sn) - i - 1];
        s -= sk[sz(sk) - i - 1];
    }
    lli v = k;
    s = accumulate(all(sk), 0);
    while (v != 0) {
        s -= v % 10;
        if (s == sum) ans++;
        v /= 10;
    }
    return ans;
}

lli findpos(lli k) {
    lli ans = 0;
    vi sk = tostring(k);
    int sum = accumulate(all(sk), 0);
    rep(s, sum) ans += dp[sz(sn)][s][1];
    ans += lesslex(k, sum);
    return ans;
}

lli findkth(lli k) {
    int s = 1;
    while (k >= dp[sz(sn)][s][1]) {
        k -= dp[sz(sn)][s][1];
        s++;
    }
    vi sc; 
    rep(it, sz(sn)) {
        assert(lesslex(toint(sc), s) <= k);
        assert(toint(sc) <= n);
        int last = -1;
        rep(v, maxv + 1) {
            sc.pb(v);
            if (lesslex(toint(sc), s) <= k) last = v;
            sc.pop_back();
        }
        if (last == -1) break;
        sc.pb(last);
    }
    return toint(sc);
}

int main() {
    freopen("grlex.in", "r", stdin);
    freopen("grlex.out", "w", stdout);
    lli k;
    scanf("%llu%llu", &n, &k);
    sn = tostring(n);
    dp[0][0][0] = dp[0][0][1] = 1;
    repu(i, 1, sz(sn) + 1) rep(s, maxv * maxl + 1) rep(en, 2) rep(v, maxv + 1) {
        if (en && v > sn[i - 1]) continue;
        if (v > s) continue;
        dp[i][s][en] += dp[i - 1][s - v][en && v == sn[i - 1]];
    }
    printf("%llu\n", findpos(k));
    printf("%llu\n", findkth(k - 1));
}
