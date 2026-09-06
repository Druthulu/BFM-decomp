/* func_80039308 (main, src/800_c.c, 518 ins) -- NEAR, closeness 17 (518 ins, exact length).
 *
 * P32/T3 pass: 34 -> 17, starting from the S79 body (.run/S79w/opus/func_80039308.c).
 * Every number below was measured with tools/match_one.py against
 * asm/nonmatchings/800_c/func_80039308.s; the final body was re-checked with
 * tools/rtu_match.py in the real TU (same 17, no declaration conflicts).
 *
 * WHAT MOVED IT (each byte-witnessed, in the order it was found):
 *
 * 1. `s16 b4;` + `n = b4;`  (was `s32 b4; n = b4 & 0xFF;`)                     34 -> 33
 *    The target's `addu $v1,$s4,$zero` at idx 39 is a WIDENING COPY, not a mask.  A short
 *    whose only def is an `lbu` needs no extension instruction, but gcc-2.7.2 still emits
 *    the (set (reg n) (reg b4)) move and cannot coalesce it (b4 stays live, n is killed by
 *    `sll $v1,$v1,9`).  Measured INERT for this instruction: `b4 & 0xFF`, `(u8)b4`,
 *    `(s32)(u8)b4` (all `andi`); `n = b4` with b4 an s32 or a u8, `n = *s0`, `n = s0[0]`,
 *    `n = (u8)*s0` (all folded away -> 517 ins).  The s16 declaration is the whole trick.
 *
 * 2. SPLIT THE PAN SUM OFF ITS -0x40.  `pan1 = s0[4] + t9[3]; pan1 -= 0x40;` instead of
 *    one expression ties the sum's destination to the SECOND load's register, which is what
 *    the target does (`addu $v0,$a1,$v0`).  33 -> 32.
 *
 * 3. THE FIRST PAN LOAD MUST LAND IN $a1 -- REUSE A DEAD LOCAL TO PUT IT THERE.
 *    `bb = s0[4]; pan1 = bb + t9[3]; ...`, where `bb` is the depth-2 loop's own (dead) temp,
 *    shares $a1 with `cc`, exactly as the target does.  32 -> 30.  A fresh temp, `cc`, `x`
 *    and `res` were each measured: 47, 32, 35, 36.  THE VARIABLE'S IDENTITY IS THE LEVER --
 *    which dead local you reuse decides the hard register.
 *
 * 4. MERGE THE arm-1 `sav[0]` TEMP WITH THE else-arm COMPARE LOCAL (`k2`).            30 -> 26
 *    Sweeping 22 candidates for that temp: only `k2` pays, and it pays in the OTHER arm --
 *    the merge makes k2 a cross-arm global pseudo, so the else head comes out
 *    `addu $t1,$t6,$v0` / `addu $t0,$s5,$zero` (was $t0 / $s2) and idx 440/441/443/452 all
 *    close.  Splitting it back out (with or without a dummy `k2 = b2` def in arm 1) is 21.
 *
 * 5. PIN THE DEAD-RESET CONSTANT LOCAL: `register s32 two __asm__("$2")`.           26 -> 22
 *    `two` is the S349 dead-reset local holding the 2 stored to D_800762B0[j].  Pinned to
 *    $v0 it forces the D_800762B0 pointer load up into the A2B98 sequence and fixes the
 *    `sb $v0,0($v1)` operands.  Swept $2..$8: $2 is the unique optimum (26,26,53,60,58,56).
 *
 * 6. A SECOND MASK TEMP AND AN ADDRESS LOCAL, BOTH PINNED TO $4.                     22 -> 21
 *      mp = &mm[j];  mv = ~*mp;  D_800C7D20 &= mv;  mv2 = *mp;  D_800A2B98 |= mv2;
 *    with `register s32 *mp __asm__("$4")` AND `register s32 mv2 __asm__("$4")`.  Two
 *    variables on ONE hard register is the point: the target's address register dies INTO
 *    the second loaded value (`lw $a0,0x0($a0)`), and only the shared pin reproduces
 *    `lui $v0,%hi(D_80073140) / sll $a0,$a2,2 / addu $a0,$a0,$v0 / lw $v0,0x0($a0)`.
 *    mv2 swept $2..$7: 21,43,17,18,31,25 -- $4 unique.  The mp pin alone is inert.
 *
 * 7. NAME THE BYTE OFFSET IN A DEAD LOCAL AND COMPUTE t9 FIRST.                      21 -> 17
 *      v = n * 0x10;
 *      t9 = *(u8 **)((u8 *)arg0 + 0x1E0) + n * 0x200;
 *      cnt = *(*(u8 **)((u8 *)arg0 + 0x1DC) + v);
 *    Naming the offset takes the MULT out of the MEM address, so the address PLUS keeps its
 *    source operand order (base first) instead of being canonicalised to (mult, base); the
 *    t9-before-cnt order then lets both `sll`s issue before the `addu`.  The whole head
 *    block (idx 38/40/41/42) closes.  25 candidate locals were swept for that offset temp:
 *    `v`, `pan` and `mv2` all give 17 (identical diff sets), `x` 20, `xoff` 21, most 22+.
 *
 * MEASURED INERT ON THIS BODY (do not re-try):
 *  - THE HEAD, before item 7: textual operand swap, `(n << 4)`, `*(u32 *)` casts,
 *    `tbl = base; cnt = tbl[n*0x10]`, `tbl = base; tbl += n*0x10; cnt = *tbl` (this one DOES
 *    fix the RTL operand order but flips $v0/$a0), pinning a named base pointer to $2 or $4,
 *    pinning t9 to $25 (514 ins), pinning an offset local to $4 (85).  27-46 each.
 *  - idx 390/391, the missing `addu $a2,$a0,$zero`: `p = r;` before the guard, a fresh
 *    `p2 = r;`, `p = &D_800C6DD0[idx1*0x60];` recomputed, `p = r + 0`.  cse propagates `r`
 *    into all eleven post-guard stores ($a0) AND flips p/q from $a2/$a3 to $a3/$a2: 57-70.
 *    The copy needs a pseudo cse will not canonicalise away; no C spelling found.
 *  - idx 49/50 (`sll $s2,$s5,8` vs `addiu $s3,$zero,2`, a 2-insn preheader swap): swapping
 *    the u26/vbase statements (35), `vbase = u26 * 0x100` (17, conserved), hoisting the 2
 *    into a named local (520 ins) or a $19-pinned one (520 ins), unpinning vbase (59),
 *    moving vbase into the loop (515 / 262).
 *  - idx 412/415 (`lhu $t0` vs `lhu $s7`): pinning k2 to $21/$22/$23 explodes to 501-504 at
 *    521 ins (a callee-saved pin forces extra copies); $8/$9/$10 are 22/26/26.
 *  - THE MASK BLOCK'S LAST 11 (idx 484-490, 494-497) IS ONE ALIAS FACT.  The second
 *    `D_80073140[j]` load cannot be scheduled above the `D_800C7D20` store from C.  Writing
 *    it as a struct member (`((VMask *)mp)->w`, or typing mp as `VMask *`) DOES hoist it --
 *    gcc-2.7.2's true_dependence returns 0 when MEM_IN_STRUCT_P differs and the OTHER ref's
 *    address does not vary -- but it costs the item-6 allocation: net 20-24, never better.
 *    Putting both loads adjacent lets cse merge them (516/517 ins).  Mixed spellings (array
 *    `D_80073140[j]` for one side, `*mp` for the other) either merge or do not hoist.  Also
 *    swept: mm pinned $2..$5 (the pin IS honoured and conserved at 22), mv pinned $2/$3/$5/$6,
 *    reordering the two read-modify-writes, naming the `~`, both operand orders, moving
 *    `two = 2` and the D_800762B4 store, a named D_800762B0 pointer, a 4th dead reset, and
 *    zero-byte `__asm__ ("" :: "r"(...))` sliders on mm/mv.  All 17 or worse.
 *  - permuter_ils --klass REGALLOC, 2 cycles x 150s @ -j3, seeded with the 22-point body:
 *    best 22, no improvement.  These residuals are cross-block allocation + sched2 order,
 *    outside the permuter's reach.
 *
 * RESIDUAL (17, exact length, same instruction multiset in every cluster):
 *   idx 49,50    2  preheader: the hoisted `2` vs the vbase `sll`, adjacent swap
 *   idx 390,391  2  the un-spellable `addu $a2,$a0,$zero` (reorg duplicates the target insn)
 *   idx 412,415  2  the sav[0] temp on $t0 where the target reuses $s7
 *   idx 484-490  7  the second mask load stuck below the D_800C7D20 store (alias)
 *   idx 494-497  4  the D_800762B0 `addu` scheduled after the A2B98 store instead of before
 *
 * Relocation audit (SYS law 1c): the 16 D_ symbols named here are exactly the 16 %hi/%lo
 * operands of this .s -- verified by grepping both.  The function is a leaf (0 jal), so
 * there is no S263 call-arity axis.  Declarations are copied from src/800_c.c and
 * rtu_match.py confirms the TU accepts them.
 */
