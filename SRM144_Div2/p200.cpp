#include <string>
#include <sstream>

class Time{
public:
  std::string whatTime(int seconds){
    
    int hours = seconds / 3600;
    int mins = (seconds % 3600) / 60;
    int secs = seconds % 60;
    
    std::stringstream ss;
    ss << hours << ":" << mins << ":" <<secs;
    return ss.str();
  }
};
