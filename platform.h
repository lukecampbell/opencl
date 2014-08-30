#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include <vector>
#include <string>
#include <OpenCL/opencl.h>

class CLPlatform
{
public:
    CLPlatform(cl_platform_id platform_id);
    cl_int get_profile(std::string &out);
    cl_int get_version(std::string &out);
    cl_int get_name(std::string &out);
    cl_int get_vendor(std::string &out);
    cl_int get_extensions(std::string &out);
    cl_int get_info(cl_platform_info info_enum, std::string &out);
    static void err_check(cl_int err);

private:
    cl_platform_id platform_id;

};

cl_int get_platforms(std::vector<CLPlatform> &out);

#endif /* __PLATFORM_H__ */
