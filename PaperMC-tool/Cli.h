#pragma once

#include <iostream>
#include <vector>

class Cli
{
public:
	Cli(std::vector<std::string> args);
    void handle_args();
    void help();
	void run();

private:
    std::vector<std::string> args;
};

