// @class: regalloc-order
// @stuck: 33/304 ins (89%); structure/frame/calls/consts all correct. Residual = entry-block regalloc:
//   target puts param_3 in $a3 and the 2 load temps in $v1/$v0 (keeping $a0 live so `addu $s4,$a0,$zero`
//   fills the load-delay slot); mine gets $a2/$v0/$a0, which shifts the prologue save order (runs 1..6,
//   10..17, 21..22) and the region-B store schedule (run 83..101) + one load swap (271..272).
//   The $a3 pin is emulated with a register-pinned copy; gcc copy-propagates the raw param into the
//   first load, so the pin move sinks into the delay slot instead of staying in the prologue.
// CRACKED IDIOMS (byte-verified here, reusable):
//   * sched1 (pre-reload) interleaves two back-to-back `d = p[i] - q[i]` pairs into 4 live temps;
//     REUSING one explicit C temp pair (s32 t,u) creates WAR anti-deps gcc-2.7.2 cannot rename away
//     -> the serial 2-temp $v1/$v0 form the target has. (u16 t,u does NOT work: HImode re-widens.)
//   * fold-const.c `associate:` only calls split_tree on ARG0 -> `A + (B + C)` never reassociates,
//     giving `addiu B,+C; addu A,B` instead of `addu A,B; addiu +C`. Use `a1[1] + (desc.y + 0x10)`.
//   * `s32 r = (s16)call(...)` sign-extends AT the call (sll/sra around the jal); `s16 r = call(...)`
//     keeps it raw and sign-extends at the use (+1 move). The target wants the former.
//   * an 8-byte align-1 copy (lwl/lwr+swl/swr) = __builtin_memcpy((void*)(s32)&dst,(void*)(s32)&src,8):
//     the (void*)(int) cast drops get_pointer_alignment to 1 while the addr still folds to sp+const.
//   * `(s16)(dx|dz) == 0` gives `or; sll 16; beqz` (andi 0xffff comes from the & 0xFFFF form).


typedef struct { u16 x, y, z, w; } V4;

typedef struct {
    u16 x, y, z, w;      /* 0x00 */
    s32 pad[4];          /* 0x08 */
    s32 f18;             /* 0x18 */
    s32 f1C;             /* 0x1C */
    s32 f20;             /* 0x20 */
} Desc;                  /* 0x24 */

typedef struct Ent {
    u16 f0;              /* 0x00 */
    u16 f2;
    u16 f4;
    u16 x;               /* 0x06 */
    u16 f8;
    u16 y;               /* 0x0A */
    u16 fC;
    u16 z;               /* 0x0E */
    u8  p10[0x10];       /* 0x10 */
    s32 f20;             /* 0x20 */
    u8  p24[0x34];       /* 0x24 */
    s32 f58;             /* 0x58 */
    u16 f5C;             /* 0x5C */
    u16 f5E;
    u8  p60[0x10C - 0x60];
} Ent;                   /* 0x10C */

extern s16 currentLocationId;
extern Ent D_801202A0[];
extern u8 D_8018876C[];
extern u16 D_801152A8;
extern u16 D_801152AC;

extern s32 ratan2(s32 a0, s32 a1);
extern s32 func_80135A4C(s32 a0, s32 a1, s32 *a2, s32 a3);
extern s32 func_80012A60(s32 a0, s32 a1);
extern void func_800139C8(s32 a0, void *a1, void *a2);
extern s32 func_80135888(s32 a0, s32 a1, s32 a2, s32 a3);
extern s32 func_8014DCE0(s32 a0, s32 a1, s32 a2);
extern s32 func_80133784(s32 a0, void *a1, s32 a2);

