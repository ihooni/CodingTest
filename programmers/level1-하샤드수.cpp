#include <string>
#include <vector>

using namespace std;

bool solution(int x) {
    bool answer = false;

    // integer to char pointer
    string numStr = to_string(x);
    const char* numCP = numStr.c_str();

    int sumOfDigits = 0;
    int i = 0;
    while (numCP[i] != '\0') {  // until end of char
        sumOfDigits += (numCP[i] - '0');  // sum up each digits
        i++;
    }

    // check if harshad number
    if (x % sumOfDigits == 0) {
        answer = true;
    }

    return answer;
}