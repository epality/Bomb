#include<bits/stdc++.h>
#include "bitsetand.h"
#pragma once
using namespace std;
const int PLANE_NUM = 3;
const int PLANE_SIZE = 10;
const int R = 10, C = 10;
const int Up = 0, Right = 1, Down = 2, Left = 3;
int turnright(int face) {return (face+1)&3;}

typedef pair<int,int> Pos;
Pos operator+(const Pos &a, const Pos &b) {
  return make_pair(a.first+b.first, a.second+b.second);
}
Pos operator-(const Pos &a, const Pos &b) {
  return make_pair(a.first-b.first, a.second-b.second);
}
Pos operator*(const int &a, const Pos &b) {
  return make_pair(a*b.first, a*b.second);
}
Pos operator*(const Pos &b, const int &a) {
  return make_pair(a*b.first, a*b.second);
}

const Pos v[] = {{-1,0}, {0,1}, {1,0}, {0,-1}};
const Pos PlaneShape[PLANE_SIZE] = {{0,0}, {0,-1}, {1,-1}, {2,-1}, {-1,-1}, {-2,-1}, {0,-2}, {0,-3}, {1,-3}, {-1,-3}};

vector<array<char, R*C> > ans_list;
const int ANS_NUM = 66816;
void get_ans_list(){
  freopen("AnswerList.txt","r",stdin);
  char str[R*C];
  array<char, R*C> arr;
  while(scanf("%s",str)!=EOF){
    for(int i=0;i<R*C;++i) arr[i]=str[i]-'0';
    ans_list.push_back(arr);
  }
  assert(ANS_NUM == ans_list.size());
  fclose(stdin);
  freopen("CON","r",stdin);
}

bitset<ANS_NUM> eigen[R*C][3];
void count_ans(int ans_id, array<char,R*C> ans){
  for(int i=0;i<R*C;++i){
    eigen[i][ans[i]][ans_id]=1;
  }
}
void get_choice_vector(){
  get_ans_list();
  for(int i=0;i<ANS_NUM;++i) count_ans(i,ans_list[i]);
}

double get_weight(const bitset<ANS_NUM> &v0,const bitset<ANS_NUM> &v1,const bitset<ANS_NUM> &v2,double K){
  double res = 0;
  int x0 = v0.count(), x1 = v1.count(), x2 = v2.count();
  // cout<<x0<<" "<<x1<<" "<<x2<<endl;
  if(x0) res += x0*log(x0);
  if(x1) res += x1*log(x1);
  if(x2) res += x2*log(x2);
  res /= x0+x1+x2;
  return -res+1.0 * x2/(x0+x1+x2)*K;
}

int solve(const bitset<ANS_NUM> &cur, const bitset<R*C> &ban, double K){
  int best_i = -1;
  double best_w = -1e9;
  for(int i=0;i<R*C;++i){
    if(ban[i]) continue;
    bitset<ANS_NUM> bs1,bs2,bs3;
    bitset_and(bs1,eigen[i][0],cur);
    bitset_and(bs2,eigen[i][1],cur);
    bitset_and(bs3,eigen[i][2],cur);
    double w = get_weight(bs1,bs2,bs3,K);
    // cout<<i<<" "<<w<<endl;
    if(best_i==-1||w>best_w){
      best_i = i;
      best_w = w;
    }
  }
  return best_i;
}