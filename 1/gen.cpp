#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

const int N = 200, M = 5000;
bool seen[N][N];

int main() {
  srand(time(NULL));
  printf("%d %d\n", N, M);
  for (int i = 0; i < M; ++i) {
    int u = rand() % N;
    int v = rand() % N;
    if (u==v || seen[u][v] || seen[v][u]) { --i; continue; }
    seen[u][v] = true;
    int upp = rand() % 100000 + 1;
    int low = rand() % min(upp,50000) + 1;
    printf("%d %d %d %d\n", u+1, v+1, low, upp);
  }
  return 0;
}
