#include "common.h"
#include "../shared/engine_core.h"


/* ==== Phase-26 §8b carried decl layer (jr_isolate_all.py) ===================
 * The file-scope decl environment from earlier code regions of this object —
 * file-local types, col-0 decls, DEFINE_func macro externs, and each earlier
 * definition's implied prototype (types first, then decls in original order).
 * Decls emit no code => byte-neutral. See cookbook §8c. */
   /* 12-byte sub-table record (stride 0xC) */
 /* 0x20 bytes */
DEFINE_func_8016AB6C()  /* dedup: shared engine-core @0x8016AB6C (src/shared) */



DEFINE_func_8016AE5C()  /* dedup: shared engine-core @0x8016AE5C (src/shared) */

DEFINE_func_8016AFB0()  /* dedup: shared engine-core @0x8016AFB0 (src/shared) */

DEFINE_func_8016B114()  /* dedup: shared engine-core @0x8016B114 (src/shared) */



DEFINE_func_8016B234()  /* dedup: shared engine-core @0x8016B234 (src/shared) */


DEFINE_func_8016B3F4()  /* dedup: shared engine-core @0x8016B3F4 (src/shared) */

DEFINE_func_8016B428()  /* dedup: shared engine-core @0x8016B428 (src/shared) */

DEFINE_func_8016B448()  /* dedup: shared engine-core @0x8016B448 (src/shared) */


DEFINE_func_8016B4BC()  /* dedup: shared engine-core @0x8016B4BC (src/shared) */



// @class: struct
// @stuck: none — MATCH

extern void func_80015978(s32 a0, s32 *a1);
extern int func_8016B9F8(int);
extern int func_8016B834(int, int);
extern void func_8016B984(void *a0);
extern void func_8016B91C(int);
extern int D_801E9B08;

void func_8016B4F8(int param_1)
{
    int iVar1;
    int uVar2;
    volatile int buf[2];

    ((void (*)(int, void *))func_80015978)(param_1 + 4, &D_801E9B08);
    if (func_8016B9F8(param_1) == 0) {
        *(int *)(param_1 + 0x18) = 0;
        *(int *)(param_1 + 0x14) = 0;
        *(int *)(param_1 + 0x10) = 0;
        iVar1 = func_8016B834(param_1, 0);
        *(int *)(param_1 + 0x10) = iVar1;
        if (iVar1 != 0) {
            iVar1 = func_8016B834(param_1, 1);
            *(int *)(param_1 + 0x14) = iVar1;
            if (iVar1 != 0) {
                iVar1 = func_8016B834(param_1, 2);
                *(int *)(param_1 + 0x18) = iVar1;
                if (iVar1 != 0) goto success;
            }
        }
    }
    ((void (*)(int))func_8016B984)(param_1);
    return;
success:
    func_8016B91C(param_1);
    uVar2 = *(int *)(param_1 + 0x2c);
    if (uVar2 == 0) {
        uVar2 = 0xf0;
    } else {
        uVar2 = 0x2d0;
    }
    *(int *)(param_1 + 0x1c) = uVar2;
    uVar2 = *(unsigned short *)(param_1 + 2);
    uVar2 = uVar2 + 1;
    *(unsigned short *)(param_1 + 2) = uVar2;
}



// @class: schedule
// @stuck: none — MATCH


extern s32 func_8016B9F8(s32 param_1);
extern void func_8016B984(void *a0);
extern void func_8016B6BC(s32, s32, s32, s32);
extern void func_8016B91C(s32);

extern s16 D_8018E748[];

void func_8016B5C0(s32 param_1) {
    s32 iVar4;
    s32 iVar2;
    s32 iVar5;
    s16 sVar1;
    s16 *psVar5;
    s32 i;

    iVar4 = *(s32 *)(param_1 + 0x18);
    if (((s32 (*)(void))func_8016B9F8)() != 0) {
        goto L984;
    }
    sVar1 = *(s16 *)(iVar4 + 0x1a) + 0x200;
    *(s16 *)(iVar4 + 0x1a) = sVar1;
    *(s16 *)(iVar4 + 0x18) = sVar1;
    if (*(s32 *)(param_1 + 0x2c) == 0) {
        iVar2 = *(s32 *)(param_1 + 0x1c);
    } else {
        iVar2 = *(s32 *)(param_1 + 0x1c) / 3;
    }
    iVar5 = *(s32 *)(param_1 + 0x1c) + -0x20;
    *(s32 *)(param_1 + 0x1c) = iVar5;
    if (iVar5 >= 0) {
        goto LOOP;
    }
L984:
    ((void (*)(s32))func_8016B984)(param_1);
    return;
LOOP:
    i = 0;
    psVar5 = D_8018E748;
    do {
        func_8016B6BC(param_1, iVar2, (s32)*psVar5, (s32)(s16)i);
        psVar5 = psVar5 + 1;
        i = i + 1;
    } while (i < 6);
    func_8016B91C(param_1);
    return;
}



// @class: schedule
// @stuck: none — MATCH (94/94 ins, match_one relocation-masked)
//
// Exemplar of the 138-member h_seq family. The whole crack was ONE statement-order
// lever in the tail: the target's post-func_80015978 fix-up runs
//   v[2].x += off.x;  v[2].y += off.y;  v[0].c = 3;
// (the `c = 3` store LAST). Writing `c = 3` between the two v[2] RMWs — the order the
// Ghidra-C literally prints, and what every prior draft copied — costs 12 mismatches:
// gcc hoists the `li 3` into the load-delay window, which pushes v[2].x into $v1 and
// the off.x temp into $a0, and then the `addu $a0,$s1,$zero` arg copy can no longer be
// scheduled early enough to become the base register of the v[2]/v[0].c stores.
// With `c = 3` last, the arg copy births at the v[2].x/v[2].y boundary (idx 76) exactly
// as the target does, and the mixed $s1-load / $a0-store addressing falls out for free.
// (§67-adjacent: the copy PLACEMENT was the root cause — but here plain statement order
// reaches it, no `__asm__` launder and no register pin needed. Prior notes calling this a
// regalloc tie-break and pinning $a0 were chasing the consequence, not the cause.)
//
// Everything else follows the Ghidra-C: `Prim *p = &prim` (one alias only — a second
// pointer name splits the pseudo and breaks the $s1 base), the `q++` post-increment
// running pointer over the 8-byte table rows, and the ((param_4 << 16) >> 14) byte-offset
// index into D_8018E730 (sll 16 / sra 14).


             /* 0x28 */


               /* the 8-byte D_8018E730[] row */

DEFINE_func_8016B6BC()  /* dedup: shared engine-core @0x8016B6BC (src/shared) */



// @class: schedule
// @stuck: none — MATCH (statement order: compute puVar2 base before puVar3 table lookup so param*0x40+base schedule into prologue, leaving the 0x2c load-delay nop)
extern void func_801465C0(void);
extern void func_8001CD9C(int, void *);
extern void func_800233CC(void *, unsigned short);

extern int *D_8018E78C[];
extern unsigned short D_8018E794[];
extern unsigned short D_8018E79C[];
extern unsigned char D_801E9B10[];

int func_8016B834(int param_1, int param_2) {
    int *puVar3;
    int *puVar2;
    int iVar1;

    puVar2 = (int *)(D_801E9B10 + param_2 * 0x40);
    puVar3 = D_8018E78C[*(int *)(param_1 + 0x2c)];
    iVar1 = ((int (*)(void))func_801465C0)();
    if (iVar1 != 0) {
        func_8001CD9C(iVar1, puVar2);
        func_800233CC(puVar2, D_8018E794[param_2]);
        puVar2[0] = *(int *)((int)puVar3 + param_2 * 8);
        puVar2[1] = *(int *)((int)puVar3 + param_2 * 8 + 4);
        *(unsigned int *)(iVar1 + 4) = *(unsigned int *)(iVar1 + 4) | 0x50040000;
        *(short *)(iVar1 + 0x1e) = D_8018E79C[param_2];
    }
    return iVar1;
}


DEFINE_func_8016B91C()  /* dedup: shared engine-core @0x8016B91C (src/shared) */

DEFINE_func_8016B964()  /* dedup: shared engine-core @0x8016B964 (src/shared) */

DEFINE_func_8016B984()  /* dedup: shared engine-core @0x8016B984 (src/shared) */


// @class: regalloc-order
// @stuck: none — MATCH (result is func_8012EFB8's return saved in $s0 across the func_80015954 call; the save-move fills the 2nd call's delay slot. func_80015954's return is discarded.)


extern s32 D_801E9B08;
extern void func_8012EFB8(s32 a0);
extern void func_80015954(s32 a0, s32 a1);

s32 func_8016B9F8(s32 param_1)
{
    s32 buf[2];
    u32 v;

    v = ((u32 (*)(s32 *, s32 *))func_8012EFB8)(&D_801E9B08, buf);
    ((void (*)(s32 *, s32 *))func_80015954)(buf, (s32 *)(param_1 + 4));
    return (v & 0xffffefff) != 0;
}


