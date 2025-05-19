#include "Boom.h"
using namespace std;

int main(){
  get_choice_vector();
  bitset<ANS_NUM> cur;
  bitset<R*C> vis;
  cur.set();
  int kill = 0;
  for(int i=0;i<14;++i){
    // puts("!!!!!!!!");
    int x = solve(cur,vis), y;
    vis[x]=true;
    cout<<(char)((x%10)+'a')<<x/10+1<<endl;
    cin>>y;
    if(y==2) ++kill;
    if(kill==3) break;
    cur &= eigen[x][y];
  }
}