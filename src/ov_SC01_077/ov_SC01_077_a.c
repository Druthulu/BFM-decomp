#include "common.h"
#include "../shared/engine_core.h"

/* ==== Phase-17 canonical-sig layer (tools/derive_canonical_sigs.py) ===================
 * ONE byte-neutral canonical signature per undeclared-stub conflict callee, so the parallel
 * hand-matching wave declares each shared callee consistently and the one-big-TU build stops
 * failing on `conflicting types` (hand-matching-process.md §7c). Form: s32 return (void->s32
 * byte-neutral, §3a-1) + s32 params (matched bodies cast int->ptr), arity from Ghidra-C + asm
 * read-before-write $a0-$a3 (agree on all 14 cached; 6 stubs call-site-validated). LOCAL to
 * this TU on purpose (reach-1 names like func_801809BC differ across overlays, so NOT in the
 * shared engine_core.h). Whole-binary harvest_verify byte-gate remains the sole arbiter (G3/P9). */
extern s32 func_8016EC0C(s32 a0, s32 a1);                /* match-first, arity 2 */
extern s32 func_8012B4B8(s32 a0);                        /* match-first, arity 1 */
extern s32 func_801670E4(s32 a0, s32 a1, s32 a2, s32 a3); /* derive-decl, arity 4 */
extern s32 func_80169A4C(s32 a0, s32 a1);                /* match-first, arity 2 */
extern s32 func_8016A8FC(s32 a0);                        /* match-first, arity 1 */
extern s32 func_8012B8E4(s32 a0, s32 a1);                /* match-first, arity 2 */
extern s32 func_8015E1B8(s32 a0);                        /* match-first, arity 1 */
extern s32 func_8015EE08(s32 a0);                        /* match-first, arity 1 */
extern s32 func_8015F7D4(s32 a0);                        /* match-first, arity 1 */
extern s32 func_80160B34(s32 a0);                        /* match-first, arity 1 */
extern s32 func_80165140(s32 a0);                        /* match-first, arity 1 */
extern s32 func_80161CD0(s32 a0, s32 a1);                /* match-first, arity 2 */
extern s32 func_80175268(s32 a0);                        /* match-first, arity 1 */
extern s32 func_8017EC7C(s32 a0);                        /* match-first, arity 1 */
extern s32 func_801809BC(s32 a0, s32 a1);                /* match-first, arity 2 */
extern s32 func_8012DE2C(s32 a0);                        /* derive-decl, arity 1 */
extern s32 func_8012DDA4(void);                          /* derive-decl, arity 0 */
extern s32 func_801759D8(void);                          /* derive-decl, arity 0 */
extern s32 func_80175820(void);                          /* derive-decl, arity 0 */
extern s32 func_801758FC(void);                          /* derive-decl, arity 0 */
/* ==== end canonical-sig layer ==================================================== */

DEFINE_func_80128158()  /* dedup: shared engine-core @0x80128158 (src/shared) */

DEFINE_func_80128178()  /* dedup: shared engine-core @0x80128178 (src/shared) */

DEFINE_func_80128198()  /* dedup: shared engine-core @0x80128198 (src/shared) */

DEFINE_func_801281B8()  /* dedup: shared engine-core @0x801281B8 (src/shared) */

DEFINE_func_801281D8()  /* dedup: shared engine-core @0x801281D8 (src/shared) */

DEFINE_func_801281F8()  /* dedup: shared engine-core @0x801281F8 (src/shared) */

extern s32 D_801D7F90;

s32 func_80128218(void) {
    return D_801D7F90;
}

DEFINE_func_80128228()  /* dedup: shared engine-core @0x80128228 (src/shared) */

DEFINE_func_80128248()  /* dedup: shared engine-core @0x80128248 (src/shared) */

DEFINE_func_80128268()  /* dedup: shared engine-core @0x80128268 (src/shared) */

extern u16 D_800B99F6;
extern void (*D_80186DB4[])(void);

void func_80128288(void) {
    u32 v1;
    v1 = D_800B99F6;
    if (v1 < 9) {
        D_80186DB4[v1]();
    }
}

DEFINE_func_801282CC()  /* dedup: shared engine-core @0x801282CC (src/shared) */

DEFINE_func_801282EC()  /* dedup: shared engine-core @0x801282EC (src/shared) */

DEFINE_func_8012832C()  /* dedup: shared engine-core @0x8012832C (src/shared) */


DEFINE_func_80128420()  /* dedup: shared engine-core @0x80128420 (src/shared) */

DEFINE_func_801284B8()  /* dedup: shared engine-core @0x801284B8 (src/shared) */

DEFINE_func_801284F0()  /* dedup: shared engine-core @0x801284F0 (src/shared) */

DEFINE_func_8012853C()  /* dedup: shared engine-core @0x8012853C (src/shared) */

DEFINE_func_80128564()  /* dedup: shared engine-core @0x80128564 (src/shared) */

DEFINE_func_801285D4()  /* dedup: shared engine-core @0x801285D4 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_801285E4);

/* HANDWRITTEN scratchpad-stack-switch sequencer: stores $sp at the scratchpad slot
 * 0x1F8003FC and repoints $sp into the D-cache scratchpad before each engine call,
 * restoring it after. Manipulating $sp is not expressible in C; full inline asm
 * (manages its own frame). Signature pinned by engine_core.h: void func_80128678(void). */
DEFINE_func_80128678()  /* dedup: shared engine-core @0x80128678 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80128714);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_801287B8);

extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 sp10);
extern s32 D_801D7F90;
extern u8 D_800AEFD0;

s32 func_801288B0(void) {
    func_8001ABBC(0, 0, &D_800AEFD0, D_801D7F90, 0);
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_801288E8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80128940);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80128998);

extern s32 D_801D7F90;
extern u8 D_800AECB8;
extern void func_8001ABBC(s32 a0, s32 a1, void *a2, s32 a3, s32 a4);

s32 func_801289F0(void) {
    func_8001ABBC(0, 0, &D_800AECB8, D_801D7F90, 0);
}

M2C_UNK func_80010DE0();                            /* extern */
extern void func_80011B7C(int);
extern void func_80011C10(void);
extern u16 D_800B99F6;
extern s16 D_800B9A00;
extern M2C_UNK (*D_80186AF0)();
extern s16 (*D_80186AF4)();

void func_80128A28(void) {
    s16 temp_v0;

    switch (D_800B99F6) {                           /* irregular */
    case 1:
        D_80186AF0();
        /* fallthrough */
    case 0:
        func_80011C10();
        return;
    case 2:
        temp_v0 = D_80186AF4();
        if (temp_v0 != 0) {
            if (temp_v0 < 0) {
                func_80011B7C(0);
                D_800B9A00 = 1;
                return;
            }
            func_80010DE0();
        } else {
            return;
        }
        break;
    }
}


M2C_UNK func_80010DE0();                            /* extern */
extern void func_80011B7C(int);
extern void func_80011C10(void);
extern void func_8002AEF8(void);
s32 func_8002AF08();                                /* extern */
extern void func_800CFBBC(void);
s32 func_800CFBE8();                                /* extern */
extern u16 D_800B99F6;
extern M2C_UNK (*D_80186AFC)();
extern s32 (*D_80186B00)();
extern s32 D_801D9480;

void func_80128AF4(void) {
    switch (D_800B99F6) {                           /* irregular */
    case 0:
        D_801D9480 = func_8002AF08();
        func_80011C10();
        return;
    case 1:
        D_80186AFC();
        func_80011C10();
        return;
    case 2:
        if ((D_80186B00() << 0x10) != 0) {
            if (D_801D9480 == 1) {
                if (func_800CFBE8() != 0) {
                    func_800CFBBC();
                    func_80011B7C(0x13);
                } else {
                    func_80011B7C(4);
                }
            } else {
                func_80010DE0();
            }
            func_8002AEF8();
        }
        return;
    }
}


DEFINE_func_80128C14()  /* dedup: shared engine-core @0x80128C14 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80128C98);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80128CFC);

DEFINE_func_80128D60()  /* dedup: shared engine-core @0x80128D60 (src/shared) */

// @class: struct
// @stuck: none — MATCH
DEFINE_func_80128DB4()  /* dedup: shared engine-core @0x80128DB4 (src/shared) */


DEFINE_func_80128EA8()  /* dedup: shared engine-core @0x80128EA8 (src/shared) */

