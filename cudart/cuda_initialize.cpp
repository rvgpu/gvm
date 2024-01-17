#include "cuda_runtime.hpp"

cuda::Runtime *rtstatic = NULL;

void cuda_runtime_init(void) __attribute__((constructor));
void cuda_runtime_init(void) {
    rtstatic = new cuda::Runtime();
}

void cuda_runtime_exit(void) __attribute__((destructor));
void cuda_runtime_eixt(void) {
    delete rtstatic;
}