DEFINE_func_8016BA48()  /* dedup: shared engine-core @0x8016BA48 (src/shared) */

DEFINE_func_8016BA68()  /* dedup: shared engine-core @0x8016ba68 (src/shared) */


DEFINE_func_8016BADC()  /* dedup: shared engine-core @0x8016BADC (src/shared) */


DEFINE_func_8016BBA4()  /* dedup: shared engine-core @0x8016BBA4 (src/shared) */


// @class: plumbing
// @stuck: none — MATCH (56 ins, match_one relocation-masked)




s32 func_8016BBE0(s32 param_1) {
    extern void func_8016BF34(void *a0);
    extern void func_8016BF50(s32);
    extern void func_8001CF00(s32);
    extern M2C_UNK D_801E9C44;
    extern u8 D_801E9C45;
    extern u8 D_801E9C46;
    extern M2C_UNK D_801E9C48;
    extern u8 D_801E9C49;
    extern u8 D_801E9C4A;

    int iVar1;
    int temp;

    iVar1 = ((s32 (*)(void))func_801465C0)();
    *(int *)(((int)param_1) + 0x20) = iVar1;
    if (iVar1 != 0) {
        ((void (*)(s32))func_8016BF34)(((int)param_1));
        func_8016BF50(((int)param_1));
        func_8001CF00(iVar1);
        *(s16 *)(iVar1 + 0x10) = 0;
        temp = *(int *)(((int)param_1) + 0x2c);
        *(s16 *)(iVar1 + 0x14) = 0;
        *(s16 *)(iVar1 + 0x1a) = 0;
        *(s16 *)(iVar1 + 0x18) = 0;
        *(s16 *)(iVar1 + 0x12) = temp * 0x555;
        *(s16 *)(((int)param_1) + 0x10) = 0;
        *(s16 *)(((int)param_1) + 0x14) = 0;
        (*(u8 *)&D_801E9C44) = 0x20;
        D_801E9C45 = 0x20;
        D_801E9C46 = 0;
        (*(u8 *)&D_801E9C48) = 0xc0;
        D_801E9C49 = 0xc0;
        D_801E9C4A = 0;
        *(u16 *)(((int)param_1) + 2) += 1;
    } else {
        ((void (*)(s32))func_80146C3C)(((int)param_1));
    }
}



extern void func_8016BFA8(s32 a0, s32 a1, s32 a2, s32 a3);
extern M2C_UNK D_801E9C44;
extern M2C_UNK D_801E9C48;

void func_8016BCC0(void *arg0) {
    u16 temp_a2;
    u16 temp_v0;
    void *temp_s0;

    temp_s0 = M2C_FIELD(arg0, void **, 0x20);
    func_8016BF50();
    temp_a2 = M2C_FIELD(arg0, u16 *, 0x10) + 0x60;
    M2C_FIELD(arg0, u16 *, 0x10) = temp_a2;
    temp_v0 = M2C_FIELD(temp_s0, u16 *, 0x1A) + temp_a2;
    M2C_FIELD(temp_s0, u16 *, 0x1A) = temp_v0;
    M2C_FIELD(temp_s0, u16 *, 0x18) = temp_v0;
    M2C_FIELD(temp_s0, u16 *, 0x12) = (u16) ((M2C_FIELD(temp_s0, u16 *, 0x12) + 0x71) & 0xFFF);
    func_8016BFA8(arg0, &D_801E9C44, &D_801E9C48, temp_s0 + 0x18);
    if ((s16) M2C_FIELD(temp_s0, u16 *, 0x1A) >= 0x1001) {
        M2C_FIELD(temp_s0, u16 *, 0x18) = 0x1000U;
        M2C_FIELD(temp_s0, u16 *, 0x1A) = 0x1000U;
        func_80146E90(arg0, M2C_FIELD(arg0, s32 *, 0x30));
        M2C_FIELD(arg0, u16 *, 2) = (u16) (M2C_FIELD(arg0, u16 *, 2) + 1);
    }
}


// @class: struct
// @stuck: none — MATCH (74 ins, relocation-masked)




s32 func_8016BD78(s32 param_1)
{
    extern void func_8016BF50(void);
    extern u8 D_801E9C45;
    extern u8 D_801E9C46;
    extern u8 D_801E9C49;
    extern u8 D_801E9C4A;

    s32 iVar2;
    u16 uVar1;
    u8 *p1;
    u8 *p2;

    iVar2 = *(s32 *)(param_1 + 0x20);
    func_8016BF50();

    p1 = &(*(u8 *)&D_801E9C44);
    if (*p1 != 0) *p1 -= 4;
    if (D_801E9C45 != 0) D_801E9C45 -= 4;
    if (D_801E9C46 != 0) D_801E9C46 -= 4;
    p2 = &(*(u8 *)&D_801E9C48);
    if (*p2 != 0) *p2 -= 4;
    if (D_801E9C49 != 0) D_801E9C49 -= 4;
    if (D_801E9C4A != 0) D_801E9C4A -= 4;

    uVar1 = *(u16 *)(iVar2 + 0x18) - 0x80;
    *(u16 *)(iVar2 + 0x18) = uVar1;
    if ((s32)((unsigned int)uVar1 << 0x10) < 0) {
        *(u16 *)(iVar2 + 0x18) = 0;
        *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
    }
    *(u16 *)(iVar2 + 0x12) = (*(u16 *)(iVar2 + 0x12) + 0x22) & 0xfff;

    ((void (*)(s32, u8 *, u8 *, s32))func_8016BFA8)(param_1, p1, p2, iVar2 + 0x18);
}



// @class: plumbing
// @stuck: none — MATCH

s32 func_8016BEA0(s32 param_1)
{
    extern void func_8016BF50(void);

    int iVar2;
    unsigned short uVar1;

    iVar2 = *(int *)(((int)param_1) + 0x20);
    func_8016BF50();
    uVar1 = *(unsigned short *)(((int)param_1) + 0x10) - 0x18;
    *(unsigned short *)(((int)param_1) + 0x10) = uVar1;
    *(unsigned short *)(iVar2 + 0x1a) = *(unsigned short *)(iVar2 + 0x1a) + uVar1;
    *(unsigned short *)(iVar2 + 0x12) = (*(unsigned short *)(iVar2 + 0x12) + 0x22) & 0xfff;
    ((void (*)(int, void *, void *, int))func_8016BFA8)(((int)param_1), &(*(int *)&D_801E9C44), &(*(int *)&D_801E9C48), iVar2 + 0x18);
    if (*(short *)(iVar2 + 0x1a) < 0) {
        ((void (*)(int))func_80146C3C)(((int)param_1));
    }
}



DEFINE_func_8016BF34()  /* dedup: shared engine-core @0x8016BF34 (src/shared) */


/* §71 sibling-first: this is the head of the already-matched func_8016C2C4
 * (src/ov_SC03_099/ov_SC03_099_jr_8016AB6C.c L2707) lifted into its own leaf. */

DEFINE_func_8016BF50()  /* dedup: shared engine-core @0x8016BF50 (src/shared) */



DEFINE_func_8016BFA8()  /* dedup: shared engine-core @0x8016BFA8 (src/shared) */


// @class: struct
// @stuck: none — MATCH (95 ins). Keys: (1) 4-byte unaligned copies via `struct{char b[4];}`
//   assignment -> lwl/lwr/swl/swr with reload; (2) 0x40-byte stack buffer `buf` (Mtx_8016BFD0 padded to
//   0x40, not 0x20) sets the frame to 0x70 and lands v1/v2 at sp+0x50/0x58; (3) func_80017714(a4)
//   takes param_5 as an arg -> gcc materializes `addu $a0,$s0,$zero` and stores the 4 zeros via $a0.




