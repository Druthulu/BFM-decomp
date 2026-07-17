// @class: loose-typing
// @stuck: close=76/371; ins 0..263 MATCH byte-exact. Residual starts at the D_80126CE0 block
//   (0x80176B6C): target reads that ONE global TWICE — `lh $v0` for the `!= 0` test AND
//   `lhu $a1` for the value (gcc won't CSE across sign/zero-extend modes). From `extern s16
//   D_80126CE0` + `(u16)D_80126CE0` gcc CSEs to a single `lh` => mine is 2 ins short there and
//   everything downstream shifts. Forcing the pair with `uv = *(u16*)&D_80126CE0` DOES emit both
//   loads (verified: 371/371 ins, lui/lh/lui/lhu/beqz structurally exact at 270..274) but it
//   drops register pressure => frame 0x40 -> 0x38 => whole-function save-offset cascade
//   (close 76 -> 84..95). Classic §27 frame-pressure lock: the dual-load and the 0x40 frame are
//   mutually exclusive from every C form tried. Needs the permuter (frame-preserving search) or
//   an aliasing/type lever that adds the 2nd load WITHOUT relieving pressure.
//
// LEVERS BANKED (all byte-verified, each strictly reduced close):
//   330 -> 179  e2 = e+0x3C hoisted OUT of the if (target computes it before the beqz) + QImode
//               narrowing (`u8 d` var => addiu -0x80 on both arms, not +0x80).
//   179 -> 174  ENT() RELOAD inside the `q[0x48]>=4` block (gcc CSEs the ADDRESS into $a0 but
//               redoes the `lw` — the intervening `sb 0xD($a1)` may alias); + branch polarity
//               flip at 0x8017694C (`==` so the ne-block is the branch target, not fall-through).
//   174 -> 154  two-variable param model: `e = ENT(b, param_1); arg = param_1;` — CSE canonicalizes
//               the FIRST use to the incoming $a0 (`sll $v0,$a0,16`), later uses take $s6.
//               NOTE: `register s32 arg __asm__("$22")` as a PARAMETER does not parse in gcc-2.7.2.
//   154 -> 119  f1: non-pinned temp `t2` forces the `addu $s5,$v0,$zero` copy (pinning f1 alone
//               makes gcc compute the whole xor/sltu chain directly in $s5); + `g != 3` polarity.
//   119 ->  95  §28 coalescing pin `register s32 v __asm__("$2")` for `v = res` (gcc coalesces a
//               plain copy back into $s0); + `num` pinned $a0 so the dividend/quotient leaves $v1
//               free. This alone fixed the ins count to exactly 371.
//    95 ->  86  single reused `e` (pinned $a1) instead of ee/ee2/e3/e4 — the target keeps EVERY
//               ENT result in $a1, i.e. the original reuses ONE variable. The 0x80176984 block is
//               the exception ($a0) => its own block-local `e5`/`tt`.
//    86 ->  76  `arg = param_1;` BEFORE p/q/r (orders the $s6 def ahead of the $s1/$s2/$s4 defs)
//               while `e = ENT(b, param_1)` stays AFTER them — moving the ENT before p/q/r makes
//               b's first use fold the symbol into the §18 `lui $at; addu; lw %lo` form (+frame).
//               Div block: `one` pinned $v1 + emitted first, then div, then rt=r[0x48], then
//               q[0x47]=one, then p[0x4B]=rt|0xF0, then p[0x47]=num (the `rt` temp forces the
//               lbu-first order so the store fills the load-delay slot).
//
// STRUCTURE (byte-confirmed): base-cache — $s3=&D_8011F7A8, $s1=b+0x48 (== D_8011F7F0, the same
// base the MATCHED sibling func_801775E0 uses in this TU), $s2=b+0xE0, $s4=D_80078E78, $s6=arg,
// $s5=f1, $s0=res/f2. ENT(b,a) = *(s32*)(b + (s16)a*4 + 0x28).
#include "common.h"

extern u8 D_8011F7A8[];
extern u8 D_80078E78[];

