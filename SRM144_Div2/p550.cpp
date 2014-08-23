#include <string>
#include <vector>
#include <iostream>

class BinaryCode{

  std::string helper(std::string Q, std::string P, int val){
    int cur_P = P[val] - '0';
    int prev_P = 0;
    if(val > 0){
      prev_P = P[val-1] - '0';
    }
    int cur_Q = Q[val] - '0';
    int new_P_val = cur_Q-(cur_P+prev_P);
    if((new_P_val != 1) && (new_P_val != 0)){
      return "NONE";	//must be a 0 or 1
    }
    if(val == Q.length()-1){
      if(new_P_val == 0){
	return P; //Checks out!
      }else{
	std::cout << "Got NONE because last check failed";
	return "NONE";
      }
    }
    std::string new_P = P + std::to_string(new_P_val);
    return helper(Q,new_P,val+1);
  }
public:
  std::vector<std::string> decode(std::string Q){
    std::string ret_first = helper(Q,"0",0);
    std::string ret_second = helper(Q,"1",0);
    std::vector<std::string> ret;
    ret.push_back(ret_first);
    ret.push_back(ret_second);
    return ret;
  }

};
