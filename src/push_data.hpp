//input: tx number, tx hash, json api
//output:: complete json made of inputs
/*
void uploadToBlockchain(string)
string getTransactionNumber()
string getTransactionHash()
string mergeData(): complete json in string
void createJSON(string completeJSONinString)
void uploadToDB(File jsonFile)

*/
#include<iostream>

class PushData {
public:
  std::string transaction_num;
  std::string transaction_hash;
  void uploadToBlockchain(std::string);
  std::string getTransactionNumber(); //get this directly when push transaction to the uploadToBlockchain
  std::string getTransactionHash();
  std::string mergeData(std::string trx, std::string hash, std::string api);
  void createJSON(std::string mergeddata);
  void uploadToDB(std::string filename);
private:
};
