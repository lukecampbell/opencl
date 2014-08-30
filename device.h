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
    cl_int get_info(cl_device_info info_enum, cl_bool &out) const;

    /* String Info getters */
    cl_int get_device_built_in_kernels(std::string &out) const;
    cl_int get_device_extensions(std::string &out) const;
    cl_int get_device_name(std::string &out) const;
    cl_int get_device_opencl_c_version(std::string &out) const;
    cl_int get_device_profile(std::string &out) const;
    cl_int get_device_vendor(std::string &out) const;
    cl_int get_device_version(std::string &out) const;
    cl_int get_driver_version(std::string &out) const;

    /* Bool Info Getters */
    cl_int get_device_available(cl_bool &out) const;
    cl_int get_device_compiler_available(cl_bool &out) const;
    cl_int get_device_endian_little(cl_bool &out) const;
    cl_int get_device_error_correction_support(cl_bool &out) const;
    cl_int get_device_host_unified_memory(cl_bool &out) const;
    cl_int get_device_image_support(cl_bool &out) const;
    cl_int get_device_linker_available(cl_bool &out) const;
    cl_int get_device_preferred_interop_user_sync(cl_bool &out) const;


    /* Statics */
    static cl_int get_devices(const CLPlatform &platform, std::vector<CLDevice> &out);
    static void err_check(cl_int err);

private:
    cl_device_id device_id;
    cl_device_type device_type;

};


#endif /* __DEVICE_H__ */
