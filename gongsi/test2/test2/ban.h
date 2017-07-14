#include "iostream"
#include "vector"
#include "stdlib.h"
#include "map"
using namespace std;

class ban{
	typedef void(ban::*fun)(int i);
public:
	ban();
	void pushban();
public:
	void print1(int i);
	void print2(int i);
	void print3(int i);
	map<int,vector<fun>> mp;
};