#include <string>
#include <iostream>


using namespace std;

class PeopleCircle{
public:
  string order(int numMales, int numFemales,int k){
    string curOrder = "";
    for(int i =0;i<numMales;i++){
      curOrder+= "M";
    }
    Ret myRet = helper(curOrder,numFemales,k,0);
    string ans = "";
    int j = myRet.pos;
    int N = myRet.order.length();
    for(int i=0;i<N;i++){
      j = j%N;
      ans+=myRet.order[j++];
    }
    return ans;
  }

private:
  struct Ret{
    int pos;
    string order;
  };

  Ret helper(string curOrder, int numFemaleLeft, int k, int curPos){
    int newPos = curPos-k+1;
    int N = curOrder.size();
    newPos = N==0 ? 0 : newPos % N;
    newPos = newPos<0 ? newPos+N : newPos;
	
    if(numFemaleLeft == 0){
      Ret myRet;
      myRet.order = curOrder;
      myRet.pos = newPos;
      return myRet;
    }

    string newOrder = "";
    int curOrder_i =0;
    for(int i=0;i<curOrder.size()+1;i++){
      if(i==newPos){
	newOrder += "F";
      }else{
	newOrder += curOrder[curOrder_i++];
      }
    }
    return helper(newOrder,numFemaleLeft-1,k,newPos);
  }

};

int main(int argc, char* argv[]){
  if(argc != 4){
    cout << "Wrong number of inputs: "<<argc<<endl;
    return 0;
  }
  int m = stoi(string(argv[1]));
  int f = stoi(string(argv[2]));
  int k = stoi(string(argv[3]));
  PeopleCircle p;
  cout<<"Calling order("<<m<<", "<<f<<", "<<k<<")"<<endl;
  string ret = p.order(m,f,k);
  cout<<"Answer: "<<ret<<endl;

}
