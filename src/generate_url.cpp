#include <iostream>
#include <string>
#include "define.h"
#include <iostream>
#include <cstdlib>
#include <map>
#include "md5.h"
#include <CommonCrypto/CommonDigest.h>

using namespace std;

class GenerateURL {
public:
  std::string date = START_DATE;
  std::string time = START_TIME;
  std::string url = API_URL;
  std::string pkey = PRIVATE_KEY;
  __int64_t getEpoch();
  std::string getCurrentDate();
  std::string getCurrentTime() ;
  std::string appendParameters(std::string private_key);
  std::string getHashValue();
  std::string getURL();
private:
};

__int64_t GenerateURL::getEpoch() {
  __int64_t current_time;
  current_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
  return current_time;
}

std::string GenerateURL::getCurrentDate(){
  std::time_t rawtime;
  std::tm* timeinfo;
  char buffer1 [80];
  std::time(&rawtime);
  timeinfo = std::localtime(&rawtime);
  std::strftime(buffer1,80,"%Y-%m-%d",timeinfo);
  //std::puts(buffer1);
  std::string buf1(buffer1);
  return buf1;
}

std::string GenerateURL::getCurrentTime(){
  std::time_t rawtime;
  std::tm* timeinfo;
  char buffer2 [80];
  std::time(&rawtime);
  timeinfo = std::localtime(&rawtime);
  std::strftime(buffer2,80,"%H:%M:%S",timeinfo);
  //std::puts(buffer2);
  std::string buf2(buffer2);
  return buf2;
}

std::string GenerateURL::appendParameters(std::string private_key) { // 여기 어레이가 들어가야 할 듯!
  string str = private_key + "endDate=" + getCurrentDate() + " " + getCurrentTime() + "&operatorID=ibct_iwc&startDate=" +
  date + " " + time  +"&time=" + std::to_string(getEpoch()) + "&transType=1&vendorID=0";
  return str;
}


std::string GenerateURL::getHashValue() {
  std::string hash = "";
  char buffer [80];
  std::string params = appendParameters(pkey);
  unsigned char digest[params.length()];
  const char* string = params.c_str();
  CC_MD5(string, (CC_LONG)strlen(string), digest);
  for (size_t i=0; i<CC_MD5_DIGEST_LENGTH; ++i) {
      //printf("%.2x", digest[i]);
      snprintf(buffer, sizeof(buffer), "%.2x", digest[i]);
      std::string hash_temp (buffer);
      hash = hash + hash_temp;
  }
  return hash;
}
// "Accept and handle parameter for URL init#2 github test"
std::string GenerateURL::getURL() {
  url = url + "endDate=" + getCurrentDate() + "%20" + getCurrentTime() + "&operatorID=ibct_iwc&startDate=" +
  date + "%20" + time  +"&time=" + std::to_string(getEpoch()) + "&transType=1&vendorID=0&hash=" + getHashValue();
  return url;
}

/*int main() {
  GenerateURL a = * new GenerateURL();
  cout << a.getURL() << endl;
  return 0;
}*/
