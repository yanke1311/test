#include "iostream"
#include "vector"
#include "algorithm"
using namespace std;

void GetResult(vector<vector<int>>& result,int sum,int target,vector<int>& path,int pos,vector<int>& candi) {
	if (sum == target) {
		result.push_back(path);
		return;
	}
	if (sum > target) {
		return;
	}
	for (int i = pos; i < candi.size(); ++i) {
		path.push_back(candi[i]);
		GetResult(result, sum + candi[i], target, path, i, candi);
		path.pop_back();
	}
}

vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
	vector<vector<int>> result;
	if (candidates.empty()) {
		return result;
	}
	sort(candidates.begin(), candidates.end());
	vector<int> path;
	GetResult(result, 0, target, path, 0, candidates);
	return result;
}

int main() {
	int target = 7;
	vector<int> cand = { 2,3,6,7 };
	vector<vector<int>> result=combinationSum(cand, target);
	for (auto i : result) {
		for (auto j : i) {
			cout << j << " ";
		}
		cout << endl;
	}

}