#include <string>
#include <vector>

using namespace std;

int sigma(int n) {
  return (n * (n + 1)) / 2;
}

/**
 * If (N - sigma N) % integer is 0,
 * it can be represented by the sum of consecutive numbers.
 *
 * @param n
 * @return
 */
int solution(int n) {
  int answer = 0;

  int i = 0;
  int temp = 0;

  while (true) {
    temp = n - sigma(i);

    // iteration over
    if (temp / (i + 1) == 0) {
      break;
    }

    if (temp % (i + 1) == 0) {
      answer++;
    }

    i++;
  }

  return answer;
}