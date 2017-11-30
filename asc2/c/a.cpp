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
    freopen("huffman.in", "r", stdin);
    freopen("huffman.out", "w", stdout);
    int n;
    scanf("%d", &n);
    priority_queue<lli, vlli, greater<lli>> q;
    rep(i, n) {
        int p;
        scanf("%d", &p);
        q.push(p);
    }
    lli ans = 0;
    while (q.size() > 1) {
        lli u = q.top(); q.pop();
        lli v = q.top(); q.pop();
        ans += u + v;
        q.push(u + v);
    }
    printf("%lld\n", ans);
}
