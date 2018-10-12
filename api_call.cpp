#include <iostream>
#include "api_call.hpp"
#include "define.h"


using namespace std;

__int64_t ApiCall::getCurrentTime() {
    currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    return currentTime;
}

int main() {
  ApiCall inst = *new ApiCall();
  cout << inst.getCurrentTime() << endl;
  return 0;
}
