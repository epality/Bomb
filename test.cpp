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
int cur_step = 5;
int num_stat = (1<<(2*(cur_step-1)));
int best_choice[1 << 26], best_acc[1 << 26], tot[1 << 26];
double best_weight[1 << 26];
bool invalid(int x) {
  for (int step = 1; step < cur_step; ++step)
    if(((x>>(2*step-2))&3)==0)
      return true;
  return false;
}
void work() {
  #pragma omp parallel for
  for (int x = 0; x < R*C; ++x) {
    for (int stat = 0; stat < num_stat; stat ++) {
      int kill = 0, sum = 0;
      double weight = 0;
      bitset<ANS_NUM> cur,tmp[3];
      cur.set();
      bitset<R * C> vis;
      if(invalid(stat)) continue;
      for (int step = 1; step < cur_step; ++step){
        int choice = best_c[(stat&((1<<(2*step-2))-1))];
        int i = ((stat>>(2*step-2))&3)-1;
        if (i == 2) kill += 1;
        bitset_and(cur, cur, eigen[choice][i]);
        if (cur.count() == 0) {
          break;
        }
        vis[choice] = 1;
      }
      if (vis[x]) continue;
      vis[x] = 1;
      tot[stat] = cur.count();
      if (tot[stat] == 0) {
        continue;
      }
      for(int i=0;i<3;++i) {
        bitset_and(tmp[i],eigen[x][i],cur);
        sum+=dfs(cur_step, kill + (i==2), tmp[i], vis);
      }
      weight = get_weight(tmp[0], tmp[1], tmp[2]);
      #pragma omp critical
      {
        if(best_acc[stat]<sum || best_acc[stat] == sum && best_weight[stat] < weight) {
          best_acc[stat]=sum;
          best_c[stat] = x;
          best_choice[stat]=x;
          best_weight[stat] = weight;
        }
        // printf("status=%5d, step=%2d, Acc=%d/%d\n",stat , x, sum, tot[stat]);
        // fflush(stdout);
      }
    }
  }
  // for(int i=0;i<num_stat;++i) {
  //   if (invalid(i)) continue;
  //   printf(",{%d,%d}", i, best_choice[i]);
  //   // printf("status %5d, choice %2d\n", i, best_choice[i]);
  // }
  // puts("");
  int sum = 0;
  for(int i=0;i<num_stat;++i) {
    if (invalid(i)) continue;
    // printf("status %5d, choice %2d, Acc=%d/%d\n", i, best_choice[i], best_acc[i], tot[i]);
    sum += best_acc[i];
  }
  printf("cur_step=%d Acc=%d/%d\n", cur_step, sum, ANS_NUM);
}
int main(){
  get_choice_vector();
  load_strategy();
  for (cur_step = 2; cur_step <= 12; cur_step += 1) {
    num_stat = (1<<(2*(cur_step-1)));
    work();
  }
  freopen("strategy.txt", "w", stdout);
  for (int i = 0; i < num_stat; i++) {
    if (invalid(i)) continue;
    printf("%d %d\n", i, num_stat);
  }
  fclose(stdout);
  return 0;
}
