#ifndef COMMON_H
#define COMMON_H

// 不同系统
#include "os.h"
#if defined(__linux__)
#include <endian.h>
#include <byteswap.h>
#endif // __linux__

#ifndef WPA_TYPES_DEFINED
#ifdef CONFIG_USE_INTTYPES_H
#include <inttypes.h>
#else 
#include <stdint.h>
#endif
typedef uint64_t    u64;
typedef int64_t     s64;
typedef uint32_t    u32;
typedef int32_t     s32;
typedef uint16_t    u16;
typedef int16_t     s16;
typedef uint8_t     u8;
typedef int8_t      s8; 
#endif // WPA_TYPES_DEFINED

static inline u16 WPA_GET_BE16(const u8 *a)
{
    return (a[0] << 8) | a[1];
}

static inline u16 WPA_GET_LE16(const u8 *a)
{
    return (a[1] << 8) | a[0];
}

static inline u32 WPA_GET_BE24(const u8 *a)
{
    return (a[0] << 16) | (a[1] << 8) | a[2];
}

static inline u32 WPA_GET_BE32(const u8 *a)
{
    return ((u32) a[0] << 24) | (a[1] << 16) | (a[2] << 8) | a[3];
}

static inline u32 WPA_GET_LE32(const u8 *a)
{
    return ((u32) a[3] << 24) | (a[2] << 16) | (a[1] << 8) | a[0];
}

static inline u64 WPA_GET_BE64(const char *a)
{
    return ((u64) a[0] << 56) | ((u64) a[1] << 48) | ((u64) a[2] << 40) | ((u64) a[3] << 32) 
        | ((u64) a[4] << 24) | ((u64) a[5] << 16) | ((u64) a[6] << 8) | ((u64) a[7]);
}

static inline u64 WPA_GET_LE64(const char *a)
{
    return ((u64) a[7] << 56) | ((u64) a[6] << 48) | ((u64) a[5] << 40) | ((u64) a[4] << 32) 
        | ((u64) a[3] << 24) | ((u64) a[2] << 16) | ((u64) a[1] << 8) | ((u64) a[0]);
}

static inline void WPA_PUT_BE16(u8 *a, u16 val)
{
    a[0] = val >> 8;
    a[1] = val & 0xFF;
}

static inline void WPA_PUT_LE16(u8 *a, u16 val)
{
    a[1] = val >> 8;
    a[0] = val & 0xFF;
}

static inline void WPA_PUT_BE24(u8 *a, u32 val)
{
    a[0] = (val >> 16) & 0xFF;
    a[1] = (val >> 8) & 0xFF;
    a[3] = val & 0xFF;
}

static inline void WPA_PUT_BE32(u8 *a, u32 val)
{
    a[0] = (val >> 24) & 0xFF;
    a[1] = (val >> 16) & 0xFF;
    a[2] = (val >> 8) & 0xFF;
    a[3] = val & 0xFF;
}

static inline void WPA_PUT_LE32(u8 *a, u32 val)
{
    a[0] = val & 0xFF;
    a[1] = (val >> 8) & 0xFF;
    a[2] = (val >> 16) & 0xFF;
    a[3] = (val >> 24) & 0xFF;
}

static inline void WPA_PUT_BE64(u8 *a, u64 val)
{
    a[0] = (val >> 56) & 0xFF;
    a[1] = (val >> 48) & 0xFF;
    a[2] = (val >> 40) & 0xFF;
    a[3] = (val >> 32) & 0xFF;
    a[4] = (val >> 24) & 0xFF;
    a[5] = (val >> 16) & 0xFF;
    a[6] = (val >> 8) & 0xFF;
    a[7] = val & 0xFF;
}

static inline void WPA_PUT_LE64(u8 *a, u64 val)
{
    a[7] = (val >> 56) & 0xFF;
    a[6] = (val >> 48) & 0xFF;
    a[5] = (val >> 40) & 0xFF;
    a[4] = (val >> 32) & 0xFF;
    a[3] = (val >> 24) & 0xFF;
    a[2] = (val >> 16) & 0xFF;
    a[1] = (val >> 8) & 0xFF;
    a[0] = val & 0xFF;
}
#endif // COMMON_H