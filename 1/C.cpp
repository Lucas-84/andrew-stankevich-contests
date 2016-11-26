// Dynamic programming
// u := node identifier
// a := father grant available
// dp(u, TRUE) := max(1000 + dp(son, FALSE)  + dp(brother, FALSE),
//                    dp(son, TRUE) + dp(brother, TRUE))
// dp(u, FALSE) := dp(son, TRUE) + dp(brother, FALSE)
#include <bits/stdc++.h>
using namespace std;
#define mp make_pair
#define pb push_back
#define fst first
#define snd second
#ifndef M_PI
#   define M_PI 3.14159265358979323846
#endif
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;
const int INF = 1000 * 1000 * 1000;
const ll LLINF = 1ll << 53;

const int MAXN = 500 * 1000;
int dp[MAXN][2];
bool taken[MAXN][2];
bool granted[MAXN];
int ne[MAXN];
int fs[MAXN];

void relax(int& r, int v) {
  r = max(r, v);
}

int solve(int u, bool a) {
  if (u == -1) return 0;
  if (dp[u][a] != -1) return dp[u][a];
  dp[u][a] = solve(fs[u], true) + solve(ne[u], a);
  if (a) {
    int nval = 1000 + solve(fs[u], false) + solve(ne[u], false);
    if (nval > dp[u][a]) {
      dp[u][a] = nval;
      taken[u][a] = true;
    }
  }
  return dp[u][a];
}

void mark(int u, bool a) {
  if (u == -1) return;
  if (taken[u][a]) {
    granted[u] = true;
    mark(fs[u], false);
    mark(ne[u], false);
  } else {
    mark(fs[u], true);
    mark(ne[u], a);
  }
}

int main() {
freopen("grant.in", "r", stdin);
freopen("grant.out", "w", stdout);
  int N;
  scanf("%d", &N);
  fill(fs, fs + N, -1);
  fill(ne, ne + N, -1);
  for (int u = 0; u < N; ++u) dp[u][true] = dp[u][false] = -1;
  for (int v = 1; v < N; ++v) {
    int u;
    scanf("%d", &u);
    --u;
    ne[v] = fs[u];
    fs[u] = v;
  }
  printf("%d\n", solve(0, false));
  mark(0, false);
  for (int u = 0; u < N; ++u) if (granted[u]) printf("%d ", u + 1);
  puts("");
  return 0;
}
