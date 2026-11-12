#include "common.h"

/* SetRotMatrix: PsyQ libgte: loads a MATRIX's rotation part into the GTE rotation registers
 * Cited, library symbol: linked PsyQ symbol at this address (build/us/SLUS_007.26.map)
 * Names ledger: config/names.tsv SetRotMatrix; Citation: build/us/SLUS_007.26.map:2015 (SetRotMatrix, linked PsyQ libgte object) */
INCLUDE_ASM("asm/nonmatchings/libgte6", SetRotMatrix);

INCLUDE_ASM("asm/nonmatchings/libgte6", func_8004917C);

/* SetTransMatrix: PsyQ libgte: loads a MATRIX's translation into the GTE translation registers
 * Cited, library symbol: linked PsyQ symbol at this address (build/us/SLUS_007.26.map)
 * Names ledger: config/names.tsv SetTransMatrix; Citation: build/us/SLUS_007.26.map:2020 (SetTransMatrix, linked PsyQ libgte object) */
INCLUDE_ASM("asm/nonmatchings/libgte6", SetTransMatrix);

INCLUDE_ASM("asm/nonmatchings/libgte6", ReadGeomOffset);

INCLUDE_ASM("asm/nonmatchings/libgte6", func_800491EC);

INCLUDE_ASM("asm/nonmatchings/libgte6", func_800491FC);

INCLUDE_ASM("asm/nonmatchings/libgte6", func_8004921C);
