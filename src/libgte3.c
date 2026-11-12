#include "common.h"

INCLUDE_ASM("asm/nonmatchings/libgte3", CompMatrix);

/* ApplyMatrixLV: PsyQ libgte: multiplies a long vector by a MATRIX's rotation part (v1 = m x v0)
 * Cited, library symbol: linked PsyQ symbol at this address (build/us/SLUS_007.26.map)
 * Names ledger: config/names.tsv ApplyMatrixLV; Citation: build/us/SLUS_007.26.map:1979 (ApplyMatrixLV, linked PsyQ libgte object) */
INCLUDE_ASM("asm/nonmatchings/libgte3", ApplyMatrixLV);

INCLUDE_ASM("asm/nonmatchings/libgte3", ApplyRotMatrix);

INCLUDE_ASM("asm/nonmatchings/libgte3", PushMatrix);

INCLUDE_ASM("asm/nonmatchings/libgte3", PopMatrix);

INCLUDE_ASM("asm/nonmatchings/libgte3", ReadRotMatrix);
