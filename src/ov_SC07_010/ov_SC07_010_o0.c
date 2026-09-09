#include "common.h"
#include "../shared/engine_prelude.h"


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
    extern Spr_8013B598 D_801A9420[];

    D_801A9420[a0].f0 = 1;
    D_801A9420[a0].f4 = ((Src_8013B598 *)a1)->f0;
    D_801A9420[a0].f6 = ((Src_8013B598 *)a1)->f2;
    D_801A9420[a0].f8 = ((Src_8013B598 *)a1)->f4;
    D_801A9420[a0].fC = 0x100;
}




void func_8013B6A0(s32 idx, u16 *src, s32 val)
{
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


extern s32 D_801A94D8;
extern s32 D_801A953C;

void func_8013B83C(s32 a0, s32 a1, s32 a2) {
                       /* sizeof 0x1C */
    extern Ent_8013B83C D_801DAA08_e[] __asm__("D_801A9420");
    extern s32 D_801A94BC;
    extern s32 D_801A94C0;
    extern s32 D_801A94C4;
    extern s32 D_801A94E8;
    extern s32 D_801A9538;
    extern s32 D_801A9540;
    extern s16 D_800B9A0E;
    extern void func_80052D90(s32 a0, void *a1);
    extern void func_8013C08C(void *a0, s32 a1);
    s32 i;

    D_801A94D8 = 0;
    D_801A94C4 = 0;
    D_801A94C0 = 0;
    D_801A94BC = 0;
    func_80052D90(0, &D_801A94E8);
    if (a0 == 0) {
        return;
    }
    D_801A9538 = a2 + 500;
    D_801A953C = a2;
    for (i = 0; i < 4; i++) {
        D_801DAA08_e[i].f0 = 0;
        D_801DAA08_e[i].f4 = D_801DAA08_e[i].f6 = D_801DAA08_e[i].f8 = 0x6000;
        D_801DAA08_e[i].fC = 0x100;
        D_801DAA08_e[i].f18 = 0;
    }
    switch (*(u8 *)a0) {
    case 0x42:
        if (D_800B9A0E == 0) {
            func_8013BD74(&D_801A94D8, a0);
        } else {
            func_8013BD74(&D_801A94D8, a1);
        }
        D_801A9540 = 0;
        break;
    case 0x43:
        func_8013C08C(&D_801A94D8, a0);
        D_801A9540 = 1;
        break;
    case 0x44:
        func_8013C08C(&D_801A94D8, a0);
        D_801A9540 = 2;
        break;
    case 0x45:
        func_8013C08C(&D_801A94D8, a0);
        D_801A9540 = 3;
        break;
    case 0x46:
        func_8013C08C(&D_801A94D8, a0);
        D_801A9540 = 4;
        break;
    case 0x47:
        func_8013C08C(&D_801A94D8, a0);
        D_801A9540 = 5;
        break;
    case 0x48:
        func_8013C08C(&D_801A94D8, a0);
        D_801A9540 = 6;
        break;
    case 0x49:
        func_8013C08C(&D_801A94D8, a0);
        D_801A9540 = 9;
        break;
    case 0x4A:
        func_8013C08C(&D_801A94D8, a0);
        D_801A9540 = 0xC;
        break;
    case 0x4B:
        func_8013C08C(&D_801A94D8, a0);
        D_801A9540 = 0xD;
        break;
    case 0x4C:
        func_8013C08C(&D_801A94D8, a0);
        D_801A9540 = 0xE;
        break;
    case 0x4D:
        func_8013C08C(&D_801A94D8, a0);
        D_801A9540 = 0xF;
        break;
    case 0x4E:
        func_8013C08C(&D_801A94D8, a0);
        D_801A9540 = 0x10;
        break;
    }
}




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



extern s16 D_801A93E0;
extern s16 D_801A93E2;
extern s16 D_801A93E4;
extern s16 D_801A93E6;

void func_8013BD74(void *a0, s32 a1) {
    /* §100 draft-LOCAL types: file-scope typedefs are NOT carried by extract_unit/remap_hseq, so a
       file-scope E_13BD74 banks the exemplar and then fails every sibling with `E_13BD74'
       undeclared (the §94 type-carry class, measured on ov_SC01_000). Block scope travels with the
       body and is byte-neutral (a type emits no code). */
    s32 *q;
    s32 *p;
    s32 i;
    s32 unused0;
    s32 unused1;
    P_13BD74 *e;
    P_13BD74 *end;
    s32 unused2;
    s32 base;
    s32 unused3;

    D_801A93E0 = -0xA0;
    D_801A93E2 = -0x78;
    D_801A93E4 = 0x140;
    D_801A93E6 = 0xF0;
    ((E_13BD74 *)a0)->f8 = (void *)a1;
    ((E_13BD74 *)a0)->fC = (void *)(a1 + 8);
    base = a1 + 0x4008;
    if (((u8 *)a1)[4] == 0) {
        p = (s32 *)((E_13BD74 *)a0)->fC;
        for (i = 0; i < 0x1000; i++) {
            if (*p != 0) {
                *p += (s32)((E_13BD74 *)a0)->fC;
                q = (s32 *)*p;
                q[0] += (s32)q;
                q[5] += (s32)q;
                e = (P_13BD74 *)q[5];
                q[6] = q[6] * 12 + q[5];
                end = (P_13BD74 *)q[6];
                while (e < end) {
                    switch (e->code) {
                    case 0x24:
                    case 0x2C:
                    case 0x34:
                    case 0x3C:
                        *(s32 *)e = (*(s32 *)e & 0xFFFFFF) + base;
                        break;
                    case 0x26:
                    case 0x2E:
                    case 0x36:
                    case 0x3E:
                        *(s32 *)e = (*(s32 *)e & 0xFFFFFF) + base;
                        break;
                    }
                    e++;
                }
            }
            p++;
        }
        ((u8 *)a1)[4] = 1;
    }
}


#include "../shared/ov/func_8013C08C.h"



#include "../shared/ov/func_8013C0F8__t95d2c582.h"


#include "../shared/ov/func_8013C360.h"



#include "../shared/ov/func_8013C414__t0f8a552a.h"


void func_8013C938(void) {

    extern s32 D_801A94D8;
    D_801A94D8 = 1;
}



void func_8013C964(void) {

    extern s32 D_801A94D8;
    D_801A94D8 = 0;
}

