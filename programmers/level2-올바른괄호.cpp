#include<string>
#include <iostream>

using namespace std;

bool solution(string s)
{
  int i, sum = 0;
  char currChar;
  for (i = 0; i < s.length(); i++) {
    currChar = s.at(i);

    if (currChar == '(') {
      sum++;
    } else {
      sum--;
    }

    if (sum < 0) {
      return false;
    }
  }

  if (sum != 0) {
    return false;
  }

  return true;
}