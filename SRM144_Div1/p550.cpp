#include <string>
#include <vector>
#include <cstdint>
#include <cassert>
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;


class Lottery{
private:
struct MyData{
	string name;
	uint64_t num;
	
	bool operator<(const MyData &d) const{
		if(num == d.num){	//if numbers are the same, sort by name
			return name < d.name;
		}else{					//else sort by numbers
			return num < d.num;
		}
	}
};

bool parseBool(string str){
	if(str == "T"){
		return true;
	}else if(str == "F"){
		return false;
	}else{
		assert(false);
	}
}

string getNextString(istringstream &ss, char delem){
	string str;
	if(getline(ss,str, delem)){
		cout<<"Got String: "<<str<<endl;
		return str;
	}else{
		assert(false);
	}
}

/** 
s*(s-1)*(s-2)*(s-3)*...*(e+2)*(e+1) 
Note: includes s, does not include e
**/
uint64_t factorial(uint64_t s, uint64_t e){
	uint64_t ret = 1;
	for(int i=s;i>e;i--){
		ret *= i;
	}
	return ret;
}

/**
a^b
**/
uint64_t myPOW(uint64_t a, uint64_t b){
	uint64_t ret = 1;
	for(int i=0;i<b;i++){
		ret *= a;
	}
	return ret;
}

MyData helper(string rule){
	//<NAME>: <CHOICES> <BLANKS> <SORTED> <UNIQUE>
	int end_name = rule.find(":");
	string name = rule.substr(0,end_name);
	rule.erase(0,end_name+2); //+2 to include delimiter and space after
	istringstream ss(rule);
	
	uint64_t choices = stoi(getNextString(ss, ' '));
	uint64_t blanks = stoi(getNextString(ss, ' '));
	bool sorted = parseBool(getNextString(ss, ' '));
	bool unique = parseBool(getNextString(ss, ' '));

	
	cout<<name<<": ";
	int num=0;
	if(sorted && unique){
		cout<<"Type #1: ";
		// C!/(B!*(C-B)!)
		num = factorial(choices,choices-blanks)/factorial(blanks,0);
	}else if(!sorted && unique){
		cout<<"Type #2: ";
		//C!/(C-B)!
		num = factorial(choices,choices-blanks);
	}else if(sorted && !unique){
		cout<<"Type #3: ";
		//(C+B-1)!/(B!*(C-1)!)
		num = factorial(choices+blanks-1,choices-1)/factorial(blanks,0);
	}else if(!sorted && !unique){
		cout<<"Type #4: ";
		//C^B
		num = myPOW(choices,blanks);
		
	}else{
		assert(false);
	}
	cout<<"Choices: "<<choices<<", blanks: "<<blanks<<endl;
	
	MyData ret;
	ret.name = name;
	ret.num = num;
	return ret;
} 
public:
vector<string> sortByOdds(vector<string> rules){
	vector<MyData> x;
	for(auto &i : rules){
		x.push_back(helper(i));
	}
	sort(x.begin(), x.end());
	
	vector<string> ret;
	for(auto &i : x){
		ret.push_back(i.name);
	}
	return ret;
}


};
