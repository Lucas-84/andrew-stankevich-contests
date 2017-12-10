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

int lim;

int phi(int n) {
    int ans = n;
    for (int i = 2; i * i <= n; ++i) if (n % i == 0) {
        while (n % i == 0) n /= i;
        ans = ans * (i - 1) / i;
    }
    if (n > 1) ans = ans * (n - 1) / n;
    return ans;
}

int powmod(int n, int m, int t) {
    int ans = 1;
    while (m > 0) {
        if (m & 1) ans = ans * n % t;
        n = n * n % t;
        m /= 2;
    }
    return ans;
}

int solve(int n, int m, int t) {
    if (t == 1) return 0;
    if (n == 1) return 2 * m % t;
    if (m == 1) return 2 % t;
    if (m == 2) return 4 % t;
    if (n == 2) return powmod(2, m, t);
    if (n == 3) {
        if (m == 3) return 16 % t;
        int e = solve(n, m - 1, phi(t));
        return powmod(2, phi(t) + e, t);
    }
    if (n == 4 && m == 3) return (1 << 16) % t;
    return lim;
}

int findlim(int t, int e = 10) {
    assert(e >= 0);
    if (t == 1) return 0;
    return powmod(2, phi(t) + findlim(phi(t), e - 1), t);
}

int main() {
    freopen("ackerman.in", "r", stdin);
    freopen("ackerman.out", "w", stdout);
    int t;
    scanf("%d", &t);
    lim = findlim(t);
    int n, m;
    int i = 1;
    while (scanf("%d%d", &n, &m) == 2 && n != 0)
        printf("Case %d: %d\n", i++, solve(n, m, t));
}
