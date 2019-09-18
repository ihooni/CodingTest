#include <string>
#include <vector>

using namespace std;

vector<vector<int>> solution(vector<vector<int>> arr1, vector<vector<int>> arr2) {
  vector<vector<int>> answer;

  unsigned long arr1RowCount = arr1.size();
  unsigned long arr1ColumnCount = arr1[0].size();
  unsigned long arr2ColumnCount = arr2[0].size();
  int element = 0;

  // (m x n) mul (n x k) = m x k
  answer.resize(arr1RowCount, vector<int>(arr2ColumnCount, 0));

  int i, j, k;
  for (i = 0; i < arr1RowCount; i++) {
    for (j = 0; j < arr2ColumnCount; j++) {
      element = 0;
      for (k = 0; k < arr1ColumnCount; k++) {
        element += arr1[i][k] * arr2[k][j];
      }

      answer[i][j] = element;
    }
  }

  return answer;
}