#include "random.h"

typedef unsigned int uint;
typedef unsigned int u32;
typedef unsigned long u64;
_Static_assert(sizeof (u32) == 4, "size of u32 is not 4 bytes");
_Static_assert(sizeof (u64) == 8, "size of u64 is not 8 bytes");

const uint n = 624;
u32 y[624];
uint id = 624;

void init_random() {
    u64 seed = 1234567890;
    for(uint i = 0; i < n; i++) {
        seed = (seed * 0x5DEECE66DL + 0xBL) & 0xFFFFFFFFFFFF;
        y[i] = (seed >> 16);
    }
}

static u32 getY(uint i) {
    return y[i % n];
}

int get_next(int max) {
    static const u32 magic[] = {0, 0x9908B0DF};
    // take highest bit of first seed and 31 lower bits of the next seed
    u32 h = (getY(id - n) & 0x80000000) | (getY(id - n + 1) & 0x7FFFFFFF);
    u32 nextY = getY(id - 227) ^ (h >> 1) ^ magic[h & 1];
    y[(id - n) % n] = nextY;
    id++;

    u32 a = nextY ^ (nextY >> 11);
    u32 b = a ^ ((a << 7) & 0x9D2C5680);
    u32 c = b ^ ((b << 15) & 0xEFC60000);
    return ((c ^ (c >> 18)) & 0x7FFFFFFF) % max;
}