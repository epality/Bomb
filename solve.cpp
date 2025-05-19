#include "Boom.h"
using namespace std;

static const double K = 0.79;
double get_weight(bitset<ANS_NUM> v0,bitset<ANS_NUM> v1,bitset<ANS_NUM> v2){
  double res = 0;
  int x0 = v0.count(), x1 = v1.count(), x2 = v2.count();
  // cout<<x0<<" "<<x1<<" "<<x2<<endl;
  if(x0) res += x0*log(x0);
  if(x1) res += x1*log(x1);
  if(x2) res += x2*log(x2);
  res /= x0+x1+x2;
  return -res+x2/(x0+x1+x2)*K;
}

int solve(bitset<ANS_NUM> cur){
  int best_i = -1;
  double best_w = -1e9;
  for(int i=0;i<R*C;++i){
    double w = get_weight(eigen[i][0]&cur,eigen[i][1]&cur,eigen[i][2]&cur);
    // cout<<i<<" "<<w<<endl;
    if(best_i==-1||w>best_w){
      best_i = i;
      best_w = w;
    }
  }
  return best_i;
}

int main(){
  get_choice_vector();
  bitset<ANS_NUM> cur;
  cur.set();
  int kill = 0;
  for(int i=0;i<14;++i){
    // puts("!!!!!!!!");
    int x = solve(cur), y;
    cout<<(char)((x%10)+'a')<<x/10+1<<endl;
    cin>>y;
    if(y==2) ++kill;
    if(kill==3) break;
    cur &= eigen[x][y];
  }
}