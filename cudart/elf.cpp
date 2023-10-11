/*
 * Copyright © 2023 Sietium Semiconductor.
 */

#include "elf.hpp"

using namespace cuda;

#include <cstdio>
ELF::ELF(void *elf, int size) {
    header = elf;
    this->size = size;
}