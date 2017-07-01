#include "iostream"
#include "vector"
#include "string"
using namespace std;

vector<int> GetNext(string& m) {
	//if(m.empty())
	vector<int> next;
	next.resize(m.size());
	next[0] = -1;
	next[1] = 0;
	int pos = 2;
	int cn = 0;
	while (pos < m.size()) { //cn为前面匹配，pos为当前的所在位置
		if (m[pos - 1] == m[cn]) {
			next[pos++] = ++cn;
		}
		else if (cn != 0) {
			cn = next[cn];
		}
		else {
			next[pos++] = 0;
		}
	}
	return next;
}

int GetMatch(string s, string m) {
	vector<int> next = GetNext(m);
	int spos = 0, mpos = 0;
	while (spos < s.size() && mpos < m.size()) {
		if (s[spos] == m[mpos]) {
			++spos;
			++mpos;
		}
		else if(next[mpos]==-1){
			++spos;
		}
		else {
			mpos = next[mpos];
		}
	}
	return mpos == m.size() ? spos - mpos : -1;  //一定要全匹配
}

int main() {
	string s = "acbc";
	string m = "bcc";
	cout << GetMatch(s, m)<<endl;
	system("pause");
}
