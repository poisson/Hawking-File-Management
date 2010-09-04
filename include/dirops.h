#ifndef __DIROPS_H__
#define __DIROPS_H__

#include <string.h>
#include <cstring>
#include <iostream>
#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <vector>

bool scanDir(const std::string& pathname);
bool isDir(const std::string& pathname);

#endif
