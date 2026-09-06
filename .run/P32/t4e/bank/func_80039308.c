/* func_80039308 (main, src/800_c.c, 518 ins) -- BANKED byte-identical, P32 T4c hand pass (S85, 2026-09-06),
 * ZERO register pins, zero fences, zero asm bodies.  Sequencer note-on / voice allocation: walks the track's
 * 16 voice records (D_800C6DD0, 0x60 each), allocates or steals a voice for note b2 at velocity b3, computes
 * pan/volume/pitch through D_8006AF08 / D_8006ACD8 / D_8006AB30 / D_8006ABD8, and updates the D_800A2B98 /
 * D_800C7D20 / D_800C7D2C / D_800A2BA0 voice masks; the else arm releases the voices playing note b2.
 *
 * The three mechanisms that closed the S84 PLATEAU (cookbook §501-Q, §501-R, accelerators (15)-(16)):
 *  1. THE PHANTOM 8-BYTE FRAME SLOT ([arg1 @0][8 no-traffic bytes @8][cnt @0x10]) is a combine GHOST: the chain
 *     `gx = s0[1]; gx -= 0x100; v = b3 * (u8)gx;` compiles to the same `lbu` as `s0[1]`, but combine deletes the
 *     self-update with `i2dest_in_i2src` (combine.c:2306 skips the reference decrement), the load then merges into
 *     the (u8) use, and the pseudo `gx` keeps stale refs with no insns -- reload's initial alter_reg loop mints an
 *     8-byte slot for it in regno order, between arg1's spill and cnt's eviction slot.  Reproducers: .run/P32/t4e/ghost/.
 *  2. THE HOISTED VOLUME BASE `sll $s2,$s5,8` sits between two hoisted constants ([li 2][sll][li 1]) and is read
 *     three times ($s2 in the copy and both pan arms): loop.c's combine_movables merges the three inline
 *     `(b2 * 0x100)` temps into ONE hoisted movable (savings 3), which needs (a) a compiler TEMP, not a named
 *     variable (a user variable set after the inner loop's jumps is never a movable: loop.c:695-700), and (b) cse1
 *     NOT folding the arms onto `vol`: with `u16 vol`, the copy `vol = b2 * 0x100` is a subreg move, so `vol` never
 *     joins the shift's quantity (cse.c make_regs_eqv prefers the later-mentioned register) and the arms keep the
 *     temp.  The copy-first form is what puts `vol` in $a1 (born while pan is live in $a0) and in the first
 *     branch's delay slot; every copy-last / named-vbase / pinned form was measured (b13-b51, NOTES.md).
 *  3. THE ELSE HEAD ($t1/$t0): the release loop's pointer and compare temp are the note-on arm's `s17`/`s18`
 *     variables reused (the target's rows 410/411 and 440/441 share the registers); a fresh `tb`/`k2` pair lands in
 *     $t0/$s2 instead.
 * Kept from the S83/S84 drafts: `s16 b4` + `n = b4` (the widening copy), the pan sum split, `bb` as the first pan
 * load, the offset local `v` computed before t9, the cross-arm k2 reading of the +6 store ... see the S83 notes in
 * git history (this header replaces them).
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
    s32 *mp;
    s32 mv2;
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
