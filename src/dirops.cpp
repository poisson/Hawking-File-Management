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
	    std::cout << pent->d_name << ": ";
	    std::string newpath(pent->d_name);
	    newpath = currentdir + "/" + newpath;
	    std::cout << fileType(newpath) << '\n';
	    if (isDir(newpath)) 
	    {
	        directories.push_back(newpath);
	    }
        }
        if (errno)
        { 
            std::cerr << "Problems reading directory - check permissions: " << strerror(errno) << std::endl;
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

std::string fileType(const std::string& pathname)
{
    magic_t cookie;
    std::string filetype;
    cookie = magic_open(MAGIC_NONE);
    if (cookie == NULL || magic_load(cookie, NULL) != 0)
    {
	std::cerr << "Error initializing libmagic: " << magic_error(cookie) << std::endl;
	magic_close(cookie);
	return "";
    }
    filetype = magic_file(cookie, pathname.c_str());
    errno = 0;
    magic_close(cookie);
    return filetype;
}
