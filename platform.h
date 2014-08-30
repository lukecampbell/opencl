#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include <vector>
#include <string>
#include <OpenCL/opencl.h>

class CLPlatform
{
public:
    CLPlatform(cl_platform_id platform_id);
    
    cl_platform_id get_platform_id() const { return platform_id; }
   
    /* Info Getters */
    cl_int get_info(cl_platform_info info_enum, std::string &out) const;
    
    cl_int get_name(std::string &out) const;
    cl_int get_vendor(std::string &out) const;
    cl_int get_version(std::string &out) const;
    cl_int get_profile(std::string &out) const;
    cl_int get_extensions(std::string &out) const;
   
    /* Statics */
    static cl_int get_platforms(std::vector<CLPlatform> &out);
    static void err_check(cl_int err);

private:
    cl_platform_id platform_id;

};


#endif /* __PLATFORM_H__ */
