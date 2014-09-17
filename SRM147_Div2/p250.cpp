#include <vector>
#include <string>
#include <iostream>

using namespace std;

class CCipher{
public:
  string decode(string cipherText,int shift){
    string ret = "";
    for(char c: cipherText){
      char newc = c-shift;
      if(newc<'A'){
	newc+= 26;
      }
      ret += newc;
    }
    return ret;
  }

};
