#include <string>
#include <iostream>

using namespace std;

class RectangularGrid{
public:
  long long countRectangles(int width, int height){
    long long count = 0;
    for(int w=1;w<=width;w++){
      for(int h=1;h<=height;h++){
	if(w!=h){
	  count += (abs(w-width)+1)*(abs(h-height)+1);
	}
      }
    }
	
    return count;
  }


};
