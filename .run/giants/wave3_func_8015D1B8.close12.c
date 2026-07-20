/* func_8015D1B8 (ov_SC01_077 jr_8015AE2C) -- NEAR: 114/114 ins, 12 masked mismatches.
 * Structure + register allocation are byte-identical to target. Two gcc-internal residuals:
 *  (1) frame 0x30 vs target 0x38: an extra reserved 8-byte DEAD local slot (body has no stack
 *      stores below the reg-saves). reload-reserved-then-recovered spill; not C-steerable.
 *  (2) idx 63-66: 2-insn address materialization (&D_801893E0) scheduled AFTER srl/sll instead
 *      of before -- a scheduler tie-break; srl is intrinsically first in the post-guard BB so
 *      no statement ordering moves the address ahead of it.
 * Load-bearing choices (proven by byte-gate): sum/uVar4 SPLIT (merge => 89 mismatch);
 * s16 m for (m/512) => srl (int m => sra); e0 assigned AFTER idx keeps addr in post-guard BB;
 * &D_801893E0 - 8 anchor gives addiu $a1,$v0,-8 base reuse. => permuter/Fable5 frame-fragility. */
extern s32 func_80149FB0(s32 a0);
extern void func_80147324(s32 a0);
extern u16 func_80148800(s32 *a0);
extern void func_80149724(void);
extern void func_80154274(s32 *a0, s32 a1);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern void func_801477E8(s32 *a0, s32 a1);
extern void func_8014FA04(s32 a0);
extern void func_8014E6A0(void);
extern void func_80147078(s32 *a0, s16 a1);
extern void func_80159B70(void *a0);
extern void func_8015D380(void *a0);
extern s32 func_801725F4(u8 *a0);
extern void (*D_801891B8[])(void *);
extern s32 D_800D4C14;
extern s32 D_801893E0;
extern s32 D_801893D8;
extern s32 D_80189398;
extern s32 D_8018939C;

void func_8015D1B8(u8 *p) {
    s32 uVar4;
    s16 uVar1;
    s16 sVar2;
    s16 diff;
    s16 m;
    s32 idx;
    s32 *e0;

    s32 sum;
    ((void (*)(void))func_80149FB0)();
    sum = *(u16 *)(*(s32 *)(p + 0x20) + 0x10) + *(u16 *)(p + 0x236);
    *(u16 *)(*(s32 *)(p + 0x20) + 0x10) = sum & 0xfff;
    uVar4 = sum;
    uVar1 = *(s16 *)(p + 0x244);
    sVar2 = *(s16 *)(*(s32 *)(p + 0x20) + 0x10);
    if (sVar2 - uVar1 >= 0) {
        diff = sVar2 - uVar1;
    } else {
        diff = uVar1 - sVar2;
    }
    if (diff > 0x800) {
        func_80147324(0x5e9);
    }
    *(u16 *)(p + 0x244) = *(u16 *)(*(s32 *)(p + 0x20) + 0x10);
    if ((func_80148800((s32 *)p) & 0x40) != 0) {
        D_801891B8[*(u16 *)p](p);
        ((void (*)(u8 *))func_80149724)(p);
        func_80154274((s32 *)p, (s32)&D_800D4C14);
        func_80146E90((s32 *)p, 0x10);
        m = uVar4 & 0xfff;
        idx = (m / 512) * 8;
        e0 = &D_801893E0;
        *e0 = *(s32 *)((u8 *)&D_80189398 + idx);
        func_80146DB8((s32 *)p, (s32 *)((u8 *)e0 - 8));
        func_801477E8((s32 *)p, *(s32 *)((u8 *)&D_8018939C + idx));
        func_80147324(0x5ea);
    } else {
        func_8014FA04((s32)p);
        if (((s32 (*)(s32 *))func_8014E6A0)((s32 *)p) == 0) {
            D_801891B8[*(u16 *)p](p);
            func_80147078((s32 *)p, 0);
            func_80159B70(p);
        } else {
            func_8015D380(p);
            ((void (*)(u8 *))func_801725F4)(p);
        }
    }
}
