#include <iostream>
#include "device.h"
#include "clexception.h"

CLDevice::CLDevice(cl_device_id device_id) : device_id(device_id)
{

}

cl_int CLDevice::get_info(cl_device_info info_enum, std::string &out) const
{
    char *info;
    size_t info_size;
    cl_int err;
    err = clGetDeviceInfo(device_id, info_enum, 0, NULL, &info_size);
    if(err != CL_SUCCESS)
    {
        return err;
    }
    info = new char[info_size+1];
    err = clGetDeviceInfo(device_id, info_enum, info_size, info, &info_size);
    if(err != CL_SUCCESS)
    {
        return err;
    }
    info[info_size] = '\0';
    out = std::string(info);

    delete info;
    return err;
}

cl_int CLDevice::get_info(cl_device_info info_enum, cl_bool &out) const
{
    size_t info_size;
    cl_int err;
    err = clGetDeviceInfo(device_id, info_enum, sizeof(cl_bool), &out, &info_size);
    if(err != CL_SUCCESS)
    {
        return err;
    }
    return err;
}

cl_int CLDevice::get_device_built_in_kernels(std::string &out) const
{
    return get_info(CL_DEVICE_BUILT_IN_KERNELS, out);
}

cl_int CLDevice::get_device_extensions(std::string &out) const
{
    return get_info(CL_DEVICE_EXTENSIONS, out);
}

cl_int CLDevice::get_device_name(std::string &out) const
{
    return get_info(CL_DEVICE_NAME, out);
}

cl_int CLDevice::get_device_opencl_c_version(std::string &out) const
{
    return get_info(CL_DEVICE_OPENCL_C_VERSION, out);
}

cl_int CLDevice::get_device_profile(std::string &out) const
{
    return get_info(CL_DEVICE_PROFILE, out);
}

cl_int CLDevice::get_device_vendor(std::string &out) const
{
    return get_info(CL_DEVICE_VENDOR, out);
}

cl_int CLDevice::get_device_version(std::string &out) const
{
    return get_info(CL_DEVICE_VERSION, out);
}

cl_int CLDevice::get_driver_version(std::string &out) const
{
    return get_info(CL_DRIVER_VERSION, out);
}

cl_int CLDevice::get_device_available(cl_bool &out) const
{
    return get_info(CL_DEVICE_AVAILABLE, out);
}

cl_int CLDevice::get_device_compiler_available(cl_bool &out) const
{
    return get_info(CL_DEVICE_COMPILER_AVAILABLE, out);
}

cl_int CLDevice::get_device_endian_little(cl_bool &out) const
{
    return get_info(CL_DEVICE_ENDIAN_LITTLE, out);
}

cl_int CLDevice::get_device_error_correction_support(cl_bool &out) const
{
    return get_info(CL_DEVICE_ERROR_CORRECTION_SUPPORT, out);
}

cl_int CLDevice::get_device_host_unified_memory(cl_bool &out) const
{
    return get_info(CL_DEVICE_HOST_UNIFIED_MEMORY, out);
}

cl_int CLDevice::get_device_image_support(cl_bool &out) const
{
    return get_info(CL_DEVICE_IMAGE_SUPPORT, out);
}

cl_int CLDevice::get_device_linker_available(cl_bool &out) const
{
    return get_info(CL_DEVICE_LINKER_AVAILABLE, out);
}

cl_int CLDevice::get_device_preferred_interop_user_sync(cl_bool &out) const
{
    return get_info(CL_DEVICE_PREFERRED_INTEROP_USER_SYNC, out);
}

cl_int CLDevice::get_devices(const CLPlatform &platform, std::vector<CLDevice> &out)
{
    cl_device_id *device_ids;
    cl_uint num_devices = 0;
    cl_int err;

    err = clGetDeviceIDs(platform.get_platform_id(), CL_DEVICE_TYPE_ALL, 0, NULL, &num_devices);
    if(err != CL_SUCCESS)
    {
        return err;
    }

    device_ids = new cl_device_id[num_devices];
    err = clGetDeviceIDs(platform.get_platform_id(), CL_DEVICE_TYPE_ALL, num_devices, device_ids, &num_devices);
    if(err != CL_SUCCESS)
    {
        return err;
    }

    for(int i=0; i < num_devices; i++)
    {
        out.push_back(CLDevice(device_ids[i]));
    }

    delete device_ids;
    return err;
}

void CLDevice::err_check(cl_int err)
{
    switch(err)
    {
        case CL_INVALID_DEVICE:
            std::cerr << "Invalid device" << std::endl;
            break;
        case CL_INVALID_VALUE:
            std::cerr << "Invalid value" << std::endl;
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

