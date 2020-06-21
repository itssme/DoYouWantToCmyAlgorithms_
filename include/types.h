#ifndef DOYOUWANTTOCMYALGORITHMS__TYPES_H
#define DOYOUWANTTOCMYALGORITHMS__TYPES_H

#include <stdint.h>
#include <stddef.h>

typedef unsigned int uint;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

_Static_assert(sizeof(u64) == sizeof(size_t), "size_t is not 64 bit");

#endif //DOYOUWANTTOCMYALGORITHMS__TYPES_H
