#pragma once

#include <string>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

class PaperMC
{
public:
    json getVersions();
    json getBuilds(std::string version);
    std::string selectVersion(json versions);
    std::string selectBuild(json builds);
    void download(std::string version, std::string build);

private:
	std::string url;
};

