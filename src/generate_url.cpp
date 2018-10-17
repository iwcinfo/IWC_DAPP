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
  std::string getHashValue(std::string pkey, std::string parameters);
  std::string getURL(std::string url_base, std::map<std::string, std::string> paramater_map);
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

std::string GenerateURL::getHashValue(std::string pkey, std::string parameters) {
  std::string hash = "";
  char buffer [99];
  std::string params = pkey + parameters;
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

// Accept and handle parameter for URL
std::string GenerateURL::getURL(std::string url_base, std::map<std::string, std::string> paramater_map) {
  std::string url = url_base + "?";
  std::string url_parameters = "";
  for (auto it = paramater_map.begin(); it != paramater_map.end(); ){
    std::string parameter_name = it->first;
    std::string parameter_value = it->second;
    url_parameters += parameter_name + "=" + parameter_value;
    ++it;

    if (it == paramater_map.end()) {
      url += url_parameters + "&hash=" + getHashValue(pkey, url_parameters);
    } else {
      url_parameters += "&";
    }
  }

  return url;
}

int main() {
  GenerateURL a = * new GenerateURL();
  std::map<std::string, std::string> parameters;
  parameters.insert(make_pair("endDate", a.getCurrentDate() + "%20" + a.getCurrentTime()));
  parameters.insert(make_pair("operatorID", "ibct_iwc"));
  std::string url = a.getURL("http://iwc.io/apiTest", parameters);
  cout << url << endl;
  return 0;
}