void func_8016BFD0(s32 a0, s32 a1, s32 a2, s32 a3, void *a4) {
    extern void func_80017714();
    extern s32 D_8018E7B4;
    extern s32 D_8018E7BC;
    extern s32 D_8018E7C4;
    extern s32 D_8018E7CC;

    Mtx_8016BFD0 buf;
    Vec3_8016BFD0 v1;
    Vec3_8016BFD0 v2;
    s32 iVar5 = *(s32 *)(a0 + 0x20);

    *(u32 *)((s32)a4 + 0x30) = 0x50000000;
    *(W_8016BFD0 *)((s32)a4 + 0x20) = *(W_8016BFD0 *)a1;
    *(W_8016BFD0 *)((s32)a4 + 0x24) = *(W_8016BFD0 *)a1;
    *(W_8016BFD0 *)((s32)a4 + 0x28) = *(W_8016BFD0 *)a2;
    *(W_8016BFD0 *)((s32)a4 + 0x2c) = *(W_8016BFD0 *)a2;

    v1.x = *(u16 *)(a0 + 6);
    v1.y = *(u16 *)(a0 + 0xa);
    v1.z = *(u16 *)(a0 + 0xe);
    ((void(*)())func_8012EFB8)(&v1, &v1);
    ((void(*)())func_80013F3C)(&buf);
    ((void(*)())func_800123F0)(&buf, (s32)*(s16 *)(iVar5 + 0x12));

    v2.x = *(u16 *)(a3 + 0);
    v2.y = *(u16 *)(a3 + 2);
    v2.z = *(u16 *)(a3 + 4);
    ((void(*)())func_80020F34)(&buf, &v2);

    buf.t[0] = v1.x;
    buf.t[1] = v1.y;
    buf.t[2] = v1.z;
    ((void(*)())func_8012F14C)(&buf, &D_8018E7B4, (s32)a4);
    ((void(*)())func_8012F14C)(&buf, &D_8018E7BC, (s32)a4 + 8);
    ((void(*)())func_8012F14C)(&buf, &D_8018E7C4, (s32)a4 + 0x10);
    ((void(*)())func_8012F14C)(&buf, &D_8018E7CC, (s32)a4 + 0x18);

    *(s16 *)((s32)a4 + 4) = 0;
    *(s16 *)((s32)a4 + 0xc) = 0;
    *(s16 *)((s32)a4 + 0x14) = 0;
    *(s16 *)((s32)a4 + 0x1c) = 0;
    func_80017714(a4);
}




DEFINE_func_8016C14C()  /* dedup: shared engine-core @0x8016C14C (src/shared) */


extern void func_801465C0(void);
extern void func_80149350(s32 arg0);

void func_8016C188(s32 param)
{
    register s32 s1 __asm__("$17");
    register s32 s2 __asm__("$18");
    register u8 *s0 __asm__("$16");
    u16 buf[3];
    s16 *pBCC;
    s16 *pBD4;
    s32 t34;

    extern void func_80015954(s32, s32);
    extern s32 func_8016C374(s32, s32, s32, s32);
    extern void func_80146C3C(void);
    extern void func_8001CD9C(s32, void *);
    extern void func_800233CC(void *, unsigned short);
    extern u8 D_801E9C04[];
    extern s16 D_801E9C4C;
    extern s16 D_801E9C4E;
    extern s16 D_801E9C50;
    extern s16 D_801E9C54;
    extern s16 D_801E9C56;
    extern s16 D_801E9C58;

    s1 = param;
    s2 = ((s32 (*)(void))func_801465C0)();
    *(s32 *)(s1 + 0x20) = s2;
    if (s2 != 0) {
        *(u16 *)(s1 + 0x12) = *(u16 *)(s1 + 0x6);
        *(u16 *)(s1 + 0x16) = *(u16 *)(s1 + 0xA);
        *(u16 *)(s1 + 0x1A) = *(u16 *)(s1 + 0xE);
        t34 = *(s32 *)(s1 + 0x34);
        buf[0] = *(u16 *)(s1 + 0x12);
        buf[1] = *(u16 *)(s1 + 0x16);
        buf[2] = *(u16 *)(s1 + 0x1A);
        ((void (*)(s32, void *, void *))func_80149350)(t34, buf, buf);
        ((void (*)(void *, s32))func_80015954)(buf, s1 + 4);
        s0 = D_801E9C04;
        ((void (*)(s32, void *))func_8001CD9C)(s2, s0);
        *(s16 *)(s2 + 0x1E) = 0xCCC;
        *(s32 *)(s2 + 4) = *(s32 *)(s2 + 4) | 0x50000000;
        ((void (*)(void *, s32))func_800233CC)(s0, 0x80);
        *(s16 *)(s2 + 0x1A) = 0;
        *(s16 *)(s2 + 0x18) = 0;
        *(s16 *)(s1 + 0x10) = 0;
        pBCC = &D_801E9C4C;
        pBD4 = &D_801E9C54;
        *pBCC = 0x20;
        D_801E9C4E = 0x20;
        D_801E9C50 = 0;
        *pBD4 = 0xC0;
        D_801E9C56 = 0xC0;
        D_801E9C58 = 0;
        ((s32 (*)(s32, void *, void *, void *))func_8016C374)(s1, pBCC, pBD4, s0);
        *(u16 *)(s1 + 2) = *(u16 *)(s1 + 2) + 1;
    } else {
        ((void (*)(s32))func_80146C3C)(s1);
    }
}



// @class: schedule
// @stuck: none — MATCH (44 ins; pins $s0/$s1 + hoist call-arg into a temp so its load fills the buf-store delay slot)


