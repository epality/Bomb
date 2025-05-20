#include "Boom.h"
using namespace std;

static const double K0 = 0.79;
static const double dK = 0;
static int sum_status = 1;
static map<int,int> best_c = {{1,32}};
int main(){
  get_choice_vector();
  bitset<ANS_NUM> cur;
  bitset<R*C> vis;
  cur.set();
  int kill = 0;
  double K = K0;
  for(int i=0;i<14;++i){
    // puts("!!!!!!!!");
    int x , y;
    if(best_c.count(sum_status)) x = best_c[sum_status];
    else x = solve(cur,vis,K);
    vis[x]=true;
    cout<<(char)((x%10)+'a')<<x/10+1<<endl;
    cin>>y;
    sum_status = sum_status*3+y;
    if(y==2) ++kill;
    if(kill==3) break;
    cur &= eigen[x][y];
    K += dK;
  }
}