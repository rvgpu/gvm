#include <stdio.h>

#include "cuda_runtime_api.h"

#include "builtin_types.h"
#include "driver_types.h"
#include "cudaProfiler.h"

#include "cuda_api.h"

#include "cuda_runtime.hpp"

cudaError_t g_last_cudaError = cudaSuccess;

cudart::Runtime *cudart_Runtime() {
    static cudart::Runtime *rt = NULL;
    if (rt == NULL) {
        rt = new cudart::Runtime();
    }

    return rt;
}

extern "C" {

char __cudaInitModule(void **fatCubinHandle) {
	printf("%s\n", __func__);
    return 0;
}

void **cudaRegisterFatBinaryInternal(void *fatCubin) {
    __fatDeviceText *fatDeviceText = (__fatDeviceText *)fatCubin;
    COB_header *cob = (COB_header *)fatDeviceText->pCOB;
    printf("cob.magic: %s\n", cob->magic_string);
    printf("cob.entries_n: %ld\n", cob->entries_num);
    bundle_entry *next_entry = (bundle_entry *)cob->entries;
    uint32_t next_entry_size = sizeof(bundle_entry) + next_entry->entry_id_length;

    for (uint32_t i=0; i<cob->entries_num; i++) {
        bundle_entry *entry = next_entry;
        uint32_t entry_size = next_entry_size;

        printf("### Entry Info: \n");
        printf("entry.object_offset: %lx\n", entry->code_object_offset);
        printf("entry.object_size: %lx\n", entry->code_object_size);
        printf("entry.id_len: %ld\n", entry->entry_id_length);
        printf("entry.id: %s\n", (char *)entry->entry_id);
        printf("entry size: %x\n", entry_size);

        next_entry = (bundle_entry *)((uint64_t)entry + entry_size);
        next_entry_size = sizeof(bundle_entry) + next_entry->entry_id_length;
    }

    return NULL;
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
    static cudart::Runtime *rt = cudart_Runtime();
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