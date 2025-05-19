#include<bits/stdc++.h>
using namespace std;
char str[1000];
map<pair<pair<int,int> ,int> ,int> a;
vector<array<int,4> > b;
int main(){
  freopen("AnswerList.txt","r",stdin);
  int cnt=0;
  while(scanf("%s",str)!=EOF){
    int x=0,y=0,z=0;
    while(str[x]!='2') ++x;
    y=x+1;
    while(str[y]!='2') ++y;
    z=y+1;
    while(str[z]!='2') ++z;
    a[make_pair(make_pair(x,y),z)]++;
  }
  for(auto x:a){
    b.push_back({-x.second,x.first.first.first,x.first.first.second,x.first.second});
  }
  sort(b.begin(),b.end());
  for(auto x:b){
    printf("%d %d %d %d\n", -x[0], x[1], x[2], x[3]);
  }
}