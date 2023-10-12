#include <stdio.h>
#include <iostream>

#include "cuda_runtime_api.h"

#include "cuda_runtime.hpp"

cudaError_t g_last_cudaError = cudaSuccess;

#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)

inline cuda::Runtime *cuda_Runtime() {
    static cuda::Runtime *rtstatic = NULL;
    if (unlikely(rtstatic == NULL)) {
        rtstatic = new cuda::Runtime();
    }

    return rtstatic;
}

extern "C" {

char __cudaInitModule(void **fatCubinHandle) {
    return 0;
}

cudaError_t CUDARTAPI __cudaPopCallConfiguration(dim3 *gridDim, dim3 *blockDim, size_t *sharedMem, void *stream) {
    return g_last_cudaError;
}

__host__ cudaError_t CUDARTAPI cudaLaunchKernel(const void *hostFun, dim3 gridDim, dim3 blockDim, void **args, size_t sharedMem, cudaStream_t stream) {
    cuda::Runtime *rt = cuda_Runtime();
    rt->LaunchKerne(hostFun, gridDim, blockDim, args);
    return g_last_cudaError;
}

void ** CUDARTAPI __cudaRegisterFatBinary(void *fatCubin) {
    cuda::Runtime *rt = cuda_Runtime();
    return rt->RegisterFatBinary(fatCubin);
}

void CUDARTAPI __cudaRegisterFunction(void **fatCubinHandle, const char *hostFun, char *deviceFun, const char *deviceName, int thread_limit, uint3 *tid, uint3 *bid, dim3 *bDim, dim3 *gDim) {
    // only deviceFun used ???  @qihangkong
    cuda::Runtime *rt = cuda_Runtime();
    return rt->RegisterFunction(fatCubinHandle, deviceFun);
}

void CUDARTAPI __cudaRegisterFatBinaryEnd(void **fatCubinHandle) {
}

void __cudaUnregisterFatBinary(void **fatCubinHandle) {
}

__host__ cudaError_t CUDARTAPI cudaMalloc(void **devPtr, size_t size) {

    cuda::Runtime *rt = cuda_Runtime();
    *devPtr = (void *) rt->Malloc((uint32_t)size);

    if (*devPtr) {
        return g_last_cudaError = cudaSuccess;
    } else {
        return g_last_cudaError = cudaErrorMemoryAllocation;
    }
}

__host__ cudaError_t CUDARTAPI cudaMemcpy(void *dst, const void *src, size_t count, enum cudaMemcpyKind kind) {

    cuda::Runtime *rt = cuda_Runtime();

    if (kind == cudaMemcpyHostToDevice) {
        rt->Memcpy((uint64_t)dst, (uint64_t)src, (uint32_t)count, true);
    } else if (kind == cudaMemcpyDeviceToHost) {
        rt->Memcpy((uint64_t)dst, (uint64_t)src, (uint32_t)count, false);
    } else {
        // TODO: HostToHost, DeviceToDevice
    }

    return g_last_cudaError;
}

unsigned CUDARTAPI __cudaPushCallConfiguration(dim3 gridDim, dim3 blockDim, size_t sharedMem, struct CUstream_st *stream) {
    return 0;
}

cudaError_t CUDARTAPI cudaDeviceSynchronize(void) {
    return g_last_cudaError;
}

cudaError_t cudaDeviceReset(void) {
    return g_last_cudaError;
}

}
