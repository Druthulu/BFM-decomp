#ifndef OV_SC02_005_SHARED_H
#define OV_SC02_005_SHARED_H

/* §431 THREE-WAY SPLIT (P31 S74) — types that CROSS the two new TU boundaries.
 * ov_SC02_005_jr_80181D30.c was cut at vram 0x80185060 and 0x80185E80 so that each piece owns
 * exactly ONE contiguous .rodata run (the carve constraint, cookbook §8/§426/§431). Five typedefs
 * were used on both sides of a cut, so they were MOVED here (never copied — a duplicate typedef
 * is a C89 error). Typedefs emit no code, so this is byte-neutral — proven by the gate.
 * Include set is the original TU's. */

#include "common.h"
#include "../shared/engine_core.h"

/* HOISTED (P31 S54): these three typedefs were defined further down the file, BELOW the
 * INCLUDE_ASM lines of stubs that need them. harvest_verify strips a draft's own copy of any
 * typedef the TU already provides, which left the name undefined at the earlier insertion
 * point (pregate_check: TYPEDEF-USED-ABOVE-DEFINITION). Typedefs emit no code, so moving them
 * to the top is byte-neutral -- proven by the gate, not asserted. */
typedef struct {
    s16 f0;
    s16 f2;
    s16 f4;
    s16 f6;
} D_80195AF6_t;

typedef struct {
    u8 pad[4];
    s32 field_4;
} SubStruct;

typedef struct {
    u8 pad_00[0x20];
    SubStruct *f_20;
    u8 pad_24[0xA8];
    void *f_CC;
    void *f_D0;
    void *f_D4;
    u8 pad_D8[0x10];
    s32 f_E8;
} MainStruct;

/* from the Phase-26 §8b carried decl layer of ov_SC02_005_jr_80181D30.c */
typedef struct { s16 m[3][3]; s32 t[3]; } MTX_CF90;

typedef struct {
    s16 f0;
    s16 f2;
    s16 f4;
    s16 f6;
} D_80195AF4_t;

#endif /* OV_SC02_005_SHARED_H */
