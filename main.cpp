#include <OpenCL/opencl.h>
#include <iostream>

#include "platform.h"
#include "clexception.h"


int main(int argc, char *argv[])
{
    cl_int err;
    std::vector<CLPlatform> platforms;
    err = get_platforms(platforms);
    if(err != CL_SUCCESS)
    {
        std::cerr << "Failed to get platforms" << std::endl;
    }

    for(std::vector<CLPlatform>::iterator it = platforms.begin(); it != platforms.end(); it++)
    {
        CLPlatform *platform = &(*it);
        std::string buf;
        try 
        {
            CLPlatform::err_check(platform->get_name(buf));
            std::cout << "Name: " << buf << std::endl;
            CLPlatform::err_check(platform->get_vendor(buf));
            std::cout << "Vendor: " << buf << std::endl;
            CLPlatform::err_check(platform->get_version(buf));
            std::cout << "Version: " << buf << std::endl;
            CLPlatform::err_check(platform->get_profile(buf));
            std::cout << "Profile: " << buf << std::endl;
            CLPlatform::err_check(platform->get_extensions(buf));
            std::cout << "Extensions: " << buf << std::endl;
        } catch(CLException &e) {
            std::cerr << e.what() << std::endl;
            return 1;
        }
    }

    return 0;
}
