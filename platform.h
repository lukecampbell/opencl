#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include <vector>
#include <string>
#include <OpenCL/opencl.h>

class CLPlatform
{
public:
    CLPlatform(cl_platform_id platform_id);
    std::string get_profile();
    std::string get_version();
    std::string get_name();
    std::string get_vendor();
    std::string get_extensions();
    std::string get_info(cl_platform_info info_enum);

private:
    cl_platform_id platform_id;

};

std::vector<CLPlatform> get_platforms();

#endif /* __PLATFORM_H__ */