s32 func_8014D820(s32 a0, u16 *a1, u16 *a2x) {
    register u16 *a2 __asm__("$7") = a2x;
    V4 out[3];
    V4 pos;
    Desc desc;
    Ent *ent;
    Ent *p;
    s32 dx, dz;
    s32 ex, ez;
    s32 r1, r2, r3;
    s32 ang;
    s32 x0, y0, z0, tx, tz;
    s32 r;
    s32 t;
    register s32 u __asm__("$2");

    t = a2[0]; u = a1[0];
    dx = t - u;
    t = a2[2]; u = a1[2];
    dz = t - u;
    if ((s16)(dx | dz) == 0) goto fail;
    desc.x = dx;
    desc.y = a2[1] - a1[1];
    desc.z = a2[2] - a1[2];
    ent = *(Ent **)(a0 + 0x170);
    if (ent->f0 == 0) goto fail;
    if ((ent->f5C & 0x1000) == 0) goto fail;
    if (ent->f58 == 0) goto fail;
    if (((s32 (*)(s32, s32, s32))func_80135A4C)(ent->f20, ent->f58, (s32)a1) == 0) goto fail;
    ex = ent->x - *(u16 *)(a0 + 6);
    ez = ent->z - *(u16 *)(a0 + 0xE);
    r1 = (s16)ratan2((s16)dz, (s16)dx);
    r2 = (s16)ratan2((s16)ez, (s16)ex);
    r3 = (s16)func_80012A60(r1, r2);
    if (r3 >= 0x400) goto fail;
    desc.f20 = 0;
    desc.f1C = 0;
    desc.f18 = 0;
    x0 = ent->x;
    z0 = ent->z;
    tx = x0 + desc.x;
    pos.x = x0;
    y0 = ent->y;
    pos.y = y0;
    desc.y = y0 + desc.y + 8;
    tz = z0 + desc.z;
    pos.z = z0;
    desc.x = tx;
    desc.z = tz;
    if (currentLocationId != 0x3008) {
        for (p = D_801202A0; p < D_801202A0 + 96; p++) {
            if (p == ent) continue;
            if (p->f0 == 0) continue;
            if (p->f5C == 0) continue;
            if (p->f58 == 0) continue;
            func_80135888(p->f20, p->f58, (s32)&pos, (s32)&desc);
        }
    } else {
        ang = ratan2((s16)x0 - (s16)tx, (s16)z0 - (s16)tz) & 0xFFF;
        func_800139C8(ang, D_8018876C, &out[0]);
        func_800139C8((s16)(ang - 0x155), D_8018876C, &out[1]);
        func_800139C8((s16)(ang + 0x155), D_8018876C, &out[2]);
        out[0].x += pos.x;
        out[0].y = pos.y;
        out[0].z += pos.z;
        out[1].x += pos.x;
        out[1].y = pos.y;
        out[1].z += pos.z;
        out[2].x += pos.x;
        out[2].y = pos.y;
        out[2].z += pos.z;
        for (p = D_801202A0; p < D_801202A0 + 96; p++) {
            if (p == ent) continue;
            if (p->f0 == 0) continue;
            if (p->f5C == 0) continue;
            if (p->f58 == 0) continue;
            if (func_8014DCE0((s32)p, (s32)&pos, (s32)&out[0]) != 0) {
                __builtin_memcpy((void *)(s32)&desc, (void *)(s32)&pos, 8);
            }
        }
    }
    r = func_80133784(0, &pos, (s32)&desc);
    if (r == 0 || (r == 0x2000 && (D_801152A8 | D_801152AC) == 0)) {
        ent->x = desc.x - desc.f18;
        ent->y = desc.y;
        ent->z = desc.z - desc.f20;
        desc.x -= pos.x;
        desc.y -= pos.y;
        desc.z -= pos.z;
        *(u16 *)(a0 + 6) = a1[0] + desc.x;
        *(u16 *)(a0 + 0xA) = a1[1] + (desc.y + 0x10);
        *(u16 *)(a0 + 0xE) = a1[2] + desc.z;
    } else {
        *(u16 *)(a0 + 6) = a1[0];
        *(u16 *)(a0 + 0xA) = a1[1] + 0x10;
        *(u16 *)(a0 + 0xE) = a1[2];
    }
    return 1;
fail:
    *(s32 *)(a0 + 0x170) = 0;
    return 0;
}