// LOAD-BEARING register pins (cookbook §17 + §25): the residual here was NOT scheduling but
// gcc-2.7.2 COPY-COALESCING — gcc folded the index-preserve copy (idc) into the multiply operand
// (`sll $v0,$a3,3` on the copy) instead of multiplying $v1 directly. Pinning idc to its target
// reg ($a3) forces the multiply onto $v1 and emits the copy separately AFTER it; routing idc+1
// through the dead $v0-pinned `cnt` lands it in $v0 (target's scratch), not back in $a3.
// Do NOT "simplify" the pins or the cnt reuse — each is byte-load-bearing (byte-gated).
#include "common.h"

s32 func_80128ED8(s32 param_1, s32 *param_2) {
    register s32 iVar4 __asm__("$8");   /* base ptr, lives whole fn in $t0 */
    register s32 cnt   __asm__("$2");   /* decremented count in $v0 */
    register s32 cc    __asm__("$3");   /* preserved count copy in $v1 (forces the bne-delay-slot copy) */
    register s32 idx   __asm__("$3");   /* offset-4 index, loaded into $v1 */
    register s32 idc   __asm__("$7");   /* $a3: preserved idx copy, forced SEPARATE from the multiply */
    u32 uVar3;
    s32 frame_pad[4];                   /* phantom 0x10 frame the target reserves (induce via clobber anchor) */

    __asm__ __volatile__("" : : "r"(&frame_pad) : "memory");
    iVar4 = *param_2;
    cnt = *(s16 *)((s32)param_2 + 6);
    if (cnt == 0) {
        return 1;
    }
    cc = cnt;
    __asm__ __volatile__("" : "=r"(cc) : "0"(cc));   /* force the count-preserve copy ($v1=$v0) */
    cnt = cc - 1;
    *(s16 *)((s32)param_2 + 6) = (s16)cnt;
    if (cnt * 0x10000 < 1) {
        idx = *(s16 *)((s32)param_2 + 4);
        __asm__ __volatile__("" : "=r"(idx) : "0"(idx));   /* pin the index into $v1 */
        uVar3 = *(u32 *)(idx * 8 + iVar4 + 4);
        idc = idx;
        if ((uVar3 & 0xc0) == 0xc0) {
            *(s16 *)((s32)param_2 + 6) = 0;
            return 1;
        }
        if ((uVar3 & 0x80) != 0) {
            *(s16 *)((s32)param_2 + 4) = 0;
        } else {
            cnt = idc + 1;                       /* reuse the dead $v0 pin so idc+1 lands in $v0, not $a3 */
            *(s16 *)((s32)param_2 + 4) = cnt;
        }
        *(u16 *)((s32)param_2 + 6) =
            (u16)(*(u32 *)((s16)param_2[1] * 8 + iVar4 + 4) & 0x3f);
        *(u16 *)(param_1 + 0x28) = *(u16 *)((s16)param_2[1] * 8 + iVar4);
        *(u16 *)(param_1 + 0x2a) = *(u16 *)((s16)param_2[1] * 8 + iVar4 + 2);
    }
    return 0;
}


M2C_UNK func_8001534C(M2C_UNK, M2C_UNK *, M2C_UNK, M2C_UNK, s32, s32); /* extern */
M2C_UNK func_800153CC(M2C_UNK, u16, M2C_UNK, M2C_UNK, s32, s32); /* extern */
extern M2C_UNK D_801D7F94;

void func_80128FAC(u16 *arg0) {
    func_8001534C(4, &D_801D7F94, 0x80, 0x90, 0, 0);
    func_800153CC(5, *arg0, 0xA8, 0x90, 0x40, 0);
}


DEFINE_func_80129010()  /* dedup: shared engine-core @0x80129010 (src/shared) */

extern u8 *func_8012913C(s32 a0);

u8 *func_801290DC(s32 a0, u8 *a1) {
    u8 *v1 = func_8012913C(a0 & 0xFFFF);

    if (v1 != 0) {
        *(u16 *)(v1 + 0x6) = *(u16 *)(a1 + 0x0);
        *(u16 *)(v1 + 0xA) = *(u16 *)(a1 + 0x2);
        *(u16 *)(v1 + 0xE) = *(u16 *)(a1 + 0x4);
    }
    return v1;
}


/* Callees — canonical-consistent sigs.
 * func_8001D074: canonical `void func_8001D074(s32, s32)`; widened return to s32
 *   (byte-neutral, §3a-1) because this fn uses the result.
 * func_801291C0: canonical `u8 *func_801291C0(void)` (engine_core.h DEFINE_func_801291C0).
 * func_8001CC3C: arity-4 from m2c/asm read-before-write $a0-$a3; void->s32 byte-neutral.
 */
DEFINE_func_8012913C()  /* dedup: shared engine-core @0x8012913C (src/shared) */


DEFINE_func_801291C0()  /* dedup: shared engine-core @0x801291C0 (src/shared) */

extern void func_80129258(void);
extern void func_80129248(s16 a0);

void func_80129220(void) {
    func_80129258();
    func_80129248(1);
}

DEFINE_func_80129248()  /* dedup: shared engine-core @0x80129248 (src/shared) */

DEFINE_func_80129258()  /* dedup: shared engine-core @0x80129258 (src/shared) */

DEFINE_func_8012927C()  /* dedup: shared engine-core @0x8012927C (src/shared) */

DEFINE_func_801292C8()  /* dedup: shared engine-core @0x801292C8 (src/shared) */

DEFINE_func_8012931C()  /* dedup: shared engine-core @0x8012931C (src/shared) */

DEFINE_func_80129350()  /* dedup: shared engine-core @0x80129350 (src/shared) */

DEFINE_func_80129374()  /* dedup: shared engine-core @0x80129374 (src/shared) */

DEFINE_func_80129398()  /* dedup: shared engine-core @0x80129398 (src/shared) */

DEFINE_func_80129428()  /* dedup: shared engine-core @0x80129428 (src/shared) */

DEFINE_func_8012943C()  /* dedup: shared engine-core @0x8012943C (src/shared) */

// @class: schedule
// @stuck: none — MATCH (72 ins)

DEFINE_func_8012944C()  /* dedup: shared engine-core @0x8012944C (src/shared) */


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_8012956C);


DEFINE_func_801298F4()  /* dedup: shared engine-core @0x801298F4 (src/shared) */


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_801299C8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80129C40);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80129CF8);

DEFINE_func_80129FF4()  /* dedup: shared engine-core @0x80129FF4 (src/shared) */

extern u8 D_80126948[];
void func_8012A048(void *a0, s32 a1, u8 a2);

void func_8012A018(s32 a0, s32 a1)
{
    func_8012A048(D_80126948, a0, a1);
}

DEFINE_func_8012A048()  /* dedup: shared engine-core @0x8012A048 (src/shared) */

DEFINE_func_8012A094()  /* dedup: shared engine-core @0x8012A094 (src/shared) */

DEFINE_func_8012A0E0()  /* dedup: shared engine-core @0x8012A0E0 (src/shared) */

DEFINE_func_8012A100()  /* dedup: shared engine-core @0x8012A100 (src/shared) */

DEFINE_func_8012A110()  /* dedup: shared engine-core @0x8012A110 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_8012A1BC);

DEFINE_func_8012A2F4()  /* dedup: shared engine-core @0x8012A2F4 (src/shared) */

DEFINE_func_8012A304()  /* dedup: shared engine-core @0x8012A304 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_8012A328);


struct Q16 { s32 a, b, c, d; };

extern s32 D_801151D4;
extern struct BigCopy D_80114EE8;

void func_8012A418(void) {
    struct Q16 *src;
    struct Q16 *dst;
    struct Q16 *end;

    src = (struct Q16 *)D_801151D4;
    dst = &D_80114EE8;
    end = src + 10;
    do {
        *dst = *src;
        src++;
        dst++;
    } while (src != end);
    *(s32 *)dst = *(s32 *)src;
}


typedef struct { s32 w[8]; } Vec8;

extern s32 D_801151D4;
extern Vec8 D_80114F24;

void func_8012A464(void)
{
    D_80114F24 = *(Vec8 *)(*(s32 *)&D_801151D4 + 0x3C);
}

DEFINE_func_8012A4BC()  /* dedup: shared engine-core @0x8012A4BC (src/shared) */

DEFINE_func_8012A568()  /* dedup: shared engine-core @0x8012A568 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_8012A598);

DEFINE_func_8012A5F8()  /* dedup: shared engine-core @0x8012A5F8 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_8012A62C);

DEFINE_func_8012A68C()  /* dedup: shared engine-core @0x8012A68C (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_8012A6D0);

DEFINE_func_8012A758()  /* dedup: shared engine-core @0x8012A758 (src/shared) */

