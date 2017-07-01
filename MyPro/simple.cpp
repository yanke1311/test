//#include <iostream>
//#include <typeinfo>
//#include "string"
//#include "vector"
//#include "ctime"
//using namespace std;
//
//bool cancore(string& s1, int i1, string&s2, int i2, string& s3, int i3) {
//	if (i3 == s3.size()) {
//		return true;
//	}
//	if (i1 == s1.size() && i2 == s2.size())
//		return false;
//	bool can = false;
//	if (i1 < s1.size() && s3[i3] == s1[i1]) {
//		can = cancore(s1, i1 + 1, s2, i2, s3, i3 + 1);
//	}
//	if (!can&&i2 < s2.size() && s3[i3] == s2[i2]) {
//		can = cancore(s1, i1, s2, i2 + 1, s3, i3 + 1);
//	}
//	if (!can&&i1 < s1.size() && s3[i3] != s1[i1]) {
//		int index = i1;
//		while (index < s1.size() && s3[i3] != s1[index]) {
//			++index;
//		}
//		can = cancore(s1, index, s2, i2, s3, i3);
//	}
//	if (!can&&i2 < s2.size() && s3[i3] != s2[i2]) {
//		int index = i2;
//		while (index < s2.size() && s3[i3] != s2[index]) {
//			++index;
//		}
//		can = cancore(s1, i1, s2, index, s3, i3);
//	}
//	return can;
//}
//
//bool canuse(string& s1, string&s2, string&s3) {
//	return cancore(s1, 0, s2, 0, s3, 0);
//}
//
//int main()
//{
//	string s1 = "abcdegmopqrst";
//	string s2 = "acfmnorqstlxy";
//	string s3 = "abcdegmnnopsto";
//	bool can = canuse(s1, s2, s3);
//	if (can == true) {
//		cout << "can" << endl;
//	}
//	else {
//		cout << "cannot" << endl;
//	}
//}