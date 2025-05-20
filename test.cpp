#include "Boom.h"
using namespace std;
int cnt = 0;
int dfs(int d, int kill, const bitset<ANS_NUM> &cur, bitset<R * C> &vis, double K=0.79, double dK=0) {
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
  #pragma omp parallel for
  for (int step1 = 0; step1 < R*C; ++step1) {
    bitset<ANS_NUM> cur,tmp;
    cur.set();
    bitset<R * C> vis;
    vis[step1]=1;
    int sum = 0;
    for(int status=0;status<3;++status) bitset_and(tmp,eigen[step1][status],cur), sum+=dfs(1, status==2, tmp, vis);
    #pragma omp critical
    {
      printf("step1=%2d, Acc=%d/%d\n", step1, sum, ANS_NUM);
      fflush(stdout);
    }
  }
  return 0;
}
