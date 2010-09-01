#ifndef __SCANDIR_H__
#define __SCANDIR_H__

#include <string.h>
#include <iostream>
#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>

bool scanDir(std::string pathname);

#endif