extern void func_80149350(s32 arg0);
extern void func_80015954(s32 a0, s32 a1);
extern s32 func_8016C374(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80146C3C(void);

extern u8 D_801E9C4C[];
extern u8 D_801E9C54[];
extern u8 D_801E9C04[];

void func_8016C2C4(s32 param)
{
    register s32 s1 __asm__("$17");
    register s32 s0 __asm__("$16");
    u16 buf[3];
    s16 v;
    s32 r;
    s32 arg;

    s1 = param;
    s0 = *(s32 *)(s1 + 0x20);
    arg = *(s32 *)(s1 + 0x34);
    buf[0] = *(u16 *)(s1 + 0x12);
    buf[1] = *(u16 *)(s1 + 0x16);
    buf[2] = *(u16 *)(s1 + 0x1a);
    ((void (*)(s32, void *, void *))func_80149350)(arg, buf, buf);
    ((void (*)(void *, s32))func_80015954)(buf, s1 + 4);
    v = *(s16 *)(s1 + 0x10) + 0x10;
    *(s16 *)(s1 + 0x10) = v;
    v = *(s16 *)(s0 + 0x1a) + v;
    *(s16 *)(s0 + 0x1a) = v;
    *(s16 *)(s0 + 0x18) = v;
    r = ((s32 (*)(s32, void *, void *, void *))func_8016C374)(s1, D_801E9C4C, D_801E9C54, D_801E9C04);
    if (r == 0) {
        ((void (*)(s32))func_80146C3C)(s1);
    }
}


DEFINE_func_8016C374()  /* dedup: shared engine-core @0x8016C374 (src/shared) */

// @class: regalloc-order
// @stuck: none — MATCH (172/172, relocation-masked)



s32 func_8016C49C(s32 param_1_arg) {
    extern s32 VectorNormalSS(void *, void *);
    extern void func_8001CD9C(s32, void *);
    extern void func_8016CF04(s32, s32);
    extern u8 D_801E9C60[];
    extern u8 D_801E9D20;

    register u16 *param_1 __asm__("$17") = ((u16 *)param_1_arg);
    int iVar5;
    int iVar6;
    u16 sv[4];
    s32 mat[8];
    short sVar1;

    iVar5 = *(int *)(param_1 + 0x18);
    iVar6 = *(int *)(param_1 + 0x1a);
    param_1[0x14] = *(u16 *)(iVar5 + 0x36);
    if ((*(u32 *)(param_1 + 0x16) & 0x8000) == 0) {
        short iVar4 = 0;
        u16 *psVar3 = (u16 *)&D_8011D030;
        do {
            if (psVar3 != param_1 && *psVar3 == 0x30) {
                ((void(*)(void *))func_80146C3C)(psVar3);
            }
            iVar4 = iVar4 + 1;
            psVar3 = psVar3 + 0x2c;
        } while (iVar4 < 0x1e);
        D_801E9C60[1] = 0xff;
        D_801E9C60[2] = 0x10;
        D_801E9C60[0] = 0x10;
        D_801E9C60[6] = 0;
        D_801E9C60[5] = 0;
        D_801E9C60[4] = 0;
        ((void(*)(void *, s32))func_800233CC)(D_801E9C60, 10);
        sv[0] = *(u16 *)(iVar5 + 6) - *(u16 *)(iVar6 + 6);
        {
            int t = *(u16 *)(iVar6 + 0xa) + 0x28;
            sv[1] = *(u16 *)(iVar5 + 0xa) - t;
        }
        sv[2] = *(u16 *)(iVar5 + 0xe) - *(u16 *)(iVar6 + 0xe);
        VectorNormalSS(sv, sv);
        param_1[3] = *(u16 *)(iVar5 + 6) + ((s16)sv[0] >> 9);
        param_1[5] = *(u16 *)(iVar5 + 0xa) + (((s16)sv[1] >> 9) - 0x28);
        param_1[7] = *(u16 *)(iVar5 + 0xe) + ((s16)sv[2] >> 9);
        ((void(*)(void *))func_800D23D0)(sv);
        sv[0] = 0;
        ((void(*)(void *, void *))RotMatrixYXZ)(sv, param_1 + 0x1c);
        ((void(*)(void *, s32))func_80016714)(&D_801E9D20, 0x620);
        ((s32(*)(s32, void *, s32, s32, s32, s32, s32))func_80146A6C)(0x32, param_1, 0, 0, 0, 0, *(int *)(param_1 + 0x18));
        sVar1 = 5;
    } else {
        int iVar5b = ((s32(*)())func_801465C0)();
        u32 uVar2;
        if (iVar5b == 0) {
            return;
        }
        func_8001CD9C(iVar5b, D_801E9C60);
        *(u32 *)(iVar5b + 4) |= 0x50000000;
        uVar2 = ((int(*)())rand)();
        sv[0] = (uVar2 & 0x7f) * 8 - 0x80;
        sv[1] = ((uVar2 & 0x7f00) >> 4) - 0x400;
        sv[2] = 0;
        ((void(*)(void *, void *))RotMatrixYXZ)(sv, mat);
        ((void(*)(void *, void *))func_80048EAC)(param_1 + 0x1c, mat);
        sv[1] = 0;
        sv[0] = 0;
        sv[2] = 0xb;
        ((void(*)(void *, void *, void *))ApplyMatrixSV)(mat, sv, sv);
        param_1[9] = sv[0];
        param_1[0xb] = sv[1];
        param_1[0xd] = sv[2];
        *(int *)(param_1 + 0x10) = iVar5b;
        *(int *)(param_1 + 0xe) = 8;
        func_8016CF04((s32)param_1, 0);
        *(int *)(param_1 + 0x16) = 0;
        sVar1 = param_1[1] + 1;
    }
    param_1[1] = sVar1;
}



DEFINE_func_8016C74C()  /* dedup: shared engine-core @0x8016C74C (src/shared) */

DEFINE_func_8016C83C()  /* dedup: shared engine-core @0x8016C83C (src/shared) */


DEFINE_func_8016C998()  /* dedup: shared engine-core @0x8016C998 (src/shared) */



DEFINE_func_8016CB84()  /* dedup: shared engine-core @0x8016CB84 (src/shared) */



DEFINE_func_8016CBC0()  /* dedup: shared engine-core @0x8016CBC0 (src/shared) */


/* func_8016CF04 returns short (case 2: 1 if the decremented f2 hit 0, else 0; all other
 * paths return 0 via the addu $v0,$zero,$zero at 0x8016D154). The TU/engine_core.h declare
 * it `void` in 4 DEFINE_ macros + one block-scope decl in func_8016C49C; the real apply is the
 * byte-neutral engine_core.h void->short flip (every caller discards or ptr-casts the return,
 * cf. func_8016D5EC's `(s16)(...)` cast). The //@EDIT lines above are the rtu_match proxy for
 * that flip. Body verified 166/166 in isolation AND in a whole-TU compile w/ the reconciled hdr. */
                /* 4 + 16*12 = 0xC4 stride */

DEFINE_func_8016CF04()  /* dedup: shared engine-core @0x8016CF04 (src/shared) */




DEFINE_func_8016D19C()  /* dedup: shared engine-core @0x8016D19C (src/shared) */







   /* 8 bytes */
                 /* 32 bytes */


DEFINE_func_8016D1D8()  /* dedup: shared engine-core @0x8016D1D8 (src/shared) */



DEFINE_func_8016D428()  /* dedup: shared engine-core @0x8016D428 (src/shared) */


DEFINE_func_8016D464()  /* dedup: shared engine-core @0x8016D464 (src/shared) */

DEFINE_func_8016D4DC()  /* dedup: shared engine-core @0x8016D4DC (src/shared) */

DEFINE_func_8016D5EC()  /* dedup: shared engine-core @0x8016D5EC (src/shared) */

DEFINE_func_8016D64C()  /* dedup: shared engine-core @0x8016D64C (src/shared) */


extern void func_801465C0(void);
extern void func_800233CC(void*, unsigned short);
extern void func_8001CD9C(int, void *);

void func_8016D688(int param_1)
{

    extern unsigned char D_801E9CA0[];
    int iVar2;
    int iVar3;

    D_801E9CA0[1] = 0xe0;
    D_801E9CA0[2] = 0xe0;
    D_801E9CA0[0] = 0xe0;
    D_801E9CA0[6] = 0;
    D_801E9CA0[5] = 0;
    D_801E9CA0[4] = 0;
    iVar2 = ((int (*)(void))func_801465C0)();
    if (iVar2 != 0) {
        *(int *)(param_1 + 0x20) = iVar2;
        ((void (*)(void *, int))func_800233CC)(D_801E9CA0, 0x28);
        func_8001CD9C(iVar2, D_801E9CA0);
        *(unsigned short *)(iVar2 + 0x1a) = 0x1400;
        *(unsigned int *)(iVar2 + 4) = *(unsigned int *)(iVar2 + 4) | 0x50000000;
        iVar3 = *(int *)(param_1 + 0x30);
        *(unsigned short *)(param_1 + 0x28) = *(unsigned short *)(iVar3 + 0x36);
        *(unsigned short *)(param_1 + 0x12) = *(unsigned short *)(iVar3 + 6);
        *(short *)(param_1 + 0x16) = *(unsigned short *)(iVar3 + 0xa) - 0x28;
        *(unsigned short *)(param_1 + 0x1a) = *(unsigned short *)(iVar3 + 0xe);
        *(short *)(param_1 + 2) = *(short *)(param_1 + 2) + 1;
    }
    return;
}


DEFINE_func_8016D778()  /* dedup: shared engine-core @0x8016D778 (src/shared) */

DEFINE_func_8016D848()  /* dedup: shared engine-core @0x8016D848 (src/shared) */

DEFINE_func_8016D984()  /* dedup: shared engine-core @0x8016D984 (src/shared) */

DEFINE_func_8016DA04()  /* dedup: shared engine-core @0x8016DA04 (src/shared) */


// @class: struct
// @stuck: none — MATCH expected; param_1 survives jal in $s0, table fp-call with %lo-fold
extern void func_8016DBD8(u8 *a0);
extern void (*D_8018E868[])(int);

void func_8016DA30(int param_1)
{
    ((void (*)(void))func_8016DBD8)();
    D_8018E868[*(unsigned short *)(param_1 + 2)](param_1);
}




// @class: plumbing
// @stuck: none — MATCH (clean if/else, one call-crossing local; bnez polarity = if(iVar1==0) fall-through)

extern void func_801465C0(void);
extern void func_80146C3C(void);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);

extern u8 D_8018E80C;
extern u8 D_8018E818;

void func_8016DA7C(s32 param_1)
{
    s32 iVar1;

    iVar1 = ((s32 (*)(void))func_801465C0)();
    if (iVar1 == 0) {
        ((void (*)(s32))func_80146C3C)(param_1);
    } else {
        *(s32 *)(param_1 + 0x20) = iVar1;
        ((void (*)(s32, s32, s32, s32))func_8001CC3C)(iVar1, (s32)&D_8018E80C, 0x250, 0x100);
        *(u8 *)(iVar1 + 0x27) = 0x90;
        *(u16 *)(iVar1 + 0x18) = 0x3000;
        *(u16 *)(iVar1 + 0x1a) = 0x4000;
        *(u32 *)(iVar1 + 4) = *(u32 *)(iVar1 + 4) | 0x50000000;
        func_80128EA8(iVar1, param_1 + 0x24, (s32)&D_8018E818);
        *(s32 *)(param_1 + 0x10) = 0;
        *(s32 *)(param_1 + 0x14) = 0xfff40000;
        *(s16 *)(param_1 + 2) = *(s16 *)(param_1 + 2) + 1;
    }
}


DEFINE_func_8016DB34()  /* dedup: shared engine-core @0x8016DB34 (src/shared) */

DEFINE_func_8016DBD8()  /* dedup: shared engine-core @0x8016DBD8 (src/shared) */


DEFINE_func_8016DC20()  /* dedup: shared engine-core @0x8016DC20 (src/shared) */



DEFINE_func_8016DEA4()  /* dedup: shared engine-core @0x8016DEA4 (src/shared) */


DEFINE_func_8016DEE0()  /* dedup: shared engine-core @0x8016DEE0 (src/shared) */


DEFINE_func_8016DF20()  /* dedup: shared engine-core @0x8016DF20 (src/shared) */


extern Blk20 D_800AE620;
extern s32 D_8011D030;
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
extern void func_8001CD50(s32 a0, s32 a1);
extern void func_800233CC(void *, unsigned short);
extern void func_801465C0(void);
extern void func_80146C3C(void);




