#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <iostream>
#include <cpprest/json.h>
using namespace utility;                    // Common utilities like string conversions
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features
using namespace concurrency::streams;       // Asynchronous streams

class GetJsonAPI {
public:
	pplx::task<json::value> data;
	void getJsonAPI(std::string url);
	void GetJson(std::string url);
};

void GetJsonAPI::getJsonAPI(std::string url)
{
	http_client client(U(url));
	http_request req(methods::GET);
	client.request(req).then([=](http_response r){
		std::string data =  r.extract_json().get().serialize(); //string data of json output
	//	std::cout << "start here" << std::endl << std::endl;
	//	std::cout << "end here" << std::endl << std::endl;
		//std::string size = v.at(U("totalDataSize")).serialize(); //string data of total datasize
	//	std::cout << size << std::endl
	//data = r.extract_json();
		//std::cout << std::endl<< std::endl << r.extract_json().get() << std::endl << std::endl;
	}).wait();
}

void GetJsonAPI::GetJson(std::string url)
{
	http_client client(U(url));

	http_request req(methods::GET);

	client.request(req).then([=](http_response r){
		r.extract_json(true).then([](json::value v) {
			json::value transaction = v.at(U("transactions"));
			std::cout << transaction.at(0).at(U("transType")) << std::endl;
			//std::cout << size << std::endl;
			//std::cout << "DATASIZE:  ";
			//std::cout << v.at(U("totalDataSize")) << std::endl;
			//std::cout<< "Type is "<< v.at(U("totalDataSize")).type() << endl;
			//std::cout << v.at(U("transactions")).get(U("transID")) << std::endl;
			//std::cout << v.at(U("transactions")).at(U("transID")).as_string() << std::endl;
		}).wait();

	}).wait();

}
/*int main(int argc, char* argv[])
{
	GetJsonAPI a = * new GetJsonAPI();
    a.getJsonAPI("test");
    return 0;
}*/