DEFINE_func_8012A79C()  /* dedup: shared engine-core @0x8012A79C (src/shared) */

DEFINE_func_8012A7D4()  /* dedup: shared engine-core @0x8012A7D4 (src/shared) */


DEFINE_func_8012A828()  /* dedup: shared engine-core @0x8012A828 (src/shared) */

DEFINE_func_8012A860()  /* dedup: shared engine-core @0x8012A860 (src/shared) */

DEFINE_func_8012A8B0()  /* dedup: shared engine-core @0x8012A8B0 (src/shared) */

DEFINE_func_8012A8E8()  /* dedup: shared engine-core @0x8012A8E8 (src/shared) */

DEFINE_func_8012A908()  /* dedup: shared engine-core @0x8012A908 (src/shared) */

DEFINE_func_8012A988()  /* dedup: shared engine-core @0x8012A988 (src/shared) */


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_8012AAAC);

extern void func_8012AAAC(void);
extern M2C_UNK D_80186E48;

void func_8012ACA0(void *arg0) {
    M2C_FIELD(arg0, M2C_UNK **, 0x90) = &D_80186E48;
    M2C_FIELD(arg0, s32 *, 0x94) = 0;
    M2C_FIELD(arg0, s32 *, 0x9C) = 0;
    M2C_FIELD(arg0, s16 *, 0x9A) = 0;
    M2C_FIELD(arg0, u16 *, 0x72) = (u16) (M2C_FIELD(arg0, u16 *, 0x72) & 0xF9FF);
    func_8012AAAC();
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_8012ACE0);

DEFINE_func_8012AD44()  /* dedup: shared engine-core @0x8012AD44 (src/shared) */

DEFINE_func_8012AD50()  /* dedup: shared engine-core @0x8012AD50 (src/shared) */


void func_8012AD64(s32 *a0, s16 a1) {
    *(s16*)((s32)a0 + 0x34) = a1;
}

DEFINE_func_8012AD6C()  /* dedup: shared engine-core @0x8012AD6C (src/shared) */

DEFINE_func_8012AD80()  /* dedup: shared engine-core @0x8012AD80 (src/shared) */

DEFINE_func_8012ADE4()  /* dedup: shared engine-core @0x8012ADE4 (src/shared) */

DEFINE_func_8012AE00()  /* dedup: shared engine-core @0x8012AE00 (src/shared) */

extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_800132BC(s32 a0, s32 a1);

/* LOAD-BEARING: the 8-byte sp+0x18->sp+0x20 copy is an alignment-2 struct copy
   (3 shorts written, then copied) -> gcc emits lwl/lwr/swl/swr.  An aligned-2
   base-type typedef did NOT reproduce it; only a short-only struct (align 2) does. */

DEFINE_func_8012AF0C()  /* dedup: shared engine-core @0x8012AF0C (src/shared) */

DEFINE_func_8012B030()  /* dedup: shared engine-core @0x8012B030 (src/shared) */

// @class: schedule
// @stuck: none — MATCH (38 ins, relocation-masked)

DEFINE_func_8012B0B4()  /* dedup: shared engine-core @0x8012B0B4 (src/shared) */


DEFINE_func_8012B14C()  /* dedup: shared engine-core @0x8012B14C (src/shared) */

DEFINE_func_8012B178()  /* dedup: shared engine-core @0x8012B178 (src/shared) */

DEFINE_func_8012B1B4()  /* dedup: shared engine-core @0x8012B1B4 (src/shared) */

DEFINE_func_8012B200()  /* dedup: shared engine-core @0x8012B200 (src/shared) */

DEFINE_func_8012B21C()  /* dedup: shared engine-core @0x8012B21C (src/shared) */

DEFINE_func_8012B23C()  /* dedup: shared engine-core @0x8012B23C (src/shared) */

DEFINE_func_8012B260()  /* dedup: shared engine-core @0x8012B260 (src/shared) */

DEFINE_func_8012B2CC()  /* dedup: shared engine-core @0x8012B2CC (src/shared) */

DEFINE_func_8012B370()  /* dedup: shared engine-core @0x8012B370 (src/shared) */

DEFINE_func_8012B414()  /* dedup: shared engine-core @0x8012B414 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_8012B4B8);

DEFINE_func_8012B608()  /* dedup: shared engine-core @0x8012B608 (src/shared) */

DEFINE_func_8012B6D4()  /* dedup: shared engine-core @0x8012B6D4 (src/shared) */

DEFINE_func_8012B70C()  /* dedup: shared engine-core @0x8012B70C (src/shared) */

DEFINE_func_8012B744()  /* dedup: shared engine-core @0x8012B744 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_8012B77C);

DEFINE_func_8012B864()  /* dedup: shared engine-core @0x8012B864 (src/shared) */

DEFINE_func_8012B8A4()  /* dedup: shared engine-core @0x8012B8A4 (src/shared) */

DEFINE_func_8012B8E4()  /* dedup: shared engine-core @0x8012B8E4 (src/shared) */



/* canonical data externs (per pre-resolved sigs); asm loads them lh -> (s16) cast at use */
extern u16 D_80126B66;
extern u16 D_80126B5E;
/* callee func_8004CFEC, linked as symbol "ratan2" (config/symbols.us.txt: 0x8004CFEC);
 * canonical s32(s32,s32) -- matches the banked sibling func_8012B8E4 in engine_core.h */
extern s32 ratan2(s32 a0, s32 a1);

s32 func_8012BA10(s32 arg0, s32 arg1) {
    register s32 d __asm__("$16");      /* $s0 -- pinned: divisor, live across the jal */
    register s32 s1ang __asm__("$17");  /* $s1 -- pinned: ptr+0x12 angle, live across the jal */
    s32 u5; s32 u6; s32 iVar4; s32 q; s32 t;
    d = arg1;
    s1ang = *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x12);
    u5 = (ratan2(*(s16 *)(arg0 + 0xE) - (s16)D_80126B66, (s16)D_80126B5E - *(s16 *)(arg0 + 6)) - 0x400) & 0xFFF;
    __asm__ __volatile__("" : : "r"(u5));   /* scheduling barrier: anchor u5 before the (s16)d cast */
    d = (s16)d;
    u6 = s1ang & 0xFFF;
    if (u6 == u5) return 0;
    iVar4 = u5 - u6;
    if (iVar4 > 0x800) { t = u6 + 0x1000; iVar4 = u5 - t; }
    if (iVar4 < -0x800) { t = u6 - 0x1000; iVar4 = u5 - t; }
    if (iVar4 >= 0) { q = iVar4 / d; if (q == 0) q = 1; }
    else { q = iVar4 / d; if (q == 0) q = -1; }
    return q;
}



DEFINE_func_8012BB3C()  /* dedup: shared engine-core @0x8012BB3C (src/shared) */


DEFINE_func_8012BC60()  /* dedup: shared engine-core @0x8012BC60 (src/shared) */

DEFINE_func_8012BCCC()  /* dedup: shared engine-core @0x8012BCCC (src/shared) */

DEFINE_func_8012BD14()  /* dedup: shared engine-core @0x8012BD14 (src/shared) */

DEFINE_func_8012BD3C()  /* dedup: shared engine-core @0x8012BD3C (src/shared) */

DEFINE_func_8012BDBC()  /* dedup: shared engine-core @0x8012BDBC (src/shared) */

DEFINE_func_8012BE54()  /* dedup: shared engine-core @0x8012BE54 (src/shared) */

DEFINE_func_8012BE98()  /* dedup: shared engine-core @0x8012BE98 (src/shared) */


DEFINE_func_8012BEE8()  /* dedup: shared engine-core @0x8012BEE8 (src/shared) */

DEFINE_func_8012BF10()  /* dedup: shared engine-core @0x8012BF10 (src/shared) */

void func_8012BF4C(s32 *a0, s32 a1) {
    *(s32*)((s32)a0 + 0x1C) = a1;
}

DEFINE_func_8012BF54()  /* dedup: shared engine-core @0x8012BF54 (src/shared) */

/* func_8012BF68: lhu 0x5C; andi 0x7FFF; sh 0x5C; jr (sh in delay slot)
 * void form: no return value => no extra andi v0,0xffff truncation past the mask. */
DEFINE_func_8012BF68()  /* dedup: shared engine-core @0x8012BF68 (src/shared) */

DEFINE_func_8012BF7C()  /* dedup: shared engine-core @0x8012BF7C (src/shared) */

