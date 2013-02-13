#pragma once
#include <QString>
#include <QMap>
#define CL_USE_DEPRECATED_OPENCL_1_1_APIS
#include <CL/opencl.h>

QMap<cl_platform_id, QString> oclGetPlatforms();
QMap<cl_device_id, QString> oclGetDevicesForPlatform(cl_platform_id platformId);
