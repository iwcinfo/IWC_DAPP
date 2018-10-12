#include <ctime>
#include <chrono>

class ApiCall {
public:
  __int64_t getCurrentTime();
private:
  __int64_t currentTime;
};
