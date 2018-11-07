#include "generate_url.cpp"
#include "md5hash.h"
#include "md5hash.cpp"
#include "call_api.cpp"
#include "parse_json.cpp"
#include "add_to_db.cpp"
#include "define.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void msleep(unsigned long milisec)
{
  struct timespec req={0};
  time_t sec=(int)(milisec/1000);
  milisec=milisec-(sec*1000);
  req.tv_sec=sec;
  req.tv_nsec=milisec*1000000L;
  while(nanosleep(&req,&req)==-1)
    continue;
}


int main(int argc, char* argv[]) {
  std:string pkey = PRIVATE_KEY; // private key from define.h
  GenerateURL url_inst = GenerateURL(argv[1], argv[2]); // url inst, constructor
  std::ofstream start_date ("/home/eos/contracts/IWC_DEV/log/start_date.txt");
  std::ofstream start_time ("/home/eos/contracts/IWC_DEV/log/start_time.txt");
  std::string url = url_inst.getURL(); // url
  MD5 hash_inst = MD5(url_inst.appendParameters(pkey)); // get hash
  std::string hash = hash_inst.hexdigest(); // get hash
  url = url + hash; // url + hash
  std::ofstream out ("/home/eos/contracts/IWC_DEV/log/output.txt");
  out << url << std::endl << std::endl;
  start_date << url_inst.getStartDate();
  start_time << url_inst.getStartTime();
  out.close();
  start_date.close();
  start_time.close();
  runApiCallScript(); //in call_api.cpp
  readJson(url_inst.epoch); // in parse_json.cpp
  addToDB();
  return 0;
}
