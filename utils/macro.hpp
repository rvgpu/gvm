#pragma once

// 用于结构体对齐
#define ALIGNED(alignsize)  __attribute__((aligned(alignsize)))

#define ALIGN_SIZE(size, align)     (((size + align - 1) / align ) * align)
#define ALIGN_SIZE_4(size)          ALIGN_SIZE(size, 4)