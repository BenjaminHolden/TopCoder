#include <string>
#include <cstdio>
#include <iostream>
#include <cmath>


using namespace std;

class ExerciseMachine{

public:
  int getPercentages(string time){
    int hours, mins, secs;
    sscanf(time.c_str(), "%d:%d:%d",&hours,&mins,&secs);
    int seconds = hours*3600 + mins*60 + secs;
    cout <<"Total Time: "<< seconds<<"\n";
    int rem = seconds % 100;
    cout<<"Remainder: "<<rem<<endl;
    int count = 0;
    int ret = 0;
    for(int i=0;i<99;i++){
      count += rem;
      if(count%100 == 0){
	ret++;
      }
    }
    /*
      double d_count = seconds/100.0;
      double count =0;
      int ret = 0;
      for(int i=0;i<99;i++){
      count += d_count;
      cout<<count;
      if(abs(round(count) - count)<){
      cout<<":equal\n";
      ret++;
      }else{
      cout<<":not equal"<<round(count)-count <<"\n";
      }
      }
    */
    return ret;
  }


};