// @class: schedule
// @stuck: none — MATCH (39/39 reloc-masked words byte-verified via objdump -s raw .text; match_one's "18 mismatched" is the objdump zero-run-elision artifact dropping the 2 cop2-latency nops, same as sibling DEFINE_func_8013E2C4 @ ov_SC01_077.c:326)
#include "common.h"

DEFINE_func_8012BFA8()  /* dedup: shared engine-core @0x8012BFA8 (src/shared) */


DEFINE_func_8012C044()  /* dedup: shared engine-core @0x8012C044 (src/shared) */

// @class: plumbing
// @stuck: none — MATCH expected; tail-call passes incoming param through (nop delay slot)

extern void func_8012C218(void *a0);

void func_8012C098(void *param_1)
{
    int iVar1;

    iVar1 = *(int *)((char *)param_1 + 0x68);
    if ((iVar1 != 0) && ((*(short *)((char *)param_1 + 0x72) & 0x8000) != 0)) {
        *(unsigned short *)(iVar1 + 10) = *(unsigned short *)(iVar1 + 10) & 0x7fff;
    }
    func_8012C218(param_1);
    return;
}


// @class: other
// @stuck: none — MATCH (42 ins, relocation-masked); func_8012C044 dispatch idiom, if(fp==0) branch-polarity
extern s32 D_801274D4;
extern s16 D_80126CAC;
extern s32 D_801274E0;
extern s32 func_80013478(s32 a0, s32 a1);
extern void func_8012C218(void *a0);

s32 func_8012C0EC(s32 a0) {
    s32 (*fp)(s32) = (s32 (*)(s32))D_801274D4;
    s32 cond;
    s32 *p;

    if (fp == 0) {
        cond = (func_80013478(a0 + 4, (s32)&D_80126CAC) < D_801274E0) ^ 1;
    } else {
        cond = fp(a0);
    }
    if (cond == 0) {
        return 0;
    }
    p = *(s32 **)(a0 + 0x68);
    if (p != 0) {
        if ((*(s16 *)(a0 + 0x72) & 0x8000) != 0) {
            *(u16 *)((s32)p + 0xA) = *(u16 *)((s32)p + 0xA) & 0x7FFF;
        }
    }
    func_8012C218((void *)a0);
    return 1;
}


DEFINE_func_8012C194()  /* dedup: shared engine-core @0x8012C194 (src/shared) */

DEFINE_func_8012C1B8()  /* dedup: shared engine-core @0x8012C1B8 (src/shared) */

DEFINE_func_8012C1DC()  /* dedup: shared engine-core @0x8012C1DC (src/shared) */

DEFINE_func_8012C218()  /* dedup: shared engine-core @0x8012C218 (src/shared) */

DEFINE_func_8012C284()  /* dedup: shared engine-core @0x8012C284 (src/shared) */

// @class: schedule
// @stuck: none — MATCH expected (lifted byte-proven loop idiom from sibling func_8012C750 @0x8012C750)
#include "common.h"

DEFINE_func_8012C2D0()  /* dedup: shared engine-core @0x8012C2D0 (src/shared) */


DEFINE_func_8012C31C()  /* dedup: shared engine-core @0x8012C31C (src/shared) */

DEFINE_func_8012C354()  /* dedup: shared engine-core @0x8012C354 (src/shared) */

DEFINE_func_8012C438()  /* dedup: shared engine-core @0x8012C438 (src/shared) */

DEFINE_func_8012C51C()  /* dedup: shared engine-core @0x8012C51C (src/shared) */


DEFINE_func_8012C588()  /* dedup: shared engine-core @0x8012C588 (src/shared) */



extern u8 D_80126720[];
extern s32 func_8012C890(s32 a0, s32 a1, s32 a2);

struct S8012C658 {
    u16 unk0;
    u16 unk2;
    u16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    s32 unk10;
};

s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2) {
    struct S8012C658 sp;
    s32 var_v0;
    u16 *var_a1;
    u16 *end;
    u16 *param;

    if ((arg2 != 0) && (*(u16 *)(arg2 + 0x0) != 0)) {
        sp.unk0 = *(u16 *)(arg2 + 0x6);
        sp.unk2 = *(u16 *)(arg2 + 0xA);
        sp.unk4 = *(u16 *)(arg2 + 0xE);
    } else {
        sp.unk4 = 0;
        sp.unk2 = 0;
        sp.unk0 = 0;
    }
    sp.unk6 = (s16)arg0;
    sp.unk8 = (s16)arg1;
    sp.unkA = 0;
    sp.unk10 = 0;
    sp.unkE = 0;
    sp.unkC = 0x7FFF;
    param = &sp.unk0;
    end = (u16 *)D_80126720;
    if (arg2 == 0) {
        var_a1 = (u16 *)((u8 *)end - 0x6480);
    } else {
        var_a1 = (u16 *)(arg2 + 0x10C);
    }
    while (var_a1 != end) {
        if (*var_a1 == 0) {
            goto found;
        }
        var_a1 = (u16 *)((u8 *)var_a1 + 0x10C);
    }
    var_a1 = 0;
found:
    var_v0 = 0;
    if (var_a1 != 0) {
        var_v0 = ((s32 (*)(u16 *, u16 *))func_8012C890)(param, var_a1);
    }
    return var_v0;
}


DEFINE_func_8012C724()  /* dedup: shared engine-core @0x8012C724 (src/shared) */

// @class: iv-combine
// @stuck: none — MATCH (52 ins)
#include "common.h"

extern u8 D_80120194[];
extern u8 D_801202A0[];
extern s32 func_8012C890(s32 a0, s32 a1, s32 a2);

s32 func_8012C750(s32 a0)
{
    s32 p;
    s32 it;
    s32 v0;

    if (*(u16 *)(a0 + 0xA) & 0x800) {
        s32 base = (s32)D_80120194;
        p = base + 0x6480;
        if (p != base) {
            do {
                if (*(u16 *)p == 0) goto found;
                p -= 0x10C;
            } while (p != base);
        }
        p = 0;
        goto found;
    } else {
        it = (s32)D_80120194;
        __asm__ __volatile__("" : "=r"(it) : "0"(it));
        p = it + 0x658C;
        goto test;
    copy:
        p = it;
        goto found;
    test:
        it = (s32)D_801202A0;
        __asm__ __volatile__("" : "=r"(it) : "0"(it));
        if (it == p) goto zero;
    body:
        if (*(u16 *)it == 0) goto copy;
        it += 0x10C;
        if (it != p) goto body;
    zero:
        p = 0;
    }
found:
    if (p == 0) {
        v0 = 0;
    } else {
        *(u16 *)(a0 + 0xA) = *(u16 *)(a0 + 0xA) | 0x8000;
        v0 = func_8012C890(a0, p, 0);
    }
    return v0;
}


DEFINE_func_8012C820()  /* dedup: shared engine-core @0x8012C820 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_8012C890);

DEFINE_func_8012CAE4()  /* dedup: shared engine-core @0x8012CAE4 (src/shared) */


DEFINE_func_8012CB64()  /* dedup: shared engine-core @0x8012CB64 (src/shared) */


extern void func_8012CC88(s32 a, s32 b, s32 c);
extern u8 D_800D3918[];

void func_8012CBA4(s32 a0) {
    func_8012CC88(a0, 0, (s32)D_800D3918);
}

extern void func_8012CC88(s32 a, s32 b, s32 c);
extern u8 D_800D3918[];

void func_8012CBCC(s32 a0) {
    func_8012CC88(a0, 1, (s32)D_800D3918);
}

DEFINE_func_8012CBF4()  /* dedup: shared engine-core @0x8012CBF4 (src/shared) */

DEFINE_func_8012CC1C()  /* dedup: shared engine-core @0x8012CC1C (src/shared) */

DEFINE_func_8012CC40()  /* dedup: shared engine-core @0x8012CC40 (src/shared) */

DEFINE_func_8012CC64()  /* dedup: shared engine-core @0x8012CC64 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_8012CC88);

DEFINE_func_8012CE2C()  /* dedup: shared engine-core @0x8012CE2C (src/shared) */

DEFINE_func_8012CEB0()  /* dedup: shared engine-core @0x8012CEB0 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_8012CFA8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_8012D098);

DEFINE_func_8012D38C()  /* dedup: shared engine-core @0x8012D38C (src/shared) */

DEFINE_func_8012D3AC()  /* dedup: shared engine-core @0x8012D3AC (src/shared) */

