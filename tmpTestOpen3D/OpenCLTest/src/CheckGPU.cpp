
#include <stdio.h>
#include <stdlib.h>

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

#define MEM_SIZE (128)
#define MAX_SOURCE_SIZE (0x100000)

int main()
{
	cl_platform_id platform_id = NULL;
	cl_device_id device_id = NULL;
	cl_uint ret_num_devices;
	cl_uint ret_num_platforms;
	cl_int ret;
	cl_uint work_item_dim;
	size_t work_item_sizes[3];
	size_t work_group_size;
	cl_uint ucomput_uint = 0;
	cl_uint uconstant_args = 0;
	cl_ulong uconstant_buffer_size = 0;

	ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
	ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_DEFAULT, 1, &device_id, &ret_num_devices);
	printf("devices   : %d\n", ret_num_devices);

	char pform_vendor[40];
	clGetPlatformInfo(platform_id, CL_PLATFORM_VENDOR, sizeof(pform_vendor), &pform_vendor, NULL);
	printf("vendor   : %s\n", &pform_vendor);

	clGetDeviceInfo(device_id, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof(cl_uint), (void *)&work_item_dim, NULL);
	clGetDeviceInfo(device_id, CL_DEVICE_MAX_WORK_ITEM_SIZES, sizeof(work_item_sizes), (void *)work_item_sizes, NULL);
	clGetDeviceInfo(device_id, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(size_t), (void *)&work_group_size, NULL);
	clGetDeviceInfo(device_id, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(cl_uint), (void *)&ucomput_uint, NULL);
	clGetDeviceInfo(device_id, CL_DEVICE_MAX_CONSTANT_ARGS, sizeof(cl_uint), (void *)&uconstant_args, NULL);
	clGetDeviceInfo(device_id, CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE, sizeof(cl_ulong), (void *)&uconstant_buffer_size, NULL);

	printf("Max work-item dimensions   : %d\n", work_item_dim);
	printf("Max work-item sizes        : %d %d %d\n", work_item_sizes[0], work_item_sizes[1], work_item_sizes[2]);
	printf("Max work-group sizes       : %d\n", work_group_size);
	printf("Max comput_uint            : %u\n", ucomput_uint);
	printf("Max constant_args          : %u\n", uconstant_args);
	printf("Max constant_buffer_size   : %u\n", uconstant_buffer_size);

	system("pause");
	return 0;
}
