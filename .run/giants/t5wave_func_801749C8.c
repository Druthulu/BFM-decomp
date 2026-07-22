// @class: schedule
// @stuck: none — MATCH (105 ins)
//
// func_801749C8 — per-frame actor pose/transform update (ov_SC06_018 jr_801734BC family).
// Levers used (all byte-proven here):
//  * register pins (§17): cx=$s2/$18 (D_80126B5E), cz=$s1/$17 (sign-extended D_80126B66);
//    both are the only values live across the func_80049CAC call (D_80126B62 is RELOADED,
//    so it must be read inline, never hoisted into a local).
//  * lhu+sll+sra (NOT lh): `(s16)D_80126B66` is folded by combine into a single `lh`.
//    An intervening STORE between the u16 load and the sign-extension blocks that fold
//    (same mechanism as cookbook §49) — hence `czr = D_80126B66;` ... store ... `cz = (czr<<16)>>16;`
//    with czr a SEPARATE temp (reusing one var costs 5 more mismatches).
//  * LUID dial (§49/§50-A): materializing `t28 = *(s16*)(param_1+0x28)` BEFORE `cx = ...`
//    moves the 0x28 load ahead of the D_80126B5E lui/lh in the expand stream — the last 3.
//  * frame: MATRIX at sp+0x10 (t[] at sp+0x24), SVECTOR in at sp+0x30, SVECTOR out at sp+0x38;
//    locals are laid out in DECLARATION order.
//  * canonical sigs kept (func_8012F14C is `void(s32)` in the TU) -> cast at the call site.

typedef struct { s16 vx, vy, vz, pad; } SV4_801749C8;
typedef struct { s16 m[3][3]; s16 pad; s32 t[3]; } MTX_801749C8;

extern s32 func_80012C6C(s32 a0, s32 a1, s32 a2);
extern s16 func_80012ABC(s32 a0, s32 a1, s32 a2);
extern void func_80049CAC(s32 a0, s32 a1);
extern void func_8012F14C(s32);

extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;

void func_801749C8(s32 param_1)
{
    MTX_801749C8 mtx;     /* sp+0x10 */
    SV4_801749C8 in;      /* sp+0x30 */
    SV4_801749C8 out;     /* sp+0x38 */
    register s32 cx __asm__("$18");
    register s32 cz __asm__("$17");
    s32 czr;
    s32 t28;

    *(s32 *)(param_1 + 0x08) = (s16)func_80012C6C(*(s16 *)(param_1 + 0x08), *(s16 *)(param_1 + 0x0C), 4);
    *(s32 *)(param_1 + 0x10) = (s16)func_80012C6C(*(s16 *)(param_1 + 0x10), *(s16 *)(param_1 + 0x14), 4);
    *(s16 *)(param_1 + 0x18) = func_80012ABC(*(s16 *)(param_1 + 0x18), *(s16 *)(param_1 + 0x20), 4);
    *(s16 *)(param_1 + 0x1A) = func_80012ABC(*(s16 *)(param_1 + 0x1A), *(s16 *)(param_1 + 0x22), 4);
    *(s16 *)(param_1 + 0x1C) = func_80012ABC(*(s16 *)(param_1 + 0x1C), *(s16 *)(param_1 + 0x24), 4);
    *(s16 *)(param_1 + 0x28) = func_80012C6C(*(s16 *)(param_1 + 0x28), *(s16 *)(param_1 + 0x2E), 0x10);
    *(s16 *)(param_1 + 0x2A) = func_80012C6C(*(s16 *)(param_1 + 0x2A), *(s16 *)(param_1 + 0x30), 0x10);
    *(s16 *)(param_1 + 0x2C) = func_80012C6C(*(s16 *)(param_1 + 0x2C), *(s16 *)(param_1 + 0x32), 0x10);

    t28 = *(s16 *)(param_1 + 0x28);
    cx = (s16)D_80126B5E;
    czr = D_80126B66;

    *(s32 *)(param_1 + 0x48) = t28 + cx;
    cz = (czr << 16) >> 16;
    *(s32 *)(param_1 + 0x4C) = *(s16 *)(param_1 + 0x2A) + (s16)D_80126B62;
    *(s32 *)(param_1 + 0x50) = *(s16 *)(param_1 + 0x2C) + cz;

    func_80049CAC(param_1 + 0x18, (s32)&mtx);

    mtx.t[0] = *(s16 *)(param_1 + 0x28) + cx;
    mtx.t[1] = *(s16 *)(param_1 + 0x2A) + (s16)D_80126B62;
    mtx.t[2] = *(s16 *)(param_1 + 0x2C) + cz;
    in.vx = 0;
    in.vy = 0;
    in.vz = *(s32 *)(param_1 + 0x10);
    ((void (*)(s32, s32, s32))func_8012F14C)((s32)&mtx, (s32)&in, (s32)&out);

    *(s32 *)(param_1 + 0x3C) = out.vx;
    *(s32 *)(param_1 + 0x40) = out.vy;
    *(s32 *)(param_1 + 0x44) = out.vz;
}
