#include<bits/stdc++.h>
#include "Boom.h"
using namespace std;
int main(){
  default_random_engine e;
  uniform_int_distribution<int> u(1,ANS_NUM);
  e.seed(time(0));
  int ansid = u(e);
  char str[R*C];
  freopen("AnswerList.txt", "r", stdin);
  while(ansid--) scanf("%s", str);
  fclose(stdin);
  freopen("CON", "r", stdin);

  char pos[10];
  for(int i=0;i<14;++i){
    scanf("%s",pos);
    int y = pos[0]-'a';
    int x = pos[1]-'1';
    int p = x*C+y;
    cout<<str[p]<<endl;
  }
}