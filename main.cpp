#include <OpenCL/opencl.h>
#include <iostream>

#include "platform.h"
#include "device.h"
#include "clexception.h"


int main(int argc, char *argv[])
{
    cl_int err;
    std::vector<CLPlatform> platforms;
    std::vector<CLDevice> devices;
    std::string buf;
    err = CLPlatform::get_platforms(platforms);
    try
    {
        CLPlatform::err_check(err);
    } catch (CLException &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }


    for(std::vector<CLPlatform>::iterator it = platforms.begin(); it != platforms.end(); it++)
    {
        CLPlatform *platform = &(*it);
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

    CLPlatform platform = platforms[0];

    err = CLDevice::get_devices(platform, devices);
    try
    {
        CLDevice::err_check(err);
    } catch (CLException &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    for(std::vector<CLDevice>::iterator it = devices.begin(); it != devices.end(); it++)
    {
        CLDevice *device = &(*it);
        try
        {
            CLDevice::err_check(device->get_device_name(buf));
            std::cout << "    Device Name: " << buf << std::endl;
        } catch (CLException &e) {
            std::cerr << e.what() << std::endl;
            return 1;
        }
    }
    return 0;
}
