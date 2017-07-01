//#include "iostream"
//#include "vector"
//#include "string"
//#include "algorithm"
//using namespace std;
//
//vector<int> maxun(string& s) {
//	vector<int> len(s.size());
//	if (s.empty())
//		return len;
//	vector<int> map(256, -1);
//	int pre = -1;
//	int cur = 0;
//	for (int i = 0; i < s.size(); ++i) {
//		pre = max(pre, map[s[i]]);
//		cur = i - pre;
//		len[i] = cur;
//		map[s[i]] = i;
//	}
//	return len;
//}
//
//int main() {
//	string s = "aabcb";
//	vector<int> v = maxun(s);
//	int imax = 0;
//	for (int i = 0; i < v.size(); ++i) {
//		if (v[i] > v[imax])
//			imax = i;
//	}
//	string s1 = "";
//	s1+=s[imax];
//	int right = v[imax];
//	for (int i = imax-1; i >= 0; --i) {
//		if (v[i] == right - 1) {
//			s1 += s[i];
//			right -= 1;
//		}
//	}
//	reverse(s1.begin(), s1.end());
//	cout << s1 << endl;
//}