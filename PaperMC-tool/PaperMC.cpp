#include <iostream>
#include "nlohmann/json.hpp"
#include "PaperMC.h"
#include "curl/curl.h"

using json = nlohmann::json;

static size_t WriteCallback(char *contents, size_t size, size_t nmemb, char *buffer_in)
{
	((std::string*)buffer_in)->append((char*)contents, size * nmemb);

	return size * nmemb;
}

void PaperMC::getVersions()
{
	std::cout << "PEGANDO VERSOES..." << std::endl << std::endl;

	CURL *curl;
	CURLcode res;
	std::string readBuffer;

	curl = curl_easy_init();

	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "https://papermc.io/api/v2/projects/paper");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);

		json data = json::parse(readBuffer);
		for (std::string version : data["versions"]) {
			std::cout << version << std::endl;
		}
	}

	std::cout << std::endl << "Precione alguma tecla para sair..." << std::endl;
	std::cin.get();
}