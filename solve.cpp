#include "Boom.h"
using namespace std;

static const double K0 = 0.79;
static const double dK = 0;
static int sum_status = 0;
int main(){
  get_choice_vector();
  load_strategy();
  bitset<ANS_NUM> cur;
  bitset<R*C> vis;
  cur.set();
  int kill = 0;
  double K = K0;
  for(int i=0;i<14;++i){
    // puts("!!!!!!!!");
    int x , y;
    if(sum_status<BEST_CAP&&best_c[sum_status]!=-1) x = best_c[sum_status];
    else x = solve(cur,vis,K);
    vis[x]=true;
    cout<<(char)((x%10)+'a')<<x/10+1<<endl;
    cin>>y;
    sum_status |= (y+1)<<(i<<1);
    if(y==2) ++kill;
    if(kill==3) break;
    cur &= eigen[x][y];
    K += dK;
  }
}