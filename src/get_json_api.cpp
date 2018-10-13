#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <iostream>
#include <cpprest/json.h>
using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams

void getJsonAPI()
{
	http_client client2(U("http://api.krw.ximaxgames.com/wallet/api/getAccountBalance?isRenew=true&operatorID=ibct_iwc&thirdPartyCode=29&time=1539427068325&userID=IBCT_IWC&vendorID=0&hash=bfb69d8998ad6ab58419c1d1dd0c23b7"));
	http_request req2(methods::GET);
client2.request(req2).then([=](http_response r){
//  web::json::value v1 = json::value::parse(U("{ \"a\" : 10 }"));
//  std::cout << v1.at(U("a")) << std::endl;
//  std::cout << v1 << std::endl;
  std::cout << std::endl<< std::endl << r.extract_json().get() << std::endl << std::endl;
}).wait();
}

int main(int argc, char* argv[])
{
    getJsonAPI();
    return 0;
}
