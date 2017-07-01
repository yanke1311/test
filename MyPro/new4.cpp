//#include "vector"
//#include "iostream"
//#include "algorithm"
//#include "string"
//using namespace std;
//
//bool search(vector<int>& nums, int target) {
//	if (nums.empty())
//		return false;
//	int start = 0;
//	int end = nums.size()-1;
//	int mid;
//	while (start <= end) {
//		mid = (start + end) / 2;
//		if (nums[mid] == target)
//			return true;
//		else if (nums[mid] > nums[start]) {
//			if (target >= nums[start] && target < nums[mid]) {
//				end = mid - 1;
//			}
//			else {
//				start = mid + 1;
//			}
//		}
//		else if (nums[mid] < nums[start]) {
//			if (target<=nums[end] && target>nums[mid]) {
//				start = mid + 1;
//			}
//			else {
//				end = mid - 1;
//			}
//		}
//		else {  //nums[mid]==nums[start]
//			++start;
//		}
//	}
//	return false;
//}
//
//int main() {
//	vector<int> v = { 1,3,5 };
//	int i = 1;
//	cout<<search(v, i)<<endl;
//}