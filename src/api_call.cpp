#include <iostream>
#include <string>
#include "api_call.hpp"
#include "define.h"


using namespace std;

__int64_t ApiCall::getCurrentTime() {
  current_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
  return current_time;
}

__int64_t ApiCall::getHashValue() {

  return 0;
}

/*
1. Collect all parameters in a string of the format except hash parameter
Parameters must be ordered by alphabetically.
-> param1=val1&param2=val2
2. Append PrivateKey supplied beforehand to the beginning of the string created in the previous step to receive the following string :
PrivateKeyparam1=val1&param2=val2
If PrivateKey is aabb, input string will be :
-> aabbparam1=val1&param2=val2
*/
string appendParameters(__int64_t private_key) { // 여기 어레이가 들어가야 할 듯!
  return "sss";

}

__int64_t performMdHash() {

  return 0;
}

int main() {
  ApiCall inst = *new ApiCall();
  cout << inst.getCurrentTime() << endl;
  return 0;
}
