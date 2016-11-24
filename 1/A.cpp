// Largest generator of Z/NZ <= N/2
// - If N = 2K+1, then ans = K
// - If N = 2K and K even, then ans = K-1
// - If N = 2K and K odd,  then ans = K-2
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

const int MAXL = 2000;
int a[MAXL + 1];
int l;

bool iseven() {
  return a[l - 1] % 2 == 0;
}

void dec() {
  int i = l - 1;
  while (a[i] == 0) {
    a[i] = 9;
    --i;
  }
  --a[i];
}

int main() {
  freopen("china.in", "r", stdin);
  freopen("china.out", "w", stdout);

  // Read input
  int c;
  while (isdigit(c = getchar())) a[l++] = c - '0';

  bool n_even = iseven();

  // Divide by 2
  for (int i = l - 1; i >= 0; --i) {
    if (a[i] % 2 != 0) a[i + 1] += 5;   
    a[i] /= 2;
  }

  for (int i = l - 1; i > 0; --i) {
    a[i - 1] += a[i] / 10;
    a[i] %= 10;
  }

  // Fix answer
  if (n_even) {
    dec();
    if (iseven()) dec();
  }

  // Print result
  if (a[0] > 0) printf("%d", a[0]);
  for (int i = 1; i < l; ++i) printf("%d", a[i]);
  puts("");
  return 0;
}
