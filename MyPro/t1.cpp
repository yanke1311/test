#include "iostream"
#include "vector"
#include "random"
#include "ctime"
using namespace std;

vector<unsigned> randomGenerate(const unsigned low, const unsigned high)
{
	static default_random_engine e(time(0));
	static uniform_int_distribution<unsigned> u(low, high);

	vector<unsigned> vec;
	for(int i = 0; i<10; i++)
		vec.push_back(u(e));
	return vec;
}

int main(){
    for (int i = 0; i < 10; i++)
    {
    	vector<unsigned> vec = randomGenerate(0, 30);
    	for (auto &i : vec)
    		cout << i<< " ";
    	cout << endl;
    }
}