DEFINE_func_8012D3B4()  /* dedup: shared engine-core @0x8012D3B4 (src/shared) */


// @class: plumbing
// @stuck: none — MATCH (sibling of func_8012D3B4 + func_8012DEB8 sp10/sp18 prelude)
#include "common.h"

DEFINE_func_8012D4B4()  /* dedup: shared engine-core @0x8012D4B4 (src/shared) */


DEFINE_func_8012D5DC()  /* dedup: shared engine-core @0x8012D5DC (src/shared) */

DEFINE_func_8012D5E4()  /* dedup: shared engine-core @0x8012D5E4 (src/shared) */

DEFINE_func_8012D624()  /* dedup: shared engine-core @0x8012D624 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_8012D664);

// @class: struct
// @stuck: none — MATCH expected; base = (*(u32*)(p+0x58) & 0xFFFFFFF) | 0x80000000 held once, %lo folds via offsets
#include "common.h"

DEFINE_func_8012D714()  /* dedup: shared engine-core @0x8012D714 (src/shared) */


extern void func_8012F568(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5);
extern void func_8014C978(void);
extern M2C_UNK D_80186E60;
extern M2C_UNK D_80186E68;

s32 func_8012DB84(void)
{
    func_8014C978();
    func_8012F568(1, 0xC001, 0, 0x3E8, &D_80186E60, &D_80186E68);
}


// @class: regalloc-order
// @stuck: none — MATCH. Pins: args $s2/$s4/$s5/$s3, loop-actor $s0, running-max/square $s1; abs load-temp pinned $v0 ($2) so abs copies $v0->$v1; re-tie barrier on iVar4 kills slt-into-bgez-delay duplication; nested ifs keep the two 0x5c bit-tests from folding to one andi 0xc000.
#include "common.h"

DEFINE_func_8012DBD0()  /* dedup: shared engine-core @0x8012DBD0 (src/shared) */


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_8012DDA4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_8012DE2C);

DEFINE_func_8012DEB8()  /* dedup: shared engine-core @0x8012DEB8 (src/shared) */

DEFINE_func_8012DF34()  /* dedup: shared engine-core @0x8012DF34 (src/shared) */

DEFINE_func_8012DFBC()  /* dedup: shared engine-core @0x8012DFBC (src/shared) */

DEFINE_func_8012DFCC()  /* dedup: shared engine-core @0x8012DFCC (src/shared) */

DEFINE_func_8012DFD4()  /* dedup: shared engine-core @0x8012DFD4 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_8012E014);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_8012E138);

s32 func_8012E27C(void) {
    return 1;
}

DEFINE_func_8012E284()  /* dedup: shared engine-core @0x8012E284 (src/shared) */

// @class: struct
// @stuck: none — MATCH (modeled on DEFINE_func_8012D3B4 sibling idiom: (s8*)&D_800A651C + (u16)D_800B9A02*0x14)

DEFINE_func_8012E28C()  /* dedup: shared engine-core @0x8012E28C (src/shared) */


DEFINE_func_8012E32C()  /* dedup: shared engine-core @0x8012E32C (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_8012E364);

DEFINE_func_8012E470()  /* dedup: shared engine-core @0x8012E470 (src/shared) */

DEFINE_func_8012E4C8()  /* dedup: shared engine-core @0x8012E4C8 (src/shared) */

DEFINE_func_8012E504()  /* dedup: shared engine-core @0x8012E504 (src/shared) */

DEFINE_func_8012E544()  /* dedup: shared engine-core @0x8012E544 (src/shared) */

DEFINE_func_8012E57C()  /* dedup: shared engine-core @0x8012E57C (src/shared) */

// @class: schedule
// @stuck: none — MATCH
extern u8 D_800AF648;
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern void func_8002D4C8(s32 a0, s32 a1);

void func_8012E5CC(s32 param_1, u16 param_2, u16 param_3)
{
    struct { short xy[2]; int sp14; int flag; } f;
    register void *p __asm__("$4");
    p = &D_800AF648;
    func_8004914C(p);
    func_800491AC(&D_800AF648);
    RotTransPers(param_1, (s32)f.xy, &f.sp14, &f.flag);
    if (f.flag >= 0 && (u16)(f.xy[0] + 199) < 399 && (u16)(f.xy[1] + 0xA9) < 0x153) {
        func_8002D4C8(param_2, param_3);
    }
}


// @class: regalloc-order
// @stuck: none — MATCH (60/60). Pins: $4 defeats &D_800AF648 CSE; $16/$17 force param_2/param_3 saved-reg order vs the guard-branch reversal
#include "common.h"

DEFINE_func_8012E688()  /* dedup: shared engine-core @0x8012E688 (src/shared) */


// @class: other
// @stuck: none — MATCH (69/69 ins, relocation-masked 0 diffs via tools/match_one precise check)
#include "common.h"

/* GTE inline-asm sequences (psyq inline_c.h bodies). rtps uses the project's
 * `rtps` assembler macro (include/gte_macros.inc, pulled in by common.h ->
 * include_asm.h -> labels.inc) which encodes 0x4A180001 — NOT the psyq
 * `.word 0x0000007f`, which assembles to the wrong word for this target. */
#define gte_SetRotMatrix(r0) __asm__ volatile (         \
    "lw $12, 0( %0 );"                                   \
    "lw $13, 4( %0 );"                                   \
    "ctc2 $12, $0;"                                      \
    "ctc2 $13, $1;"                                      \
    "lw $12, 8( %0 );"                                   \
    "lw $13, 12( %0 );"                                  \
    "lw $14, 16( %0 );"                                  \
    "ctc2 $12, $2;"                                      \
    "ctc2 $13, $3;"                                      \
    "ctc2 $14, $4"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )

#define gte_SetTransMatrix(r0) __asm__ volatile (        \
    "lw $12, 20( %0 );"                                  \
    "lw $13, 24( %0 );"                                  \
    "ctc2 $12, $5;"                                      \
    "lw $14, 28( %0 );"                                  \
    "ctc2 $13, $6;"                                      \
    "ctc2 $14, $7"                                       \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13", "$14" )

#define gte_ldlv0(r0) __asm__ volatile (                 \
    "lhu $13, 4( %0 );"                                  \
    "lhu $12, 0( %0 );"                                  \
    "sll $13, $13, 16;"                                  \
    "or $12, $12, $13;"                                  \
    "mtc2 $12, $0;"                                      \
    "lwc2 $1, 8( %0 )"                                   \
    :                                                    \
    : "r"( r0 )                                          \
    : "$12", "$13" )

#define gte_rtps() __asm__ volatile ("nop;nop;rtps")

#define gte_stsxy(r0) __asm__ volatile (                 \
    "swc2 $14, 0( %0 )"                                  \
    :                                                    \
    : "r"( r0 )                                          \
    : "memory" )

typedef struct { s32 m[3][3]; s32 t[3]; } MATRIX;
typedef struct { s32 vx, vy, vz; } VECTOR;

extern u8 D_800AF648;

s32 func_8012E778(int param_1, int param_2)
{
    MATRIX *r0;
    int iVarX;
    int iVarY;
    int iVar3;
    int iVar4;
    int sp[6];

    sp[0] = (int)*(short *)(param_1 + 6);
    sp[1] = (int)*(short *)(param_1 + 10);
    sp[2] = (int)*(short *)(param_1 + 0xe);
    r0 = (MATRIX *)&D_800AF648;
    gte_SetRotMatrix(r0);
    gte_SetTransMatrix(r0);
    gte_ldlv0((VECTOR *)sp);
    gte_rtps();
    gte_stsxy((long *)((int)sp + 0x10));

    iVarX = (int)*(short *)((int)sp + 0x10);
    iVar3 = (short)param_2;
    if (iVarX >= 0) {
        if (iVar3 >= iVarX) goto cy;
        return 0;
    }
    if (iVar3 < -iVarX) return 0;
cy:
    iVarY = (int)*(short *)((int)sp + 0x12);
    iVar4 = param_2 >> 0x10;
    if (iVarY >= 0) {
        if (iVar4 >= iVarY) goto c1;
        return 0;
    }
    if (iVar4 < -iVarY) return 0;
c1:
    return 1;
}


DEFINE_func_8012E88C()  /* dedup: shared engine-core @0x8012E88C (src/shared) */

DEFINE_func_8012E8A8()  /* dedup: shared engine-core @0x8012E8A8 (src/shared) */

DEFINE_func_8012E8C4()  /* dedup: shared engine-core @0x8012E8C4 (src/shared) */

