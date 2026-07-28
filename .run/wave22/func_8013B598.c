/* func_8013B598 (ov_SC01_077_o0, -O0): fills entry a0 of the 0x1C-stride table at
 * D_801DAA08 from a 3-halfword source record.
 *
 * -O0 CONSTANT-OFFSET FOLD (the quirk that stalled this -O0 cluster in Phase 19):
 * at -O0 gcc-2.7.2 folds a constant offset into the memory operand ONLY through a
 * COMPONENT_REF / a real ARRAY_REF on an array-typed DECL:
 *     D_801DAA08[a0].f4 = ...   ->  lui $at,%hi(sym); addu $at,$at,idx; sh %lo(sym+4)($at)
 * A CAST base defeats it (NOP_EXPR over the ADDR_EXPR), and so does pointer indexing:
 *     ((S *)D_801DAA08)[a0].f4  ->  lui;addiu;addu;sh 4(reg)      (+2 ins per store)
 *     a1[1]                     ->  addiu $v1,$a0,2; lhu 0($v1)   (+1 ins per load)
 * So the table extern must carry the FULL struct type (not the pad-only canonical
 * E_3B7AC), and the source record must be read as ->field, not as a[i]. Casting the
 * incoming POINTER is harmless (a NOP on a register), only the base decl's type matters.
 *
 * Both types are body-scoped (cookbook §100) and the extern is declared inside the body,
 * matching the established -O0 sibling pattern in src/ov_SC07_010/ov_SC07_010_o0.c
 * (func_8013B7AC: `extern E_3B7AC D_801A9420[];` in-body). NOTE FOR BANKING: the canonical
 * sig-layer decl `extern E_3B7AC D_801DAA08[];` (f0 + pad only) CANNOT be used here — it has
 * no f4/f6/f8/fC members. The in-body decl below must be the one that survives; do not also
 * emit a file-scope E_3B7AC decl for D_801DAA08 (conflicting types).
 *
 * 66/66 instructions byte-identical (match_one --o0).
 */
void func_8013B598(s32 a0, u16 *a1) {
    typedef struct { u16 f0; u16 f2; u16 f4; } Src_8013B598;
    typedef struct { s32 f0; u16 f4; u16 f6; u16 f8; u16 fA; s32 fC; u8 pad[0xC]; } Spr_8013B598;
    extern Spr_8013B598 D_801DAA08[];

    D_801DAA08[a0].f0 = 1;
    D_801DAA08[a0].f4 = ((Src_8013B598 *)a1)->f0;
    D_801DAA08[a0].f6 = ((Src_8013B598 *)a1)->f2;
    D_801DAA08[a0].f8 = ((Src_8013B598 *)a1)->f4;
    D_801DAA08[a0].fC = 0x100;
}
