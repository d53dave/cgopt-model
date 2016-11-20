//
// Created by dotdi on 20.11.16.
//

#pragma once

class CudaManaged {
public:
    void *operator new(size_t len) {
        void *ptr;
        cudaMallocManaged(&ptr, len);
        return (ptr);
    }

    void operator delete(void *ptr) {
        cudaFree(ptr);
    }
};