typedef struct { u32 w; } VMask;

extern u8 *D_800762B0;
extern u8 D_800762B3[];
extern u8 D_800762B4[];
extern s32 D_80073140[][1];  /* [][1] spelling: load-bearing for func_800391D4 (S79 lever; §500-I) */
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
    s16 b4;
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
    register s32 *mp __asm__("$4");
    register s32 mv2 __asm__("$4");
    s32 two;
    s32 tmp;
    s32 pan;
    s32 pan1;
    s32 x;
    s32 s17;
    s32 s18;
    s32 v;
    s32 u26;
    s32 n;
    s32 off;
    u32 t2;
    u16 vol;
    u32 vv;
    u32 prod;
    s32 k2;
    u8 *tbl;
    s32 tmp2;
    s32 coff;
    s32 xoff;
    s32 mv;
    s32 j;
    s32 ax;
    s32 ax2;
    u8 *pb;
    s32 c7;
    u32 gx;

    src = *arg0;
    *arg0 = src + 1;
    b2 = src[0];
    *arg0 = src + 2;
    b3 = src[1];

    if (b3 != 0) {
        if ((((u8 *)arg0 + arg1)[0x1BA] & 1) == 0) {
            s0 = (u8 *)arg0 + (arg1 * 26 + 26);
            i = 0;
            b4 = *s0;
            n = b4;
            v = n * 0x10;
            t9 = *(u8 **)((u8 *)arg0 + 0x1E0) + n * 0x200;
            cnt = *(*(u8 **)((u8 *)arg0 + 0x1DC) + v);
            if (cnt != 0) {
                u26 = b2;
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
                            gx = s0[1];
                            gx -= 0x100;
                            v = b3 * (u8)gx;
                            v >>= 7;
                            v = v * t9[2];
                            v >>= 7;
                            v = D_8006ACD8[v];
                            v = v * *(s16 *)((u8 *)arg0 + 0x1F2);
                            v >>= 7;
                            if (D_800A4F19 != 0) {
                                bb = s0[4];
                                pan1 = bb + t9[3]; pan1 -= 0x40;
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
                            vol = b2 * 0x100;
                            if (pan >= 0x41) {
                                vol = (b2 * 0x100) + (u32)((pan - 0x40) * t9[0xD] * 4);
                            } else if (pan < 0x40) {
                                vol = (b2 * 0x100) - (u32)((0x40 - pan) * t9[0xC] * 4);
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
                            p = r;
                            if (r[0x5A] != 0) {
                                coff = *(s16 *)&r[6] * 26;
                                *(u8 *)(*(u32 *)&r[0x50] + coff + idx1 + 0x23) = 0;
                                r[0x5A] = 0;
                            }
                            r = 0;
                            *(s0 + idx1 + 9) = 1;
                            *(s16 *)(p + 4) = b2;
                            *(s16 *)(p + 8) = b4;
                            p[0xC] = i;
                            p[0x5C] = 1;
                            *(s16 *)(p + 0) = s17;
                            *(s16 *)(p + 2) = s18;
                            *(s16 *)(p + 6) = arg1;
                            *(u32 *)(p + 0x50) = (u32)arg0;
                            p[0x5B] = 1;
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
        s17 = (s32)((u8 *)arg0 + arg1 * 26);
        s18 = b2;
        off = 0;
        do {
            if (((u8 *)s17 + j)[0x23] != 0 && *(s16 *)&D_800C6DD4[off] == s18) {
                idx1 = (s16)j;
                xoff = idx1 * 0x60;
                cb = D_800C6DD0;
                r = cb + xoff;
                if (r[0x5A] != 0) {
                    coff = *(s16 *)&r[6] * 26;
                    *(u8 *)(*(u32 *)&r[0x50] + coff + idx1 + 0x23) = 0;
                    r[0x5A] = 0;
                }
                mm = (s32 *)D_80073140;
                D_800C7D20 &= ~mm[j];
                D_800A2B98 |= mm[j];
                pb = D_800762B0 + j;
                two = 2;
                *pb = two;
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
