/* func_80176734 — ov_SC01_077 HUD sync.  NEAR: 366/371 ins, close=217, LENGTH-DRIFT -5.
 *
 * Base idiom = the matched sibling func_80176218 in the same TU:
 *   st=&D_8011F7A8 ($s3), cach=st+0x48 ($s1), flag=st+0xE0 ($s2), cur=D_80078E78 ($s4),
 *   param copy ($s6), chg ($s5), r/chg2 ($s0).  Index expr written OFFSET-FIRST
 *   (((p<<16)>>14) + st + 0x28) so gcc emits `addu rd,off,st` like the target.
 * `u8 zbuf[8]` is NOT dead weight: it is what makes get_frame_size() give the target's
 *   0x40 frame (verified — without it the prologue is `addiu sp,sp,-56`).  buf[4] works too.
 * The 0x2E block writes the EQUAL case first so gcc emits `bne` (not `beq`) — byte-verified.
 * The tail routes t+5 / t+9 through temps so gcc emits `addiu $a2,$v1,5; addu $v0,$v0,$a2`
 *   instead of reassociating to (lhu+5)+t.
 *
 * RESIDUAL — 5 instructions the target's gcc kept and this draft's gcc optimizes away.
 * All 5 are "target gcc was LESS aggressive"; each was isolated and reproduced, but every
 * known lever for them wrecks the register allocation (see below), so none are applied.
 *   b1 (+3): missing `andi $v0,$v1,0xFF` (an explicit QI->SI zero-extend of the D_8011F7B0
 *            lbu that combine deletes here via nonzero_bits), missing `addiu $a0,$a1,0x3C`
 *            (cse folds `p[4]` into `sb 0x40($a1)`), missing the load-delay `nop` after
 *            `lh D_801152BA` (sched1 hoists the lh here, target keeps it at the branch).
 *   b2 (-3): `*(u8*)(st+8)` is const-folded to `lui/%lo(D_8011F7A8)+8` here; the target
 *            keeps `lbu/sb 0x8($s3)`.  cse knows st's constant in that block for us and
 *            not for the target.  This fold also costs `st` two references, which is why
 *            global-alloc gives st $s5 and chg $s3 here (target: st $s3, chg $s5).
 *   chg (+1)/switch(+1): the target keeps the uncoalesced copies `addu $s5,$v0,$zero` and
 *            `addu $v0,$s0,$zero` (one copy at .L80176AF4, gas duplicates it into 4 delay
 *            slots); here cse unifies the temp with the variable and the copy dies.
 *   end (+2): the target keeps the provably-redundant `beqz $v1,.L80176C84` (re-test of
 *            chg==0) and the `j .L80176C88`/`sb` split; cse's record_jump_equiv kills it here.
 *
 * PROVEN LEVERS (each reproduces its target instruction, all rejected as net-negative):
 *   __asm__("" : "=r"(p)  : "0"(p))  before the store  -> `addiu $a0,$a1,0x3C` appears (369 ins)
 *   __asm__("" : "=r"(st) : "0"(st)) before the RMW    -> `lbu/sb 0x8($s3)` appears (b2 exact)
 *   __asm__("" : "=r"(rv) : "0"(r))  before `if (r)`   -> switch region becomes 42/42 exact
 *   Each launder is also a scheduling/liveness barrier: it re-shuffles the call-saved
 *   allocation and drops aligned agreement from 138/371 to as low as 60/371.  A real fix
 *   has to make cse weaker WITHOUT a barrier (i.e. find the source shape that ends cse's
 *   extended basic block at .L801767BC), not paper over each instruction.
 */

extern void func_800183E0(s32);
extern s32 func_801619D0(void*);
extern s32 func_80161A00(s32);
extern s32 func_80161A30(s32);
extern s32 func_80161A60(s32);
void func_801775E0(s32, s32);

extern u8 D_80078E78[];
extern u8 D_800B9A13;
extern u8 D_800D43D4;
extern u8 D_800D4414;
extern u8 D_800D45D4;
extern u8 D_8011F7A8;
extern s32 D_80126B58;
extern s16 D_80126D20;
extern u16 D_8018A238;
extern u8 D_8018A2CC[];
extern s32 D_8018A2E4[];

