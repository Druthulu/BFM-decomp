void func_8017E73C(s32 a0) {

    extern u8 D_80188950[];
    extern s32 D_801B7834;
    extern s32  D_80188BB8;
    /* §135-6 dead locals: the target frame is 0x50 = args(0x20, func_80146A6C takes 7)
       + var(0x20) + gp(0x10).  Only 0x10 of that 0x20 is claimed by real spills, so the
       original carried 16 bytes of locals it no longer uses.  Without this the frame
       lands at 0x40 and every sp-relative immediate drifts by the same constant. */
    s32 dead[4];
    s32 flags;
    s32 v;
    s32 s0;
    s32 ret;
    s16 spd;
    s32 m;
    s32 raw;

    s0 = a0;
    ret = 0;
    /* §21 zero-byte re-tie.  The target reads the RAW return register for the first test
       (`andi $v0,$v0,0x6000`) while the saved copy lives in $s1 -- i.e. gcc-2.7.2 kept TWO
       pseudos: a local one that dies at the `andi` and a global one that survives the calls.
       Every source form of `flags = call(); if (flags & ...)` collapses them (cse canon_reg
       substitutes one for the other, so the surviving allocno is the GLOBAL and the `andi`
       reads $s1).  Re-tying the *global* after the copy makes the pair opaque to cse; `raw`
       stays local and takes $v0, which also flips the $v0/$v1 pair on the following
       compare constant.  8 no-barrier variants tested (temp var, `register` pin on either
       side, inverted test, subtract-form compare): all land on the identical 3-insn
       permutation. */
    raw = ((s32 (*)(s32))func_8012CBA4)(a0);
    flags = raw;

    /* `m` blocks fold_truthop from merging the two bitfield tests below into a single
       `andi $v1,$s1,0xe000` -- the target keeps `& 0x8000` and `& 0x6000` separate. */
    if ((raw & 0x6000) != 0x2000) {
        func_8012ADE4((u8 *)s0);
        func_8017EE3C(s0);
        if (*(s32 *)(s0 + 0x1C) >= 9) {
            *(s32 *)(s0 + 0x1C) = *(s32 *)(s0 + 0x1C) - 8;
        }
    }

    m = flags & 0x8000;
    if (m != 0 || (flags & 0x6000) != 0x2000) {
        if (*(s16 *)(s0 + 0x106) == 0) {
            *(s16 *)(s0 + 0x106) = 0x111;
        }
        if (*(s32 *)(s0 + 0x1C) >= 5) {
            *(s32 *)(s0 + 0x1C) = *(s32 *)(s0 + 0x1C) - 4;
        }
        *(u16 *)(s0 + 0x108) = *(u16 *)(s0 + 0x108) + 1;
    } else {
        *(s16 *)(s0 + 0x106) = 0;
    }

    v = *(s32 *)(s0 + 0x1C) - 1;
    *(s32 *)(s0 + 0x1C) = v;
    if (v != 0) {
        if ((v & 3) == 0) {
            if (func_8012BC60((void *)(s0 + 4), (void *)&D_801B7834) < 0x900) {
                *(s32 *)(s0 + 0x1C) = 1;
            }
        }
        /* The func_8017ECEC call is written in BOTH arms on purpose: gcc-2.7.2's sched1
           interleaves the $a0/$a2 arg setup into each arm's load-delay slots, and only
           then does cross-jumping merge the common tail (it stops at the differing `sh`).
           A single call after the if/else leaves those slots as nops (+2 ins, -1 length)
           and forces the arm pointer into $a0, wrecking the whole block's allocation.
           `ang0`/`ang1` are per-arm locals (§136 L1): one shared local becomes a GLOBAL
           allocno (2 deaths) and loses $a1.  Both must be s32 -- writing the expression
           inline lets convert_to_integer narrow it to UNSIGNED HImode (the u16 operand),
           which emits `ori $a1,$zero,0xfffd` instead of `addiu $a1,$zero,-0x3` + sll/sra. */
        if (*(s16 *)(s0 + 0x106) == 0) {
            s32 r = func_8012BB3C(s0 + 4, (s32)&D_801B7834,
                                  *(s16 *)(*(s32 *)(s0 + 0x20) + 0x12), 8);
            s32 p = *(s32 *)(s0 + 0x20);
            s32 ang0;
            *(s16 *)(p + 0x12) = *(u16 *)(p + 0x12) + r;
            ang0 = -3 - *(u16 *)(s0 + 0x104);
            func_8017ECEC(s0, ang0, 0);
        } else {
            s32 q = *(s32 *)(s0 + 0x20);
            s32 ang1;
            *(s16 *)(q + 0x12) = *(u16 *)(q + 0x12) + *(s16 *)(s0 + 0x106);
            ang1 = -3 - *(u16 *)(s0 + 0x104);
            func_8017ECEC(s0, ang1, 0);
        }
        if (*(s16 *)(s0 + 0x104) != 0) {
            if ((u32)*(s32 *)(s0 + 0x94) < 0xB) {
                *(s32 *)(s0 + 0x94) = *(s32 *)(s0 + 0x94) + 1;
            }
            if ((*(s32 *)(s0 + 0x1C) & 7) == 0) {
                ret = 1;
            }
        }
    } else {
        s16 t;

        func_8012B200((u8 *)s0);
        func_8012A828(s0, D_80188950);
        *(s32 *)(s0 + 0x1C) = 0x14 - (*(s16 *)(s0 + 0x104) << 1);
        if (((s32 (*)(s32))func_8012BD14)(s0) <= 0x23FFF) {
            *(s16 *)(s0 + 0x102) = 0xA - *(u16 *)(s0 + 0x104);
        } else {
            *(s16 *)(s0 + 0x102) = 0;
        }
        t = *(s16 *)(s0 + 0x104);
        if (t != 0) {
            t = t - 4;
            *(s16 *)(s0 + 0x104) = t;
            if (t < 0) {
                *(s16 *)(s0 + 0x104) = 0;
            }
        }
        *(s16 *)(s0 + 0x2) = 1;
    }

    if (*(s16 *)(s0 + 0xFC) != 0) {
        if (func_8016F1AC() != 0) {
            /* §17/idiom-7: 0x801891F4 is INTERIOR to D_801891D8 and has no symbol, but the
               target does NOT build it with its own %hi/%lo -- it derives it from the
               D_80188BB8 base already in $a2 (`addiu $a1,$a2,-0x1C`).  Caching the base in
               a POINTER LOCAL reproduces that; `(s32)&D_80188BB8 - 0x1C` folds into a
               second lui/addiu pair and splits the store into lui+sw($at). */
            s32 *tbl = &D_80188BB8;

            *(s16 *)(s0 + 0x10A) = 0;
            *tbl = *(u16 *)(s0 + 0x88) | (*(s16 *)(s0 + 0x8C) << 16);
            func_80178B70(s0, (s32)tbl - 0x1C);
            *(s16 *)(s0 + 0x98) = 0;
            *(s32 *)(s0 + 0x1C) = 0x14;
            func_8012B200((u8 *)s0);
            *(s16 *)(s0 + 0x2) = 3;
        }
        return;
    }

    if (*(u16 *)(s0 + 0x5E) != 0) {
        *(s16 *)(*(s32 *)(s0 + 0x20) + 0x12) = *(u16 *)(s0 + 0x62);
        func_8017ECEC(s0, -0xF, 0);
        func_8017ED60((s16 *)s0);
        *(s16 *)(s0 + 0x5E) = 0;
        *(s16 *)(s0 + 0x104) = 0xA;
        ret = 1;
    } else {
        s32 d = ((s32 (*)(s32))func_8012BD14)(s0);

        if (d <= 0xFFFF) {
            spd = 0;
            if (d >= 0x4000) {
                spd = (func_8012BDBC(s0, 0x500) != 0) << 2;
            } else if (d >= 0x1000) {
                if (func_8012BDBC(s0, 0x680) != 0) {
                    spd = 7;
                }
            } else {
                spd = 9;
            }
            if (spd != 0) {
                func_8017ED60((s16 *)s0);
                if (*(s16 *)(s0 + 0x104) == 0) {
                    *(s16 *)(*(s32 *)(s0 + 0x20) + 0x12) = func_8012B864(s0) - 0x800;
                    ret = 1;
                }
                *(s16 *)(s0 + 0x104) = spd;
                func_8017ECEC(s0, -7 - spd, 0);
            }
        }
    }

    /* Same §21 re-tie as the prologue, mirrored: the target evaluates the flag through a
       LOCAL copy (`addu $v0,$s2,$zero`, which reorg then duplicates into the two branch
       delay slots) rather than testing $s2 directly.  A plain `fire = ret` is copy-
       propagated away; re-tying the global keeps the pair distinct.  Without it the three
       copies vanish and everything from .L8017CD18 on drifts by 2 instructions. */
    {
        s32 fire = ret;
        if (fire != 0) {
            func_80146A6C(2, (void *)s0, 0, 0, 0, 2, 0);
        }
    }
}
