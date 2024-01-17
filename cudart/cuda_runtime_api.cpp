#include <stdio.h>
#include <iostream>

#include "utils/debug.hpp"
#include "cuda_runtime_api.h"
#include "cuda_runtime.hpp"

cudaError_t g_last_cudaError = cudaSuccess;

extern cuda::Runtime *rtstatic;
static inline cuda::Runtime *cuda_Runtime() {
    return rtstatic;
}

extern "C" {

char __cudaInitModule(void **fatCubinHandle) {
    API_ENTRY();
    return 0;
}

unsigned CUDARTAPI __cudaPushCallConfiguration(dim3 gridDim, dim3 blockDim, size_t sharedMem, struct CUstream_st *stream) {
    API_ENTRY();
    cuda::Runtime *rt = cuda_Runtime();

    return rt->PushCallConfiguration(gridDim, blockDim);
}

cudaError_t CUDARTAPI __cudaPopCallConfiguration(dim3 *gridDim, dim3 *blockDim, size_t *sharedMem, void *stream) {
    API_ENTRY();
    cudaError_t err = cudaSuccess;

    cuda::Runtime *rt = cuda_Runtime();
    rt->PopCallConfiguration(gridDim, blockDim);
    return err;
}

__host__ cudaError_t CUDARTAPI cudaLaunchKernel(const void *hostFun, dim3 gridDim, dim3 blockDim, void **args, size_t sharedMem, cudaStream_t stream) {
    API_ENTRY();
    cuda::Runtime *rt = cuda_Runtime();
    rt->LaunchKerne(hostFun, gridDim, blockDim, args);
    return g_last_cudaError;
}

void ** CUDARTAPI __cudaRegisterFatBinary(void *fatCubin) {
    API_ENTRY();
    cuda::Runtime *rt = cuda_Runtime();
    return rt->RegisterFatBinary(fatCubin);
}

/**
 * hostFunc: the pointer to function evice_stub__xxx, which will call cudaLaunchKernel
 */
void CUDARTAPI __cudaRegisterFunction(void **fatCubinHandle, const char *hostFun, char *deviceFun, const char *deviceName, int thread_limit, uint3 *tid, uint3 *bid, dim3 *bDim, dim3 *gDim) {
    API_ENTRY();
    cuda::Runtime *rt = cuda_Runtime();
    return rt->RegisterFunction(fatCubinHandle, hostFun, deviceFun);
}

void CUDARTAPI __cudaRegisterFatBinaryEnd(void **fatCubinHandle) {
    API_ENTRY();
}

void __cudaUnregisterFatBinary(void **fatCubinHandle) {
    API_ENTRY();
}

__host__ cudaError_t CUDARTAPI cudaMalloc(void **devPtr, size_t size) {
    API_ENTRY();
    cuda::Runtime *rt = cuda_Runtime();
    *devPtr = (void *) rt->Malloc((uint32_t)size);

    if (*devPtr) {
        return g_last_cudaError = cudaSuccess;
    } else {
        return g_last_cudaError = cudaErrorMemoryAllocation;
    }
}

__host__ cudaError_t CUDARTAPI cudaMemcpy(void *dst, const void *src, size_t count, enum cudaMemcpyKind kind) {
    API_ENTRY();
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

cudaError_t CUDARTAPI cudaDeviceSynchronize(void) {
    API_ENTRY();    

    return g_last_cudaError;
}

cudaError_t cudaDeviceReset(void) {
    API_ENTRY();    

    return g_last_cudaError;
}

}
