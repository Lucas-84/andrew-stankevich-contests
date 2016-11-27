// Compute sum of elements of (A)T*A
// = sum(deg(u)^2, u in V)
#include <algorithm>
#include <cstdio>
#include <map>
#include <set>
#include <vector>
#include <queue>
#include <cassert>
#include <cstdlib>
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
const int INF = 1000 * 1000 * 1000;
const ll LLINF = 1ll << 53;

int main() {
  freopen("matrix.in", "r", stdin);
  freopen("matrix.out", "w", stdout);
  int N, M;
  scanf("%d%d", &N, &M);
  vector<int> d(N);
  for (int i = 0; i < M; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    d[u - 1]++; d[v - 1]++;
  }
  ll ans = 0;
  for (int i = 0; i < N; ++i) ans += 1ll * d[i] * d[i]; 
  printf("%lld\n", ans);
  return 0;
}
