#include "common.h"

typedef struct { s16 vx, vy, vz, pad; } Vec3;

extern void (*D_801891B8[])(s32);
extern u8 D_8018914C[];
extern s32 D_8011F9C4;

extern s32 func_80161B18(s32);
extern s32 func_801619A4(s32);
extern s32 func_80149AA8(s32);
extern void func_80149AD4(s32);
extern s32 func_80149B54(s32);
extern void func_80149BAC(s32);
extern void func_801498E0(s32);
extern void func_80149954(s32);
extern s32 func_80149A64(s32);
extern void func_800CCCC0(s32);
extern s32 func_80149CD4(s32);
extern void func_8015E880(s32);
extern s32 func_80149744(s32);
extern void func_80149788(s32);
extern s32 func_801496D4(s32);
extern void func_80149704(s32);
extern s32 func_80148AFC(s32);
extern void func_80146D90(s32);
extern void func_80154150(s32, s32);
extern void func_801541D8(s32, s32, s32);
extern s32 func_801488A8(s32);
extern void func_80147078(s32, s32);
extern void func_8015A264(s32);
extern s32 func_80013294(Vec3 *, Vec3 *);
extern void func_80159B70(s32);
extern s32 func_8016F1AC(void);
extern s32 func_80029178(s32);
extern void func_80146DB8(s32, void *);
extern void func_80161CD0(s32, s32);
extern s32 func_80161208(s32);
extern void func_801725A4(s32);

s32 func_8015B950(arg0)
s32 arg0;
{
    Vec3 vzero;
    Vec3 vpos;
    s32 x;
    s32 ang;
    s32 t;
    s32 r;
    s32 lo;

    lo = -0xB0000;
    if (func_80161B18(arg0)) {
        return;
    }
    switch (func_801619A4(arg0)) {
    case 0:
    case 1:
    case 2:
    case 6:
        if (func_80149AA8(arg0)) {
            D_801891B8[*(u16 *)arg0](arg0);
            func_80149AD4(arg0);
            return;
        }
        if (func_80149B54(arg0)) {
            D_801891B8[*(u16 *)arg0](arg0);
            func_80149BAC(arg0);
            return;
        }
        break;
    case 3:
        func_801498E0(arg0);
        break;
    case 4:
        func_80149954(arg0);
        break;
    case 5:
        if (func_80149A64(arg0)) {
            D_801891B8[*(u16 *)arg0](arg0);
            func_800CCCC0(arg0);
            return;
        }
        break;
    }
    if (func_80149CD4(arg0)) {
        D_801891B8[*(u16 *)arg0](arg0);
        func_8015E880(arg0);
        return;
    }
    if (func_80149744(arg0)) {
        D_801891B8[*(u16 *)arg0](arg0);
        func_80149788(arg0);
        return;
    }
    if (func_801496D4(arg0)) {
        D_801891B8[*(u16 *)arg0](arg0);
        func_80149704(arg0);
        if (!((u8)func_80148AFC(arg0))) {
            func_80146D90(arg0);
        }
        if ((*(s32 *)(arg0 + 0x24) | *(s32 *)(arg0 + 0x2C)) != 0) {
            func_80154150(arg0, 0xF);
        } else {
            func_801541D8(arg0, 0xD, 6);
        }
        *(s32 *)(arg0 + 0x238) = 1;
        return;
    }
    if (func_801488A8(arg0)) {
        vzero.vx = 0;
        vzero.vy = 0;
        vzero.vz = 0;
        t = *(s16 *)(arg0 + 0x26);
        vpos.vx = t;
        vpos.vy = 0;
        t = *(s16 *)(arg0 + 0x2E);
        vpos.vz = t;
        D_801891B8[*(u16 *)arg0](arg0);
        func_80147078(arg0, 1);
        func_8015A264(arg0);
        ang = -(func_80013294(&vzero, &vpos) << 16);
        if (ang < *(s32 *)(arg0 + 0x2C)) {
            *(s32 *)(arg0 + 0x2C) = ang;
        }
        return;
    }
    if (*(u16 *)(arg0 + 0xB8) == 0x8000) {
        D_801891B8[*(u16 *)arg0](arg0);
        func_80147078(arg0, 0);
        func_80159B70(arg0);
        return;
    }
    x = *(s32 *)(arg0 + 0x2C);
    if (func_8016F1AC() != 0) goto Lfalse;
    if (x <= lo) goto Ltrue;
    if (D_8011F9C4 == 0) goto Lfalse;
    if ((u8)func_80029178(0x21) != 0) goto Lfalse;
Ltrue:
    r = 1;
    goto Ltest;
Lfalse:
    r = 0;
Ltest:
    if (r) {
        D_801891B8[*(u16 *)arg0](arg0);
        func_80147078(arg0, 0);
        func_80159B70(arg0);
        func_80154150(arg0, 9);
        func_80146DB8(arg0, D_8018914C);
        func_80161CD0(arg0, *(u16 *)(arg0 + 0x16E));
    } else {
        if (func_80161208(arg0) == 0) {
            func_801725A4(arg0);
        }
    }
    return;
}

/* ===== BANK BLOCKER (Phase-29 crack-wave, 2026-07-18) =====
 * match_one MATCH (271 ins) but NOT bankable as-is: def-side register-threading wall.
 * - canonical decl (engine_core.h:1839, in DEFINE_func_8015BEE4) = `extern s32 func_8015B950(void)`.
 * - caller func_8015BEE4 = thin wrapper `s32 func_8015BEE4(void){ return func_8015B950(); }` — forwards
 *   its OWN incoming $a0 to func_8015B950 IMPLICITLY (register pass-through), so func_8015B950 MUST stay
 *   declared (void) for the wrapper to compile byte-correct.
 * - BUT func_8015B950's body reads $a0 (asm insn 3: addu $s0,$a0,$zero). A `register s32 __asm__("$4")`
 *   pin compiles but PERTURBS codegen (SHA fail, not byte-neutral).
 * FOLLOW-UP: Fable5/careful analysis — either get the entry $a0-capture pin byte-exact, or thread the
 *   arg through func_8015BEE4 fleet-wide (widen both, byte-neutrally). A func_8013FAF8-class wall with a
 *   no-arg thin-wrapper caller. Draft above is the byte-correct body. */
