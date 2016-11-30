// A = adjacency matrix of the graph of borders
// ans = Sum([A^N]_{1i}, 1 <= i <= n) [P]
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
const int INF = 1000 * 1000 * 1000;
const ll LLINF = 1ll << 53;

const int MAXC = 1 << 5;
const int MAXL = 100;
int ans[MAXC][MAXC];
int adj[MAXC][MAXC];
int tmp[MAXC][MAXC];
int N[MAXL];
int L;
int M, P, C;

void build() {
  C = 1 << M;
  for (int i = 0; i < C; ++i)
    for (int j = 0; j < C; ++j) {
      adj[i][j] = 1;
      for (int k = 0; k < M - 1; ++k) {
        int v1 = (i >> k) & 3, v2 = (j >> k) & 3;
        if ((v1 == 0 && v2 == 0) || (v1 == 3 && v2 == 3)) adj[i][j] = 0;
      }
    }
}

// a = a*b
void mult(int a[MAXC][MAXC], int b[MAXC][MAXC]) {
  for (int i = 0; i < C; ++i)
    for (int j = 0; j < C; ++j) {
      tmp[i][j] = 0;
      for (int k = 0; k < C; ++k)
        tmp[i][j] = (tmp[i][j] + 1ll * a[i][k] * b[k][j]) % P;
    }

  for (int i = 0; i < C; ++i) copy(tmp[i], tmp[i] + C, a[i]);
}

void print() {
  for (int i = 0; i < L; ++i) printf("%d", N[i]); puts("");
}

void readn() {
  char s[MAXL + 1];
  scanf("%s", s);
  L = int(strlen(s));
  for (int i = 0; i < L; ++i) N[i] = s[i] - '0';
}

void dec() {
  int i;
  for (i = L - 1; i >= 0 && N[i] == 0; --i) N[i] = 9;
  assert(i >= 0);
  N[i]--;
}

bool null() {
  for (int i = 0; i < L; ++i) if (N[i]) return false;
  return true;
}

bool odd() {
  return N[L - 1] % 2 == 1;
}

void div2() {
  for (int i = L - 1; i >= 0; --i) {
    if (i < L - 1 && N[i] % 2 != 0) N[i + 1] += 5;
    N[i] /= 2;
  }
  for (int i = L - 1; i > 0; --i) {
    N[i - 1] += N[i] / 10;
    N[i] %= 10;
  }
}

int main() {
  freopen("nice.in", "r", stdin);
  freopen("nice.out", "w", stdout);
  readn();
  scanf("%d%d", &M, &P);
  dec();
  build();
  for (int i = 0; i < C; ++i) ans[i][i] = 1;
  while (!null()) {
    if (odd()) mult(ans, adj);
    mult(adj, adj);
    div2();
  }
  int res = 0;
  for (int i = 0; i < C; ++i)
    for (int j = 0; j < C; ++j)
      res = (res + ans[i][j]) % P;
  printf("%d\n", res);
  return 0;
}
