#include <iostream>

#include "clexception.h"
#include "platform.h"

CLPlatform::CLPlatform(cl_platform_id platform_id) : platform_id(platform_id)
{

}

cl_int CLPlatform::get_info(cl_platform_info info_enum, std::string &out)
{
    char *info;
    size_t info_size;
    size_t info_size_ret;
    cl_int err;

    err = clGetPlatformInfo(platform_id, info_enum, 0, NULL, &info_size);
    if(err != CL_SUCCESS) {
        return err;
    }

    info = new char[info_size+1];
    err = clGetPlatformInfo(platform_id, info_enum, info_size, info, &info_size_ret);
    if(err != CL_SUCCESS) {
        return err;
    }
    info[info_size] = '\0'; // Ensure Null Terminated
    out = std::string(info);

    delete info;
    return err;
}

cl_int CLPlatform::get_profile(std::string &out)
{
    return get_info(CL_PLATFORM_PROFILE, out);
}

cl_int CLPlatform::get_version(std::string &out)
{
    return get_info(CL_PLATFORM_VERSION, out);
}

cl_int CLPlatform::get_name(std::string &out)
{
    return get_info(CL_PLATFORM_NAME, out);
}

cl_int CLPlatform::get_vendor(std::string &out)
{
    return get_info(CL_PLATFORM_VENDOR, out);
}

cl_int CLPlatform::get_extensions(std::string &out)
{
    return get_info(CL_PLATFORM_EXTENSIONS, out);
}

void CLPlatform::err_check(cl_int err)
{
    switch(err)
    {
        case CL_INVALID_PLATFORM:
           std::cerr << "Invalid Platform" << std::endl;
           break;
        case CL_INVALID_DEVICE_TYPE: 
           std::cerr << "Invalid Device Type" << std::endl;
           break;
        case CL_INVALID_VALUE:
           std::cerr << "Invalid Value" << std::endl;
           break;
        case CL_DEVICE_NOT_FOUND:
           std::cerr << "Device not found" << std::endl;
           break;
        case CL_OUT_OF_RESOURCES: 
           std::cerr << "Out of resources" << std::endl;
           break;
        case CL_OUT_OF_HOST_MEMORY:
           std::cerr << "Out of host memory" << std::endl;
           break;
        default:
           break;
    }
    if(err != CL_SUCCESS)
    {
        throw CLException("Failed Error Check");
    }
}

cl_int get_platforms(std::vector<CLPlatform> &out)
{
    cl_platform_id *platform_ids; // Unlikely to have more than 10 platforms
    cl_uint num_platforms = 0;
    cl_int err;
    err = clGetPlatformIDs(0, NULL, &num_platforms);

    if(err != CL_SUCCESS)
    {
        return err;
    }

    platform_ids = new cl_platform_id[num_platforms];

    err = clGetPlatformIDs(num_platforms, platform_ids, &num_platforms);
    if(err != CL_SUCCESS)
    {
        return err;
    }

    for(int i=0; i < num_platforms ; i++) 
    {
        CLPlatform platform(platform_ids[i]);
        out.push_back(platform);
    }
    delete platform_ids;
    return err;
}


