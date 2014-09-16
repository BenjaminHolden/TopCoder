
#include <vector>
#include <iostream>
#include <string>
#include <climits>

using namespace std;

class BridgeCrossing{
public:
  vector<int> myTimes;

  enum Side{
    START,
    END
  };
  struct State{
    vector<int> start_side;	//holds indices of people on start side
    vector<int> end_side;
    Side mySide = START;
    int time =0;
  };

  int minTime(vector<int> times){
    int N = times.size();
    if(N == 0){
      return 0;
    }
    myTimes = times;
    State myState;
    for(int i=0;i<N;i++){
      myState.start_side.push_back(i);
    }
    return helper(myState);
  }

private:
  int helper(State s){
    if(s.start_side.size() == 0){
      return s.time;
    }
	
    int min_time = INT_MAX;
    if(s.mySide == START){
      if(s.start_side.size() == 1){
	return s.time + myTimes[s.start_side[0]];
      }
      for(int i=0;i<s.start_side.size();i++){
	for(int j=0;j<s.start_side.size();j++){
	  if(i == j){
	    continue; //can't move the same person twice at the same time
	  }
	  if(j>i){
	    continue; //i j, is the same as j i --> so don't do both
	  }
	  int person_i = s.start_side[i];
	  int person_j = s.start_side[j];
	  State s_new = s;
	  myRemove(&s_new.start_side, person_i);	
	  myRemove(&s_new.start_side, person_j);
	  s_new.end_side.push_back(person_i);
	  s_new.end_side.push_back(person_j);
	  s_new.time += max(myTimes[person_i],myTimes[person_j]);
	  s_new.mySide = END;
	  int time = helper(s_new);
	  if(time<min_time){
	    min_time = time;
	  }
	}
      }
    }else{	//mySide == END
      for(int i=0;i<s.end_side.size();i++){
	int person_i = s.end_side[i];
	State s_new = s;
	myRemove(&s_new.end_side, person_i);		 		//remove person from end side
	s_new.start_side.push_back(person_i);	//add person to start side
	s_new.time += myTimes[person_i]; 		//increase time
	s_new.mySide = START;					//change mySide to START
	//cout<<"Person: "<<person_i<<", moved from end side --> start side, in t: "<<myTimes[person_i]<<", for a current total time of: "<<s_new.time<<endl;
	int time = helper(s_new);
	if(time<min_time){
	  min_time = time;
	}
      }
	
    }
    return min_time;
	
  }

  void myRemove(vector<int>* v, int val){
    for(int i=0;i<v->size();i++){
      if(val == v->at(i)){
	v->erase(v->begin() + i);
	return;
      }
    }
    cerr << "Failed to find element with value: "<<val<<endl;
    for(auto v_e : *v){
      cerr<<v_e<<", ";
    }
    cerr<<endl;
    exit(-1);
  } 

};