void func_8016DF5C(s32 param_1)
{
    extern void func_8016E3CC(void *a0);
    extern void RotMatrixY(s32 a0, void *a1);
    extern u8 D_801EA348;
    extern u8 D_801EA349;
    extern u8 D_801EA34A;
    extern u8 D_801EA34C;
    extern u8 D_801EA34D;
    extern u8 D_801EA34E;

    s32 iVar8;
    short sVar1;

    iVar8 = *(s32 *)((u8 *)((void *)param_1) + 0x34);
    if ((*(u32 *)((u8 *)((void *)param_1) + 0x2c) & 0x8000) == 0) {
        unsigned short uVar7 = 0;
        u16 *psVar6 = (u16 *)&D_8011D030;
        register s32 iNew __asm__("$17");
        s32 base;
        do {
            if (psVar6 != (u16 *)((void *)param_1) && (*psVar6 == 0x41 || *psVar6 == 0x48)) {
                ((void (*)(void *))func_80146C3C)(psVar6);
            }
            uVar7++;
            psVar6 += 0x2c;
        } while (uVar7 < 0x1e);
        iNew = ((s32(*)())func_801465C0)();
        if (iNew == 0) {
            return;
        }
        base = (s32)&D_801EA348;
        D_801EA34A = 0xc0;
        *(u8 *)base = 0xc0;
        D_801EA349 = 0;
        D_801EA34E = 0;
        D_801EA34D = 0;
        D_801EA34C = 0;
        ((void(*)(void *, unsigned short))func_800233CC)((void *)base, 0x40);
        func_8001CD50(iNew, base);
        *(s32 *)(iNew + 0x34) = (s32)((u8 *)((void *)param_1) + 0x38);
        *(s16 *)(iNew + 0x1a) = 0;
        *(s16 *)(iNew + 0x18) = 0;
        *(u32 *)(iNew + 4) = *(u32 *)(iNew + 4) | 0x50000000;
        func_8016E3CC(((void *)param_1));
        {
            register s32 t10 __asm__("$3");
            t10 = 0x10;
            *(s32 *)((u8 *)((void *)param_1) + 0x20) = iNew;
            *(s32 *)((u8 *)((void *)param_1) + 0x1c) = t10;
        }
        sVar1 = *(u16 *)((u8 *)((void *)param_1) + 2) + 1;
    } else {
        short asStack_60[20];
        Blk20_8016DF5C localMatrix;
        s32 uVar2;

        asStack_60[0] = 0;
        asStack_60[1] = 0;
        asStack_60[2] = 0x20;
        localMatrix = (*(Blk20_8016DF5C*)&D_800AE620);
        uVar2 = ((s32(*)())rand)();
        RotMatrixY((uVar2 & 0x7f00) >> 3, &localMatrix);
        ApplyMatrixSV(&localMatrix, asStack_60, asStack_60);
        *(s16 *)((u8 *)((void *)param_1) + 6) = D_80126B5E + asStack_60[0];
        *(s16 *)((u8 *)((void *)param_1) + 0xa) = D_80126B62 - ((u16)uVar2 & 0x3f);
        *(s16 *)((u8 *)((void *)param_1) + 0xe) = D_80126B66 + asStack_60[2];
        *(Blk20_8016DF5C *)((u8 *)((void *)param_1) + 0x38) = *(Blk20_8016DF5C *)((u8 *)iVar8 + 0x38);
        *(s32 *)((u8 *)((void *)param_1) + 0x2c) = 0x1000;
        *(s32 *)((u8 *)((void *)param_1) + 0x30) = 0xff;
        *(s32 *)((u8 *)((void *)param_1) + 0x1c) = 0x10;
        __asm__ __volatile__("" ::: "memory");
        sVar1 = 4;
    }
    *(s16 *)((u8 *)((void *)param_1) + 2) = sVar1;
}


DEFINE_func_8016E1CC()  /* dedup: shared engine-core @0x8016E1CC (src/shared) */

DEFINE_func_8016E26C()  /* dedup: shared engine-core @0x8016E26C (src/shared) */

DEFINE_func_8016E2E8()  /* dedup: shared engine-core @0x8016E2E8 (src/shared) */

DEFINE_func_8016E358()  /* dedup: shared engine-core @0x8016E358 (src/shared) */

DEFINE_func_8016E3CC()  /* dedup: shared engine-core @0x8016E3CC (src/shared) */

DEFINE_func_8016E460()  /* dedup: shared engine-core @0x8016E460 (src/shared) */


DEFINE_func_8016E5B8()  /* dedup: shared engine-core @0x8016E5B8 (src/shared) */


DEFINE_func_8016E5F4()  /* dedup: shared engine-core @0x8016E5F4 (src/shared) */

DEFINE_func_8016E688()  /* dedup: shared engine-core @0x8016E688 (src/shared) */

DEFINE_func_8016E6E4()  /* dedup: shared engine-core @0x8016E6E4 (src/shared) */

DEFINE_func_8016E728()  /* dedup: shared engine-core @0x8016E728 (src/shared) */

DEFINE_func_8016E778()  /* dedup: shared engine-core @0x8016E778 (src/shared) */

// @class: regalloc-order
// @stuck: none — MATCH (74 ins); register pin $s2 forces &prim into a saved reg (§17)

                 /* 0x08 */
     /* 0x20 */

typedef struct {
    SVECTOR_8016E7C8 v[4];               /* 0x00 */
    s32 f0, f1, f2, f3, f4, f5; /* 0x20..0x37 */
    u8  f6;                     /* 0x38 */
    u8  pad[7];                 /* -> 0x40 */
} Prim_8016E7C8;


void func_8016E7C8(int param_1, short *param_2, unsigned int *param_3)
{
    extern void func_8004914C(void *a0);
    extern void func_800491AC(void *a0);
    extern void RotTransSV(void *a0, void *a1, void *a2);
    extern void func_80016ED4(void *a0);
    extern SVECTOR_8016E7C8 D_8018E8B8[4];
    extern s32 D_8018E8D8;
    extern s32 D_8018E8E0;
    extern s32 D_8018E8E8;
    extern s32 D_8018E8F0;

    Prim_8016E7C8 prim;
    MATRIX_8016E7C8 m;
    SVECTOR_8016E7C8 tmp;
    register Prim_8016E7C8 *pp __asm__("$18");   /* $s2 — force &prim into a saved reg */

    ((void (*)(void *, void *))func_80017DC4)(param_2, &m);
    m.t[0] = *(short *)(param_1 + 6);
    m.t[1] = *(short *)(param_1 + 10);
    m.t[2] = *(short *)(param_1 + 14);
    func_8004914C(&m);
    func_800491AC(&m);
    pp = &prim;
    RotTransSV(&D_8018E8B8[0], pp, &tmp);
    RotTransSV(&D_8018E8B8[1], &prim.v[1], &tmp);
    RotTransSV(&D_8018E8B8[2], &prim.v[2], &tmp);
    RotTransSV(&D_8018E8B8[3], &prim.v[3], &tmp);
    prim.v[0].vz = 3;
    prim.f5 = 0x50000000;
    prim.f0 = D_8018E8D8;
    prim.f1 = D_8018E8E0;
    prim.f2 = D_8018E8E8;
    prim.f3 = D_8018E8F0;
    prim.f4 = *param_3;
    prim.f6 = 0x27;
    func_80016ED4(pp);
}



DEFINE_func_8016E8F0()  /* dedup: shared engine-core @0x8016E8F0 (src/shared) */

DEFINE_func_8016E918()  /* dedup: shared engine-core @0x8016E918 (src/shared) */

// @class: struct
// @stuck: none — MATCH (36/36 ins, match_one relocation-masked)



typedef void (*Handler)(struct Entry_8016E95C *);


s32 func_8016E95C() {
    extern Handler D_8018E938[];

    struct Entry_8016E95C *p;
    for (p = ((struct Entry_8016E95C *)&D_80115218); p < &((struct Entry_8016E95C *)&D_80115218)[4]; p++) {
        if (p->f0 != 0) {
            D_8018E938[p->f1](p);
        }
    }
}




