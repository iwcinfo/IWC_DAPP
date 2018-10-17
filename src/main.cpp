#include "generate_url.cpp"
#include "get_json_api.cpp"
#include "define.h"
#include <iostream>

using namespace std;

int main() {
  GenerateURL a = * new GenerateURL();
  GetJsonAPI b = * new GetJsonAPI();
  std::string url = a.getURL();
//  b.getJsonAPI(url);
  b.GetJson(url);
  return 0;
}
