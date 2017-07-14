#include "iostream"
#include "ban.h"
using namespace std;

void ban::print1(int i){
	cout << i << endl;
}
void ban::print2(int i){
	cout << i + 1 << endl;
}
void ban::print3(int i){
	cout << i * 2 << endl;
}

ban::ban(){
	vector<fun> help = { &ban::print1, &ban::print2 };
	mp[1] = help;
}

void ban::pushban(){
	for (auto it = mp[0].begin(); it != mp[0].end; ++it){
		(this->*(*it))(5);
	}
}