/* @class: regalloc (non-coalescing delay-slot copy) + sched (load-temp hoist)
 * @stuck: none — MATCH (53/53 ins, match_one AND rtu_match in the real TU).
 *
 * Two levers, both from the cookbook:
 *
 * 1. §52a "non-coalescing delay-slot copy" + §17 zero-reg-copy (the load-bearing one).
 *    The target holds `p[0]-1` in TWO callee-saved regs: $s0 (the array index, later
 *    destroyed in place by `sll $s0,$s0,1`) and $s4 (the value stored to p[3]), created
 *    by `addu $s4,$s0,$zero` sitting in the DELAY SLOT of `jal func_800D2CA8`. A plain
 *    C `c = i;` is destroyed by cse.c canon_reg head-promotion (measured: 50 ins, -3),
 *    and every #APP-asm spelling of the copy is INELIGIBLE for a delay slot (measured:
 *    51 ins, -2 — tried `__asm__("":"=r"(c):"0"(i))`, a real-opcode
 *    `__asm__("addu %0,%1,$0")`, and the §52b RC-7 post-copy second-set barrier
 *    `c=i; __asm__("":"=r"(c):"0"(c))`; all three collapse or lose the slot).
 *    Only the `$0`-add — `register u32 zr __asm__("$0"); c = i + zr;` — emits a bare
 *    `addu` with no asm insn, so reorg can sink it into the call's delay slot.
 *    NOTE for ×138 propagation: this is a ZERO-REGISTER pin, not an allocation pin —
 *    it constrains no real value. family_sweep's §42e "skip pinned exemplar" guard is
 *    documented over-conservative (§86; the SIGABRT was our own extract_unit macro-drop,
 *    fixed in Phase 27), so this exemplar should still sweep.
 *
 * 2. Free-floating load temp for a scheduler hoist (§52a-adjacent, idiom 7).
 *    With the p+6 store written as one statement the sched2 list scheduler hoists
 *    `lbu $v0,1($a0)` ahead of `sb $s4,3($a0)` and sinks the D_8018E924 lui/addu/lhu
 *    chain (8 mismatched, same 53-ins multiset). Splitting the load into its own
 *    statement `h = D_8018E924[i];` placed BEFORE `p[2] = 0` (exactly what the Ghidra
 *    seed showed) puts the lhu chain right after `sh $v0,4($a0)` → 0.
 *
 * Data typing: D_8018E908 is a WORD array (`sll $v0,$s0,2`; its element is dereferenced
 * as a buffer by func_80024054) => u8 *[]. D_8018E920 is byte-indexed (`lbu`, no shift)
 * => u8[]. D_8018E924 is halfword-indexed (`sll $s0,$s0,1` + `lhu`) => u16[].
 * `*(s16 *)(p + 4) = -0xD7` emits `addiu $v0,$zero,-0xD7`; 0xFF29 as a u16 would not.
 */


extern s32 func_800D2CA8(s32 a0, s32 a1);
extern void func_800D2D10(s32 a0, s32 a1, void *a2, s32 a3);
extern s32 func_80024054(void *a0, void *a1);
extern void func_8016EC0C(s32 a0, s32 a1);

void func_8016E9EC(u8 *p)
{

    extern u8 *D_8018E908[];
    extern u8 D_8018E920[];
    extern u16 D_8018E924[];
    register u32 zr __asm__("$0");
    int i;
    int c;
    u8 *buf;
    u8 off;
    u16 h;
    s32 r;

    i = p[0] - 1;
    off = D_8018E920[i];
    buf = D_8018E908[i];
    c = i + zr;
    r = func_800D2CA8(p[3], 0x1C);
    func_800D2D10(r, 1, buf + off, 0);
    func_80024054(buf, p + 8);
    p[3] = c;
    *(s16 *)(p + 4) = -0xD7;
    h = D_8018E924[i];
    p[2] = 0;
    *(u16 *)(p + 6) = h;
    p[1] = p[1] + 1;
    ((void (*)(u8 *, s32))func_8016EC0C)(p, 0x80);
}



// @class: struct
// @stuck: none — MATCH (31/31 ins, match_one verified)

extern u16 D_8018E92C[];
extern void func_8016EC0C(s32 a0, s32 a1);

void func_8016EAC0(Wave *param_1)
{
    unsigned char bVar1;

    param_1->f4 = param_1->f4 + D_8018E92C[param_1->f2];
    ((void (*)(void *, int))func_8016EC0C)(param_1, 0x80);
    bVar1 = param_1->f2 + 1;
    param_1->f2 = bVar1;
    if (5 < bVar1) {
        param_1->f2 = 0x20;
        param_1->f1 = param_1->f1 + 1;
    }
}



// @class: loose-typing
// @stuck: none — MATCH (u8 v + 0xFF emits addiu 0xFF; v-1 would emit -1/0xffff)

extern u8 D_8018E91C[];
extern void func_8016EC0C(s32 a0, s32 a1);

void func_8016EB3C(s32 p) {
    u8 v;

    ((void (*)(s32, s32))func_8016EC0C)(p, D_8018E91C[*(u8 *)(p + 2) & 3]);

    v = *(u8 *)(p + 2);
    *(u8 *)(p + 2) = v + 0xFF;
    if (v == 0) {
        *(u8 *)(p + 2) = 5;
        *(u8 *)(p + 1) = *(u8 *)(p + 1) + 1;
    }
}



// @class: struct
// @stuck: none — MATCH (25 ins). %lo-fold via extern u16 D_8018E92C[]; predecrement emitted as +0xFF (u8 promote→sb low byte), not -1.

extern u16 D_8018E92C[];

extern void func_8016EC0C(s32 a0, s32 a1);

void func_8016EBA8(u8 *param_1)
{
    u8 c;

    *(u16 *)(param_1 + 4) =
        *(u16 *)(param_1 + 4) - D_8018E92C[param_1[2]];
    ((void (*)(u8 *, int))func_8016EC0C)(param_1, 0x80);
    c = param_1[2];
    param_1[2] = c + 0xFF;
    if (c == 0) {
        param_1[0] = 0;
    }
}



DEFINE_func_8016EC0C()  /* dedup: shared engine-core @0x8016EC0C (src/shared) */


DEFINE_func_8016ED6C()  /* dedup: shared engine-core @0x8016ED6C (src/shared) */

DEFINE_func_8016ED8C()  /* dedup: shared engine-core @0x8016ED8C (src/shared) */

DEFINE_func_8016EDBC()  /* dedup: shared engine-core @0x8016EDBC (src/shared) */

DEFINE_func_8016EDEC()  /* dedup: shared engine-core @0x8016EDEC (src/shared) */

DEFINE_func_8016EE40()  /* dedup: shared engine-core @0x8016EE40 (src/shared) */

DEFINE_func_8016EE94()  /* dedup: shared engine-core @0x8016EE94 (src/shared) */

DEFINE_func_8016EF78()  /* dedup: shared engine-core @0x8016EF78 (src/shared) */

DEFINE_func_8016EFA8()  /* dedup: shared engine-core @0x8016EFA8 (src/shared) */

DEFINE_func_8016EFC8()  /* dedup: shared engine-core @0x8016EFC8 (src/shared) */

DEFINE_func_8016F094()  /* dedup: shared engine-core @0x8016F094 (src/shared) */

// @class: plumbing
// @stuck: none — MATCH

DEFINE_func_8016F0AC()  /* dedup: shared engine-core @0x8016F0AC (src/shared) */




/* RECONCILE NOTE (uc3) — the body is byte-unchanged from uc2; only the declaration
 * environment moved.  The gate error was
 *     jr_8016AB6C.c:4183 conflicting types for func_8016F0E4 || :4089 previous declaration
 * :4089 was THIS definition; :4183 is the `extern void func_8016F0E4(void);` carried inside
 * DEFINE_func_8016F4C4() (src/shared/engine_core.h:22579), which the host TU instantiates at
 * ov_SC01_077_jr_8016AB6C.c:4136 — i.e. AFTER the definition, so it is a hard error, not the
 * mere warning produced by the earlier block-scope decl in func_8016F0AC (TU:4047).
 * Byte-true signature is `void (u8 *)`; the fleet canon is `void (void)` — a PARAM/ARITY
 * disagreement on func_8016F0E4 ITSELF.
 *
 * ESCAPE TAKEN: §37/§124 ASM-LABEL ALIAS (escape 2, T0 draft-only, zero tracked-file edits).
 * The C identifier is aF8016F0E4 so this TU declares func_8016F0E4 exactly once (the macro's
 * own `extern void`), while the emitted SYMBOL is func_8016F0E4.  Both existing callers already
 * launder through a cast or take no args, so neither is perturbed:
 *   - func_8016F0AC (TU:4047-4049) casts:  ((void (*)(void *))func_8016F0E4)(&D_80126B58);
 *   - DEFINE_func_8016F4C4 calls func_8016F0E4() with 0 args against its own (void) prototype.
 * cc1-proven: preprocess+compile of the real TU with this body spliced in is free of any
 * func_8016F0E4 diagnostic (the pre-existing unrelated warnings in the TU are unchanged).
 *
 * This SUPERSEDES uc2's //@EDIT de-macroize plan (§65b) and its T2 engine_core.h alternative
 * (§75c) — neither is needed; nothing outside this unit changes, so the bank travels to the
 * 137 siblings as a plain unit (carry the alias DECLARATION line with it — §124 trap 2).
 */

DEFINE_func_8016F0E4()  /* dedup: shared engine-core @0x8016F0E4 (src/shared) */


DEFINE_func_8016F14C()  /* dedup: shared engine-core @0x8016F14C (src/shared) */

DEFINE_func_8016F1AC()  /* dedup: shared engine-core @0x8016F1AC (src/shared) */


// @class: schedule
// @stuck: none — MATCH

extern s32 D_8018E948;
extern s32 D_80126B58;
extern s16 currentLocationId;

