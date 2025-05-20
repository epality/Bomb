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
static int sum_status = 0;
static map<int,int> best_c = {{0,32}};
int main(){
  get_choice_vector();
  const int cur_step = 2;
  const int num_stat = (1<<(2*(cur_step-1)));
  int best_choice[num_stat], best_acc[num_stat];
  #pragma omp parallel for
  for (int k = 0; k < R*C*num_stat; ++k) {
    bitset<ANS_NUM> cur,tmp;
    cur.set();
    bitset<R * C> vis;
    bool invalid =false;
    for (int step = 1; step < cur_step; ++step)
      if((((k/(R*C))>>(2*step-2))&3)==0)
        invalid = true;
    if(invalid) continue;
    for (int step = 1; step < cur_step; ++step){
      int choice = best_c[((k/(R*C))&((1<<(2*step-2))-1))];
      bitset_and(cur, cur, eigen[choice][(((k/(R*C))>>(2*step-2))&3)-1]);
      vis[choice] = 1;
    }
    int sum = 0;
    for(int status=0;status<3;++status) bitset_and(tmp,eigen[k%(R*C)][status],cur), sum+=dfs(1, status==2, tmp, vis);
    #pragma omp critical
    {
      if(best_acc[k/100]<sum) best_acc[k/100]=sum, best_choice[k/100]=k%100;
      printf("status=%5d, step=%2d, Acc=%d/%d\n",k/100 , k%100, sum, ANS_NUM);
      fflush(stdout);
    }
  }
  for(int i=0;i<num_stat;++i) printf("status %5d, choice %2d\n", i, best_choice[i]);
  return 0;
}
