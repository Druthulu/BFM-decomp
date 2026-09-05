/* func_80039308 (main, src/800_c.c, 518 ins) -- NEAR, closeness 34 (518 ins, exact length).
 *
 * S79 pass: 115 -> 34.  Prior best was 115 (S77, .run/S77w/opus/func_80039308.c); the
 * structure and the symbol map come from there and from the .s itself.  Every number below
 * was measured with tools/match_one.py against asm/nonmatchings/800_c/func_80039308.s.
 *
 * WHAT MOVED IT (each byte-witnessed, in the order it was found):
 *
 * 1. THE PRIOR DRAFT SHARED ONE LOCAL BETWEEN THE TWO BRANCHES OF `if (b3)`, AND THAT MERGE
 *    IS WHAT WRECKED THE ALLOCATION.  `tb`, `tmp`, `off`, `i`, `p`, `idx` were each used in
 *    BOTH the b3!=0 arm and the else arm, so each had one long live range, a tiny
 *    allocno priority (log2(refs)*refs*size / live_length) and therefore a late hard reg.
 *    The target gives the two arms DIFFERENT registers for each of them, i.e. they are
 *    separate pseudos in the original.  Splitting them, one at a time, measuring each:
 *      - `tbl` for the arm-1 sample-table pointer (was `tb`)            115 -> 98
 *        NOTE the split alone is a REGRESSION (364 @ 519 ins): it delays the
 *        `lw 0x1DC` past the `lh` and grows a load-delay nop.  It only pays once the
 *        offset is folded into the same expression (item 5).
 *      - `tmp2` for the second `tmp` use, and inlining the arm-1 offset    98 -> 95
 *      - `j` for the else loop counter + `idx1`/`r` reused there            75 -> 63
 *        (the else arm's slot-clear is the SAME inlined func_8003916C as the arm-1 one,
 *         and the target proves it: both use $a0 for the pointer and $a1 for the (s16)
 *         index.  Reusing arm-1's `r`/`idx1` there is what puts them on $a0/$a1.)
 *    Direction matters: splitting the ELSE arm's `p` into a new `p2` is -20 (95 -> 115),
 *    splitting `j` WITHOUT also reusing `r`/`idx1` is -14.  Only the combination pays.
 *
 * 2. NAME THE `*26` PRODUCT IN THE SLOT-CLEAR -- COPY THE MATCHED NEIGHBOUR VERBATIM.
 *    src/800_c.c:func_8003916C is the same inlined body and is already banked; it writes
 *      off = *(s16 *)&a1[6] * 26;
 *      *(u8 *)(*(u32 *)&a1[0x50] + off + arg0 + 0x23) = 0;
 *    With the product inline, gcc ties the sum to the SHIFT chain's register; with the
 *    product in a local it ties it to the `lw`, which is what the target does.  95 -> 90.
 *    (Swapping the two addends in the expression does nothing -- fold canonicalises it back.)
 *
 * 3. `v = a * b >> 7;` AND `v = a * b; v >>= 7;` ARE DIFFERENT CODE.  One statement makes
 *    the mult result its own pseudo (`mflo $s7` + `sra $a0,$s7,7`); two statements put the
 *    mflo straight into the shift's register (`mflo $a0` + `sra $a0,$a0,7`), which is the
 *    target.  Splitting the three pan/volume products: 90 -> 84, and splitting the table
 *    lookup off its multiply (`v = D_8006ACD8[v]; v = v * ...;`) another 84 -> 82.
 *
 * 4. `vv = vol & 0xFFFF;` vs `vv = (u16)vol;` -- SAME VALUE, 14 INSTRUCTIONS APART.
 *    The mask spelling keeps `vv` in $v1 and lets reorg steal the branch delay slot with
 *    the fall-through `srl`; the cast spelling puts it in $a0, schedules the `andi` between
 *    the two `sb`s and fills the delay slot with the store, exactly as the target.  58 -> 44.
 *    This is the single largest one-token win in the function.
 *
 * 5. FOLD A POINTER ADD INTO THE EXPRESSION THAT USES IT.  `tbl = ...; tbl += (tmp>>1)*0x10;`
 *    allocates `tmp` to $v1 and the offset to $v0; `tbl = ... + (tmp>>1)*0x10;` (one
 *    expression) swaps them onto the target's $v0/$v1.  44 -> 37, seven instructions.
 *
 * 6. THE POST-GUARD STORES USE THE POINTER COMPUTED AT THE TOP OF THE BLOCK, NOT A COPY.
 *    The prior draft wrote `wp = r;` and stored through `wp`; cse propagates `r` into ten of
 *    the eleven uses, so they came out on $a0 while the target has $a2.  Storing through the
 *    ORIGINAL `p` puts all eleven on $a2 directly.  82 -> 75.
 *
 * 7. FORCING THE OPERAND ORDER OF A READ-MODIFY-WRITE PAIR.  `D_800C7D20 &= ~mm[j];`
 *    expands the LHS load before the RHS load; naming the complement first
 *      mv = ~mm[j];  D_800C7D20 &= mv;  mv = mm[j];  D_800A2B98 |= mv;
 *    reorders the RTL so the C7D20 load/nor/and land in the target's order.  37 -> 34.
 *    (Two temps -- `mv` and `mv2` -- instead of reusing one lets cse merge the two loads
 *    into one and costs 2 instructions; the reuse of `mv` is load-bearing.)
 *
 * 8. THE INHERITED S148-C PRIORITY SLIDER IS NOW INERT AND WAS DELETED.  The prior draft
 *    carried `__asm__ ("" :: "r"(arg0), "r"(arg0), "r"(t7));` in the depth-2 loop, a tuned
 *    dose worth 26 points THEN.  Swept 0..4 x 0..3 against this body: (0,0) == (1,0) ==
 *    (2,0) == (2,1) == 34, everything else worse.  A zero-byte slider tuned against an old
 *    residual is dead weight once the residual changes -- re-sweep it, do not inherit it.
 *    Same for two of the three register pins: b4/$s4 and u26/$s6 are now inert (34 either
 *    way) and were DELETED; only `vbase`/$s2 still earns its keep (34 pinned, 60 unpinned).
 *
 * MEASURED INERT ON THIS BODY (do not re-try):
 *  - the `andi $v1,$s4,0xff` vs `addu $v1,$s4,$zero` at idx 39.  gcc-2.7.2 does NOT fold
 *    `(and (reg) 255)` to a move even when the reg's only set is a `lbu` -- reproduced in a
 *    12-line standalone (.run/S79w/opus/x308/mini/): `b & 0xFF`, `(u8)b`, `b & 0xFFFF`,
 *    `(u16)b`, `b & 0x1FF` ALL emit `andi`; `b & 0x7FFFFFFF` and `((u32)b<<16)>>16` emit
 *    nothing at all.  The ONLY spelling that produces a surviving `move` is a copy at a
 *    JOIN -- `if (c) n = b; else n = b;` -- because cse cannot carry the equivalence into a
 *    block with two predecessors.  That DOES reproduce the target instruction, but only
 *    with `b4` UNPINNED (a hard-reg source is always folded), and unpinning shifts the whole
 *    callee-saved file ($s4 <-> $s1, the hoisted 1 and 2 constants) -- net 44 vs 44, then
 *    34 vs 34 with `register s32 n __asm__("$3")` added.  Conserved, so the plainer C wins.
 *  - the 20-instruction else-branch mask block (idx 477-498) is the same multiset in a
 *    different sched order.  Fifteen spellings measured (VMask alias cast, named address,
 *    named value temps, both operand orders on the `&`/`|`, hoisting the D_800762B0 load to
 *    three positions, dropping the `two` local, reordering/moving the three S349 dead
 *    resets): every one is 34 or worse.  All three S349 resets are still load-bearing
 *    (dropping `two` = 80, `cb` = 60, `mm` = 97 @ 517 ins).
 *  - `k2` on $s6 where the target has $t0 (4 diffs).  Priority sliders on k2 at doses 1/2/3
 *    change the object but not that register; pinning k2 to $t0 is 104, pinning tb to $t1
 *    is 40, reusing arm-1's `t0`/`t1` locals is 66/70.
 *  - `sv` on $v0 where the target has $s7: pinning it to $23 is 503 @ 522 ins.
 *  - the missing `addu $a2,$a0,$zero` at idx 391 CAN be restored with `p = r;` in both arms
 *    of the guard, but it costs two other diffs in the clear block -- conserved at 34.
 *
 * RESIDUAL (34, all register-permutation / sched order, no structural difference):
 *   head  7  idx 38-42 the andi + a 3-slot sched rotation, idx 49-50 a preheader swap
 *   mid   3  idx 212-215 which scratch holds the two pan bytes
 *   tail  4  idx 390/391 the wp copy, idx 412/415 sv on $v0 vs $s7
 *   else 20  idx 440-452 k2/tb on $s6/$t0 vs $t0/$t1, idx 477-498 the mask-block sched
 *
 * Relocation audit (SYS law 1c): the 16 D_ symbols this draft names are exactly the 16
 * %hi/%lo operands of this .s -- no extras, none invented, none carried from a neighbour.
 * The declarations are copied verbatim from src/800_c.c (D_800762B0 u8*, D_800762B4 u8[],
 * D_80073140 s32[], D_8006AB30/D_8006ABD8 u16[], D_800A2B98/D_800A2BA0/D_800C7D20/
 * D_800C7D2C s32, D_800C6DD0 u8[]).  The function is a leaf (0 jal), so there is no
 * S263 call-arity axis here.
 */
