#include <OpenCL/opencl.h>
#include <iostream>

#include "platform.h"
#include "device.h"
#include "clexception.h"

std::string b2s(const cl_bool &b2s)
{
    return (b2s ? "yes" : "no");
}

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
            cl_bool bool_buf;
            device->get_device_name(buf);
            std::cout << "  - Device Name: " << buf << std::endl;
            device->get_device_available(bool_buf);
            std::cout << "    Device Available: " << b2s(bool_buf) << std::endl;
            device->get_device_vendor(buf);
            std::cout << "    Device Vendor: " << buf << std::endl;
            device->get_device_version(buf);
            std::cout << "    Device Version: " << buf << std::endl;
            device->get_device_compiler_available(bool_buf);
            std::cout << "    Device Compiler Available: " << b2s(bool_buf) << std::endl;
            device->get_device_endian_little(bool_buf);
            std::cout << "    Device Endian Little: " << b2s(bool_buf) << std::endl;
            device->get_device_error_correction_support(bool_buf);
            std::cout << "    Device Error Correction Support: " << b2s(bool_buf) << std::endl;
            device->get_device_host_unified_memory(bool_buf);
            std::cout << "    Device Host Unified Memory: " << b2s(bool_buf) << std::endl;
            device->get_device_image_support(bool_buf);
            std::cout << "    Device Image Support: " << b2s(bool_buf) << std::endl;
            device->get_device_linker_available(bool_buf);
            std::cout << "    Device Linker Available: " << b2s(bool_buf) << std::endl;
            device->get_device_preferred_interop_user_sync(bool_buf);
            std::cout << "    Device Preffered Interop User Sync: " << b2s(bool_buf) << std::endl;
        } catch (CLException &e) {
            std::cerr << e.what() << std::endl;
            return 1;
        }
    }
    return 0;
}
