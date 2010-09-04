#include "dirops.h"

bool scanDir(const std::string& pathname)
{
    DIR* pdir;
    struct dirent* pent;
    std::vector<std::string> directories;
    std::string currentdir;
    directories.push_back(pathname);
    while (!directories.empty())
    {
        currentdir = directories[directories.size() - 1];
	directories.pop_back();
        pdir = opendir(currentdir.c_str());
        if (!pdir) 
        {
    	    std::cerr << "Problems opening directory - check path name." << std::endl;
	    return false;
        }
        errno = 0; // makes it easier to check for success later
        while ((pent = readdir(pdir)))
        {
    	    if (pent->d_name[0] == '.') continue;
	    std::cout << pent->d_name << '\n';
	    std::string newpath(pent->d_name);
	    newpath = currentdir + "/" + newpath;
	    if (isDir(newpath)) 
	    {
	        directories.push_back(newpath);
	    }
        }
        if (errno)
        { 
            std::cout << strerror(errno) << '\n';
            std::cerr << "Problems reading directory - check permissions." << std::endl;
            closedir(pdir);
	    errno = 0;
            return false;
        }
        closedir(pdir);
    }
    return true;
}

bool isDir(const std::string& pathname)
{
    struct stat fileinfo;
    lstat(pathname.c_str(), &fileinfo);
    return (S_ISDIR(fileinfo.st_mode));
}
