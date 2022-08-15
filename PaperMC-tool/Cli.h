#pragma once

#include <iostream>

class Cli
{
public:
	Cli(int arg_c, char* arg_v[]);
	void run();

private:
	int arg_c;
	char** arg_v;
};

