//#include "iostream"
//#include "algorithm"
//#include "vector"
//#include "set"
//#include "string"
//using namespace std;
//
//string decore(string& s, int& i, int time) {
//	string s1 = "";
//	while (i < s.size() && s[i] != ']') {
//		if (s[i]>='0'&&s[i]<='9' ) {
//			int t1 = s[i ] - '0';
//			i += 2;
//			string st = decore(s, i , t1);
//			++i;
//			s1 += st;
//		}
//		else {
//			s1 += s[i++];
//		}
//	}
//	string sr = "";
//	for (int j = 0; i < time; ++j) {
//		sr.append(s1);
//	}
//	return sr;
//}
//
//string decodeString(string s) {
//	if (s.empty())
//		return s;
//	string sr = "";
//	int i = 0;
//	sr += decore(s, i, 1);
//	return sr;
//}
//
//int main() {
//	string s = "3[a]2[bc]";
//	cout << decodeString(s) << endl;
//}