s32 func_8016F1C4(void) {
    s32 *p;
    s32 cur;
    s32 loc;
    s32 v;
    s32 *base = &D_80126B58;

    p = &D_8018E948;
    cur = *p;
    if (cur != 0) {
        loc = currentLocationId;
        p = p + 1;
        for (;;) {
            if (loc == cur) {
                return 1;
            }
            cur = *p;
            p = p + 1;
            if (cur == 0) {
                break;
            }
        }
    }
    v = base[0x7E];
    if (((v & 0x80FFFFFF) != 0) && ((v & 0x10000000) != 0)) {
        return 0;
    }
    return base[0x7E] & 0x80FFFFFF;
}


DEFINE_func_8016F250()  /* dedup: shared engine-core @0x8016F250 (src/shared) */

DEFINE_func_8016F264()  /* dedup: shared engine-core @0x8016F264 (src/shared) */

DEFINE_func_8016F288()  /* dedup: shared engine-core @0x8016F288 (src/shared) */

DEFINE_func_8016F2A8()  /* dedup: shared engine-core @0x8016F2A8 (src/shared) */

DEFINE_func_8016F2C8()  /* dedup: shared engine-core @0x8016F2C8 (src/shared) */

DEFINE_func_8016F2EC()  /* dedup: shared engine-core @0x8016F2EC (src/shared) */

DEFINE_func_8016F30C()  /* dedup: shared engine-core @0x8016F30C (src/shared) */

DEFINE_func_8016F330()  /* dedup: shared engine-core @0x8016F330 (src/shared) */

DEFINE_func_8016F350()  /* dedup: shared engine-core @0x8016F350 (src/shared) */

DEFINE_func_8016F374()  /* dedup: shared engine-core @0x8016F374 (src/shared) */

DEFINE_func_8016F388()  /* dedup: shared engine-core @0x8016F388 (src/shared) */

DEFINE_func_8016F398()  /* dedup: shared engine-core @0x8016F398 (src/shared) */

DEFINE_func_8016F410()  /* dedup: shared engine-core @0x8016F410 (src/shared) */

DEFINE_func_8016F44C()  /* dedup: shared engine-core @0x8016F44C (src/shared) */

DEFINE_func_8016F470()  /* dedup: shared engine-core @0x8016F470 (src/shared) */

DEFINE_func_8016F494()  /* dedup: shared engine-core @0x8016F494 (src/shared) */

DEFINE_func_8016F4C4()  /* dedup: shared engine-core @0x8016F4C4 (src/shared) */

DEFINE_func_8016F4F4()  /* dedup: shared engine-core @0x8016F4F4 (src/shared) */

DEFINE_func_8016F4FC()  /* dedup: shared engine-core @0x8016F4FC (src/shared) */

DEFINE_func_8016F540()  /* dedup: shared engine-core @0x8016F540 (src/shared) */

DEFINE_func_8016F578()  /* dedup: shared engine-core @0x8016F578 (src/shared) */

DEFINE_func_8016F5B0()  /* dedup: shared engine-core @0x8016F5B0 (src/shared) */

DEFINE_func_8016F5E0()  /* dedup: shared engine-core @0x8016F5E0 (src/shared) */

DEFINE_func_8016F610()  /* dedup: shared engine-core @0x8016F610 (src/shared) */

DEFINE_func_8016F648()  /* dedup: shared engine-core @0x8016F648 (src/shared) */

DEFINE_func_8016F680()  /* dedup: shared engine-core @0x8016F680 (src/shared) */

DEFINE_func_8016F6B0()  /* dedup: shared engine-core @0x8016F6B0 (src/shared) */


DEFINE_func_8016F6E0()  /* dedup: shared engine-core @0x8016F6E0 (src/shared) */


DEFINE_func_8016F71C()  /* dedup: shared engine-core @0x8016F71C (src/shared) */

DEFINE_func_8016F764()  /* dedup: shared engine-core @0x8016F764 (src/shared) */


DEFINE_func_8016F798()  /* dedup: shared engine-core @0x8016F798 (src/shared) */


DEFINE_func_8016F7D4()  /* dedup: shared engine-core @0x8016F7D4 (src/shared) */

DEFINE_func_8016F804()  /* dedup: shared engine-core @0x8016F804 (src/shared) */


DEFINE_func_8016F834()  /* dedup: shared engine-core @0x8016F834 (src/shared) */


DEFINE_func_8016F870()  /* dedup: shared engine-core @0x8016F870 (src/shared) */

DEFINE_func_8016F8AC()  /* dedup: shared engine-core @0x8016F8AC (src/shared) */


DEFINE_func_8016F8E4()  /* dedup: shared engine-core @0x8016F8E4 (src/shared) */


DEFINE_func_8016F920()  /* dedup: shared engine-core @0x8016F920 (src/shared) */

DEFINE_func_8016F95C()  /* dedup: shared engine-core @0x8016F95C (src/shared) */


DEFINE_func_8016F9C4()  /* dedup: shared engine-core @0x8016F9C4 (src/shared) */


DEFINE_func_8016FA00()  /* dedup: shared engine-core @0x8016FA00 (src/shared) */

DEFINE_func_8016FA44()  /* dedup: shared engine-core @0x8016FA44 (src/shared) */


DEFINE_func_8016FA84()  /* dedup: shared engine-core @0x8016FA84 (src/shared) */


DEFINE_func_8016FAC0()  /* dedup: shared engine-core @0x8016FAC0 (src/shared) */

DEFINE_func_8016FB10()  /* dedup: shared engine-core @0x8016FB10 (src/shared) */

DEFINE_func_8016FB50()  /* dedup: shared engine-core @0x8016FB50 (src/shared) */


DEFINE_func_8016FB7C()  /* dedup: shared engine-core @0x8016FB7C (src/shared) */


DEFINE_func_8016FBB8()  /* dedup: shared engine-core @0x8016FBB8 (src/shared) */

DEFINE_func_8016FC24()  /* dedup: shared engine-core @0x8016FC24 (src/shared) */

DEFINE_func_8016FC64()  /* dedup: shared engine-core @0x8016FC64 (src/shared) */


DEFINE_func_8016FC90()  /* dedup: shared engine-core @0x8016FC90 (src/shared) */


DEFINE_func_8016FCCC()  /* dedup: shared engine-core @0x8016FCCC (src/shared) */

DEFINE_func_8016FD08()  /* dedup: shared engine-core @0x8016FD08 (src/shared) */

DEFINE_func_8016FD7C()  /* dedup: shared engine-core @0x8016FD7C (src/shared) */


DEFINE_func_8016FDB4()  /* dedup: shared engine-core @0x8016FDB4 (src/shared) */


DEFINE_func_8016FDF0()  /* dedup: shared engine-core @0x8016FDF0 (src/shared) */

DEFINE_func_8016FE2C()  /* dedup: shared engine-core @0x8016FE2C (src/shared) */

DEFINE_func_8016FE78()  /* dedup: shared engine-core @0x8016FE78 (src/shared) */

DEFINE_func_8016FED0()  /* dedup: shared engine-core @0x8016FED0 (src/shared) */


DEFINE_func_8016FF30()  /* dedup: shared engine-core @0x8016FF30 (src/shared) */


DEFINE_func_8016FF6C()  /* dedup: shared engine-core @0x8016FF6C (src/shared) */

DEFINE_func_8016FFA8()  /* dedup: shared engine-core @0x8016FFA8 (src/shared) */


DEFINE_func_8016FFDC()  /* dedup: shared engine-core @0x8016FFDC (src/shared) */


DEFINE_func_80170018()  /* dedup: shared engine-core @0x80170018 (src/shared) */

DEFINE_func_80170068()  /* dedup: shared engine-core @0x80170068 (src/shared) */

DEFINE_func_801700B8()  /* dedup: shared engine-core @0x801700B8 (src/shared) */

DEFINE_func_80170100()  /* dedup: shared engine-core @0x80170100 (src/shared) */


DEFINE_func_80170150()  /* dedup: shared engine-core @0x80170150 (src/shared) */


DEFINE_func_8017018C()  /* dedup: shared engine-core @0x8017018C (src/shared) */

DEFINE_func_801701C8()  /* dedup: shared engine-core @0x801701C8 (src/shared) */


DEFINE_func_80170240()  /* dedup: shared engine-core @0x80170240 (src/shared) */


DEFINE_func_8017027C()  /* dedup: shared engine-core @0x8017027C (src/shared) */

DEFINE_func_801702B8()  /* dedup: shared engine-core @0x801702B8 (src/shared) */


DEFINE_func_801702FC()  /* dedup: shared engine-core @0x801702FC (src/shared) */


DEFINE_func_80170338()  /* dedup: shared engine-core @0x80170338 (src/shared) */

DEFINE_func_80170374()  /* dedup: shared engine-core @0x80170374 (src/shared) */


DEFINE_func_801703E0()  /* dedup: shared engine-core @0x801703E0 (src/shared) */


DEFINE_func_8017041C()  /* dedup: shared engine-core @0x8017041C (src/shared) */

DEFINE_func_8017044C()  /* dedup: shared engine-core @0x8017044C (src/shared) */


