#include <vector>
#include <string>

using namespace std;

class ImageDithering{

public:
  int count(string dithered, vector<string> screen){
    int count = 0;
    for(auto s: screen){
      for(auto d: dithered){
	for(auto c: s){
	  if(d == c){
	    count++;
	  }
	}
      }
    }
    return count;
  }
};