/* derived from the asm (not in sig_hints) */
extern s16 D_801152BA;
extern u8 D_80115214;
extern u8 D_8011F7B0;
extern s16 D_80126CE0;
extern u16 D_8018A22A[];
extern u8 D_8018A2D8[];

void func_80176734(s32 param_1)
{
    s32 st   = (s32)&D_8011F7A8;
    s32 cach = st + 0x48;
    s32 flag = st + 0xE0;
    s32 cur  = (s32)D_80078E78;
    s32 e;
    s32 b;
    s32 chg;
    s32 chg2;
    u16 g;
    s32 r;
    u8 fv;
    u8 zbuf[8];

    e = *(s32 *)(((param_1 << 16) >> 14) + st + 0x28);
    if (D_801152BA != 0) {
        u8 *p = (u8 *)(e + 0x3C);
        s32 vv = D_8011F7B0 - 0x80;
        if (D_8011F7B0 >= 0x80) {
            vv = ~D_8011F7B0 - 0x80;
        }
        p[4] = vv;
        *(u8 *)(e + 4) = vv;
        *(u8 *)(st + 8) = *(u8 *)(st + 8) + D_80115214;
    } else {
        *(u8 *)(e + 0x40) = 0x80;
        *(u8 *)(e + 4) = 0x80;
    }

    fv = *(u8 *)(flag + 0x48);
    if (fv != 0) {
        b = ((param_1 << 16) >> 14) + st;
        *(u8 *)(*(s32 *)(b + 0x28) + 0xD) = D_8018A2D8[fv];
        fv = *(u8 *)(flag + 0x48);
        if (fv < 4) {
            *(u8 *)(flag + 0x48) = fv + 1;
        } else {
            u8 cv = *(u8 *)(cach + 0x48);
            s32 ee = *(s32 *)(b + 0x28);
            if (cv & 0x80) {
                *(u16 *)(ee + 0x20) = D_8018A238;
                func_800183E0((s32)&D_800D45D4);
            } else if (cv != 0) {
                *(u16 *)(ee + 0x20) = D_8018A22A[cv];
                func_800183E0(D_8018A2E4[*(u8 *)(cach + 0x48)]);
            }
            fv = *(u8 *)(flag + 0x48);
            if (fv == 5) {
                if (*(u8 *)(cach + 0x48) == 0) {
                    *(u8 *)(flag + 0x48) = 0;
                } else {
                    *(u8 *)(flag + 0x48) = fv + 1;
                }
            } else if (fv == 10) {
                *(u8 *)(flag + 0x48) = 0;
            } else {
                *(u8 *)(flag + 0x48) = fv + 1;
            }
        }
    } else {
        u8 cv = *(u8 *)(cach + 0x48);
        u8 sv = *(u8 *)(cur + 0x48);
        if (cv != sv) {
            if (cv == 0 && sv != 0) {
                *(u8 *)(flag + 0x48) = 5;
            } else {
                *(u8 *)(flag + 0x48) = 0;
            }
            *(u8 *)(cach + 0x48) = *(u8 *)(cur + 0x48);
            {
                s32 bb2 = ((param_1 << 16) >> 14) + st;
                u8 f2 = *(u8 *)(flag + 0x48);
                s32 ee = *(s32 *)(bb2 + 0x28);
                *(u8 *)(flag + 0x48) = f2 + 1;
                *(u8 *)(ee + 0xD) = D_8018A2D8[f2];
            }
        }
    }

    {
        s16 sv2 = *(s16 *)(cur + 0x2E);
        if (*(s16 *)(cach + 0x2E) == sv2) {
            if (*(s16 *)(flag + 0x2E) == 0) goto L9C0;
            *(s16 *)(flag + 0x2E) = 0;
        } else {
            *(s16 *)(cach + 0x2E) = sv2;
            *(s16 *)(flag + 0x2E) = 1;
        }
    }
    {
        s32 ee = *(s32 *)(((param_1 << 16) >> 14) + st + 0x28);
        s32 t = (s32)(*(u16 *)(cach + 0x2E)) << 16;
        if (t != 0) {
            *(u8 *)(ee + 0x49) = D_8018A2CC[t >> 20];
        } else {
            *(u8 *)(ee + 0x49) = 0xA0;
        }
    }
L9C0:
    {
        s32 fa = *(s16 *)(cach + 0x1E) & 0x8000;
        s32 fb = *(s16 *)(cur + 0x1E) & 0x8000;
        if (fa != fb) {
            s32 arg;
            if (fa != 0) {
                arg = (s32)&D_800D43D4;
                *(s16 *)(cach + 0x1E) = 0;
            } else {
                *(s16 *)(cach + 0x1E) = -0x8000;
                arg = (s32)&D_800D4414;
            }
            func_800183E0(arg);
        }
    }

    {
        u8 cc3 = D_800B9A13;
        if (cc3 == 3) {
            chg = 0;
        } else {
            chg = (*(u8 *)(st + 7) != cc3);
            if (chg != 0) {
                *(u8 *)(st + 7) = cc3;
            }
        }
    }

    r = 0;
    switch (*(u8 *)(cur + 0x48)) {
    case 3:
        if (func_801619D0(&D_80126B58) != 0) r = 0xFF;
        break;
    case 4:
        if (func_80161A00((s32)&D_80126B58) != 0) r = 0xFF;
        break;
    case 5:
        if (func_80161A30((s32)&D_80126B58) != 0) r = 0xFF;
        break;
    case 6:
        if (func_80161A60((s32)&D_80126B58) != 0) r = 0xBA;
        break;
    }

    if (r != 0) {
        *(u8 *)(flag + 0x47) = 1;
        *(u8 *)(cach + 0x4B) = *(u8 *)(cur + 0x48) | 0xF0;
        *(u8 *)(cach + 0x47) = ((s32)D_80126D20 << 7) / r;
        goto LC88;
    }

    if (*(u8 *)(cach + 0x4B) >= 0xF0) {
        *(u8 *)(cach + 0x4B) = 0;
    }

    if (D_80126CE0 != 0) {
        g = *(u16 *)&D_80126CE0;
        *(u8 *)(cach + 0x4B) = g;
        chg2 = (*(u8 *)(cach + 0x47) != (u8)g);
    } else {
        g = *(u8 *)(cur + 0x47);
        chg2 = 0;
        if (*(u8 *)(cach + 0x47) != (u8)g || *(u8 *)(cach + 0x47) == 0x80) {
            chg2 = 1;
        }
        if (*(u8 *)(cur + 0x47) != 0 && *(u8 *)(cach + 0x4B) != 0) {
            *(u8 *)(cach + 0x4B) = 0;
            *(u8 *)(cach + 0x47) = *(u8 *)(cur + 0x47);
        }
    }

    if (chg2 == 0 && chg == 0) {
        if (*(u8 *)(flag + 0x47) == 0) goto LC88;
        if (chg == 0) {
            *(u8 *)(flag + 0x47) = 0;
            goto LC88;
        }
    }
    {
        u8 c47 = *(u8 *)(cach + 0x47);
        if (c47 < (s16)g) {
            *(u8 *)(cach + 0x47) = g;
        } else {
            if ((s16)g != 0) {
                *(u8 *)(cach + 0x47) = c47 - 3;
            } else {
                *(u8 *)(cach + 0x47) = c47 - 8;
            }
            c47 = *(u8 *)(cach + 0x47);
            if (c47 == 0 || c47 > 0x80) {
                *(u8 *)(cach + 0x47) = 0;
                *(u8 *)(cach + 0x4B) = 0;
            } else if (c47 < (s16)g) {
                *(u8 *)(cach + 0x47) = g;
            }
        }
        *(u8 *)(flag + 0x47) = 1;
    }
LC88:
    b = ((param_1 << 16) >> 14) + st;
    {
        s32 t = (*(u8 *)(st + 7) != 0) << 8;
        s32 t5 = t + 5;
        s32 t9 = t + 9;
        *(s16 *)(*(s32 *)(b + 0x28) + 0x32) = *(u16 *)(st + 0x12) + t5;
        func_801775E0(*(s32 *)(b + 0x28) + 0x64,
                      (s16)(*(u16 *)(st + 0x12) + t9));
    }
}
