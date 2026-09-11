void func_8017E73C(s32 a0) {

    extern u8 D_80188950[];
    extern s32 D_801B7834;
    extern s32  D_80188BB8;
    /* §135-6 dead locals: the target frame is 0x50 = args(0x20, func_80146A6C takes 7)
       + var(0x20) + gp(0x10).  Only 0x10 of that 0x20 is claimed -- by two phantom reload
       slots (the sign extensions of the 0x106 and 0x104 halfwords, which combine folds into
       `lh` while the pseudos keep stale ref counts) -- so the original carried 16 bytes of
       locals it no longer uses.  Without this the frame lands at 0x40. */
    s32 dead[4];
    u16 flags;
    s32 v;
    s16 ret;
    s16 spd;
    s32 m;

    ret = 0;
    /* `flags` is a u16 (only its low 16 bits are ever tested): the copy into it is a
       HImode SUBREG move that cse's (set REG0 REG1) swap cannot take, so the call result
       stays its own local pseudo -- the first test reads it straight from $v0 while the
       saved copy lives in $s1 (`move s1,v0; andi v0,v0,0x6000`). */
    flags = ((s32 (*)(s32))func_8012CBA4)(a0);

    /* `m` blocks fold_truthop from merging the two bitfield tests below into a single
       `andi $v1,$s1,0xe000` -- the target keeps `& 0x8000` and `& 0x6000` separate. */
    if ((flags & 0x6000) != 0x2000) {
        func_8012ADE4((u8 *)a0);
        func_8017EE3C(a0);
        if (*(s32 *)(a0 + 0x1C) >= 9) {
            *(s32 *)(a0 + 0x1C) = *(s32 *)(a0 + 0x1C) - 8;
        }
    }

    m = flags & 0x8000;
    if (m != 0 || (flags & 0x6000) != 0x2000) {
        if (*(s16 *)(a0 + 0x106) == 0) {
            *(s16 *)(a0 + 0x106) = 0x111;
        }
        if (*(s32 *)(a0 + 0x1C) >= 5) {
            *(s32 *)(a0 + 0x1C) = *(s32 *)(a0 + 0x1C) - 4;
        }
        *(u16 *)(a0 + 0x108) = *(u16 *)(a0 + 0x108) + 1;
    } else {
        *(s16 *)(a0 + 0x106) = 0;
    }

    v = *(s32 *)(a0 + 0x1C) - 1;
    *(s32 *)(a0 + 0x1C) = v;
    if (v != 0) {
        if ((v & 3) == 0) {
            if (func_8012BC60((void *)(a0 + 4), (void *)&D_801B7834) < 0x900) {
                *(s32 *)(a0 + 0x1C) = 1;
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
        if (*(s16 *)(a0 + 0x106) == 0) {
            s32 r = func_8012BB3C(a0 + 4, (s32)&D_801B7834,
                                  *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12), 8);
            s32 p = *(s32 *)(a0 + 0x20);
            s32 ang0;
            *(s16 *)(p + 0x12) = *(u16 *)(p + 0x12) + r;
            ang0 = -3 - *(u16 *)(a0 + 0x104);
            func_8017ECEC(a0, ang0, 0);
        } else {
            s32 q = *(s32 *)(a0 + 0x20);
            s32 ang1;
            *(s16 *)(q + 0x12) = *(u16 *)(q + 0x12) + *(s16 *)(a0 + 0x106);
            ang1 = -3 - *(u16 *)(a0 + 0x104);
            func_8017ECEC(a0, ang1, 0);
        }
        if (*(s16 *)(a0 + 0x104) != 0) {
            if ((u32)*(s32 *)(a0 + 0x94) < 0xB) {
                *(s32 *)(a0 + 0x94) = *(s32 *)(a0 + 0x94) + 1;
            }
            if ((*(s32 *)(a0 + 0x1C) & 7) == 0) {
                ret = 1;
            }
        }
    } else {
        s16 t;

        func_8012B200((u8 *)a0);
        func_8012A828(a0, D_80188950);
        *(s32 *)(a0 + 0x1C) = 0x14 - (*(s16 *)(a0 + 0x104) << 1);
        if (((s32 (*)(s32))func_8012BD14)(a0) <= 0x23FFF) {
            *(s16 *)(a0 + 0x102) = 0xA - *(u16 *)(a0 + 0x104);
        } else {
            *(s16 *)(a0 + 0x102) = 0;
        }
        t = *(s16 *)(a0 + 0x104);
        if (t != 0) {
            t = t - 4;
            *(s16 *)(a0 + 0x104) = t;
            if (t < 0) {
                *(s16 *)(a0 + 0x104) = 0;
            }
        }
        *(s16 *)(a0 + 0x2) = 1;
    }

    if (*(s16 *)(a0 + 0xFC) != 0) {
        if (func_8016F1AC() != 0) {
            /* §17/idiom-7: 0x801891F4 is INTERIOR to D_801891D8 and has no symbol, but the
               target does NOT build it with its own %hi/%lo -- it derives it from the
               D_80188BB8 base already in $a2 (`addiu $a1,$a2,-0x1C`).  Caching the base in
               a POINTER LOCAL reproduces that; `(s32)&D_80188BB8 - 0x1C` folds into a
               second lui/addiu pair and splits the store into lui+sw($at). */
            s32 *tbl = &D_80188BB8;

            *(s16 *)(a0 + 0x10A) = 0;
            *tbl = *(u16 *)(a0 + 0x88) | (*(s16 *)(a0 + 0x8C) << 16);
            func_80178B70(a0, (s32)tbl - 0x1C);
            *(s16 *)(a0 + 0x98) = 0;
            *(s32 *)(a0 + 0x1C) = 0x14;
            func_8012B200((u8 *)a0);
            *(s16 *)(a0 + 0x2) = 3;
        }
        return;
    }

    if (*(u16 *)(a0 + 0x5E) != 0) {
        *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) = *(u16 *)(a0 + 0x62);
        func_8017ECEC(a0, -0xF, 0);
        func_8017ED60((s16 *)a0);
        *(s16 *)(a0 + 0x5E) = 0;
        *(s16 *)(a0 + 0x104) = 0xA;
        ret = 1;
    } else {
        s32 d = ((s32 (*)(s32))func_8012BD14)(a0);

        if (d <= 0xFFFF) {
            spd = 0;
            if (d >= 0x4000) {
                spd = (func_8012BDBC(a0, 0x500) != 0) << 2;
            } else if (d >= 0x1000) {
                if (func_8012BDBC(a0, 0x680) != 0) {
                    spd = 7;
                }
            } else {
                spd = 9;
            }
            if (spd != 0) {
                func_8017ED60((s16 *)a0);
                if (*(s16 *)(a0 + 0x104) == 0) {
                    *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12) = func_8012B864(a0) - 0x800;
                    ret = 1;
                }
                *(s16 *)(a0 + 0x104) = spd;
                func_8017ECEC(a0, -7 - spd, 0);
            }
        }
    }

    /* `ret` is a short: the test sign-extends it, combine reduces the extension of a 0/1
       value to a plain copy (`move v0,s2`, which reorg also puts in the two delay slots). */
    if (ret != 0) {
        func_80146A6C(2, (void *)a0, 0, 0, 0, 2, 0);
    }
}
