//Appears to be the same as the p550.cpp
//still chose to do new solution

#include <vector>
#include <string>

using namespace std;

class BinaryCode{
private:
  /** Given Q, Find P **/
  string helper(string Q, string P){
    if(Q.length() == P.length()){
      return P;
    }
    int i = P.length()-1;	//min will be 0 because first call P.length()==1
    int Q_cur = Q[i] -'0';	
    int P_prev = 0;
    if(i-1 >= 0){
      P_prev = P[i-1] - '0';
    }
    int P_cur = P[i] - '0';
    int P_next = Q_cur - P_prev - P_cur;
    if(P_next != 0 && P_next != 1){
      cout<<Q_cur<<", "<<P_prev<<", "<<P_cur;
      return "NONE"+P;
    }
    char P_next_char = (char) (P_next + '0');
    return helper(Q,P+P_next_char);
  }

public:
  vector<string> decode(string msg){
    vector<string> ret;
    ret.push_back(helper(msg,"0"));
    ret.push_back(helper(msg,"1"));
    return ret;
  }
};
