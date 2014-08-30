#include <OpenCL/opencl.h>
#include <iostream>

#include "platform.h"

int main(int argc, char *argv[])
{

    std::vector<CLPlatform> platforms = get_platforms();
    CLPlatform platform = platforms[0];
    for(std::vector<CLPlatform>::iterator it = platforms.begin(); it != platforms.end(); it++)
    {
        CLPlatform *platform = &(*it);
        std::cout << "Name: "       << platform->get_name()       << std::endl;
        std::cout << "Vendor: "     << platform->get_vendor()     << std::endl;
        std::cout << "Version: "    << platform->get_version()    << std::endl;
        std::cout << "Profile: "    << platform->get_profile()    << std::endl;
        std::cout << "Extensions: " << platform->get_extensions() << std::endl;
    }

    return 0;
}
