#include <dirent.h>
#include "scandir.h"
#include <iostream>

int main (int argc, char** argv)
{
    if (argc != 2) {
	std::cerr << "Incorrect number of arguments." << std::endl;
	return 1;
    }
    std::string pathname(argv[1]);
    if (!scanDir(pathname))
    {
	std::cerr << "Something went wrong." << std::endl;
	return 1;
    }
    return 0;
}