DEFINE_func_8012E8E0()  /* dedup: shared engine-core @0x8012E8E0 (src/shared) */


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_8012E9C0);

// @class: regalloc-order
// @stuck: none — MATCH (93 ins)


extern void func_80049CAC(s32 a0, s32 a1);

typedef struct { u32 a, b, c, d; } Blk16;
typedef struct { s16 h[8]; } Buf;

void func_8012EA90(s32 param_1, s32 param_2, s32 *param_3)
{
    Buf buf;
    s32 iVar4;
    register u32 v __asm__("$17");      /* $s1 */

    iVar4 = *(s32 *)(param_1 + 0x20);
    v = *(u32 *)(iVar4 + 0x20);

    if (v == 0) {
        *(Blk16 *)(param_3)        = *(Blk16 *)(iVar4 + 0x34);
        *(Blk16 *)((s32)param_3 + 0x10) = *(Blk16 *)(iVar4 + 0x44);
    } else if ((v & 0x1000000) != 0) {
        register s32 p __asm__("$16");
        s32 w;
        p = (s32)(v & 0xfeffffff);
        p = p + param_2 * 8;

        buf.h[0] = *(s16 *)(p + 6);
        w = *(s32 *)p;
        buf.h[1] = (s16)(*(u8 *)(p + 1) | ((w & 0xf) << 8));
        buf.h[2] = (s16)(((w >> 0x10) & 0xff) | ((w & 0xf0) << 4));
        func_80049CAC((s32)&buf, (s32)param_3);
        param_3[5] = *(s8 *)(p + 3);
        param_3[6] = *(s8 *)(p + 4);
        param_3[7] = *(s8 *)(p + 5);
    } else {
        s32 q;
        v = v + param_2 * 0xc;
        q = (s32)v;
        buf.h[0] = *(s16 *)(q + 6);
        buf.h[1] = *(s16 *)(q + 8);
        buf.h[2] = *(s16 *)(q + 0xa);
        func_80049CAC((s32)&buf, (s32)param_3);
        param_3[5] = *(s16 *)(q + 0);
        param_3[6] = *(s16 *)(q + 2);
        param_3[7] = *(s16 *)(q + 4);
    }
}


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_8012EC04);

DEFINE_func_8012EECC()  /* dedup: shared engine-core @0x8012EECC (src/shared) */

DEFINE_func_8012EF34()  /* dedup: shared engine-core @0x8012EF34 (src/shared) */

DEFINE_func_8012EF70()  /* dedup: shared engine-core @0x8012EF70 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_8012EFB8);

// @class: other
// @stuck: none — MATCH (33 ins, match_one verified)

extern void ApplyTransposeMatrixLV(void *a0, void *a1, void *a2);

void func_8012F038(int param_1, short *param_2, short *param_3) {
    int in[3];
    int out[3];

    in[0] = (int)param_2[0] - *(int *)(param_1 + 0x14);
    in[1] = (int)param_2[1] - *(int *)(param_1 + 0x18);
    in[2] = (int)param_2[2] - *(int *)(param_1 + 0x1c);
    ApplyTransposeMatrixLV((void *)param_1, in, out);
    param_3[0] = out[0];
    param_3[1] = out[1];
    param_3[2] = out[2];
}


DEFINE_func_8012F0BC()  /* dedup: shared engine-core @0x8012F0BC (src/shared) */

// @class: plumbing
// @stuck: none — MATCH (clone of confirmed func_8012F214 template; passthrough a0)
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(s32 a0, s32 a1, void *a2);

void func_8012F14C(s32 a0, s32 a1, s32 a2)
{
    s32 buf[2];
    func_8004914C((void *)a0);
    func_800491AC((void *)a0);
    RotTransSV(a1, a2, buf);
}


DEFINE_func_8012F1A4()  /* dedup: shared engine-core @0x8012F1A4 (src/shared) */

DEFINE_func_8012F214()  /* dedup: shared engine-core @0x8012F214 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_8012F274);

DEFINE_func_8012F2E8()  /* dedup: shared engine-core @0x8012F2E8 (src/shared) */

DEFINE_func_8012F374()  /* dedup: shared engine-core @0x8012F374 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_8012F40C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_8012F49C);

// @class: schedule
// @stuck: none — MATCH (35 ins). Two unaligned 8-byte memcpy to globals then sh a1/a2/a3 + lhu/or/sh RMW on D_80126B94. KEY: an `__asm__ __volatile__("":::"memory")` barrier between the 2nd memcpy and the halfword section pins the D_80126B94 RMW *read* AFTER both memcpys (without it gcc hoists the lhu between the two memcpy blocks; volatile globals over-anchors it to the END).

DEFINE_func_8012F568()  /* dedup: shared engine-core @0x8012F568 (src/shared) */


DEFINE_func_8012F5F4()  /* dedup: shared engine-core @0x8012F5F4 (src/shared) */



struct S80131E00;
DEFINE_func_8012F68C()  /* dedup: shared engine-core @0x8012F68C (src/shared) */


extern void func_80131B14(void);
extern void func_80131CA8(int a0, int a1);

void func_8012F75C(s32 a0) {
    *(u8 *)(a0 + 0xC1) = 3;
    if (*(s32 *)(a0 + 0xB4) & 0x4) {
        func_80131B14();
        *(s32 *)(a0 + 0x1C) = 0x10;
        *(s16 *)(a0 + 0x98) = 0;
    }
    func_80131CA8(a0, 6);
}

DEFINE_func_8012F7B4()  /* dedup: shared engine-core @0x8012F7B4 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_8012F828);

DEFINE_func_8012F87C()  /* dedup: shared engine-core @0x8012F87C (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_8012F8C8);

DEFINE_func_8012F91C()  /* dedup: shared engine-core @0x8012F91C (src/shared) */

// @class: struct
// @stuck: none — MATCH (123 ins). Keys: 3 stack out-params as ONE struct (kept all live + word-load),
//         branch-polarity inverts on the two if/else, and the 0x98=0 store moved AFTER the 3rd division.
#include "common.h"

DEFINE_func_8012F968()  /* dedup: shared engine-core @0x8012F968 (src/shared) */


DEFINE_func_8012FB54()  /* dedup: shared engine-core @0x8012FB54 (src/shared) */

DEFINE_func_8012FC30()  /* dedup: shared engine-core @0x8012FC30 (src/shared) */

DEFINE_func_8012FCA4()  /* dedup: shared engine-core @0x8012FCA4 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_8012FCC4);

// @class: other
// @stuck: clean control-flow fn; expecting MATCH from direct structural reconstruction

extern void func_80131E00(struct S80131E00 *a0, s32 a1);
extern void func_8012CBF4(s32 a0);
void func_801319E0(int);
void func_80131C78(int);
void func_80131CA8(int, int);

void func_8012FDA8(int param_1)
{
    int iVar1;
    unsigned int uVar2;

    if ((*(unsigned int *)(param_1 + 0xb4) & 0x100) != 0) {
        iVar1 = *(int *)(param_1 + 0x1c) + 1;
        *(int *)(param_1 + 0x1c) = iVar1;
        if (0x14 < iVar1) {
            ((void (*)(int, int))func_80131E00)(param_1, 0xd);
            return;
        }
        uVar2 = ((int (*)(int))func_8012CBF4)(param_1);
        if ((uVar2 & 0x2000) != 0) {
            if ((uVar2 & 0xff) == 2) {
                ((void (*)(int, int))func_80131E00)(param_1, 0x12);
                return;
            }
            if ((uVar2 & 0xff) == 0x1a) {
                func_801319E0(param_1);
                return;
            }
            func_80131C78(param_1);
        }
    }
    func_80131CA8(param_1, 0x1d);
    return;
}


struct S80131E00;
DEFINE_func_8012FE70()  /* dedup: shared engine-core @0x8012FE70 (src/shared) */

DEFINE_func_8012FF00()  /* dedup: shared engine-core @0x8012FF00 (src/shared) */

DEFINE_func_8012FF4C()  /* dedup: shared engine-core @0x8012FF4C (src/shared) */

DEFINE_func_8012FF98()  /* dedup: shared engine-core @0x8012FF98 (src/shared) */

DEFINE_func_8013001C()  /* dedup: shared engine-core @0x8013001C (src/shared) */

DEFINE_func_80130088()  /* dedup: shared engine-core @0x80130088 (src/shared) */

// @class: schedule
// @stuck: none — MATCH (61 ins); shared-tail done=1 at the post-if/else merge point fills the shared jal's delay slot
#include "common.h"

