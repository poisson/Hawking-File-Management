#include "scandir.h"

bool scanDir(const std::string& pathname)
{
    DIR* pdir;
    struct dirent* pent;
    struct stat;
    pdir=opendir(pathname.c_str());
    if (!pdir) 
    {
	std::cerr << "Problems opening directory - check path name." << std::endl;
	return false;
    }
    errno = 0; // makes it easier to check for success later
    while (pent = readdir(pdir))
    {
	std::cout << pent->d_name;
	lstat(pent->dname, &stat);
	if (stat.st_mode & S_IFDIR)
	    scanDir(pent->dname);
    }
    if (errno)
    {
        std::cerr << "Problems reading directory - check permissions." << std::endl;
	return false;
    }
}
