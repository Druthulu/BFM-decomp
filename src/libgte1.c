#include "common.h"

/* rsin: PsyQ libgte: sine of a 12-bit angle (0x1000 = one turn) in 1.12 fixed point
 * Cited, library symbol: linked PsyQ symbol at this address (build/us/SLUS_007.26.map)
 * Names ledger: config/names.tsv rsin; Citation: build/us/SLUS_007.26.map:1941 (rsin, linked PsyQ libgte object GEO_00.o, .text at :1940) */
INCLUDE_ASM("asm/nonmatchings/libgte1", rsin);

INCLUDE_ASM("asm/nonmatchings/libgte1", GEO_00_OBJ_2C);

INCLUDE_ASM("asm/nonmatchings/libgte1", func_800478B8);

void GEO_00_OBJ_C4(void) {
}

/* rcos: PsyQ libgte: cosine of a 12-bit angle (0x1000 = one turn) in 1.12 fixed point
 * Cited, library symbol: linked PsyQ symbol at this address (build/us/SLUS_007.26.map)
 * Names ledger: config/names.tsv rcos; Citation: build/us/SLUS_007.26.map:1945 (rcos, linked PsyQ libgte object GEO_01.o, .text at :1944) */
INCLUDE_ASM("asm/nonmatchings/libgte1", rcos);

void GEO_01_OBJ_98(void) {
}

INCLUDE_ASM("asm/nonmatchings/libgte1", csqrt_1);

INCLUDE_ASM("asm/nonmatchings/libgte1", COR_05_OBJ_130);

INCLUDE_ASM("asm/nonmatchings/libgte1", COR_05_OBJ_134);

INCLUDE_ASM("asm/nonmatchings/libgte1", csqrt);

INCLUDE_ASM("asm/nonmatchings/libgte1", COR_05_OBJ_1AC);

INCLUDE_ASM("asm/nonmatchings/libgte1", COR_05_OBJ_1D8);

INCLUDE_ASM("asm/nonmatchings/libgte1", catan);

INCLUDE_ASM("asm/nonmatchings/libgte1", COR_06_OBJ_A4);

INCLUDE_ASM("asm/nonmatchings/libgte1", func_80047CAC);

INCLUDE_ASM("asm/nonmatchings/libgte1", func_80047CB4);
