#include <iostream>
#include <vector>
#include "Cli.h"

int main(int argc, char** argv)
{
    std::vector<std::string> args;
    for (size_t i = 1; i < argc; i++) {
        args.emplace_back(argv[i]);
    }

	Cli app(args);
	app.run();

	return EXIT_SUCCESS;
}