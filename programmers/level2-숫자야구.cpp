#include <string>
#include <vector>

using namespace std;

vector<int> countStrikeAndBall(int call, int test) {
  vector<int> strikeAndBall(2, 0);

  string callString = to_string(call);
  string testString = to_string(test);

  char const *callChar = callString.c_str();
  char const *testChar = testString.c_str();

  if (testChar[0] == testChar[1]) {
    return strikeAndBall;
  }

  if (testChar[0] == testChar[2]) {
    return strikeAndBall;
  }

  if (testChar[1] == testChar[2]) {
    return strikeAndBall;
  }

  if (testChar[1] == '0') {
    return strikeAndBall;
  }

  if (testChar[2] == '0') {
    return strikeAndBall;
  }

  int i, j;
  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      if (callChar[i] == testChar[j]) {
        if (i == j) {
          strikeAndBall[0]++;
        } else {
          strikeAndBall[1]++;
        }
      }
    }
  }

  return strikeAndBall;
}

int solution(vector<vector<int>> baseball) {
  int answer = 0;
  vector<int> result;

  int flag = 1;
  for (int i = 111; i < 999; i++) {
    for (vector<int> temp: baseball) {
      if (flag) {
        result = countStrikeAndBall(temp[0], i);

        if (result[0] != temp[1] || result[1] != temp[2]) {
          flag = 0;
        }
      }
    }

    if (flag) {
      answer++;
    }

    flag = 1;
  }

  return answer;
}