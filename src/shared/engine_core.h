/* src/shared/engine_core.h — Phase 15 shared engine-core bodies (cross-overlay dedup, §14).
 * Each DEFINE_func_XXXX() expands to the WHOLE matched body once; instantiated in place at the
 * func_XXXX site in every overlay that shares it (address order preserved). Registry +
 * byte-honesty: config/dedup.us.yaml + tools/dedup_integrate.py. Tool-generated; do not hand-edit. */
#ifndef SHARED_ENGINE_CORE_H
#define SHARED_ENGINE_CORE_H
#include "common.h"

#define DEFINE_func_80128EA8() \
    void func_80128EA8(s32 a0, s32 a1, s32 a2) { \
        *(s32 *)(a1 + 0x0) = a2;                       /* sw a2, 0x0(a1) */ \
        *(s16 *)(a1 + 0x4) = 0;                         /* sh zero, 0x4(a1) */ \
        *(s16 *)(a1 + 0x6) = (*(s32 *)(a2 + 0x4)) & 0x3F; /* lw; andi 0x3F; sh 0x6(a1) */ \
        *(s16 *)(a0 + 0x28) = *(u16 *)(a2 + 0x0);      /* lhu 0x0(a2); sh 0x28(a0) */ \
        *(s16 *)(a0 + 0x2A) = *(u16 *)(a2 + 0x2);      /* lhu 0x2(a2); sh 0x2A(a0) */ \
    }

#define DEFINE_func_8012A568() \
    extern void func_8012A598(void *a0); \
    void func_8012A568(void (*a0)(void)) { \
        func_8012A598(a0); \
        a0(); \
    }

#define DEFINE_func_80132EC4() \
    void func_80132EC4(void *a0, s16 a1) { \
        while (*(s32 *)a0 != 0) { \
            *(s16 *)((s32)a0 + 4) = a1; \
            a0 = (void *)((s32)a0 + 8); \
        } \
    }

#define DEFINE_func_80138C30() \
    void func_80138C30(void *a0) { \
        if (*(s16 *)((s32)a0 + 4) == 4) { \
            *(s16 *)((s32)a0 + 4) = 2; \
        } else { \
            *(u32 *)((s32)a0 + 8) |= 0x800; \
        } \
    }

#endif
