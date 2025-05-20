#include "Boom.h"
using namespace std;
int cnt = 0;
int dfs(int d, int kill, const bitset<ANS_NUM> &cur, bitset<R * C> &vis, double K, double dK) {
  if (kill == 3) {
    return cur.count();
  }
  if (d == 14 || cur.count() == 0) {
    return 0;
  }
  int res = 0;
  int x = solve(cur, vis, K);
  vis[x] = 1;
  for (int i = 0; i < 3; i++) {
    bitset<ANS_NUM> tmp;
    bitset_and(tmp, eigen[x][i],  cur);
    res += dfs(d + 1, kill + (i == 2), tmp, vis, K+dK, dK);
  }
  vis[x] = 0;
  return res;
}
int main(){
  get_choice_vector();
  #pragma omp parallel
  for (double K0 = 0.70; K0 <= 0.80; K0 += 0.01) {
    for (double dK = 0.00; dK <= 0.02; dK += 0.002) {
      bitset<ANS_NUM> cur;
      cur.set();
      bitset<R * C> vis;
      printf("K0 = %.4lf, dK = %.4lf, Acc=%d/%d\n", K0, dK, dfs(0, 0, cur, vis, K0, dK), ANS_NUM);
    }
  }
  return 0;
}