DEFINE_func_801704B0()  /* dedup: shared engine-core @0x801704B0 (src/shared) */


DEFINE_func_801704EC()  /* dedup: shared engine-core @0x801704EC (src/shared) */

DEFINE_func_8017051C()  /* dedup: shared engine-core @0x8017051C (src/shared) */


DEFINE_func_80170548()  /* dedup: shared engine-core @0x80170548 (src/shared) */


DEFINE_func_80170584()  /* dedup: shared engine-core @0x80170584 (src/shared) */

DEFINE_func_801705C0()  /* dedup: shared engine-core @0x801705C0 (src/shared) */


DEFINE_func_801705F8()  /* dedup: shared engine-core @0x801705F8 (src/shared) */


DEFINE_func_80170634()  /* dedup: shared engine-core @0x80170634 (src/shared) */

DEFINE_func_80170670()  /* dedup: shared engine-core @0x80170670 (src/shared) */


DEFINE_func_801706AC()  /* dedup: shared engine-core @0x801706AC (src/shared) */


DEFINE_func_801706E8()  /* dedup: shared engine-core @0x801706E8 (src/shared) */

DEFINE_func_80170718()  /* dedup: shared engine-core @0x80170718 (src/shared) */


DEFINE_func_80170748()  /* dedup: shared engine-core @0x80170748 (src/shared) */


DEFINE_func_80170784()  /* dedup: shared engine-core @0x80170784 (src/shared) */

DEFINE_func_801707D4()  /* dedup: shared engine-core @0x801707D4 (src/shared) */


DEFINE_func_80170810()  /* dedup: shared engine-core @0x80170810 (src/shared) */


DEFINE_func_8017084C()  /* dedup: shared engine-core @0x8017084C (src/shared) */


DEFINE_func_801708B0()  /* dedup: shared engine-core @0x801708B0 (src/shared) */


DEFINE_func_80170928()  /* dedup: shared engine-core @0x80170928 (src/shared) */

DEFINE_func_80170970()  /* dedup: shared engine-core @0x80170970 (src/shared) */

DEFINE_func_801709B8()  /* dedup: shared engine-core @0x801709B8 (src/shared) */

DEFINE_func_80170A00()  /* dedup: shared engine-core @0x80170A00 (src/shared) */

DEFINE_func_80170A48()  /* dedup: shared engine-core @0x80170A48 (src/shared) */

DEFINE_func_80170A90()  /* dedup: shared engine-core @0x80170A90 (src/shared) */


DEFINE_func_80170AD8()  /* dedup: shared engine-core @0x80170AD8 (src/shared) */


DEFINE_func_80170B14()  /* dedup: shared engine-core @0x80170B14 (src/shared) */

DEFINE_func_80170B48()  /* dedup: shared engine-core @0x80170B48 (src/shared) */

DEFINE_func_80170B90()  /* dedup: shared engine-core @0x80170B90 (src/shared) */


DEFINE_func_80170BD8()  /* dedup: shared engine-core @0x80170BD8 (src/shared) */


DEFINE_func_80170C14()  /* dedup: shared engine-core @0x80170C14 (src/shared) */

DEFINE_func_80170C44()  /* dedup: shared engine-core @0x80170C44 (src/shared) */


DEFINE_func_80170C74()  /* dedup: shared engine-core @0x80170C74 (src/shared) */


DEFINE_func_80170CB0()  /* dedup: shared engine-core @0x80170CB0 (src/shared) */


DEFINE_func_80170CF0()  /* dedup: shared engine-core @0x80170CF0 (src/shared) */



DEFINE_func_80170D68()  /* dedup: shared engine-core @0x80170D68 (src/shared) */


DEFINE_func_80170DA4()  /* dedup: shared engine-core @0x80170DA4 (src/shared) */

DEFINE_func_80170DE0()  /* dedup: shared engine-core @0x80170DE0 (src/shared) */


DEFINE_func_80170E34()  /* dedup: shared engine-core @0x80170E34 (src/shared) */


DEFINE_func_80170E70()  /* dedup: shared engine-core @0x80170E70 (src/shared) */

DEFINE_func_80170EAC()  /* dedup: shared engine-core @0x80170EAC (src/shared) */


DEFINE_func_80170EFC()  /* dedup: shared engine-core @0x80170EFC (src/shared) */


DEFINE_func_80170F38()  /* dedup: shared engine-core @0x80170F38 (src/shared) */

DEFINE_func_80170F74()  /* dedup: shared engine-core @0x80170F74 (src/shared) */


DEFINE_func_80170FB0()  /* dedup: shared engine-core @0x80170FB0 (src/shared) */


DEFINE_func_80170FEC()  /* dedup: shared engine-core @0x80170FEC (src/shared) */

DEFINE_func_80171028()  /* dedup: shared engine-core @0x80171028 (src/shared) */


DEFINE_func_80171064()  /* dedup: shared engine-core @0x80171064 (src/shared) */


DEFINE_func_801710A0()  /* dedup: shared engine-core @0x801710A0 (src/shared) */

DEFINE_func_801710DC()  /* dedup: shared engine-core @0x801710DC (src/shared) */


DEFINE_func_80171120()  /* dedup: shared engine-core @0x80171120 (src/shared) */


DEFINE_func_8017115C()  /* dedup: shared engine-core @0x8017115C (src/shared) */

DEFINE_func_8017118C()  /* dedup: shared engine-core @0x8017118C (src/shared) */


DEFINE_func_801711C0()  /* dedup: shared engine-core @0x801711C0 (src/shared) */


DEFINE_func_801711FC()  /* dedup: shared engine-core @0x801711FC (src/shared) */

DEFINE_func_80171238()  /* dedup: shared engine-core @0x80171238 (src/shared) */


DEFINE_func_80171260()  /* dedup: shared engine-core @0x80171260 (src/shared) */


DEFINE_func_8017129C()  /* dedup: shared engine-core @0x8017129C (src/shared) */

DEFINE_func_80171384()  /* dedup: shared engine-core @0x80171384 (src/shared) */


DEFINE_func_801714E4()  /* dedup: shared engine-core @0x801714E4 (src/shared) */


DEFINE_func_80171520()  /* dedup: shared engine-core @0x80171520 (src/shared) */

DEFINE_func_8017162C()  /* dedup: shared engine-core @0x8017162C (src/shared) */

DEFINE_func_801716AC()  /* dedup: shared engine-core @0x801716AC (src/shared) */

DEFINE_func_801717A0()  /* dedup: shared engine-core @0x801717A0 (src/shared) */

DEFINE_func_801717F4()  /* dedup: shared engine-core @0x801717F4 (src/shared) */

DEFINE_func_80171824()  /* dedup: shared engine-core @0x80171824 (src/shared) */

DEFINE_func_80171854()  /* dedup: shared engine-core @0x80171854 (src/shared) */

DEFINE_func_80171884()  /* dedup: shared engine-core @0x80171884 (src/shared) */

DEFINE_func_801718AC()  /* dedup: shared engine-core @0x801718AC (src/shared) */

DEFINE_func_80171904()  /* dedup: shared engine-core @0x80171904 (src/shared) */

DEFINE_func_80171928()  /* dedup: shared engine-core @0x80171928 (src/shared) */

DEFINE_func_8017196C()  /* dedup: shared engine-core @0x8017196C (src/shared) */

DEFINE_func_8017197C()  /* dedup: shared engine-core @0x8017197C (src/shared) */

DEFINE_func_80171990()  /* dedup: shared engine-core @0x80171990 (src/shared) */

DEFINE_func_801719A4()  /* dedup: shared engine-core @0x801719A4 (src/shared) */

DEFINE_func_80171A04()  /* dedup: shared engine-core @0x80171A04 (src/shared) */

DEFINE_func_80171A10()  /* dedup: shared engine-core @0x80171A10 (src/shared) */

DEFINE_func_80171A1C()  /* dedup: shared engine-core @0x80171A1C (src/shared) */

DEFINE_func_80171A34()  /* dedup: shared engine-core @0x80171A34 (src/shared) */

DEFINE_func_80171A44()  /* dedup: shared engine-core @0x80171A44 (src/shared) */

DEFINE_func_80171A58()  /* dedup: shared engine-core @0x80171A58 (src/shared) */

DEFINE_func_80171A6C()  /* dedup: shared engine-core @0x80171A6C (src/shared) */

DEFINE_func_80171A80()  /* dedup: shared engine-core @0x80171A80 (src/shared) */

DEFINE_func_80171A88()  /* dedup: shared engine-core @0x80171A88 (src/shared) */

DEFINE_func_80171AB0()  /* dedup: shared engine-core @0x80171AB0 (src/shared) */

DEFINE_func_80171B10()  /* dedup: shared engine-core @0x80171B10 (src/shared) */

DEFINE_func_80171B44()  /* dedup: shared engine-core @0x80171B44 (src/shared) */
