#include<bits/stdc++.h>
#pragma once
const int PLANE_NUM = 3;
const int PLANE_SIZE = 10;
const int R = 10, C = 10;
const int Up = 0, Right = 1, Down = 2, Left = 3;
int turnright(int face) {return (face+1)&3;}

typedef std::pair<int,int> Pos;
Pos operator+(const Pos &a, const Pos &b) {
  return std::make_pair(a.first+b.first, a.second+b.second);
}
Pos operator-(const Pos &a, const Pos &b) {
  return std::make_pair(a.first-b.first, a.second-b.second);
}
Pos operator*(const int &a, const Pos &b) {
  return std::make_pair(a*b.first, a*b.second);
}
Pos operator*(const Pos &b, const int &a) {
  return std::make_pair(a*b.first, a*b.second);
}

const Pos v[] = {{-1,0}, {0,1}, {1,0}, {0,-1}};
const Pos PlaneShape[PLANE_SIZE] = {{0,0}, {0,-1}, {1,-1}, {2,-1}, {-1,-1}, {-2,-1}, {0,-2}, {0,-3}, {1,-3}, {-1,-3}};

std::vector<std::array<char, R*C> > ans_list;
const int ANS_NUM = 66816;
void get_ans_list(){
  freopen("AnswerList.txt","r",stdin);
  char str[R*C];
  std::array<char, R*C> arr;
  while(scanf("%s",str)!=EOF){
    for(int i=0;i<R*C;++i) arr[i]=str[i]-'0';
    ans_list.push_back(arr);
  }
  assert(ANS_NUM == ans_list.size());
  fclose(stdin);
  freopen("CON","r",stdin);
}

std::bitset<ANS_NUM> eigen[R*C][3];
void count_ans(int ans_id, std::array<char,R*C> ans){
  for(int i=0;i<R*C;++i){
    eigen[i][ans[i]][ans_id]=1;
  }
}
void get_choice_vector(){
  get_ans_list();
  for(int i=0;i<ANS_NUM;++i) count_ans(i,ans_list[i]);
}