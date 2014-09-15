#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class YahtzeeScore{
public:
  int maxPoints(vector<int> toss){
    vector<int> val(7);
    for(auto t:toss){
      val[t] += t;
    }
    int max = 0;
    for(auto v:val){
      if(v>max){
	max = v;
      }
    }
    return max;
  }

};
