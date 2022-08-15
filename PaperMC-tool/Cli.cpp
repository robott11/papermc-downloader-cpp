#include <iostream>
#include "Cli.h"
#include "PaperMC.h"

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
		paper.getVersions();
	}
}
