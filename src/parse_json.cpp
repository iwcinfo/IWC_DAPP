#include <iostream>
#include <fstream>
//#include "generate_url.cpp"
#include <string>

std::string readJson(__int64_t epoch) {
  std::string epoch_string = std::to_string(epoch);
  std::ifstream ifs("/home/eos/contracts/IWC_DEV/log/api_out.json");
  std::string content( (std::istreambuf_iterator<char>(ifs) ),
                       (std::istreambuf_iterator<char>()    ) );
  //std::cout << content << "  ddd"<< std::endl;
  std::string command = "python /home/eos/contracts/IWC_DEV/src/parse.py \"";
  command = command.append(epoch_string);
  command = command.append("\" '");
  command = command.append(content);
  command = command.append("'");
  system(command.c_str());
  return content;
}




