#include <stdio.h>

#include "cuda_runtime_api.h"

#include "builtin_types.h"
#include "driver_types.h"
#include "cudaProfiler.h"

#include "cuda_api.h"

#include "cuda_runtime.hpp"

cudaError_t g_last_cudaError = cudaSuccess;

#define unlikely(x) __builtin_expect(!!(x), 0)
inline cuda::Runtime *cuda_Runtime() {
    static cuda::Runtime *rt = NULL;
    if (unlikely(rt == NULL)) {
        rt = new cuda::Runtime();
    }

    return rt;
}

extern "C" {

char __cudaInitModule(void **fatCubinHandle) {
	printf("%s\n", __func__);
    return 0;
}

cudaError_t CUDARTAPI __cudaPopCallConfiguration(dim3 *gridDim, dim3 *blockDim, size_t *sharedMem, void *stream) {
	printf("%s\n", __func__);
    return g_last_cudaError;
}

__host__ cudaError_t CUDARTAPI cudaLaunchKernel(const void *hostFun, dim3 gridDim, dim3 blockDim, void **args, size_t sharedMem, cudaStream_t stream) {
	printf("%s\n", __func__);
    return g_last_cudaError;    
}

void ** CUDARTAPI __cudaRegisterFatBinary(void *fatCubin) {
	printf("%s\n", __func__);
    static cuda::Runtime *rt = cuda_Runtime();
    return rt->RegisterFatBinary(fatCubin);
}

void CUDARTAPI __cudaRegisterFunction(void **fatCubinHandle, const char *hostFun, char *deviceFun, const char *deviceName, int thread_limit, uint3 *tid, uint3 *bid, dim3 *bDim, dim3 *gDim) {
    printf("%s\n", __func__);
}

void CUDARTAPI __cudaRegisterFatBinaryEnd(void **fatCubinHandle) {
    printf("%s\n", __func__);
}

void __cudaUnregisterFatBinary(void **fatCubinHandle) {
	printf("%s\n", __func__);
}

__host__ cudaError_t CUDARTAPI cudaMalloc(void **devPtr, size_t size) {
	printf("%s\n", __func__);

#if 0
    uint64_t addr = gpu_malloc_addr;
    gpu_malloc_addr += size;
    *devPtr = (void *)addr;
#endif

    return g_last_cudaError;
}

__host__ cudaError_t CUDARTAPI cudaMemcpy(void *dst, const void *src, size_t count, enum cudaMemcpyKind kind) {
	printf("%s\n", __func__);

#if 0
    if (cudaMemcpyKind == cudaMemcpyHostToDevice) {
        uint8_t *addr = (uint8_t *)src;
        for (uint32_t i = 0; i < count; i++) {
            gpu->write_vram(dst + i, addr[i], 1);
        }
    } else if (cudaMemcpyKind == cudaMemcpyHostToDevice) {
        uint8_t *addr = (uint8_t *)dst;
        for (uint32_t i = 0; i < count; i++) {
            addr[i] = gpu->read_vram(src + i, 1);
        }
    } else {
        // TODO: HostToHost, DeviceToDevice
    }
#endif

    return g_last_cudaError;
}

unsigned CUDARTAPI __cudaPushCallConfiguration(dim3 gridDim, dim3 blockDim, size_t sharedMem, struct CUstream_st *stream) {
	printf("%s\n", __func__);
    return 0;
}

cudaError_t CUDARTAPI cudaDeviceSynchronize(void) {
	printf("%s\n", __func__);
    return g_last_cudaError;
}

cudaError_t cudaDeviceReset(void) {
	printf("%s\n", __func__);
    return g_last_cudaError;
}

}