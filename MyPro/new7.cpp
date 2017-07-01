//#include "iostream"
//#include "vector"
//#include "string"
//#include "algorithm"
//#include "deque"
//#include "ctime"
//using namespace std;
//
//void findpath(vector<vector<int>>& visit, vector<vector<char>>& matrix, int i, int j, int& sum,int cur,int& k,int& m,int& n) {
//	if ((i ==m-1)  && (j ==n-1)&&(cur==k-1) ) {
//		++sum;
//		return;
//	}
//	if (i == m-1&&j == n-1) {
//		return;
//	}
//	if (i<0 || i >= m || j<0 || j >= n||matrix[i][j] == '#' || visit[i][j] == 1 ) {
//		return;
//	}
//	cur += 1;
//	visit[i][j] = 1;
//	findpath(visit, matrix, i + 1, j, sum,cur,k,m,n);
//	findpath(visit, matrix, i - 1, j, sum,cur,k,m,n);
//	findpath(visit, matrix, i, j+1, sum,cur,k,m,n);
//	findpath(visit, matrix, i , j-1, sum,cur,k,m,n);
//	visit[i][j] = 0;
//}
//
//int main() {
//	vector<vector<char>> matrix = { {'.','.','.' },{ '.','.','.' } ,{'.','#','.' } };
//	vector<vector<int>> visit(matrix.size(), vector<int>(matrix[0].size()));
//	int k = 4;
//	int sum = 0;
//	int cur = 0;
//	int m = matrix.size();
//	int n = matrix[0].size();
//	findpath(visit, matrix, m-1, 0, sum, cur, k,m,n);
//	cout << sum << endl;
//}