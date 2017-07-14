#include "new.h"
#include "iostream"
#include "algorithm"
#include "string"
#include "vector"
#include "map"
#include "banner.h"
using namespace std;

typedef void(*pm)(int);
void filter( int i){
	cout << i << endl;
}
void filter2(int j){
	cout << j+1 << endl;
}
void filter3(int k){
	cout << k+6 << endl;
}



int main(){
	vector<pm> help = {&filter,&filter2};
	vector<pm> help2 = { &filter3 };
	map<int, vector<pm>> mp;
	mp[1] = help;
	mp[2] = help2;
	
	/*for (auto it = help.begin(); it != help.end(); ++it){
		(*it)(j);
	}*/
}