extern s16 D_801152BA;
extern u8 D_8011F7B0;
extern u8 D_80115214;
extern u8 D_800B9A13;

extern u8 D_8018A2D8[];
extern u16 D_8018A22A[];
extern s32 D_8018A2E4[];
extern u16 D_8018A238;
extern u8 D_8018A2CC[];

extern u8 D_800D45D4;
extern u8 D_800D43D4;
extern u8 D_800D4414;

extern s32 D_80126B58;
extern s16 D_80126D20;
extern s16 D_80126CE0;

extern void func_800183E0(s32 a0);
extern s32 func_801619D0(void *a0);
extern s32 func_80161A00(s32 a0);
extern s32 func_80161A30(s32 a0);
extern s32 func_80161A60(s32 a0);
extern void func_801775E0(s32 a0, s32 a1);

#define ENT(bb, aa) (*(s32 *)((bb) + ((s16)(aa)) * 4 + 0x28))

void func_80176734(s32 param_1) {
    register u8 *b __asm__("$19");      /* $s3 = &D_8011F7A8      */
    register u8 *p __asm__("$17");      /* $s1 = b + 0x48         */
    register u8 *q __asm__("$18");      /* $s2 = b + 0xE0         */
    register u8 *r __asm__("$20");      /* $s4 = D_80078E78       */
    register s32 f1 __asm__("$21");     /* $s5                    */
    register s32 arg __asm__("$22");    /* $s6 = copy of param_1  */
    s32 res;                            /* $s0 (reused for f2)    */
    register s32 v __asm__("$2");       /* $v0 — §28 coalescing pin */
    s32 f2;
    register s32 e __asm__("$5");       /* $a1 — param_1 holds $a0 at e's birth */
    u8 *e2;                             /* $a0 — falls out, don't pin (§27)     */
    s32 t;
    u16 uv;
    u8 c;
    u8 n;
    s32 z;

    b = D_8011F7A8;
    arg = param_1;
    p = b + 0x48;
    q = b + 0xE0;
    r = D_80078E78;
    e = ENT(b, param_1);
    e2 = (u8 *)(e + 0x3C);
    if (D_801152BA != 0) {
        u8 d;
        c = D_8011F7B0;
        if (c < 0x80) {
            d = c + 0x80;
        } else {
            d = ~c + 0x80;
        }
        e2[4] = d;
        *(u8 *)(e + 4) = d;
        b[8] += D_80115214;
    } else {
        *(u8 *)(e + 0x40) = 0x80;
        *(u8 *)(e + 4) = 0x80;
    }

    if (q[0x48] != 0) {
        e = ENT(b, arg);
        *(u8 *)(e + 0xD) = D_8018A2D8[q[0x48]];
        if (q[0x48] >= 4) {
            u8 s = p[0x48];
            e = ENT(b, arg);
            if (s & 0x80) {
                *(s16 *)(e + 0x20) = D_8018A238;
                func_800183E0((s32)&D_800D45D4);
            } else if (s != 0) {
                *(s16 *)(e + 0x20) = D_8018A22A[s];
                func_800183E0(D_8018A2E4[p[0x48]]);
            }
            n = q[0x48];
            if (n == 5) {
                if (p[0x48] == 0) {
                    q[0x48] = 0;
                } else {
                    q[0x48] = n + 1;
                }
            } else if (n == 10) {
                q[0x48] = 0;
            } else {
                q[0x48] = n + 1;
            }
        } else {
            q[0x48] = q[0x48] + 1;
        }
    } else if (p[0x48] != r[0x48]) {
        if (p[0x48] == 0 && r[0x48] != 0) {
            q[0x48] = 5;
        } else {
            q[0x48] = 0;
        }
        p[0x48] = r[0x48];
        {
            u8 m;
            e = ENT(b, arg);
            m = q[0x48];
            q[0x48] = m + 1;
            *(u8 *)(e + 0xD) = D_8018A2D8[m];
        }
    }

    if (*(s16 *)(p + 0x2E) == *(s16 *)(r + 0x2E)) {
        if (*(s16 *)(q + 0x2E) == 0) goto L9C0;
        *(s16 *)(q + 0x2E) = 0;
    } else {
        *(s16 *)(p + 0x2E) = *(s16 *)(r + 0x2E);
        *(s16 *)(q + 0x2E) = 1;
    }
L984:
    {
        s32 e5;
        s32 tt;
        e5 = ENT(b, arg);
        tt = *(u16 *)(p + 0x2E) << 16;
        if (tt != 0) {
            *(u8 *)(e5 + 0x49) = D_8018A2CC[tt >> 20];
        } else {
            *(u8 *)(e5 + 0x49) = 0xA0;
        }
    }
L9C0:
    if ((*(s16 *)(p + 0x1E) & 0x8000) != (*(s16 *)(r + 0x1E) & 0x8000)) {
        if ((*(s16 *)(p + 0x1E) & 0x8000) != 0) {
            *(s16 *)(p + 0x1E) = 0;
            func_800183E0((s32)&D_800D43D4);
        } else {
            *(s16 *)(p + 0x1E) = -0x8000;
            func_800183E0((s32)&D_800D4414);
        }
    }

    {
        u8 g = D_800B9A13;
        if (g != 3) {
            s32 t2 = (b[7] != g);
            f1 = t2;
            if (t2 != 0) {
                b[7] = g;
            }
        } else {
            f1 = 0;
        }
    }

    res = 0;
    switch (r[0x48]) {
    case 3:
        if (func_801619D0(&D_80126B58) != 0) {
            res = 0xFF;
        }
        break;
    case 4:
        if (func_80161A00((s32)&D_80126B58) != 0) {
            res = 0xFF;
        }
        break;
    case 5:
        if (func_80161A30((s32)&D_80126B58) != 0) {
            res = 0xFF;
        }
        break;
    case 6:
        if (func_80161A60((s32)&D_80126B58) != 0) {
            res = 0xBA;
        }
        break;
    }

    v = res;
    if (v != 0) {
        register s32 num __asm__("$4");  /* $a0 — keeps $v1 free for the `1` */
        register s32 one __asm__("$3");  /* $v1 — emitted first, sched keeps it */
        u8 rt;
        one = 1;
        num = (D_80126D20 << 7) / v;
        rt = r[0x48];
        q[0x47] = one;
        p[0x4B] = rt | 0xF0;
        p[0x47] = num;
        goto L88;
    }

    if (p[0x4B] >= 0xF0) {
        p[0x4B] = 0;
    }

    if (D_80126CE0 != 0) {
        uv = (u16)D_80126CE0;
        p[0x4B] = uv;
        f2 = (p[0x47] != (u8)uv);
    } else {
        uv = r[0x47];
        f2 = 0;
        if (p[0x47] != uv || p[0x47] == 0x80) {
            f2 = 1;
        }
        if (r[0x47] != 0 && p[0x4B] != 0) {
            p[0x4B] = 0;
            p[0x47] = r[0x47];
        }
    }

    if (f2 != 0) goto BIG;
    if (f1 != 0) goto BIG;
    if (q[0x47] == 0) goto L8C;
    if (f1 == 0) goto CLR;
BIG:
    if ((s32)p[0x47] < (s16)uv) {
        goto SET;
    } else {
        p[0x47] += ((s16)uv != 0) ? -3 : -8;
        if (p[0x47] == 0 || p[0x47] > 0x80) {
            p[0x47] = 0;
            p[0x4B] = 0;
        } else if ((s32)p[0x47] < (s16)uv) {
SET:
            p[0x47] = uv;
        }
    }
    q[0x47] = 1;
    goto L88;
CLR:
    q[0x47] = 0;
L88:
L8C:
    z = (b[7] != 0) << 8;
    *(s16 *)(ENT(b, arg) + 0x32) = *(u16 *)(b + 0x12) + z + 5;
    func_801775E0(ENT(b, arg) + 0x64, (s16)(*(u16 *)(b + 0x12) + z + 9));
}
