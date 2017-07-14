#include "iostream"
#include "map"
#include "vector"
using namespace std;

struct banner{
	typedef void(*fun)(int);
	banner(){
	
	}
	void lun(int j);
private:
	void print1(int i){
		cout << i << endl;
	}
	void print2(int i){
		cout << i + 1 << endl;
	}
	void pritn3(int i){
		cout << i + 2 << endl;
	}
	vector<fun> help;

};




