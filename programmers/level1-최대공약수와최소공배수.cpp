#include <string>
#include <vector>

using namespace std;

/**
 * Calculate greatest common divisor.
 *
 * @param n
 * @param m
 *
 * @return
 */
int calculateGCD(int n, int m) {
  int divisor = 0;
  int dividend = 0;
  int remainder = 0;

  // set dividend and divisor
  if (n == m) {
    return n;
  } else if (n > m) {
    dividend = n;
    divisor = m;
  } else if (m > n) {
    dividend = m;
    divisor = n;
  }

  do {
    remainder = dividend % divisor;
    dividend = divisor;
    divisor = remainder;
  } while(remainder != 0);

  return dividend;
}

/**
 * Calculate least common multiple.
 *
 * @param n
 * @param m
 *
 * @return
 */
int calculateLCM(int n, int m) {
  return n * m / calculateGCD(n, m);
}

vector<int> solution(int n, int m) {
  vector<int> answer;
  answer.reserve(2);
  answer.push_back(calculateGCD(n, m));
  answer.push_back(calculateLCM(n, m));

  return answer;
}