DEFINE_func_801300F4()  /* dedup: shared engine-core @0x801300F4 (src/shared) */


DEFINE_func_801301E8()  /* dedup: shared engine-core @0x801301E8 (src/shared) */



struct S80131E00;

DEFINE_func_80130278()  /* dedup: shared engine-core @0x80130278 (src/shared) */


DEFINE_func_80130314()  /* dedup: shared engine-core @0x80130314 (src/shared) */

DEFINE_func_80130360()  /* dedup: shared engine-core @0x80130360 (src/shared) */

DEFINE_func_801303A0()  /* dedup: shared engine-core @0x801303A0 (src/shared) */


DEFINE_func_801303EC()  /* dedup: shared engine-core @0x801303EC (src/shared) */

// @class: plumbing
// @stuck: none — MATCH (55 ins, match_one relocation-masked)

DEFINE_func_80130438()  /* dedup: shared engine-core @0x80130438 (src/shared) */


// @class: schedule
// @stuck: none — MATCH
DEFINE_func_80130514()  /* dedup: shared engine-core @0x80130514 (src/shared) */


DEFINE_func_801305CC()  /* dedup: shared engine-core @0x801305CC (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80130650);

DEFINE_func_80130740()  /* dedup: shared engine-core @0x80130740 (src/shared) */

DEFINE_func_801307B0()  /* dedup: shared engine-core @0x801307B0 (src/shared) */

DEFINE_func_80130858()  /* dedup: shared engine-core @0x80130858 (src/shared) */

DEFINE_func_80130898()  /* dedup: shared engine-core @0x80130898 (src/shared) */

DEFINE_func_801308DC()  /* dedup: shared engine-core @0x801308DC (src/shared) */

// @class: plumbing
// @stuck: none — MATCH (41 ins, match_one verified; lh@0x18 / lhu@0x1c, andi 0x8000 on uint field)

DEFINE_func_80130974()  /* dedup: shared engine-core @0x80130974 (src/shared) */


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80130A18);

DEFINE_func_80130AC4()  /* dedup: shared engine-core @0x80130AC4 (src/shared) */

// @class: schedule
// @stuck: none — MATCH (70 ins). Early-returns (not a shared `mode` var) keep $a0 live on the first path; main-block path reloads $a0 from $s0 at the tail, giving the move+nop delay-slot the target uses.

DEFINE_func_80130AF0()  /* dedup: shared engine-core @0x80130AF0 (src/shared) */


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80130C08);

extern void (*D_80186EAC[])(void);

void func_80130D0C(void *a0) {
    D_80186EAC[*(u8 *)((s32)a0 + 0xC1)]();
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80130D48);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80131170);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_801312D0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80131340);


/* Canonical sigs (consistent with src/ov_SC01_077/ov_SC01_077.c + engine_core.h):
 *  - func_80131CA8: canonical 'extern void func_80131CA8(int, int)' (overlay .c L742,
 *    engine_core.h). Its $v0 return IS used here (asm: jal ...; bnez $v0), so cast at the
 *    call site to read it -- the codebase's own idiom (engine_core.h L17026:
 *    ((s32 (*)(int, int))func_80131CA8)(arg0, 0x2C)). Byte-neutral, no sig conflict.
 *  - func_8012C218: canonical 'void func_8012C218(void *a0)' (DEFINE_func_8012C218).
 *  - func_8002A04C: main-EXE callee (src/800.c), undeclared in this TU -> declare locally,
 *    arity 1 (asm: jal func_8002A04C; delay-slot a0=s0). No conflict.
 */
DEFINE_func_801319E0()  /* dedup: shared engine-core @0x801319E0 (src/shared) */


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80131A34);

DEFINE_func_80131AC8()  /* dedup: shared engine-core @0x80131AC8 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80131B14);

DEFINE_func_80131C78()  /* dedup: shared engine-core @0x80131C78 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80131CA8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80131CF4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80131D68);

extern void (*D_80186FEC[])(struct S80131E00 *a0);

void func_80131E00(struct S80131E00 *a0, s32 a1) {
    a0->field_B0 = a1;
    D_80186FEC[a1](a0);
}

DEFINE_func_80131E38()  /* dedup: shared engine-core @0x80131E38 (src/shared) */

struct S80131E00;
DEFINE_func_80131E7C()  /* dedup: shared engine-core @0x80131E7C (src/shared) */

DEFINE_func_80131EE4()  /* dedup: shared engine-core @0x80131EE4 (src/shared) */

extern void (*D_80187044[])(void);

void func_80131EEC(void *a0) {
    D_80187044[*(u16 *)((s32)a0 + 0x2)]();
}

extern void (*D_8018708C[])(void);

void func_80131F28(void *a0) {
    D_8018708C[*(u16 *)((s32)a0 + 0x2)]();
}

extern void (*D_80187094[])(void);

void func_80131F64(s32 *a0) {
    D_80187094[*(u16 *)((s32)a0 + 2)]();
}

extern s32 (*D_8018709C[])();

s32 func_80131FA0(s16 *a0) {
    return D_8018709C[(u16)a0[1]]();
}

extern s32 (*D_801870A4[])();

s32 func_80131FDC(s16 *a0) {
    return D_801870A4[(u16)a0[1]]();
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80132018);

DEFINE_func_801320D0()  /* dedup: shared engine-core @0x801320D0 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_801320D8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80132144);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_801321B0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_8013221C);

// @class: regalloc-order
// @stuck: none — MATCH (97 ins, relocation-masked)
DEFINE_func_80132288()  /* dedup: shared engine-core @0x80132288 (src/shared) */


DEFINE_func_8013240C()  /* dedup: shared engine-core @0x8013240C (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_801325B8);

DEFINE_func_8013277C()  /* dedup: shared engine-core @0x8013277C (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80132784);

DEFINE_func_80132DC4()  /* dedup: shared engine-core @0x80132DC4 (src/shared) */

extern void Square0(s32 *a0, s32 *a1);
extern s16 D_80126CAC;
extern s16 D_80126CB0;

s32 func_80132E6C(s16 *a0) {
    s32 in[3];
    s32 out[3];
    in[0] = a0[3] - D_80126CAC;
    in[1] = 0;
    in[2] = a0[7] - D_80126CB0;
    Square0(in, out);
    return out[0] + out[2];
}

DEFINE_func_80132EC4()  /* dedup: shared engine-core @0x80132EC4 (src/shared) */

DEFINE_func_80132EF4()  /* dedup: shared engine-core @0x80132EF4 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80132F40);

DEFINE_func_80133060()  /* dedup: shared engine-core @0x80133060 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_801330E0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80133298);

// @class: schedule
// @stuck: none — MATCH
DEFINE_func_8013339C()  /* dedup: shared engine-core @0x8013339C (src/shared) */


DEFINE_func_8013361C()  /* dedup: shared engine-core @0x8013361C (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_801336E8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_8013373C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80133784);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80133AB0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80133CD4);

typedef struct { s16 x, y, z; } Vec3s;

s32 func_80134310(Vec3s *a0, Vec3s *a1, s32 a2) {
    return a0->x * a1->x + a0->y * a1->y + a0->z * a1->z + a2;
}

DEFINE_func_8013435C()  /* dedup: shared engine-core @0x8013435C (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_801343C4);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80134510);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_801345F8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_801347A0);

DEFINE_func_80134A28()  /* dedup: shared engine-core @0x80134A28 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80134A74);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80134C20);

DEFINE_func_80134FB8()  /* dedup: shared engine-core @0x80134FB8 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80135004);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80135168);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80135260);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80135480);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80135888);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80135A4C);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80135D20);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80135EB0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80136334);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_801365B8);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80136824);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80136A94);

DEFINE_func_80136BC4()  /* dedup: shared engine-core @0x80136BC4 (src/shared) */

DEFINE_func_80136C1C()  /* dedup: shared engine-core @0x80136C1C (src/shared) */

DEFINE_func_80136C3C()  /* dedup: shared engine-core @0x80136C3C (src/shared) */

DEFINE_func_80136C44()  /* dedup: shared engine-core @0x80136C44 (src/shared) */

DEFINE_func_80136C4C()  /* dedup: shared engine-core @0x80136C4C (src/shared) */

extern unsigned short D_800B99F0;
extern void (*D_801870C8[])(void);

void func_80136C54(void)
{
    D_801870C8[D_800B99F0]();
}

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80136C90);

DEFINE_func_80136D00()  /* dedup: shared engine-core @0x80136D00 (src/shared) */

