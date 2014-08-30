#include "clexception.h"
#include "platform.h"

CLPlatform::CLPlatform(cl_platform_id platform_id) : platform_id(platform_id)
{

}

std::string CLPlatform::get_info(cl_platform_info info_enum)
{
    char *info;
    size_t info_size;
    size_t info_size_ret;
    cl_int err;

    err = clGetPlatformInfo(platform_id, info_enum, 0, NULL, &info_size);
    if(err != CL_SUCCESS) {
        throw CLException("Invalid Platform");
    }

    info = new char[info_size+1];
    err = clGetPlatformInfo(platform_id, info_enum, info_size, info, &info_size_ret);
    if(err != CL_SUCCESS) {
        throw CLException("Can't get info from platform");
    }
    info[info_size] = '\0'; // Ensure Null Terminated
    std::string retval(info);

    delete info;
    return retval;
}

std::string CLPlatform::get_profile()
{
    return get_info(CL_PLATFORM_PROFILE);
}

std::string CLPlatform::get_version()
{
    return get_info(CL_PLATFORM_VERSION);
}

std::string CLPlatform::get_name()
{
    return get_info(CL_PLATFORM_NAME);
}

std::string CLPlatform::get_vendor()
{
    return get_info(CL_PLATFORM_VENDOR);
}

std::string CLPlatform::get_extensions()
{
    return get_info(CL_PLATFORM_EXTENSIONS);
}

std::vector<CLPlatform> get_platforms()
{
    cl_platform_id *platform_ids; // Unlikely to have more than 10 platforms
    cl_uint num_platforms = 0;
    cl_int err;
    std::vector<CLPlatform> retval;
    err = clGetPlatformIDs(0, NULL, &num_platforms);

    if(err != CL_SUCCESS)
    {
        throw CLException("OpenCL failed to get the number of platforms");
    }

    platform_ids = new cl_platform_id[num_platforms];

    err = clGetPlatformIDs(num_platforms, platform_ids, &num_platforms);
    if(err != CL_SUCCESS)
    {
        throw CLException("OpenCL failed to get platforms");
    }

    for(int i=0; i < num_platforms ; i++) 
    {
        CLPlatform platform(platform_ids[i]);
        retval.push_back(platform);
    }
    delete platform_ids;
    return retval;
}