typedef struct { u32 w; } VMask;

extern u8 *D_800762B0;
extern u8 D_800762B3[];
extern u8 D_800762B4[];
extern s32 D_80073140[];
extern u16 D_8006AB30[];
extern u16 D_8006ABD8[];
extern u16 D_8006ACD8[];
extern s16 D_8006AF08[];
extern s32 D_800A2B98;
extern s32 D_800A2BA0;
extern u8 D_800A4F19;
extern u8 D_800C6DD0[];
extern u8 D_800C6DD4[];
extern u8 D_800C6DDD[];
extern s32 D_800C7D20;
extern s32 D_800C7D2C;

void func_80039308(u8 **arg0, s16 arg1) {
    u16 sav[8];
    u8 *src;
    u8 *s0;
    u8 *t9;
    u8 *a3;
    u8 *t1;
    u8 *a1p;
    u8 *a0p;
    u8 *p;
    u8 *q;
    u8 *r;
    u8 *tb;
    s32 b2;
    s32 b3;
    s32 b4;
    s32 bb;
    u8 t3;
    u8 t5;
    s16 t7;
    s16 cc;
    s32 i;
    s32 cnt;
    s32 a2;
    s32 t0;
    s32 v1;
    s32 res;
    s32 idx1;
    u8 *cb;
    s32 *mm;
    s32 two;
    s32 sv;
    s32 tmp;
    s32 pan;
    s32 pan1;
    s32 x;
    s32 s17;
    s32 s18;
    s32 v;
    s32 u26;
    s32 n;
    register s32 vbase __asm__("$18");
    s32 off;
    u32 t2;
    u32 vol;
    u32 vv;
    u32 prod;
    s32 k2;
    u8 *tbl;
    s32 tmp2;
    s32 coff;
    s32 xoff;
    s32 mv;
    s32 j;

    src = *arg0;
    *arg0 = src + 1;
    b2 = src[0];
    *arg0 = src + 2;
    b3 = src[1];

    sav[0] = arg1;
    if (b3 != 0) {
        if ((((u8 *)arg0 + arg1)[0x1BA] & 1) == 0) {
            s0 = (u8 *)arg0 + (arg1 * 26 + 26);
            i = 0;
            b4 = *s0;
            n = b4 & 0xFF;
            cnt = *(*(u8 **)((u8 *)arg0 + 0x1DC) + n * 0x10);
            t9 = *(u8 **)((u8 *)arg0 + 0x1E0) + n * 0x200;
            if (cnt != 0) {
                u26 = b2;
                vbase = b2 * 0x100;
                do {
                    if (u26 >= t9[6] && u26 <= t9[7]) {
                        t2 = 0x100;
                        t3 = 0;
                        t5 = 0;
                        t7 = -1;
                        t0 = 0;
                        a3 = D_800C6DDD;
                        a2 = 1;
                        t1 = D_800762B0;
                        do {
                            if (a3[0x4E] != 0) {
                                bb = a3[0];
                                if ((u8)bb < (t2 & 0xFF)) {
                                    t3 = a2;
                                    t2 = bb & 0xFF;
                                } else if ((u8)bb == (t2 & 0xFF)) {
                                    if (D_800762B3[a2] == 0 && *t1 == 2) {
                                        t3 = a2;
                                    }
                                }
                            } else {
                                t5 = 1;
                                t7 = t0;
                                break;
                            }
                            a2++;
                            t1++;
                            t0++;
                            a3 += 0x60;
                        } while (t0 < 0x10);
                        if (t5 == 0) {
                            if (*t9 >= t2) {
                                t7 = t3 - 1;
                            } else {
                                a1p = D_800762B0;
                                a0p = D_800762B4;
                                v1 = 0;
                                while (v1 < 0x10) {
                                    if (*a1p == 2 && *a0p == 0) {
                                        res = v1;
                                        goto found;
                                    }
                                    v1++;
                                    a1p++;
                                    a0p++;
                                }
                                res = -1;
                            found:
                                t7 = res;
                            }
                        }
                        if (t7 >= 0) {
                            p = &D_800C6DD0[t7 * 0x60];
                            q = p + 0x10;
                            p[0xD] = *t9;
                            if (p[0x5C] != 0 && *(s16 *)(p + 8) == b4 && p[0xC] == i &&
                                *(s16 *)(*(u32 *)(p + 0x50) + 0x1EC) == *(s16 *)((u8 *)arg0 + 0x1EC)) {
                                *(s32 *)(p + 0x14) = 0x13;
                            } else {
                                tmp = *(s16 *)(t9 + 0x16) - 1;
                                tbl = *(u8 **)((u8 *)arg0 + 0x1DC) + (tmp >> 1) * 0x10;
                                if (tmp & 1) {
                                    x = *(s16 *)(tbl + 0xE) << 3;
                                } else {
                                    x = *(s16 *)(tbl + 0xC) << 3;
                                }
                                *(s32 *)(q + 0x1C) = x;
                                *(u16 *)(q + 0x3A) = *(u16 *)(t9 + 0x10);
                                *(u16 *)(q + 0x3C) = *(u16 *)(t9 + 0x12);
                                *(s32 *)(q + 4) = 0x6009F;
                            }
                            v = b3 * s0[1];
                            v >>= 7;
                            v = v * t9[2];
                            v >>= 7;
                            v = D_8006ACD8[v];
                            v = v * *(s16 *)((u8 *)arg0 + 0x1F2);
                            v >>= 7;
                            if (D_800A4F19 != 0) {
                                pan1 = s0[4] + t9[3] - 0x40;
                                cc = pan1;
                                if (pan1 < 0) {
                                    cc = 0;
                                } else if (pan1 >= 0x80) {
                                    cc = 0x7F;
                                }
                                if (cc > 0) {
                                    s17 = v * D_8006AF08[0x80 - cc] * 4 >> 16;
                                } else {
                                    s17 = (s16)v;
                                }
                                s18 = v * D_8006AF08[cc] * 4 >> 16;
                            } else {
                                s17 = s18 = v * 0x2D41 >> 14;
                            }
                            *(s16 *)(q + 8) = (u32)((s16)s17 * *(s16 *)((u8 *)arg0 + 0x10)) >> 14;
                            *(s16 *)(q + 0xA) = (u32)((s16)s18 * *(s16 *)((u8 *)arg0 + 0x10)) >> 14;
                            pan = *(s16 *)(s0 + 2);
                            vol = vbase;
                            if (pan >= 0x41) {
                                vol = vbase + (u32)((pan - 0x40) * t9[0xD] * 4);
                            } else if (pan < 0x40) {
                                vol = vbase - (u32)((0x40 - pan) * t9[0xC] * 4);
                            }
                            tmp2 = t9[4] * 0x100 - t9[5];
                            *(s32 *)(p + 0x54) = tmp2;
                            tmp2 -= 0x3C00;
                            vol -= (u32)tmp2;
                            p[0x58] = t9[0xC];
                            p[0x59] = t9[0xD];
                            vv = (u16)vol;
                            if (vv >= 0x5301) {
                                *(s16 *)(q + 0x14) = 0x3FFF;
                            } else {
                                prod = D_8006AB30[vv >> 8];
                                prod *= D_8006ABD8[(vv & 0xFE) / 2];
                                *(s16 *)(q + 0x14) = prod >> 15;
                            }
                            p[0x5D] = 1;
                            D_800A2B98 &= ~((VMask *)q)->w;
                            D_800C7D20 |= ((VMask *)q)->w;
                            D_800762B4[t7] = 1;
                            if (t9[1] & 4) {
                                D_800A2BA0 &= ~((VMask *)q)->w;
                                D_800C7D2C |= ((VMask *)q)->w;
                            } else {
                                D_800C7D2C &= ~((VMask *)q)->w;
                                D_800A2BA0 |= ((VMask *)q)->w;
                            }
                            idx1 = t7;
                            r = &D_800C6DD0[idx1 * 0x60];
                            if (r[0x5A] != 0) {
                                coff = *(s16 *)&r[6] * 26;
                                *(u8 *)(*(u32 *)&r[0x50] + coff + idx1 + 0x23) = 0;
                                r[0x5A] = 0;
                            }
                            *(s0 + idx1 + 9) = 1;
                            *(s16 *)(p + 4) = b2;
                            *(s16 *)(p + 8) = b4;
                            p[0xC] = i;
                            p[0x5C] = 1;
                            *(s16 *)(p + 0) = s17;
                            *(s16 *)(p + 2) = s18;
                            sv = sav[0];
                            *(u32 *)(p + 0x50) = (u32)arg0;
                            p[0x5B] = 1;
                            *(s16 *)(p + 6) = sv;
                            if (*((u8 *)arg0 + 0x1F4) != 0) {
                                p[0x5A] = 2;
                            } else {
                                p[0x5A] = 1;
                            }
                        }
                    }
                    i++;
                    t9 += 0x20;
                } while (i < cnt);
            }
        }
    } else {
        j = 0;
        tb = (u8 *)arg0 + arg1 * 26;
        k2 = b2;
        off = 0;
        do {
            if ((tb + j)[0x23] != 0 && *(s16 *)&D_800C6DD4[off] == k2) {
                idx1 = (s16)j;
                xoff = idx1 * 0x60;
                cb = D_800C6DD0;
                r = cb + xoff;
                if (r[0x5A] != 0) {
                    coff = *(s16 *)&r[6] * 26;
                    *(u8 *)(*(u32 *)&r[0x50] + coff + idx1 + 0x23) = 0;
                    r[0x5A] = 0;
                }
                mm = D_80073140;
                mv = ~mm[j];
                D_800C7D20 &= mv;
                mv = mm[j];
                D_800A2B98 |= mv;
                two = 2;
                D_800762B0[j] = two;
                D_800762B4[j] = 0;
            }
            cb = 0;
            mm = 0;
            two = 0;
            j++;
            off += 0x60;
        } while (j < 0x10);
    }
}
