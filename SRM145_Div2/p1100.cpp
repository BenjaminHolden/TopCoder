#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <cstdio>

using namespace std;

class VendingMachine{

public:
  int cur_c = 0;
  int motor_time = 0;
  vector<vector<int>> cost;//(prices.size());		//shelf, column

  int motorUse(vector<string> prices, vector<string> purchases){
    cost.resize(prices.size());
    for(int i=0;i<prices.size();i++){
      string p = prices[i];
      stringstream ss(p);
      string v;
      while(getline(ss,v,' ')){
	int val = stoi(v);
	cost[i].push_back(val);
	cout << val <<", ";
      }
      cout<<"\n";
    }
	
	
    rotateExpensive();
    int last_time = 0;
    for(auto p:purchases){
      int s,c,t;
      sscanf(p.c_str(),"%d,%d,%d",&s,&c,&t);
      if(t-last_time >= 5){
	cout <<"Time >=5, so may rotate"<<endl;
	rotateExpensive();
      }
      rotate(c);		//updates cur_c and motorTime
      if(cost[s][c] == 0){
	return -1;
      }
      cout<<"Removed: s: "<<s<<", c: "<<c<<", val: "<<cost[s][c]<<endl;
      cost[s][c] = 0; //remove the item
      last_time = t;
    }
    rotateExpensive();
    return motor_time;
  }
private:
  void rotateExpensive(){
    int n_s = cost.size(); //number of shelfs
    int n_c = cost[0].size(); //number of columns
    int max_val = 0; 
    int max_c = 0; //which column
    for(int c=0;c<n_c;c++){
      int curSum = 0;
      for(int s=0;s<n_s;s++){
	curSum += cost[s][c];
      }
      if(curSum > max_val){ //if equal then don't change -- causes lowest c to be chosen
	max_val = curSum;
	max_c = c;
      }
    }
    cout<<"Called rotateExpensive() --> max_c = "<<max_c<<endl;
    rotate(max_c);
  }
  void rotate(int c){
    if(cur_c == c){
      return;
    }
    int n_c = cost[0].size(); //number of columns
    //find dist
    int dist1 = abs(cur_c-c);
    int dist2 = (n_c-max(c,cur_c)) + min(c,cur_c);
    int dist = min(dist1,dist2);
	
    //rotate it!
    cout<<"rotated: motor_time: "<<motor_time<<", cur_c: "<<cur_c<<endl;
    motor_time += dist;
    cur_c = c;
  }
};
