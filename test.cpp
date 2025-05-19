#include "Boom.h"
using namespace std;
int cnt = 0;
int dfs(int d, int kill, const bitset<ANS_NUM> &cur, bitset<R * C> &vis) {
  if (kill == 3) {
    return cur.count();
  }
  if (d == 14 || cur.count() == 0) {
    return 0;
  }
  int res = 0;
  int x = solve(cur, vis);
  vis[x] = 1;
  for (int i = 0; i < 3; i++) {
    res += dfs(d + 1, kill + (i == 2), eigen[x][i] & cur, vis);
  }
  vis[x] = 0;
  return res;
}
int main(){
  get_choice_vector();
  for (K = 0.1; K <= 2; K += 0.1) {
    bitset<ANS_NUM> cur;
    cur.set();
    bitset<R * C> vis;
    printf("K = %.1lf 成功率:%d/%d\n", K, dfs(0, 0, cur, vis), ANS_NUM);
  }
  return 0;
}