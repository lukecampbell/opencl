#ifndef __DEVICE_H__
#define __DEVICE_H__

#include <vector>
#include <string>
#include <OpenCL/opencl.h>
#include "platform.h"

class CLDevice
{
public:
    CLDevice(cl_device_id);

    cl_int get_info(cl_device_info info_enum, std::string &out) const;

    /* String Info getters */
    cl_int get_device_built_in_kernels(std::string &out) const;
    cl_int get_device_extensions(std::string &out) const;
    cl_int get_device_name(std::string &out) const;
    cl_int get_device_opencl_c_version(std::string &out) const;
    cl_int get_device_profile(std::string &out) const;
    cl_int get_device_vendor(std::string &out) const;
    cl_int get_device_version(std::string &out) const;
    cl_int get_driver_version(std::string &out) const;

    /* Statics */
    static cl_int get_devices(const CLPlatform &platform, std::vector<CLDevice> &out);
    static void err_check(cl_int err);

private:
    cl_device_id device_id;
    cl_device_type device_type;

};


#endif /* __DEVICE_H__ */
