#include <iostream>
#include <string>
#include <stdio.h>
#include "curl/curl.h"
#include "nlohmann/json.hpp"
#include "PaperMC.h"

using json = nlohmann::json;

static size_t WriteCallback(char *contents, size_t size, size_t nmemb, char *buffer_in)
{
	((std::string*)buffer_in)->append((char*)contents, size * nmemb);

	return size * nmemb;
}

json PaperMC::getVersions()
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

        return data["versions"];
	}
}

std::string PaperMC::selectVersion(json versions) {
    for (int i = 0; i < versions.size(); i++) {
        std::cout << "[" << i << "]" << " => " << versions[i] << std::endl;
    }

    int index;
    std::string version;

    std::cout << std::endl << "SELECIONE A VERSÃO: ";
    std::cin >> index;
    version = versions[index];
    std::cout << "VERSÃO SELECIONADA: " << version << std::endl;

    return version;
}

json PaperMC::getBuilds(std::string version) {
    std::cout << "PEGANDO BUILDS..." << std::endl << std::endl;

    std::string url = "https://papermc.io/api/v2/projects/paper/versions/" + version;

    CURL *curl;
    CURLcode res;
    std::string readBufferBuilds;

    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.data());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBufferBuilds);

        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        auto data = json::parse(readBufferBuilds);

        return data["builds"];
    }
}

std::string PaperMC::selectBuild(json builds) {
    for (int i = 0; i < builds.size(); i++) {
        std::cout << "[" << i << "]" << " => " << builds[i] << std::endl;
    }

    unsigned int index;
    unsigned int build;

    std::cout << std::endl << "SELECIONE A VERSÃO: ";
    std::cin >> index;
    build = builds[index];
    std::cout << "BUILD SELECIONADA: " << build << std::endl;

    return std::to_string(build);
}

void PaperMC::download(std::string version, std::string build) {
    std::string url = "https://papermc.io/api/v2/projects/paper/versions/" + version + "/builds/" + build;

    CURL *curl;
    CURLcode res;
    std::string projectBuffer;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.data());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &projectBuffer);
        res = curl_easy_perform(curl);

        auto file_name = json::parse(projectBuffer)["downloads"]["application"]["name"];
        url = url + "/downloads/" + file_name.get<std::string>();
        std::cout << "Downloading from " << url << std::endl;

        CURL *curl2;
        CURLcode res2;
        FILE* out_file = fopen(file_name.get<std::string>().data(), "wb");

        curl2 = curl_easy_init();
        if (curl2) {
            curl_easy_setopt(curl2, CURLOPT_URL, url.data());
            curl_easy_setopt(curl2, CURLOPT_WRITEDATA, out_file);
            res2 = curl_easy_perform(curl2);
        }

        fclose(out_file);
    }
}
