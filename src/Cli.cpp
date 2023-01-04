#include <iostream>
#include "Cli.h"
#include "PaperMC.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

Cli::Cli(int arg_c, char* arg_v[])
{
	Cli::arg_c = arg_c;
	Cli::arg_v = arg_v;
}

void Cli::run()
{
	if (arg_c > 1) {
		std::cout << "CONTEM ARGUMENTOS" << std::endl;
		return;
	}
	else {
		PaperMC paper;

        json versions = paper.getVersions();
        std::string version = paper.selectVersion(versions);
        json builds = paper.getBuilds(version);
        std::string build = paper.selectBuild(builds);
        paper.download(version, build);
    }
}
