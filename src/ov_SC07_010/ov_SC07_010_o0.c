#include "common.h"
#include "../shared/engine_core.h"


void func_8013B568(s32 arg0) {

    extern s32 D_80182714;
    D_80182714 = arg0;
}



/* func_8013B598 (ov_SC01_077_o0, -O0): fills entry a0 of the 0x1C-stride table at
 * D_801A9420 from a 3-halfword source record.
 *
 * -O0 CONSTANT-OFFSET FOLD (the quirk that stalled this -O0 cluster in Phase 19):
 * at -O0 gcc-2.7.2 folds a constant offset into the memory operand ONLY through a
 * COMPONENT_REF / a real ARRAY_REF on an array-typed DECL:
 *     D_801A9420[a0].f4 = ...   ->  lui $at,%hi(sym); addu $at,$at,idx; sh %lo(sym+4)($at)
 * A CAST base defeats it (NOP_EXPR over the ADDR_EXPR), and so does pointer indexing:
 *     ((S *)D_801A9420)[a0].f4  ->  lui;addiu;addu;sh 4(reg)      (+2 ins per store)
 *     a1[1]                     ->  addiu $v1,$a0,2; lhu 0($v1)   (+1 ins per load)
 * So the table extern must carry the FULL struct type (not the pad-only canonical
 * E_3B7AC), and the source record must be read as ->field, not as a[i]. Casting the
 * incoming POINTER is harmless (a NOP on a register), only the base decl's type matters.
 *
 * Both types are body-scoped (cookbook §100) and the extern is declared inside the body,
 * matching the established -O0 sibling pattern in src/ov_SC07_010/ov_SC07_010_o0.c
 * (func_8013B7AC: `extern E_3B7AC D_801A9420[];` in-body). NOTE FOR BANKING: the canonical
 * sig-layer decl `extern E_3B7AC D_801A9420[];` (f0 + pad only) CANNOT be used here — it has
 * no f4/f6/f8/fC members. The in-body decl below must be the one that survives; do not also
 * emit a file-scope E_3B7AC decl for D_801A9420 (conflicting types).
 *
 * 66/66 instructions byte-identical (match_one --o0).
 */
void func_8013B598(s32 a0, u16 *a1) {
    typedef struct { u16 f0; u16 f2; u16 f4; } Src_8013B598;
    typedef struct { s32 f0; u16 f4; u16 f6; u16 f8; u16 fA; s32 fC; u8 pad[0xC]; } Spr_8013B598;
    extern Spr_8013B598 D_801A9420[];

    D_801A9420[a0].f0 = 1;
    D_801A9420[a0].f4 = ((Src_8013B598 *)a1)->f0;
    D_801A9420[a0].f6 = ((Src_8013B598 *)a1)->f2;
    D_801A9420[a0].f8 = ((Src_8013B598 *)a1)->f4;
    D_801A9420[a0].fC = 0x100;
}




void func_8013B6A0(s32 idx, u16 *src, s32 val)
{
    typedef struct {
        s32 f0;
        u16 f4;
        u16 f6;
        u16 f8;
        u16 fA;
        s32 fC;
        u8  pad[0xC];
    } Ent_8013B6A0;
    typedef struct {
        u16 f0;
        u16 f2;
        u16 f4;
    } Src_8013B6A0;
    extern Ent_8013B6A0 D_801A9420[];

    D_801A9420[idx].f0 = 1;
    D_801A9420[idx].f4 = ((Src_8013B6A0 *)src)->f0;
    D_801A9420[idx].f6 = ((Src_8013B6A0 *)src)->f2;
    D_801A9420[idx].f8 = ((Src_8013B6A0 *)src)->f4;
    D_801A9420[idx].fC = val;
}


   /* sizeof 0x1C stride */
void func_8013B7AC(int a0) {
    extern E_3B7AC D_801A9420[];
 D_801A9420[a0].f0 = 0; }




void func_8013B7F4(s32 a0, s32 a1) {

    extern s32 D_801A953C;
    func_8013B83C(a0, a1, D_801A953C);
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o0", func_8013B83C);




void func_8013BC7C(void *arg0) {

    extern void (*D_80181F78[])(void *);
    D_80181F78[((S_8013BC7C *)arg0)->f68](arg0);
}



/* func_8013BCDC (ov_SC01_077_o0, -O0): guarded indirect call through D_80182714.
 * D_80182714 is declared `extern s32` in the TU (canonical-sig layer) and holds a
 * function pointer; read it as an s32, test non-null, cast to fn-ptr and call.
 * Frame residual: target frame is 0x30 (saves $ra/$fp/$s0 at 0x28/0x24/0x20) — 16
 * bytes of var_size above the minimal 0x20. At -O0 (no DCE) an unused 16-byte local
 * reserves exactly that var region (cookbook §42 lever 3, frame-pad induction) with
 * zero body instructions. 22/22 byte-identical via rtu_match. */
void func_8013BCDC(void) {

    extern s32 D_80182714;
    s32 pad[4];
    if (D_80182714 != 0) {
        ((void (*)(void))D_80182714)();
    }
}



void func_8013BD34(s32 a0) {

    extern s32 D_801A94D8;
    func_8013BD74(&D_801A94D8, a0);
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o0", func_8013BD74);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o0", func_8013C08C);

INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o0", func_8013C0F8);


void func_8013C360(s32 a0) {
    s32 *p;
    u32 i;
    p = (s32 *)(a0 + 0x10);
    for (i = 0; i < *(u32 *)(a0 + 8); i++) {
        *(s32 *)(*(s32 *)p) = *(s32 *)((s32)p + 4);
        p = (s32 *)((s32)p + 0xC);
    }
}


INCLUDE_ASM("asm/ov_SC07_010/nonmatchings/ov_SC07_010_o0", func_8013C414);


void func_8013C938(void) {

    extern s32 D_801A94D8;
    D_801A94D8 = 1;
}



void func_8013C964(void) {

    extern s32 D_801A94D8;
    D_801A94D8 = 0;
}

