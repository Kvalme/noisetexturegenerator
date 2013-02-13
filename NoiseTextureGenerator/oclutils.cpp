#include "oclutils.h"

#include <QMessageBox>

QMap<cl_platform_id, QString> oclGetPlatforms()
{
#define CHECK_CL_ERROR(text) \
{ \
    if (err != CL_SUCCESS) \
    { \
        QMessageBox::critical(0, "OpenCL error", text); \
        return platforms; \
    } \
}

    cl_int err = CL_SUCCESS;
    cl_uint platformCount;
    QMap<cl_platform_id, QString> platforms;

    err = clGetPlatformIDs(0, NULL, &platformCount);
    CHECK_CL_ERROR("Error while querying platform count");

    QSharedPointer<cl_platform_id> clPlatforms(new cl_platform_id[platformCount]);
    err = clGetPlatformIDs(platformCount, clPlatforms.data(), 0);
    CHECK_CL_ERROR("Error while querying platform");

    for(unsigned int a = 0; a < platformCount; ++a)
    {
        char buf[1024];
        QString name;
/*        err = clGetPlatformInfo(clPlatforms.data()[a], CL_PLATFORM_VENDOR, 1024, buf, 0);
        CHECK_CL_ERROR("Error while querying platform vendor");
        name.append(buf);
        name.append(" ");*/

        err = clGetPlatformInfo(clPlatforms.data()[a], CL_PLATFORM_NAME, 1024, buf, 0);
        CHECK_CL_ERROR("Error while querying platform name");
        name.append(buf);
        name.append(" ");

        err = clGetPlatformInfo(clPlatforms.data()[a], CL_PLATFORM_VERSION, 1024, buf, 0);
        CHECK_CL_ERROR("Error while querying platform version");
        name.append(buf);

        platforms.insert(clPlatforms.data()[a], name);
    }
    return platforms;
#undef CHECK_CL_ERROR
}

QMap<cl_device_id, QString> oclGetDevicesForPlatform(cl_platform_id platformId)
{
#define CHECK_CL_ERROR(text) \
{ \
    if (err != CL_SUCCESS) \
    { \
        QMessageBox::critical(0, "OpenCL error", text); \
        return devices; \
    } \
}

    QMap<cl_device_id, QString> devices;

    if (!platformId)
    {
        QMessageBox::critical(0, "Error", "Invalid plaftorm id passed to oclGetDevicesForPlatform");
        return devices;
    }

    cl_uint deviceCount;
    cl_int err = clGetDeviceIDs(platformId, CL_DEVICE_TYPE_ALL, 0, 0, &deviceCount);
    CHECK_CL_ERROR("Error while querying devices for given platform");

    QSharedPointer<cl_device_id> clDevices(new cl_device_id[deviceCount]);
    err = clGetDeviceIDs(platformId, CL_DEVICE_TYPE_ALL, deviceCount, clDevices.data(), 0);
    CHECK_CL_ERROR("Error while queruing device");

    for(unsigned int a = 0; a < deviceCount; ++a)
    {
        char buf[1024];
        QString name;

        err = clGetDeviceInfo(clDevices.data()[a], CL_DEVICE_VENDOR, 1024, buf, 0);
        CHECK_CL_ERROR("Erro while querying device vendor");
        name.append(buf);
        name.append(" ");

        err = clGetDeviceInfo(clDevices.data()[a], CL_DEVICE_NAME, 1024, buf, 0);
        CHECK_CL_ERROR("Erro while querying device name");
        name.append(buf);

        devices.insert(clDevices.data()[a], name);
    }

    return devices;
#undef CHECK_CL_ERROR

}

