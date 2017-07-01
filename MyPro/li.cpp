//#include "sstream"
//#include "iostream"
//#include "string"
//#include "vector"
//using namespace std;
//
//
//int coins(vector<int>& v, int tar) {
//	if (v.empty() || tar < 0)
//		return 0;
//	vector<vector<int>> dp(v.size(), vector<int>(tar + 1));
//	for (int i = 0; i < v.size(); ++i) {
//		dp[i][0] = 1;
//	}
//	for (int i = 1; v[0] * i <= tar; ++i) {
//		dp[0][v[0] * i] = 1;
//	}
//	for (int i = 1; i < v.size(); ++i) {
//		for (int j = 1; j <= tar; ++j) {
//			int num = 0;
//			for (int k = 0; k*v[i] <= j; ++k) {
//				num += dp[i - 1][j - k*v[i]];
//			}
//			dp[i][j] = num;
//		}
//	}
//	return dp[v.size() - 1][tar];
//}
//
//
//
//int main() {
//	vector<int> v = { 1, 2, 3,4,5 };
//	cout << coins(v, 6) << endl;
//}