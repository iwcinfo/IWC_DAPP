#include <ctime>
#include <chrono>

class ApiCall {
public:
  __int64_t getCurrentTime(); // 앞에 붙는 __는 C++ 표준이 아니라는 것을 뜻
  __int64_t getHashValue();

private:
  __int64_t current_time;
  __int64_t hash_value;
};
