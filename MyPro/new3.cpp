//#include "iostream"
//#include "vector"
//#include "string"
//#include "algorithm"
//#include "functional"
//using namespace std;
//
//bool iscore(vector<int>& nums, vector<int>& edge, int step,int tar) {
//	if (step == nums.size())
//		return true;
//	for (int i = 0; i < 4; ++i) {  //
//		if (edge[i] + nums[step]>tar)
//			continue;
//		if (step<4 && i>step)  //�϶��е���Ԫ�ض���tar�������϶����У�������ô��ǰ4����Ӧ�ó����������
//			break;
//		edge[i] += nums[step];
//		if (iscore(nums, edge, step + 1, tar))
//			return true;
//		edge[i]-=nums[step];   //���iscoreΪfalse����Ҫ�����￪ʼ
//	}
//	return false;
//}
//
//bool makesquare(vector<int>& nums) {
//	if (nums.empty())
//		return false;
//	int sum = 0;
//	for (int i = 0; i < nums.size(); ++i) {
//		sum += nums[i];
//	}
//	if (sum % 4 != 0)
//		return false;
//	sort(nums.begin(), nums.end(), greater<int>());
//	vector<int> edge(4);
//	return iscore(nums, edge, 0, sum / 4);
//}
//
//
//
//int main() {
//
//}