// @class: regalloc-order
// @stuck: none — MATCH (61 ins). Modeled on byte-proven sibling func_8012D3B4. Key: precompute ((v0+v0_2)>>3)*4 into a separate statement before AddPrim so the D_800B9A02*0x14 array-index chain regallocs to $v1/$v0 (computing the index inline left lhu in $a0 / product in $v1 → 6-off).

DEFINE_func_80136D08()  /* dedup: shared engine-core @0x80136D08 (src/shared) */


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80136DFC);

DEFINE_func_80136EC4()  /* dedup: shared engine-core @0x80136EC4 (src/shared) */

DEFINE_func_80136ECC()  /* dedup: shared engine-core @0x80136ECC (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80136F3C);

// @class: schedule
// @stuck: none — MATCH
DEFINE_func_80137030()  /* dedup: shared engine-core @0x80137030 (src/shared) */


INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80137178);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_801372B0);

DEFINE_func_801375EC()  /* dedup: shared engine-core @0x801375EC (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80137614);

DEFINE_func_8013767C()  /* dedup: shared engine-core @0x8013767C (src/shared) */

DEFINE_func_801376C8()  /* dedup: shared engine-core @0x801376C8 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_801376E8);

DEFINE_func_801377B4()  /* dedup: shared engine-core @0x801377B4 (src/shared) */

DEFINE_func_80137840()  /* dedup: shared engine-core @0x80137840 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_801378F0);

DEFINE_func_801379D8()  /* dedup: shared engine-core @0x801379D8 (src/shared) */

DEFINE_func_801379EC()  /* dedup: shared engine-core @0x801379EC (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_801379FC);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80137B80);

DEFINE_func_80137BD8()  /* dedup: shared engine-core @0x80137BD8 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80137D08);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80137DD4);

DEFINE_func_80137FD8()  /* dedup: shared engine-core @0x80137FD8 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_801380E0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_801387B8);

/* func_80138948: sh 7 @0x4; sb 0 @0x1F; sb 0 @0xD (store order = source order). */
DEFINE_func_80138948()  /* dedup: shared engine-core @0x80138948 (src/shared) */

DEFINE_func_8013895C()  /* dedup: shared engine-core @0x8013895C (src/shared) */

DEFINE_func_80138AB4()  /* dedup: shared engine-core @0x80138AB4 (src/shared) */

DEFINE_func_80138B88()  /* dedup: shared engine-core @0x80138B88 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80138BE0);

DEFINE_func_80138C30()  /* dedup: shared engine-core @0x80138C30 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80138C60);

DEFINE_func_80138D58()  /* dedup: shared engine-core @0x80138D58 (src/shared) */

DEFINE_func_80138DB8()  /* dedup: shared engine-core @0x80138DB8 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80138DE0);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80138ED0);

DEFINE_func_8013914C()  /* dedup: shared engine-core @0x8013914C (src/shared) */

DEFINE_func_801391F0()  /* dedup: shared engine-core @0x801391F0 (src/shared) */

DEFINE_func_80139220()  /* dedup: shared engine-core @0x80139220 (src/shared) */

DEFINE_func_801392C8()  /* dedup: shared engine-core @0x801392C8 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_801392FC);

extern void func_80059888(void *a0, s32 a1, s32 a2, s32 a3);

typedef struct {
    s16 f0;
    s16 f2;
    s16 f4;
    s16 f6;
} Stk801395D4;

void func_801395D4(void * a0)
{
    Stk801395D4 sp10;
    u16 mul;
    u16 base;
    sp10.f0 = *(u16 *)(a0 + 0x38);
    mul = *(u16 *)(a0 + 0x12);
    base = *(u16 *)(a0 + 0x3A);
    sp10.f4 = 0x38;
    sp10.f6 = 0xC;
    sp10.f2 = base + mul * 12;
    func_80059888(&sp10, 0, 0, 0);
}

DEFINE_func_80139634()  /* dedup: shared engine-core @0x80139634 (src/shared) */


DEFINE_func_80139680()  /* dedup: shared engine-core @0x80139680 (src/shared) */


DEFINE_func_80139788()  /* dedup: shared engine-core @0x80139788 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_801397B0);

DEFINE_func_80139914()  /* dedup: shared engine-core @0x80139914 (src/shared) */


DEFINE_func_80139954()  /* dedup: shared engine-core @0x80139954 (src/shared) */

DEFINE_func_801399A8()  /* dedup: shared engine-core @0x801399A8 (src/shared) */


DEFINE_func_801399F0()  /* dedup: shared engine-core @0x801399F0 (src/shared) */

DEFINE_func_80139A34()  /* dedup: shared engine-core @0x80139A34 (src/shared) */

DEFINE_func_80139A44()  /* dedup: shared engine-core @0x80139A44 (src/shared) */

DEFINE_func_80139A68()  /* dedup: shared engine-core @0x80139A68 (src/shared) */

DEFINE_func_80139A8C()  /* dedup: shared engine-core @0x80139A8C (src/shared) */

DEFINE_func_80139B18()  /* dedup: shared engine-core @0x80139B18 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_80139BE0);

DEFINE_func_80139C7C()  /* dedup: shared engine-core @0x80139C7C (src/shared) */


DEFINE_func_80139D04()  /* dedup: shared engine-core @0x80139D04 (src/shared) */


DEFINE_func_80139DC8()  /* dedup: shared engine-core @0x80139DC8 (src/shared) */

DEFINE_func_80139DEC()  /* dedup: shared engine-core @0x80139DEC (src/shared) */

DEFINE_func_80139DF4()  /* dedup: shared engine-core @0x80139DF4 (src/shared) */

DEFINE_func_80139E84()  /* dedup: shared engine-core @0x80139E84 (src/shared) */

DEFINE_func_80139F0C()  /* dedup: shared engine-core @0x80139F0C (src/shared) */

DEFINE_func_80139FBC()  /* dedup: shared engine-core @0x80139FBC (src/shared) */

DEFINE_func_80139FE8()  /* dedup: shared engine-core @0x80139FE8 (src/shared) */

DEFINE_func_8013A0A4()  /* dedup: shared engine-core @0x8013A0A4 (src/shared) */

DEFINE_func_8013A164()  /* dedup: shared engine-core @0x8013A164 (src/shared) */

DEFINE_func_8013A1E8()  /* dedup: shared engine-core @0x8013A1E8 (src/shared) */

DEFINE_func_8013A250()  /* dedup: shared engine-core @0x8013A250 (src/shared) */

// @class: regalloc-order
// @stuck: none — MATCH; p=&D_80127524 pointer idiom + memory barrier forces *p reload for call arg
DEFINE_func_8013A2BC()  /* dedup: shared engine-core @0x8013A2BC (src/shared) */


DEFINE_func_8013A378()  /* dedup: shared engine-core @0x8013A378 (src/shared) */


struct S8013A4C4;

DEFINE_func_8013A380()  /* dedup: shared engine-core @0x8013A380 (src/shared) */


DEFINE_func_8013A448()  /* dedup: shared engine-core @0x8013A448 (src/shared) */

DEFINE_func_8013A4C4()  /* dedup: shared engine-core @0x8013A4C4 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_8013A530);

DEFINE_func_8013A860()  /* dedup: shared engine-core @0x8013A860 (src/shared) */

DEFINE_func_8013A8B0()  /* dedup: shared engine-core @0x8013A8B0 (src/shared) */

DEFINE_func_8013A8BC()  /* dedup: shared engine-core @0x8013A8BC (src/shared) */


DEFINE_func_8013A8FC()  /* dedup: shared engine-core @0x8013A8FC (src/shared) */


DEFINE_func_8013A9B4()  /* dedup: shared engine-core @0x8013A9B4 (src/shared) */

DEFINE_func_8013A9F8()  /* dedup: shared engine-core @0x8013A9F8 (src/shared) */

DEFINE_func_8013AA24()  /* dedup: shared engine-core @0x8013AA24 (src/shared) */

DEFINE_func_8013AB54()  /* dedup: shared engine-core @0x8013AB54 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_8013AD38);

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_8013AF20);

DEFINE_func_8013B204()  /* dedup: shared engine-core @0x8013B204 (src/shared) */

INCLUDE_ASM("asm/ov_SC01_077/nonmatchings/ov_SC01_077_a", func_8013B274);

/* func_8013B568..func_8013C964 (16 contiguous fns) moved to ov_SC01_077_o0.c — built -O0 (Phase-19 T1). */
