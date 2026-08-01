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



extern s16 D_801A93E0;
extern s16 D_801A93E2;
extern s16 D_801A93E4;
extern s16 D_801A93E6;

void func_8013BD74(void *a0, s32 a1) {
    /* §100 draft-LOCAL types: file-scope typedefs are NOT carried by extract_unit/remap_hseq, so a
       file-scope E_13BD74 banks the exemplar and then fails every sibling with `E_13BD74'
       undeclared (the §94 type-carry class, measured on ov_SC01_000). Block scope travels with the
       body and is byte-neutral (a type emits no code). */
    typedef struct {
        u8    pad0[8];
        void *f8;
        void *fC;
    } E_13BD74;
    typedef struct {
        u8  pad0[3];
        u8  code;
        s32 f4;
        s32 f8;
    } P_13BD74;
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


extern void func_8013C0F8(s32 a0);

void func_8013C08C(void *a0, void *a1) {
    /* SS100 DRAFT-LOCAL type: only this function uses E_13C08C_8013C08C, so it lives in the BODY, not at
     * file scope. At file scope extract_unit's preceding-decl backscan cannot carry it: the scan
     * walks back over extern/comment/blank/typedef lines, and a MULTI-LINE typedef presents its
     * CLOSING line first, which matches none of those prefixes. Every templated sibling therefore
     * got the body without the type and the family swept 0/137 (SS94: a family 0/N is a type-carry
     * failure until proven otherwise). Declared here, it is part of the unit by construction.
     * NB no brace characters in this comment on purpose - extract_unit's forward brace-scan does
     * not strip comments, so a brace in a comment truncates the extracted unit. */
    typedef struct {
        u8   pad0[8];
        void *f8;
        void *fC;
    } E_13C08C_8013C08C;

    void *p = a1;

    ((E_13C08C_8013C08C *)a0)->f8 = a1;
    ((E_13C08C_8013C08C *)a0)->fC = (u8 *)p + 0x14;
    func_8013C0F8((s32)a1);
}



void func_8013C0F8(int param_1) {
    int iVar1;
    int iVar2;
    unsigned int local_18;
    unsigned int local_14;
    Bar *local_10;
    Foo *local_c;

    iVar1 = param_1 + 0x14;
    if (*(char *)(param_1 + 4) == '\0') {
        iVar2 = iVar1 + *(int *)(param_1 + 0xc);
        *(int *)(param_1 + 0xc) = iVar2;
        *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + iVar1;
        local_c = (Foo *)iVar1;
        for (local_18 = 0; local_18 < *(unsigned int *)(param_1 + 8); local_18++, local_c++) {
            local_c->field10 = local_c->field10 + iVar1;
            local_10 = (Bar *)local_c->field10;
            for (local_14 = 0; local_14 < local_c->count; local_14++, local_10++) {
                switch (local_10->tag) {
                case 0x24:
                case 0x2c:
                case 0x34:
                case 0x3c:
                    *(unsigned int *)local_10 = (*(unsigned int *)local_10 & 0xffffff) + iVar2;
                    break;
                case 0x26:
                case 0x2e:
                case 0x36:
                case 0x3e:
                    *(unsigned int *)local_10 = (*(unsigned int *)local_10 & 0xffffff) + iVar2;
                    break;
                }
            }
        }
        *(unsigned char *)(param_1 + 4) = 1;
    }
}


DEFINE_func_8013C360()  /* dedup: shared engine-core @0x8013C360 (src/shared) */



void func_8013C414(s32 param_1, s32 param_2)
{
    s32 base10;      /* 0x00 */
    s32 p;           /* 0x04 */
    s32 q;           /* 0x08 */
    s32 base4008;    /* 0x0C */
    s32 lo;          /* 0x10 */
    u32 i;           /* 0x14 */
    s32 unused;      /* 0x18 */
    s32 base8;       /* 0x1C */
    T3Reloc *r;      /* 0x20 */
    T3Reloc *s;      /* 0x24 */

    if (*(s32 *)(param_2 + 4) == 0) {
        base10 = param_2 + 0x10;
        base4008 = param_1 + 0x4008;
        lo = *(s32 *)(param_2 + 0xC) + base10;
        base8 = param_1 + 8;
        p = base10;
        for (i = 0; i < *(u32 *)(param_2 + 8); i++) {
            *(s32 *)p = *(s32 *)p + base8;
            if (*(s32 *)(p + 4) != 0) {
                *(s32 *)(p + 4) = *(s32 *)(p + 4) + base10;
                q = *(s32 *)(p + 4);
                *(s32 *)q = *(s32 *)q + q;
                *(s32 *)(q + 0x14) = *(s32 *)(q + 0x14) + q;
                r = (T3Reloc *)*(s32 *)(q + 0x14);
                *(s32 *)(q + 0x18) = *(s32 *)(q + 0x18) * 0xC + *(s32 *)(q + 0x14);
                s = (T3Reloc *)*(s32 *)(q + 0x18);
                while (r < s) {
                    switch (r->type) {
                    case 0x24:
                    case 0x2C:
                    case 0x34:
                    case 0x3C:
                        if ((*(u32 *)r) & 0x800000) {
                            (*(u32 *)r) = ((*(u32 *)r) & 0x7FFFFF) + lo;
                        } else {
                            (*(u32 *)r) = ((*(u32 *)r) & 0xFFFFFF) + base4008;
                        }
                        break;
                    case 0x26:
                    case 0x2E:
                    case 0x36:
                    case 0x3E:
                        if ((*(u32 *)r) & 0x800000) {
                            (*(u32 *)r) = ((*(u32 *)r) & 0x7FFFFF) + lo;
                        } else {
                            (*(u32 *)r) = ((*(u32 *)r) & 0xFFFFFF) + base4008;
                        }
                        break;
                    }
                    r++;
                }
            }
            p = p + 0xC;
        }
        *(s32 *)(param_2 + 4) = 1;
        p = param_2 + 0x10;
        for (i = 0; i < *(u32 *)(param_2 + 8); i++) {
            if (*(s32 *)(p + 8) == 0) {
                *(s32 *)(p + 8) = *(s32 *)(*(s32 *)p);
            }
            p = p + 0xC;
        }
    } else {
        p = param_2 + 0x10;
        for (i = 0; i < *(u32 *)(param_2 + 8); i++) {
            *(s32 *)(*(s32 *)p) = *(s32 *)(p + 8);
            p = p + 0xC;
        }
    }
}


void func_8013C938(void) {

    extern s32 D_801A94D8;
    D_801A94D8 = 1;
}



void func_8013C964(void) {

    extern s32 D_801A94D8;
    D_801A94D8 = 0;
}

