//#include "vector"
//#include "iostream"
//#include "queue"
//#include "stack"
//#include "functional"
//#include "string"
//#include "set"
//#include "map"
//using namespace std;
//struct TreeNode{
//	int val;
//	TreeNode* left;
//	TreeNode* right;
//	TreeNode(int i) :val(i), left(NULL), right(NULL) {}
//};
//
//int getsubsum(map<int, int>& help, TreeNode* root) {
//	if (root == NULL)
//		return 0;
//	int leftsum, rightsum;
//	leftsum=getsubsum(help, root->left);
//	rightsum=getsubsum(help, root->right);
//	int sum = root->val + leftsum + rightsum;
//	if (help.count(sum) != 0) {
//		help[sum]++;
//	}
//	else {
//		help.insert({ sum,1 });
//	}
//	return sum;
//}
//
//vector<int> findFrequentTreeSum(TreeNode* root) {
//	vector<int> res;
//	if (root == NULL)
//		return res;
//	map<int, int> help;
//	getsubsum(help, root);
//	int maxcount = INT_MIN;
//	int maxsum = 0;
//	for (auto it = help.begin(); it != help.end(); ++it) {
//		if ((it->second )> maxcount) {
//			maxcount = it->second;
//			maxsum = it->first;
//		}
//	}
//	if (maxcount == 1) {
//		for (auto it = help.begin(); it != help.end(); ++it) {
//			res.push_back(it->first);
//		}
//	}
//	else {
//		res.push_back(maxsum);
//	}
//	return res;
//}
//
//int main() {
//	TreeNode* pnode1 = new TreeNode(5);
//	TreeNode* pnode2 = new TreeNode(2);
//	TreeNode* pnode3 = new TreeNode(-3);
//	pnode1->left = pnode2;
//	pnode1->right = pnode3;
//	vector<int> v=findFrequentTreeSum(pnode1);
//	for(auto i:v){
//		cout << i << " ";
//	}
//	cout << endl;
//}