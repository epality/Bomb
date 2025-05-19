#include<bits/stdc++.h>
#include "Boom.h"
using namespace std;
static bool inmap(int r,int c,int face){
  int ubound, dbound, lbound, rbound;
  if(face==Up)    ubound=r, dbound=r+3, lbound=c-2, rbound=c+2;
  if(face==Down)  ubound=r-3, dbound=r, lbound=c-2, rbound=c+2;
  if(face==Left)  ubound=r-2, dbound=r+2, lbound=c, rbound=c+3;
  if(face==Right) ubound=r-2, dbound=r+2, lbound=c-3, rbound=c;
  return ubound>=0&&dbound<R&&lbound>=0&&rbound<C;
}
static map<Pos, char> a;
static int ans_cnt = 0;
static set<vector<char> > Ans_list;
void countAnswer(){
  vector<char> tmp(R*C);
  for(int i=0;i<R;++i) 
    for(int j=0;j<C;++j){
      tmp[i*C+j] = a[make_pair(i,j)];
    }
  Ans_list.insert(tmp);
  ++ans_cnt;
  if(ans_cnt%1000==0) printf("%d\n",ans_cnt);
}
static bool conflict(Pos p, int face) {
  Pos x_axis = v[turnright(face)], y_axis=v[face];
  for(int i=0;i<PLANE_SIZE;++i) 
    if(a[p+PlaneShape[i].first*x_axis+PlaneShape[i].second*y_axis])
      return true;
  return false;
}
static void PlacePlane(Pos p, int face, bool undo = false) {
  Pos x_axis = v[turnright(face)], y_axis=v[face];
  for(int i=1;i<PLANE_SIZE;++i) a[p+PlaneShape[i].first*x_axis+PlaneShape[i].second*y_axis]=!undo;
  a[p] = 2*!undo;
  // printf("%d %d %d %d\n", p.first, p.second, face, (int)undo);
  // for(int i=0;i<R;++i){
  //   for(int j=0;j<C;++j){
  //     printf("%d",(int)a[make_pair(i,j)]);
  //   }
  //   puts("");
  // }
  // getchar();
}
static void EnumPlane(int id){
  if(id>PLANE_NUM) {countAnswer();return;}
  for(int i=0;i<R;++i){
    for(int j=0;j<C;++j){
      for(int k=0;k<4;++k){
        if(!inmap(i,j,k)) continue;
        if(conflict(Pos(i,j),k)) continue;
        PlacePlane(Pos(i,j),k);
        EnumPlane(id+1);
        PlacePlane(Pos(i,j),k, true);
      }
    }
  }
}
void PrintAns(){
  printf("%d\n",ans_cnt);
  freopen("AnswerList.txt", "w", stdout);
  for(auto ans:ans_list){
    for(int i=0;i<R*C;++i)
      printf("%d",(int)ans[i]);
    puts("");
  }
  fclose(stdout);
}
int main(){
  EnumPlane(1);
  PrintAns();
}