#include <iostream>
#include "Cli.h"

int main(int argc, char* argv[])
{
	Cli app(argc, argv);
	app.run();

	return EXIT_SUCCESS;
}