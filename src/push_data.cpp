#include <iostream>
#include <push_data.hpp>


  void uploadToBlockchain(std::string);
  std::string getTransactionNumber(); //get this directly when push transaction to the uploadToBlockchain
  std::string getTransactionHash();
  std::string mergeData(std::string trx, std::string hash, std::string api);
  void createJSON(std::string mergeddata);
  void uploadToDB(std::string filename);

  int main() {
    return 0;

  }
