#include <iostream>
#include <string>
#include "define.h"
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <iomanip>
#include <sstream>

using namespace std;

class GenerateURL{
public:
  std::string url = API_URL;
  std::string pkey = PRIVATE_KEY;
  std::string oper = OPERATOR;
  __int64_t getEpoch();
  std::string getCurrentDate();
  std::string getCurrentTime() ;
  std::string appendParameters(std::string private_key);
  std::string getURL();
  std::string getStartTime();
  std::string getStartDate();
  std::time_t addOneSecond();
  __int64_t epoch;
  std::string current_date;
  std::string current_time;
  std::string start_time;
  std::string start_date;
  std::time_t epoch_one_second_later;
  GenerateURL(std::string start_date_, std::string start_time_) {
    epoch = getEpoch();
    current_date = getCurrentDate();
    current_time = getCurrentTime();
    epoch_one_second_later = addOneSecond();
    start_date = start_date_;
    start_time = start_time_;
  };
private:
};

__int64_t GenerateURL::getEpoch() {
  __int64_t epoch_ = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
  return epoch_;
}

std::string GenerateURL::getCurrentDate(){
  std::time_t rawtime;
  std::tm* timeinfo;
  char buffer1 [80];
  std::time(&rawtime);
  timeinfo = std::localtime(&rawtime);
  std::strftime(buffer1,80,"%Y-%m-%d",timeinfo);
  std::string current_date_(buffer1);
  return current_date_;
}

std::string GenerateURL::getCurrentTime(){
  std::time_t rawtime;
  std::tm* timeinfo;
  char buffer2 [80];
  std::time(&rawtime);
  timeinfo = std::localtime(&rawtime);
  std::strftime(buffer2,80,"%H:%M:%S",timeinfo);
  std::string current_time_(buffer2);
  return current_time_;
}

std::string GenerateURL::appendParameters(std::string private_key) {
  std:: string str = private_key + "endDate=" + current_date + " " + current_time + "&operatorID=" + oper + "&pageSize=2500&startDate=" + start_date + " " + start_time  +"&time=" + std::to_string(epoch) + "&transType=1&vendorID=0";
  return str;
}

std::string GenerateURL::getURL() {
  url = url + "endDate=" + current_date + "%20" + current_time + "&operatorID=" + oper + "&pageSize=2500&startDate=" +
    start_date + "%20" + start_time  +"&time=" + std::to_string(epoch) + "&transType=1&vendorID=0&hash=";
  return url;
}

std::time_t GenerateURL::addOneSecond() {
  return epoch / 1000 + 1;
}

std::string GenerateURL::getStartTime() {
  std::stringstream ss;
  ss << std::put_time(std::localtime(&epoch_one_second_later), "%H:%M:%S");
  return ss.str();
}

std::string GenerateURL::getStartDate() {
  std::stringstream ss;
  ss << std::put_time(std::localtime(&epoch_one_second_later), "%Y-%m-%d");
  return ss.str();
}
