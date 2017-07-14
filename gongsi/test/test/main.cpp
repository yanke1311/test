//#include "iostream"
////#include "algorithm"
//#include "vector"
////#include "functional"
////#include "numeric"
//#include "map"
//#include "sstream"
//#include "string"
//using namespace std;
///*一个挺好的求交！！*/
//
//bool binarysearch(vector<int>&list, int& v, int i, int& result){  
//	int left = i, right = list.size();
//	while (left < right - 1){
//		int mid = (right + left) >> 1;
//		if (list[mid] <= v){
//			left = mid;
//		}
//		else{
//			right = mid;
//		}
//	}
//	result = left;
//	return left >= 0 && list[left] == v;
//}
//
//void intersect(vector<int>&small, vector<int>& large, vector<int>& result){
//	int occur = 0;
//	int i = 0, j = -1;  //j感觉没必要取-1
//	int size1 = small.size(), size2 = large.size();
//	result.reserve(size1);
//	while (i < size1&&j < size2){
//		if (binarysearch(large, small[i], j, occur)){
//			result.push_back(small[i]);
//		}
//		j = occur + 1;
//		if (j < size2&&binarysearch(small, large[j], i, occur)){
//			result.push_back(large[j]);
//		}
//		i = occur + 1;
//	}
//}
//
//int main(){
//	vector<int> small = { 1, 2, 3 }, large = { 2, 3, 4, 5 }, result;
//	intersect(small, large, result);
//	for (auto i : result){
//		cout << i << " ";
//	}
//	cout << endl;
//}