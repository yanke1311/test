//#include "iostream"
//#include "stdlib.h"
//#include "vector"
//
//using namespace std;
//
//void heapadj(vector<int>& v, int start, int end)
//{
//	int i = start * 2 + 1;
//	while (i <= end) {         //´ó¸ù¶Ñ
//		if (i<end&&v[i + 1]>v[i]) {
//			++i;
//		}
//		if (v[start] < v[i]) {
//			swap(v[start], v[i]);
//			start = i;
//			i = start * 2 + 1;
//		}
//		else {
//			break;
//		}
//	}
//}
//
//void heap(vector<int>& v) {
//	int e = v.size() - 1;
//	for (int i = (e - 1) / 2; i >= 0; --i) {
//		heapadj(v, i, e);
//	}
//	for (int i = e; i > 0; --i) {
//		swap(v[i], v[0]);
//		heapadj(v, 0, i - 1);
//	}
//}
//
//
//int main() {
//	vector<int> v = { 21,43,54,23,546,878,53 };
//	heap(v);
//	for (auto i : v) {
//		cout << i << "  ";
//	}
//	cout << endl;
//}