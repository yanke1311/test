//#include "vector"
//#include "iostream"
//#include "algorithm"
//#include "string"
//#include "iostream"
//using namespace std;
//
//int getord(vector<int>& v, int left, int right) {
//	int imin = left;
//	for (int i = left + 1; i <= right; ++i) {
//		if (v[i] < v[imin])
//			imin = i;
//	}
//	return imin;
//}
//
//int getmin(vector<int>& v) {
//	if (v.empty())
//		throw new exception("a error");
//	int left = 0;
//	int right = v.size() - 1;
//	int imin = 0;
//	int imid;
//	while (v[left] >= v[right]) {
//		if (right - left == 1) {
//			imin = right;
//			break;
//		}
//		imid = (left + right) / 2;
//		if (v[left] == v[right] && v[left] == v[imid]) {
//			imin = getord(v, left, right);
//			break;
//		}
//		else if (v[imid] <= v[right])
//			right = imid;
//		else
//			left = imid;
//	}
//	return v[imin];
//}
//
//int main() {
//	vector<int> v = { 1,0,1,1,1 };
//	cout << getmin(v) << endl;
//}