#include <iostream>
#include "Cli.h"
#include "PaperMC.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

Cli::Cli(std::vector<std::string> args)
{
	Cli::args = args;
}

void Cli::help()
{
    std::cout << "Usage: PaperMC-tool [Options...] [Version] [Build]" << std::endl;
    std::cout << "--help\t\tPrint this message" << std::endl;

    exit(EXIT_FAILURE);
}

void Cli::handle_args()
{
    size_t opts = args.size();

    switch (opts)
    {
        case 1:
            if (args[0] == "--help")
                help();
            break;
        default:
            break;
    }
}

void Cli::run()
{
    handle_args();

	/*if (args.size() > 1) {
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
    }*/
}
