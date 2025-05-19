#include<bits/stdc++.h>
#include "Boom.h"
using namespace std;
int main(){
  get_choice_vector();
  freopen("EigenVector.txt", "w", stdout);
  for(int i=0;i<R*C;++i){
    for(int j=0;j<3;++j){
      printf("%d %d: ",i,j);
      for(int k=0;k<ANS_NUM;++k)
        printf("%d",(int)eigen[i][j][k]);
      printf("\n");
    }
  }
  fclose(stdout);
}