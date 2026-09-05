#include "common.h"
#include "800_shared.h"

/* P31 S72 — split out of src/800.c at the jtbl-span TU boundary (vram 0x80035270-0x8003A444).
 * This TU owns .rodata span C (0x800732A0-0x8007344C); see config/splat.us.exe.yaml and cookbook §426.
 * Declarations shared with the sibling TUs live in src/800_shared.h. */

/* func_80035270 — CD stream state machine (main, src/800_c.c, jtbl_800732A0 span C).
 *
 * Levers that made this byte-exact (all verified against asm/nonmatchings/800_c/func_80035270.s):
 *  - `+ zr` ($0 register variable, the src/800_c.c func_80036AF8 house idiom) forces the
 *    `addu $sN,$aN,$zero` copies that split `n`/`idx` and `drv`/`hi` into two pseudos.
 *  - HARD-REGISTER PINS, not declaration/statement order, fix gcc-2.7.2's global-alloc here:
 *    pinning ONLY `hi`->$s4 and `n`->$a0 rotates idx->$s2, h->$s3, drv->$a1 into place.
 *    (A full sweep of all 720 declaration orders and all 6 prologue statement orders moved
 *    nothing; the pins took the residual from 26 instructions to 6.)  `sync` reuses $a0 for
 *    its two disjoint live ranges in cases 2 and 9; case 5 keeps its own `sync5` ($v1).
 *  - The shared tails are written as explicit `goto Lret0/Lret1/Lflush/Lsetflag` with the
 *    labels placed where the .s puts the merged blocks.  gcc's cross_jump keeps the LAST
 *    duplicate; the target keeps the copy that sits with case 5's `f03 = 4; return 0`, so
 *    `default:` is co-located there (legal C89 — a case label may sit in a nested block).
 *  - `rec2 = ((s32)h << 6) + (s32)rec;` (fresh variable, h-first) puts the sum in the h64
 *    register -> `addu $v0,$v0,$v1`; the self-assignment `rec = rec + ...` used by cases 4
 *    and 6 reuses rec's register -> `addu $v1,$v1,$v0`.  Both forms are load-bearing.
 *  - `func_8003EDE8(0, vol + zr, vol + zr)` is what emits `addu $a1,$s0,$zero` /
 *    `addu $a2,$a1,$zero`; a plain `(0, vol, vol)` emits `move $a2,$s0` (cse canonicalises
 *    the second copy back to the pseudo's own hard reg).
 *  - `if (++D_800760F8 < 10)` gives lhu/addiu/sh/sll16/sra16/slti; a plain post-increment
 *    then a reload would emit `lh`.  `slti $v0,$v0,0x12D` is `<= 300`, not `< 300`.
 *  - Locals take sp offsets in DECLARATION order upward: result@0x10, param@0x18, loc@0x20.
 *
 * BANKING NOTE (§376): src/800_c.c:461 currently declares `extern void func_80035270(void);`
 * (address-taken at `req.f08 = (s32)func_80035270;`).  That conflicts with this definition;
 * the decl must become `extern s32 func_80035270(s32);` (or the use be cast) before the TU
 * will compile.
 */

extern s32 D_8006A69C;
extern u8  D_8006A6A0;
extern s32 D_8006AEE8;
extern u8  D_8006AEEC;
extern s32 D_80078F10;
extern s16 D_800760F8;
extern s32 D_80076100;
extern u8  D_800760FC;
extern u8  D_800760FD;
extern s16 D_80076208;
extern u8  D_8007620C;
extern u8  D_80076210;
extern u8  D_80076214;
extern s32 D_800A4638;
extern s16 D_800A4688;
extern u8  D_800A4698;
extern s16 D_800A4EF6;
extern s16 D_800A4EFA;

extern void func_800434BC(void);
extern s32  func_8004355C(s32 mode, u8 *result);
extern int  func_800435CC(s32, void *, void *);
extern int  func_80043830(int com, u8 *param, u8 *result);
extern int  func_80043410(void);
extern int  func_80043420(void);
extern s32  func_8003EDE8(s32, s32, s32);
extern void func_8003D650(int a0, int a1, int a2);

s32 func_80035270(s32 arg0) {
    register s32 zr __asm__("$0");
    u8 result[8];
    u8 param[8];
    CdlLOC loc;
    s32 flags;
    register s32 n __asm__("$4");
    s32 idx;
    s32 lo;
    s16 h;
    s32 drv;
    register s32 hi __asm__("$20");
    u8 *rec;
    u8 *rec2;
    u8 b;
    s32 i;
    s32 cnt;
    s32 count;
    s32 *p;
    s32 *src;
    s32 *dst;
    s32 target;
    s32 cmp;
    u8 *q;
    CdlLOC *lp;
    register s32 sync __asm__("$4");
    s32 sync5;
    s32 tmp;
    s32 inc;
    u8 ctr;
    s32 st;
    s32 t;
    s32 val;
    s32 vol;

    flags = *(s32 *)(arg0 + 0x10);
    lo = flags >> 4;
    h = lo & 0x1F;
    n = flags & 0xF;
    idx = n + zr;
    drv = (flags >> 9) & 0x1F;
    hi = drv + zr;
    if (lo & 1) {
        if (*(u8 *)((u8 *)&D_8006A6A0 + drv * 0x48) != 0) {
            idx = n + 4;
        } else {
            idx = n + 8;
        }
    }
    h = h >> 1;

    if (*(u8 *)(arg0 + 7) != 0) {
        *(u8 *)(arg0 + 7) = 0;
        *(u8 *)(arg0 + 3) = 0x11;
        if (*(s32 *)(arg0 + 0xC) == 0) {
            goto Lret1;
        }
        p = &D_80078F10;
        target = *(s32 *)(arg0 + 0x2C) + 1;
        if (target != p[0]) {
            i = 1;
            cmp = target + zr;
            for (; i < 5; i++) {
                if (p[i] == cmp) {
                    break;
                }
            }
            if (i == 5) {
                goto Lret1;
            }
            cnt = D_8006AEE8;
            if (i < cnt) {
                count = 0;
                dst = &D_80078F10;
                src = &D_80078F10 + i;
                do {
                    *dst = *src;
                    src++;
                    i++;
                    count++;
                    dst++;
                } while (i < cnt);
                D_8006AEE8 = count;
            }
        }
        *(s32 *)(arg0 + 0x14) = 0xF;
        D_800760F8 = 0;
        D_80076100 = func_80043420();
    }

    switch (*(u8 *)(arg0 + 3)) {
    case 0x11:
        q = &D_800760FC;
        *q = 1;
        D_800760FD = idx;
        if (func_80043830(0xD, q, result) == 0) {
            D_800760F8++;
            goto Lcheck;
        }
        *(u8 *)(arg0 + 3) = 0x12;
        func_8003EDE8(0, 0, 0);
        D_800760F8 = 0;
        /* fall through */
    case 0x12:
        param[0] = 200;
        if (func_80043830(0xE, param, result) == 0) {
            D_800760F8++;
            goto Lcheck;
        }
        if ((*(s32 *)(arg0 + 0x10) == 0x4486 || *(s32 *)(arg0 + 0x10) == 0x4364) &&
            D_800A4698 == 0 && D_800A4688 == 0x2B) {
            goto Lvol;
        }
        rec = (u8 *)*(s32 *)((u8 *)&D_8006A69C + hi * 0x48);
        rec2 = (u8 *)(((s32)h << 6) + (s32)rec);
        b = *(u8 *)(rec2 + (idx << 2) + 1);
        if ((b & 0x20) == 0) {
            goto Lzero;
        }
        if ((b & 0x40) == 0) {
            goto Lone;
        }
    Lvol:
        if (D_800A4EF6 >= 2) {
            func_8003D650(0, 1, 1);
        } else {
            func_8003D650(0, 1, 0);
        }
        goto Lcont;
    Lone:
        func_8003D650(0, 1, 1);
        goto Lcont;
    Lzero:
        func_8003D650(0, 1, 0);
    Lcont:
        D_800760F8 = 0;
        if (D_80076100 & 0x80) {
            *(u8 *)(arg0 + 3) = 1;
            goto Lcase1;
        }
        *(u8 *)(arg0 + 3) = 0;
        /* fall through */
    case 0:
        if (*(s32 *)(arg0 + 0x14) != 0) {
            *(s32 *)(arg0 + 0x14) = *(s32 *)(arg0 + 0x14) - 1;
        }
        if (++D_800760F8 < 10) {
            goto Lret0;
        }
        *(u8 *)(arg0 + 3) = 1;
        D_800760F8 = 0;
        /* fall through */
    case 1:
    Lcase1:
        if (*(s32 *)(arg0 + 0x14) != 0) {
            *(s32 *)(arg0 + 0x14) = *(s32 *)(arg0 + 0x14) - 1;
        }
        lp = &loc;
        CdIntToPos(*(s32 *)(arg0 + 0xC), lp);
        D_800760F8++;
        if (func_80043830(2, (u8 *)lp, 0) == 0) {
            goto Lcheck;
        }
        if (func_800435CC(0x15, lp, 0) == 0) {
            goto Lcheck;
        }
        D_800760F8 = 0;
        *(u8 *)(arg0 + 3) = 2;
        /* fall through */
    case 2:
        if (*(s32 *)(arg0 + 0x14) != 0) {
            *(s32 *)(arg0 + 0x14) = *(s32 *)(arg0 + 0x14) - 1;
        }
        sync = func_8004355C(1, result);
        if (sync == 0) {
            D_800760F8++;
            goto Lcheck;
        }
        if (sync == 5) {
            if (func_800435CC(1, param, result) != 0) {
                *(u8 *)(arg0 + 3) = 1;
                goto Lret0;
            }
            if (result[0] & 0x10) {
                goto Lsetflag;
            }
            *(u8 *)(arg0 + 3) = 1;
            goto Lret0;
        }
        D_80076208 = *(s32 *)(arg0 + 0x14);
        *(u8 *)(arg0 + 3) = 3;
        /* fall through */
    case 3:
        if (*(s32 *)(arg0 + 0x14) != 0) {
            *(s32 *)(arg0 + 0x14) = *(s32 *)(arg0 + 0x14) - 1;
            goto Lret0;
        }
        D_800760F8 = 0;
        *(u8 *)(arg0 + 3) = 4;
        /* fall through */
    case 4:
        CdIntToPos(*(s32 *)(arg0 + 0xC), &loc);
        if (func_800435CC(0x1B, &loc, 0) == 0) {
            D_800760F8++;
            goto Lcheck;
        }
        rec = (u8 *)*(s32 *)((u8 *)&D_8006A69C + hi * 0x48);
        rec = rec + ((s32)h << 6);
        D_80076210 = 0;
        D_800760F8 = 0;
        vol = (*(u8 *)(rec + (idx << 2)) * D_800A4EFA >> 7) & 0x7F;
        func_8003EDE8(0, vol + zr, vol + zr);
        D_8006AEEC = vol;
        *(u8 *)(arg0 + 3) = 5;
        /* fall through */
    case 5:
        sync5 = func_8004355C(1, result);
        if (sync5 == 2) {
            goto Lstate6;
        }
        if (sync5 == 5) {
            if (result[0] & 0x10) {
                goto Lflush;
            }
            func_800434BC();
            *(u8 *)(arg0 + 3) = 4;
    default:
    Lret0:
            return 0;
        }
        D_800760F8++;
        goto Lcheck;
    Lstate6:
        *(u8 *)(arg0 + 3) = 6;
        /* fall through */
    case 6:
        func_800435CC(1, 0, 0);
        st = func_80043410();
        D_8007620C = st;
        if ((st & 0x20) == 0) {
            goto Lret0;
        }
        rec = (u8 *)*(s32 *)((u8 *)&D_8006A69C + hi * 0x48);
        rec = rec + ((s32)h << 6);
        t = D_800A4638;
        *(s32 *)(arg0 + 0x18) = t;
        val = *(s16 *)(rec + (idx << 2) + 2) + t;
        *(s32 *)(arg0 + 0x14) = val;
        if ((u32)val < (u32)t) {
            *(u8 *)(arg0 + 6) = 1;
        } else {
            *(u8 *)(arg0 + 6) = 0;
        }
        *(u8 *)(arg0 + 3) = 7;
        /* fall through */
    case 7:
        ctr = D_80076210;
        inc = ctr + 1;
        tmp = ctr & 3;
        D_80076210 = inc;
        if (tmp == 0) {
            func_800435CC(1, 0, 0);
            st = func_80043410();
            D_8007620C = st;
            if (st & 0x10) {
                goto Lflush;
            }
        }
        t = D_800A4638;
        if ((u32)t < (u32)*(s32 *)(arg0 + 0x14)) {
            goto Lret0;
        }
        if (*(u8 *)(arg0 + 6) != 0) {
            if ((u32)t >= (u32)*(s32 *)(arg0 + 0x18)) {
                goto Lret0;
            }
        }
        *(u8 *)(arg0 + 3) = 8;
        /* fall through */
    case 8:
        func_8003EDE8(0, 0, 0);
        if (func_800435CC(9, 0, 0) == 0) {
            goto Lret0;
        }
        D_8007620C = 0;
        *(u8 *)(arg0 + 3) = 9;
        /* fall through */
    case 9:
        sync = func_8004355C(1, result);
        if (sync == 0) {
            goto Lret0;
        }
        if (sync != 5) {
            goto Lret1;
        }
        if ((result[0] & 0x10) == 0) {
            goto Lret1;
        }
        goto Lsetflag;
    }

Lcheck:
    if (D_800760F8 <= 300) {
        goto Lret0;
    }
Lflush:
    func_800434BC();
Lsetflag:
    D_80076214 = 1;
Lret1:
    return 1;
}

/* func_800359B0 — CD/stream state pump (jtbl_800732F0, cases 0..0x12).
 *
 * Two cross-jump dials carry this function (§162 / §336 / §194-N):
 *  - case 0x10's `j .L80035B40` is BACKWARD into case 9's arm, so per §162 it is a
 *    source `goto`, not a compiler tail-merge (the survivor is always the LATER copy).
 *  - `do_flag:` sits INSIDE case 9's >=0x12D arm: that surviving CODE_LABEL is what
 *    stops find_cross_jump's backward walk from swallowing case 9's own block
 *    (jump.c:2404 `GET_CODE (i1) == CODE_LABEL` -> --minimum; break).
 *  - the zero-byte fence sits at the BOTTOM of case 0x10's twin, just before the shared
 *    `goto` (§336): without it the `minimum=1` path (jump.c:1978) matches case 0x10's
 *    `jal func_800434BC` against the one preceding `do_flag` and merges them backward,
 *    costing exactly the 2 instructions at 0x80035C1C.
 */
extern u8 D_8006AEEC;
extern s16 D_800A4EFA;
extern u8 D_8007620C;
extern u16 D_80076104;
extern u8 D_80076214;
extern void func_800434BC(void);
extern s32 func_8003EDE8(s32, s32, s32);
extern int  func_800435CC(s32, void *, void *);
extern s32 func_8004355C(s32 mode, u8 *result);

void func_800359B0(s32 arg0) {
    u8 result[8];
    s32 sync;

    switch (*(u8 *)(arg0 + 3)) {
    case 1:
    case 2:
        func_800434BC();
        *(u8 *)(arg0 + 2) = 0;
        break;
    case 4:
        func_800434BC();
        *(u8 *)(arg0 + 2) = 1;
        *(u8 *)(arg0 + 3) = 0x10;
        break;
    case 6:
    case 7:
        func_8003EDE8(0, (u32)((D_8006AEEC * D_800A4EFA) >> 7 & 0xFF) * 3 >> 2,
                      (u32)((D_8006AEEC * D_800A4EFA) >> 7 & 0xFF) * 3 >> 2);
        *(u8 *)(arg0 + 2) = 1;
        D_8007620C = 0;
        *(u8 *)(arg0 + 3) = 0xB;
        break;
    case 5:
        func_800434BC();
        *(u8 *)(arg0 + 3) = 8;
        /* fall through */
    case 8:
        func_8003EDE8(0, 0, 0);
        if (func_800435CC(9, 0, 0) == 0) {
            *(u8 *)(arg0 + 2) = 1;
            *(u8 *)(arg0 + 3) = 0x10;
            D_80076104 = 0;
            return;
        }
        D_8007620C = 0;
        D_80076104 = 0;
        *(u8 *)(arg0 + 3) = 9;
        /* fall through */
    case 9:
        sync = func_8004355C(1, result);
        if (sync == 0) {
            D_80076104 = D_80076104 + 1;
            if ((s16)D_80076104 >= 0x12D) {
                func_800434BC();
            do_flag:
                D_80076214 = 1;
                *(u8 *)(arg0 + 2) = 0;
                return;
            }
            *(u8 *)(arg0 + 2) = 1;
            return;
        }
        if (sync == 5 && (result[0] & 0x10)) {
            D_80076214 = 1;
        }
        *(u8 *)(arg0 + 2) = 0;
        break;
    case 11:
        func_8003EDE8(0, D_8006AEEC >> 1, D_8006AEEC >> 1);
        *(u8 *)(arg0 + 3) = 0xC;
        break;
    case 12:
        func_8003EDE8(0, D_8006AEEC >> 2, D_8006AEEC >> 2);
        *(u8 *)(arg0 + 3) = 0xD;
        break;
    case 13:
        func_8003EDE8(0, 0, 0);
        if (func_800435CC(9, 0, 0) != 0) {
            *(u8 *)(arg0 + 3) = 9;
            return;
        }
        *(u8 *)(arg0 + 3) = 0x10;
        D_80076104 = 0;
        break;
    case 16:
        if (func_800435CC(9, 0, 0) == 0) {
            D_80076104 = D_80076104 + 1;
            if ((s16)D_80076104 >= 0x12D) {
                func_800434BC();
                __asm__ __volatile__("");   /* §336 cross-jump fence, zero bytes */
                goto do_flag;
            }
            break;
        }
        *(u8 *)(arg0 + 3) = 9;
        break;
    case 0:
    case 3:
    case 10:
    case 14:
    case 15:
    case 17:
    case 18:
    default:
        *(u8 *)(arg0 + 2) = 0;
        break;
    }
}

extern u8  D_8006AEEC;
extern s32 D_80076108;
extern s32 D_8007610C;
extern u8  D_8007620C;
extern u8  D_80076214;
extern s32 D_80078F10;
extern s16 D_800A4EF8;
extern s32 D_800A5BC8;
extern u8  D_800A63E4;
extern s32 D_800A63E8;
extern s32 D_800C6D28;
extern s32 D_800C7D30[];

extern void func_8003D650(int a0, int a1, int a2);
extern s32  func_8003EDE8(s32, s32, s32);
extern void func_80036130(s32, u8 *);
extern void func_800361CC();
extern void func_8003621C(void);
extern s32  func_80043410(void);
extern s32  func_80043420(void);
extern int  func_800435CC(s32, void *, void *);
extern s32  func_8004355C(s32 mode, u8 *result);
extern s32  func_80043704(u8 com, u8 *param);

s32 func_80035C4C(s32 arg0) {
    u8 result[8];
    u8 cmd[8];
    s32 trk;
    s32 st;
    s32 sync;
    u32 vol;

    if (*(u8 *)(arg0 + 7) != 0) {
        trk = *(s32 *)(arg0 + 0xC);
        D_8007620C = 0;
        *(u8 *)(arg0 + 7) = 0;
        *(u8 *)(arg0 + 3) = 0;
        if (D_800A5BC8 < trk) {
            return 1;
        }
        if (trk != 0) {
            if ((func_80043420() & 0x80) == 0) {
                *(u8 *)(arg0 + 3) = 1;
            }
            D_80076108 = 0;
            cmd[0] = 5;
            func_800435CC(0xE, cmd, 0);
            D_800A63E8 = *(s32 *)(arg0 + 0xC);
        } else {
            if (D_800C6D28 == 0) {
                return 1;
            }
            D_800A63E8 = D_800C6D28;
            func_80043704(3, 0);
            D_800C6D28 = 0;
            *(u8 *)(arg0 + 3) = 2;
        }
    }

    switch (*(u8 *)(arg0 + 3)) {
    case 0:
        if (++D_80076108 < 3) {
            return 0;
        }
        *(u8 *)(arg0 + 3) += 1;
        /* fall through */
    case 1:
        vol = ((u32)D_800A4EF8 * 97) >> 7;
        D_80076108 = 0;
        D_8006AEEC = vol;
        func_8003EDE8(0, vol & 0xFF, vol & 0xFF);
        func_8003D650(0, 1, 0);
        func_80043704(3, (u8 *)&D_800C7D30[*(s32 *)(arg0 + 0xC)]);
        func_800361CC(func_80036130);
        *(u8 *)(arg0 + 3) += 1;
        /* fall through */
    case 2:
        if (func_80043410() & 0x40) {
            if (D_80076108++ >= 0x12D) {
                D_80076214 = 1;
                return 1;
            }
            return 0;
        }
        sync = func_8004355C(1, result);
        if (sync == 2) {
            *(u8 *)(arg0 + 3) += 1;
            break;
        }
        if (sync != 5) {
            return 0;
        }
        if (result[0] & 0x10) {
            D_80076214 = 1;
            return 1;
        }
        return 1;
    case 3:
        st = func_80043410();
        if ((st & 0x80) == 0) {
            if (st & 0x10) {
                D_80076214 = 1;
                return 1;
            }
            return 0;
        }
        D_800A63E4 = 0xC;
        D_8007610C = 0;
        D_8007620C |= 0x80;
        *(u8 *)(arg0 + 3) += 1;
        break;
    case 4:
        if (D_800A63E4 == 0xD) {
            func_8003621C();
            func_8003EDE8(0, 0, 0);
            func_80043704(9, 0);
            D_8007620C = 0;
            D_80078F10 = 0;
        } else {
            if (D_8007610C == 0) {
                return 0;
            }
            st = func_80043410();
            if (st & 0x80) {
                return 0;
            }
            if (st & 0x10) {
                D_80076214 = 1;
            }
            func_8003621C();
            func_8003EDE8(0, 0, 0);
            D_8007620C = 0;
            D_80078F10 = 0;
            if (D_80076214 != 0) {
                return 1;
            }
            func_80043704(9, 0);
        }
        *(u8 *)(arg0 + 3) += 1;
        return 0;
    case 5:
        sync = func_8004355C(1, result);
        if (sync == 0) {
            return 0;
        }
        if (sync != 5) {
            return 1;
        }
        if (result[0] & 0x10) {
            D_80076214 = 1;
        }
        return 1;
    }
    return 0;
}

extern u8 D_80076214;
extern void func_800434BC(void);
extern s32 func_8004355C(s32 mode, u8 *result);
extern s32 func_80043704(u8 com, u8 *param);

void func_8003602C(s32 arg0) {
    u8 result[8];
    u8 state;
    s32 sync;

    switch (*(u8 *)(arg0 + 3)) {
    case 0:
    case 1:
    default:
        *(u8 *)(arg0 + 2) = 0;
        break;
    case 2:
        *(u8 *)(arg0 + 2) = 1;
        func_800434BC();
        *(u8 *)(arg0 + 3) += 2;
        break;
    case 3:
        *(u8 *)(arg0 + 2) = 1;
        func_800434BC();
        *(u8 *)(arg0 + 3) += 1;
        /* fall through */
    case 4:
        func_80043704(9, 0);
        func_8003621C();
        state = *(u8 *)(arg0 + 3);
        *(u8 *)(arg0 + 2) = 1;
        *(u8 *)(arg0 + 3) = state + 1;
        break;
    case 5:
        sync = func_8004355C(1, result);
        if (sync == 0) {
            *(u8 *)(arg0 + 2) = 1;
            return;
        }
        if (sync == 5 && (result[0] & 0x10)) {
            D_80076214 = 1;
        }
        *(u8 *)(arg0 + 2) = 0;
        break;
    }
}


extern u8 D_800A63E4;
extern s32 D_8007610C;
extern s32 D_800A63E8;

void func_80036130(s32 a0, u8 *a1) {
    u8 v1;
    s32 temp;
    s32 v3;
    s32 v0;
    s32 byte_val;
    s32 low;

    v1 = D_800A63E4;
    if (v1 != 0xC) {
        return;
    }

    v1 = a0 & 0xFF;
    if (v1 != 0x1) {
        return;
    }

    temp = D_8007610C;
    if (temp < 0xA) {
        D_8007610C = temp + 1;
        return;
    }

    if ((a1[4] & 0x80) != 0) {
        return;
    }

    byte_val = a1[1];
    v1 = byte_val >> 4;
    v0 = v1 << 2;
    v0 = v0 + v1;
    v0 = v0 << 1;
    low = byte_val & 0xF;
    v3 = D_800A63E8;
    v0 = v0 + low;

    if (v0 != v3) {
        D_800A63E4 = 0xD;
    }
}

extern void *streamLoad_savedReadyCB;
extern u8 streamLoad_cbActive;
extern void *CdReadyCallback(void *func);

void func_800361CC(void) {
    if (streamLoad_cbActive == 0) {
        streamLoad_savedReadyCB = ((void *(*)(void))CdReadyCallback)();
    } else {
        ((void *(*)(void))CdReadyCallback)();
    }
    streamLoad_cbActive = 1;
}


extern void *CdReadyCallback(void *func);
extern void *streamLoad_savedReadyCB;
extern u8    streamLoad_cbActive;

void func_8003621C(void) {
    if (streamLoad_cbActive != 0) {
        CdReadyCallback(streamLoad_savedReadyCB);
        streamLoad_savedReadyCB = 0;
        streamLoad_cbActive = 0;
    }
}

extern void func_80037334(void);
extern void func_800434BC(void);
extern void *CdReadyCallback(void *);
extern int  func_800435CC(s32, void *, void *);
extern s32 func_8004355C(s32 mode, u8 *result);   /* §376: adopt the TU's spelling verbatim */
extern void func_800415A8(s32);

extern u8   D_8006AEF4;
extern u16  D_800A4E8E;
extern int  streamLoad_state;
extern void *streamLoad_savedReadyCB;
extern u8   streamLoad_cbActive;
extern int  D_800A6544;
extern s16  D_800A46A2;
extern u8   D_800A46B0;

int func_80036260(void) {
    u8 result[8];
    u16 *flags;
    s16 *vabp;
    s32 t;
    int sync;

    func_80037334();
    D_8006AEF4 &= 0xFD;
    flags = &D_800A4E8E;
    *flags &= 0xFFDF;

    if (streamLoad_state != 0) {
        switch (streamLoad_state) {
        case 0:
        case 1:
        case 2:
            break;
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 15:
        case 16:
        case 17:
            func_800434BC();
            break;
        case 12:
            if (streamLoad_cbActive != 0) {
                CdReadyCallback(streamLoad_savedReadyCB);
                streamLoad_savedReadyCB = 0;
                streamLoad_cbActive = 0;
            }
            /* fall through */
        case 13:
        case 14:
            func_800435CC(9, 0, 0);
            streamLoad_state = 0;
            D_800A6544 = 0x3C;
            break;
        }
    }

    if (D_800A6544 != 0) {
        D_800A6544--;
        if (D_800A6544 != 0) {
            sync = func_8004355C(1, result);
            if (sync != 5 && sync != 2) {
                return 0;
            }
        }
    }

    vabp = &D_800A46A2;
    t = *vabp;
    streamLoad_state = 0;
    D_800A6544 = 0;
    if (t >= 0) {
        func_800415A8(t);
        *vabp = -1;
        D_800A46B0 = 1;
    }
    return 1;
}

#ifdef NON_MATCHING
extern int   CdControl(u8 com, u8 *param, u8 *result);
extern int   CdSync(int mode, u8 *result);
extern u32   CdMode(void);
extern void  CdFlush(void);
extern void *CdReadyCallback(void *func);
extern void  func_800377D8(void);   /* this loader's CdlReadN ready-callback */
extern int func_80036260(void);   /* sub-handler passed to func_80037CD8; §376: the definition returns int */
extern void  func_8002EC10(void);
extern void  func_80037334(void);
extern void  func_80037358(int posInt);
extern void  func_80037144(int idx);
extern int   func_80037CD8(void *arg);
extern int   func_8003750C(void);
extern int   func_800374CC(int *out);
extern int   func_8003775C(void);
extern void  func_80037D74(void);
extern void *func_80037368(int *out);

extern int   streamLoad_state;          /* 0x8006AF00 */
extern void *streamLoad_savedReadyCB;
extern u8    streamLoad_cbActive;
extern int   D_800A4F28;            /* tick / timeout counter */
extern int   D_800A4F2C;            /* CdMode-derived retry budget */
extern int   D_800A4F30;            /* remaining sub-stream repeat count (from param_3) */
extern int   D_800A4F34;            /* last sector position (stall detection) */
extern int   D_800A4F38;            /* end/abort flag */
extern int   D_800A6544;
extern u16   D_800A4E8E;            /* 16-bit status flags */
extern u8    D_8006AEF4;            /* 8-bit status flags */
extern u8    D_80068B60[];          /* per-resource descriptor table (0x10 stride) */

/* Second CD loader, DISTINCT from CdReadStateMachine: an 18-state machine (streamLoad_state) with
 * its OWN ready-callback (func_800377D8). Runs SetMode(0xA0)/SeekL/ReadN with retry + CdMode
 * handling, looping param_3 (D_800A4F30) times over sub-streams. Returns 0 = busy, 1 = done,
 * 2 = error/abort. Driven by ResourceLoadStateMachine. Provenance: static trace, Phase 3 T4 (fn id
 * verified; full semantics partial).
 * NON_MATCHING: faithful translation of the Ghidra decompile — logically faithful, not byte-verified. */
int StreamLoadStateMachine(int param_1, void *param_2, int param_3) {  /* param_2 is a CdlLOC* */
    short sVar1;
    int iVar4;
    u32 uVar2;
    char *pcVar3;
    u8 local_28[8];
    u8 local_20[8];
    int local_18;
    int local_14;

    sVar1 = *(short *)(D_80068B60 + (param_1 - 0x100) * 0x10);
    D_800A4F28++;
    switch (streamLoad_state) {
    case 0:
        D_800A4F38 = 0;
        D_800A6544 = 0;
        D_800A4F30 = param_3;
        func_8002EC10();
        streamLoad_state++;
        D_800A4E8E &= 0xFFDF;
        return 0;
    case 1:
        func_80037334();
        iVar4 = CdPosToInt((CdlLOC *)param_2);
        func_80037358(iVar4);
        func_80037144(sVar1);
        streamLoad_state++;
        /* fall through */
    case 2:
        local_14 = CdSync(1, local_20);
        if (local_14 != 5 && local_14 != 2) return 0;
        uVar2 = CdMode();
        D_800A4F2C = ((uVar2 & 0x80) == 0) ? 3 : 0;
        streamLoad_state++;
        /* fall through */
    case 3:
        local_28[0] = 0xA0;
        iVar4 = CdControl(0x0E, local_28, local_20);     /* CdlSetmode */
        if (iVar4 == 0) {
            if ((local_20[0] & 0x10) != 0) { func_80037334(); streamLoad_state = 0; return 2; }
            return 0;
        }
        D_800A4F28 = 0;
        streamLoad_state++;
        /* fall through */
    case 4:
        iVar4 = CdSync(1, local_20);
        if (iVar4 != 5) {
            if (iVar4 == 2) {
                streamLoad_state++;
                local_14 = 2;
            modeWait:
                if (D_800A4F2C != 0) { D_800A4F2C--; return 0; }
                streamLoad_state++;
                goto issueSeek;
            }
            if (D_800A4F28 < 0x3D) return 0;
        }
        streamLoad_state = 3;
        return 0;
    case 5:
        goto modeWait;
    case 6:
    issueSeek:
        iVar4 = func_80037CD8((void *)func_80036260);
        if (iVar4 == 0) return 0;
        streamLoad_state = 7;
        /* fall through */
    case 7:
        iVar4 = func_8003750C();
        if (iVar4 == 0) return 0;
        streamLoad_state++;
        /* fall through */
    case 8:
        local_14 = CdSync(1, local_20);
        if (local_14 != 5 && local_14 != 2) return 0;
        streamLoad_state++;
        /* fall through */
    case 9:
        D_800A4F28 = 0;
        iVar4 = CdControl(0x15, (u8 *)param_2, local_20);      /* CdlSeekL */
        if (iVar4 == 0) return 0;
        streamLoad_state++;
        /* fall through */
    case 10:
        local_14 = CdSync(1, local_20);
        if (local_14 == 5) {
            iVar4 = CdControl(0x01, (u8 *)0, local_20);        /* CdlNop */
            if (iVar4 == 0) { streamLoad_state = 9; return 0; }
            if ((local_20[0] & 0x10) != 0) {
                func_80037334();
                D_8006AEF4 &= 0xFD;
                streamLoad_state = 0;
                return 2;
            }
            streamLoad_state = 9;
            return 0;
        }
        if (local_14 != 2) {
            if (D_800A4F28 < 0x12D) return 0;
            CdFlush();
            streamLoad_state = 9;
            return 2;
        }
        streamLoad_state++;
        local_14 = 2;
        /* fall through */
    case 0xB:
        D_800A4F28 = 0;
        iVar4 = CdControl(0x06, (u8 *)param_2, local_20);      /* CdlReadN */
        if (iVar4 != 0) {
            if (streamLoad_cbActive == 0)
                streamLoad_savedReadyCB = CdReadyCallback((void *)func_800377D8);
            else
                CdReadyCallback((void *)func_800377D8);
            streamLoad_state++;
            streamLoad_cbActive = 1;
            return 0;
        }
        if ((local_20[0] & 0x10) == 0) return 0;
        D_8006AEF4 &= 0xFD;
        func_80037334();
        streamLoad_state = 0;
        return 2;
    case 0xC:
        iVar4 = func_800374CC(&local_18);
        if (iVar4 == 0) {
            if (local_18 != D_800A4F34) { D_800A4F34 = local_18; D_800A4F28 = 0; }
            if (D_800A4F28 > 300) {
                if (streamLoad_cbActive != 0) {
                    CdReadyCallback(streamLoad_savedReadyCB);
                    streamLoad_savedReadyCB = 0;
                    streamLoad_cbActive = 0;
                }
                streamLoad_state++;
            }
            return 0;
        }
        if (streamLoad_cbActive != 0) {
            CdReadyCallback(streamLoad_savedReadyCB);
            streamLoad_savedReadyCB = 0;
            streamLoad_cbActive = 0;
        }
        streamLoad_state++;
        /* fall through */
    case 0xD:
        iVar4 = func_8003775C();
        if (iVar4 == 0) return 0;
        func_80037D74();
        streamLoad_state++;
        return 0;
    case 0xE:
        pcVar3 = (char *)func_80037368(&local_14);
        if (local_14 != 1) { streamLoad_state = 0x11; return 0; }
        if (*pcVar3 != 1) {
            if (*pcVar3 == 2) { streamLoad_state = 0x11; D_800A4F38 = 1; return 0; }
            if (D_800A4F30 != 0) {
                if (D_800A4F30 - 1 == 0) { streamLoad_state = 0x11; D_800A4F30 = 0; return 0; }
                streamLoad_state = 1;
                D_800A4F30--;
                return 0;
            }
            streamLoad_state = 1;
            return 0;
        }
        streamLoad_state++;
        break;                                                 /* -> CdlPause (post-switch) */
    case 0xF:
        break;                                                 /* -> CdlPause (post-switch) */
    case 0x10:
        iVar4 = CdSync(1, local_20);
        if (iVar4 != 5 && iVar4 != 2) return 0;
        if (D_800A4F38 == 0) { streamLoad_state = 0; return 1; }
        streamLoad_state = 0;
        D_800A4F38 = 0;
        return 2;
    case 0x11:
        iVar4 = CdControl(0x09, (u8 *)0, local_20);            /* CdlPause */
        if (iVar4 != 0) { streamLoad_state = 0x10; return 0; }
        return 0;
    default:
        return 0;
    }
    /* shared tail for states 0xE (advance) and 0xF: pause, then wait for it */
    iVar4 = CdControl(0x09, (u8 *)0, local_20);                /* CdlPause */
    if (iVar4 != 0) { streamLoad_state++; return 0; }
    if ((local_20[0] & 0x10) != 0) { streamLoad_state = 0; return 1; }
    return 0;
}
#else

extern void func_80037334(void);
extern void func_800434BC(void);
extern void *CdReadyCallback(void *);                /* CdReadyCallback; §376: keep the TU's void spelling */
extern int  func_800435CC(s32, void *, void *);   /* CdControl  */
extern s32  func_8004355C(s32 mode, u8 *result);  /* CdSync     */

extern u8   D_8006AEF4;
extern u16  D_800A4E8E;
extern int  streamLoad_state;
extern void *streamLoad_savedReadyCB;
extern u8   streamLoad_cbActive;
extern int  D_800A6544;

extern int  func_80036260(void);   /* sub-handler passed to func_80037CD8; the definition returns int */

extern s32  func_80043420(void);   /* CdMode */
extern void func_8002EC10(void);
extern void func_80037358(int posInt);
extern void func_80037144(s32 idx);
extern int  func_80037CD8(void *arg);
extern s32  func_8003750C(void);
extern int  func_800374CC(int *out);
extern int  func_8003775C(void);
extern void func_80037D74(void);
extern void *func_80037368(int *out);
extern void func_800377D8(u8);     /* this loader's CdlReadN ready-callback (defined below) */

extern int  D_800A4F28;            /* tick / timeout counter                       */
extern int  D_800A4F2C;            /* CdMode-derived settle budget                 */
extern int  D_800A4F30;            /* remaining sub-stream repeat count (from n)   */
extern int  D_800A4F34;            /* last sector position (stall detection)       */
extern int  D_800A4F38;   /* §376: TU spelling (src/800_c.c:890); reached as a byte below */
extern u8   D_80068B60[];          /* per-resource descriptor table (0x10 stride)  */

/* Second CD loader, DISTINCT from CdReadStateMachine: an 18-state machine (streamLoad_state) with
 * its OWN ready-callback (func_800377D8). Runs SetMode(0xA0)/SeekL/ReadN with retry + CdMode
 * handling, looping n (D_800A4F30) times over sub-streams. Returns 0 = busy, 1 = done,
 * 2 = error/abort. Driven by ResourceLoadStateMachine.
 *
 * Matching notes (P31 S73):
 *  - `idx` MUST be its own local: written inline, `(arg0 - 0x100) * 0x10` folds at tree level into
 *    `arg0*0x10 - 0x1000` and the -4096 disappears into the `lh` displacement (2 insns, wrong).
 *  - `sVar1` is `int` (not `short`): a HImode local live across three calls loads with `lhu` and
 *    pays a `sll/sra` sign-extend at the use; the int-typed read sign-extends at the load (`lh`).
 *  - Every held global address is its own single-set pointer local (§429) — that is what turns
 *    `lui/%lo` pairs into the `lui + addiu` base the target uses for D_800A4F28/2C/30/34/38 and
 *    D_800A4E8E.
 *  - `break` vs `return 0` is load-bearing and NOT interchangeable here (both mean "return 0"):
 *    `break` funnels through the single trailing `return 0`, so cross_jump merges the arm's tail
 *    into .L80036AD4/.L80036ADC; `return 0` keeps the `$v0 = 0` hard-reg set inside the arm, which
 *    excludes $v0 from that block's allocation. Case 11 needs `return 0` (its state++ lands in $v1
 *    and stays inline); every other zero-return arm needs `break`. */
int StreamLoadStateMachine(int arg0, void *loc, int n) {
    u8    cmd[8];
    u8    result[8];
    int   pos;
    int   sync;
    int   resKind;
    u8   *pb;
    int  *p28;
    int  *p2C;
    int  *p30;
    int  *p34;
    u16  *flags;
    int   t;
    int   idx;

    idx = arg0 - 0x100;
    resKind = *(short *)(D_80068B60 + idx * 0x10);
    p28 = &D_800A4F28;
    *p28 += 1;
    switch (streamLoad_state) {
    case 0:
        D_800A4F30 = n;
        *(u8 *)&D_800A4F38 = 0;
        D_800A6544 = 0;
        func_8002EC10();
        flags = &D_800A4E8E;
        *flags &= 0xFFDF;
        streamLoad_state++;
        break;
    case 1:
        func_80037334();
        func_80037358(CdPosToInt((CdlLOC *)loc));
        func_80037144(resKind);
        streamLoad_state++;
        /* fall through */
    case 2:
        sync = func_8004355C(1, result);
        if (sync != 5 && sync != 2) break;
        if ((func_80043420() & 0x80) != 0) {
            D_800A4F2C = 0;
        } else {
            D_800A4F2C = 3;
        }
        streamLoad_state++;
        /* fall through */
    case 3:
        cmd[0] = 0xA0;
        if (func_800435CC(0x0E, cmd, result) == 0) {   /* CdlSetmode */
            if ((result[0] & 0x10) == 0) break;
            func_80037334();
            streamLoad_state = 0;
            return 2;
        }
        D_800A4F28 = 0;
        streamLoad_state++;
        /* fall through */
    case 4:
        sync = func_8004355C(1, result);
        if (sync == 5) {
            streamLoad_state = 3;
            break;
        }
        if (sync != 2) {
            if (D_800A4F28 < 0x3D) break;
            streamLoad_state = 3;
            break;
        }
        streamLoad_state++;
        /* fall through */
    case 5:
        p2C = &D_800A4F2C;
        if (*p2C != 0) {
            *p2C -= 1;
            break;
        }
        streamLoad_state++;
        /* fall through */
    case 6:
        if (func_80037CD8((void *)func_80036260) == 0) break;
        streamLoad_state = 7;
        /* fall through */
    case 7:
        if (func_8003750C() == 0) break;
        streamLoad_state++;
        /* fall through */
    case 8:
        sync = func_8004355C(1, result);
        if (sync != 5 && sync != 2) break;
        streamLoad_state++;
        /* fall through */
    case 9:
        D_800A4F28 = 0;
        if (func_800435CC(0x15, loc, result) == 0) break;   /* CdlSeekL */
        streamLoad_state++;
        /* fall through */
    case 10:
        sync = func_8004355C(1, result);
        if (sync == 5) {
            if (func_800435CC(1, 0, result) == 0) {         /* CdlNop */
                streamLoad_state = 9;
                break;
            }
            if ((result[0] & 0x10) == 0) {
                streamLoad_state = 9;
                break;
            }
            func_80037334();
            D_8006AEF4 &= 0xFD;
            streamLoad_state = 0;
            return 2;
        }
        if (sync != 2) {
            if (D_800A4F28 < 0x12D) break;
            func_800434BC();
            streamLoad_state = 9;
            return 2;
        }
        streamLoad_state++;
        /* fall through */
    case 11:
        D_800A4F28 = 0;
        if (func_800435CC(6, loc, result) == 0) {           /* CdlReadN */
            if ((result[0] & 0x10) == 0) break;
            D_8006AEF4 &= 0xFD;
            func_80037334();
            streamLoad_state = 0;
            return 2;
        }
        if (streamLoad_cbActive == 0) {
            streamLoad_savedReadyCB = ((void *(*)(void *))CdReadyCallback)((void *)func_800377D8);
        } else {
            CdReadyCallback((void *)func_800377D8);
        }
        streamLoad_cbActive = 1;
        streamLoad_state++;
        return 0;   /* NOT `break` -- see the header note */
    case 12:
        if (func_800374CC(&pos) == 0) {
            p34 = &D_800A4F34;
            if (pos != *p34) {
                *p34 = pos;
                D_800A4F28 = 0;
            }
            if (D_800A4F28 < 0x12D) break;
            if (streamLoad_cbActive != 0) {
                CdReadyCallback(streamLoad_savedReadyCB);
                streamLoad_savedReadyCB = 0;
                streamLoad_cbActive = 0;
            }
            streamLoad_state++;
            break;
        }
        if (streamLoad_cbActive != 0) {
            CdReadyCallback(streamLoad_savedReadyCB);
            streamLoad_savedReadyCB = 0;
            streamLoad_cbActive = 0;
        }
        streamLoad_state++;
        /* fall through */
    case 13:
        if (func_8003775C() == 0) break;
        func_80037D74();
        streamLoad_state++;
        break;
    case 14:
        pb = (u8 *)func_80037368(&sync);
        if (sync != 1) {
            streamLoad_state = 0x11;
            break;
        }
        if (*pb == 1) {
            streamLoad_state++;
        } else if (*pb == 2) {
            *(u8 *)&D_800A4F38 = 1;
            streamLoad_state = 0x11;
            break;
        } else {
            p30 = &D_800A4F30;
            t = *p30;
            if (t == 0) {
                streamLoad_state = 1;
                break;
            }
            t -= 1;
            *p30 = t;
            if (t != 0) {
                streamLoad_state = 1;
                break;
            }
            streamLoad_state = 0x11;
            break;
        }
        /* fall through */
    case 15:
        if (func_800435CC(9, 0, result) == 0) {             /* CdlPause */
            if ((result[0] & 0x10) == 0) break;
            streamLoad_state = 0;
            return 1;
        }
        streamLoad_state++;
        break;
    case 16:
        sync = func_8004355C(1, result);
        if (sync != 5 && sync != 2) break;
        pb = (u8 *)&D_800A4F38;
        t = *pb;
        streamLoad_state = 0;
        if (t != 0) {
            *pb = 0;
            return 2;
        }
        return 1;
    case 17:
        if (func_800435CC(9, 0, result) != 0) streamLoad_state = 0x10;
        break;
    }
    return 0;
}
#endif


extern s32 D_8006A69C;
extern u8  D_8006A6A0;
extern s32 D_8006A6A4;
extern s32 D_8006AEE8;
extern s32 D_80078F10;
extern u8  D_800A46BA;
extern u8  D_800A4F1A;
extern s32 func_80034CF0(u8 *);
extern void func_80034DFC(short);
extern s32 func_80035270();    /* §376: def returns s32 and takes (s32) */
extern void func_800359B0();   /* §376: def takes (s32) */
extern void func_80036D24(void);
extern void func_80036FB0(s32, s32);

typedef struct {
    s32 f00;
    s32 f04;
    s32 f08;
    s32 f0c;
    s32 f10;
    s32 f14;
    s32 f18;
    s32 f1c;
    s32 f20;
    s32 f24;
    s32 f28;
    s32 f2c;
} CdReq;

void func_80036AF8(CdlLOC *loc, s32 flags) {
    register s32 zr __asm__("$0");
    CdReq req;
    s32 mode;
    s32 n;
    s32 idx;
    s32 lo;
    s16 h;
    s32 drv;
    s32 hi;
    u8 b;
    s32 i;
    s32 ret;
    u8 *rec;
    u8 *rec2;
    u8 *tbl;
    s32 hoff;

    mode = flags + zr;
    if (!(flags & 0x4000)) {
        return;
    }

    n = flags & 0xF;
    idx = n + zr;
    lo = (s32)(flags << 16) >> 20;
    drv = ((s32)(flags << 16) >> 25) & 0x1F;
    hi = drv + zr;
    h = lo & 0x1F;
    if (lo & 1) {
        if (*(u8 *)((u8 *)&D_8006A6A0 + drv * 0x48) != 0) {
            idx = n + 4;
        } else {
            idx = n + 8;
        }
    }

    h = h >> 1;
    rec = (u8 *)*(s32 *)((u8 *)&D_8006A69C + hi * 0x48);
    rec2 = rec + (h << 6);
    b = *(u8 *)(rec2 + (idx << 2) + 1);
    if ((b & 0xF0) == 0) {
        return;
    }

    if (D_8006AEE8 != 0) {
        if ((b & 0xF) == 0) {
            return;
        }
        if ((b & 0xF) == 1) {
            for (i = 0; i < D_8006AEE8; i++) {
                func_80034DFC(*(short *)(&D_80078F10 + i));
                (&D_80078F10)[i] = 0;
            }
            D_8006AEE8 = 0;
        }
    }

    req.f08 = (s32)func_80035270;
    D_800A46BA = 0;
    if (h != 0) {
        ret = CdPosToInt(loc);
        hoff = hi * 0x48;
        tbl = (u8 *)&D_8006A6A4;
        req.f0c = ret + *(s32 *)(tbl + hoff + h * 4);
    } else {
        req.f0c = CdPosToInt(loc);
    }
    req.f10 = (s16)mode;
    req.f1c = (s32)func_80036D24;
    req.f24 = (s32)func_800359B0;
    req.f20 = 0;
    req.f28 = (s32)func_80036FB0;
    ret = func_80034CF0((u8 *)&req);
    if (ret != 0) {
        (&D_80078F10)[D_8006AEE8] = ret;
        D_8006AEE8 = D_8006AEE8 + 1;
    }
    D_800A4F1A = 1;
}

extern s32 D_8006AEE8;
extern s32 D_80078F10;
extern u8 D_800A4F1A;

void func_80036D24(void) {
    s32 v0 = D_8006AEE8;
    D_80078F10 = 0;
    if (v0 < 2) {
        D_8006AEE8 = 0;
        D_800A4F1A = 0;
    }
}










extern s32 D_8006AEE8;
extern s32 D_80078F10;
extern s32 D_800C6D28;
extern u8 D_800A46BA;
extern u8 D_800A4F1A;
extern s16 D_800A4EF8;

extern s32 func_80034CF0(u8 *);
extern void func_80034DFC(s16);
extern s32 func_8003EDE8(s32, s32, s32);
extern s32 func_80035C4C();    /* §376: def returns s32 and takes (s32) */
extern void func_80036F98(void);
extern void func_8003602C(s32);   /* §376: the definition takes s32 (the use is address-taken and already cast) */
extern void func_80036FB0(s32, s32);

void func_80036D58(s16 arg0)
{
    CdReq req;
    s32 pad[2];
    s32 i;
    s16 *p;
    s32 r;
    s32 n;
    s32 cnt;

    if (arg0 != 0 || D_800C6D28 != 0) {
        D_800A46BA = 0;
        if (D_8006AEE8 != 0) {
            i = 0;
            if (D_8006AEE8 > 0) {
                p = (s16 *)&D_80078F10;
                do {
                    func_80034DFC(*p);
                    i++;
                    cnt = D_8006AEE8;
                    *(s32 *)p = 0;
                    p += 2;
                } while (i < cnt);
            }
            D_8006AEE8 = 0;
        }
        req.f08 = (s32)func_80035C4C;
        req.f0c = arg0;
        req.f1c = (s32)func_80036F98;
        req.f20 = 0;
        req.f24 = (s32)func_8003602C;
        req.f28 = (s32)func_80036FB0;
        r = func_80034CF0((u8 *)&req);
        n = D_8006AEE8;
        (&D_80078F10)[n] = r;
        if (r != 0) {
            D_8006AEE8 = n + 1;
        }
        D_800A4F1A = 0;
        if (arg0 != 0) {
            D_800C6D28 = 0;
        }
        func_8003EDE8(0, ((u32)D_800A4EF8 * 97) >> 7 & 0xFF, ((u32)D_800A4EF8 * 97) >> 7 & 0xFF);
    }
}



extern u8 D_800A4F1A;
extern s32 D_800C6D28;
extern void func_80036F18(void);

void func_80036EB4(void) {
    if (!D_800A4F1A) {
        func_80036F18();
        D_800C6D28 = 0;
    }
}


extern u8 D_800A4F1A;
extern s32 D_800C6D28;
extern void func_80036F18(void);

void func_80036EE8(void) {
    func_80036F18();
    D_800C6D28 = 0;
    D_800A4F1A = 0;
}

extern s32 D_800C6D28;
extern s32 D_80078F10;
extern s32 D_800A63E8;
extern s32 D_8006AEE8;
extern void func_80034DFC(short);

void func_80036F18(void) {
    s32 i;

    if (D_8006AEE8 != 0) {
        D_800C6D28 = D_800A63E8;
        for (i = 0; i < D_8006AEE8; i++) {
            func_80034DFC(*(short *)(&D_80078F10 + i));
            (&D_80078F10)[i] = 0;
        }
        D_8006AEE8 = 0;
    }
}

extern s32 D_80078F10;
extern s32 D_8006AEE8;

void func_80036F98(void) {
    D_80078F10 = 0;
    D_8006AEE8 = 0;
}

void func_80036FB0(s32 arg0, s32 arg1) {
    extern s32 D_8006AEE8;
    extern s32 D_80078F10;
    f64 hole;
    s32 count;
    s32 i;
    s32 *p;

    __asm__ volatile("" ::
                     "m"(hole));
    if (D_8006AEE8 > 0) {
        i = 0;
        count = D_8006AEE8;
        p = &D_80078F10;
        do {
            if (*p == arg0) {
                *p = arg1;
            }
            p++;
            i++;
        } while (i < count);
    }
}

CLEAR_TBL40(func_80037004)  /* dedup I0: shared body (src/shared/clearTbl40.h) */


/* func_80037028 -- resource-slot allocator (5 slots x 0x10 bytes at 0x80076244).
 *
 * MATCHING NOTES (P31 second pass, cookbook §31 / sched.md S1+S5):
 *
 * 1) The slot table MUST be modelled as struct arrays with symbol+scaled-index
 *    addressing (`sw $5,D_80076240+4($4)`), not as six independent `u8 X[]`
 *    externs indexed by a byte offset.  With separate symbols gcc hoists the
 *    D_80064D49 load chain to the top of the block and sinks the mark-used
 *    store (37 mismatches); with the struct form the block is exact.
 *
 * 2) TWO overlapping bases are used on purpose (D_80076240 for the words,
 *    D_80076244 for the bytes) so that EVERY field access has a NON-ZERO
 *    constant offset from its base symbol.  sched.c:memrefs_conflict_p reaches
 *    find_symbolic_term() -- and therefore proves "distinct symbols, no alias"
 *    -- only for the plain `(plus reg symbol_ref)` form.  A zero-offset store
 *    thus loses its dependence on the later D_80064D49 / D_800A463C loads,
 *    becomes ready immediately and floats to the bottom of the block.  With a
 *    single base at D_80076244 the `unk00 = val` store did exactly that
 *    (19 mismatches).  Every offset here is non-zero, so all four leading
 *    stores stay pinned behind the loads and are emitted in source order.
 *    Final addresses are unchanged: D_80076240+4 == D_80076244, +8 == 248,
 *    +12 == 24C; D_80076244+12 == D_80076250, +13 == 251, +14 == 252.
 *
 * 3) `D_8007622C[0]` (not a plain scalar) is required by the /s asymmetry in
 *    sched.c:true_dependence -- a non-MEM_IN_STRUCT_P, non-varying store is
 *    assumed not to alias a MEM_IN_STRUCT_P varying load, so the D_800A463C
 *    reload hoisted above it.  Making the store an ARRAY_REF sets /s, kills
 *    the exclusion clause, and pins the reload after it.
 *
 * 4) D_80076248 is deliberately never named: src/800.c already declares it as
 *    `extern Rsc16 D_80076248[]`, and a second `extern u8 D_80076248[]` here
 *    would be a conflicting-types error at bank time.
 */





extern Slot16A D_80076240[];
extern Slot16 D_80076244[];
extern Elm12   D_80064D49[];
extern Ent24   D_800A463C[];
extern u8  D_80076251;
extern s32 D_8007622C[];
extern W32 D_80076228;
extern W8  D_80076243;
extern W8  D_80076242;
extern W32 D_80076294;
extern W32 D_80076238;
extern s32 D_8007629C;

void func_80037028(s32 base, s32 val) {
    s32 slot;
    s32 i;
    s32 b;

    for (slot = 0, i = 0; slot < 5; slot++, i += 0x10) {
        if ((&D_80076251)[i] == 0) {
            break;
        }
    }

    if (slot < 5) {
        D_80076244[slot].unk0D = 1;
        D_80076240[slot].unk04 = val;
        D_80076244[slot].unk0C = 0;
        D_80076240[slot].unk08 = base;
        b = D_80064D49[base].unk00;
        D_80076244[slot].unk0E = b;
        D_80076240[slot].unk0C = D_800A463C[b].unk00;

        if (slot == 0) {
            s32 r;
            D_8007622C[0] = val;
            r = D_800A463C[b].unk00;
            D_80076228.v = val;
            D_80076240[0].unk00 = 0;
            D_80076243.v = 2;
            D_80076242.v = 0;
            D_80076294.v = 0;
            D_80076238.v = r;
        }
    }

    D_8007629C = 0;
}


/* The 5-entry, 0x10-stride CD-resource slot table.  src/800.c already declares the SAME
 * memory as `Rsc16 D_80076248[]` (base = 0x80076248, .unk09 = D_80076251, .unk0A = D_80076252);
 * this function also touches the word 4 bytes BELOW that base, so the array is spelled from
 * D_80076244 here (offsets shift by -4; the emitted %lo values are identical, and every one of
 * D_80076244/48/4C/50/51/52 is a relocation symbol in this function's own .s).
 *      .unk00 = D_80076244   .unk04 = D_80076248   .unk08 = D_8007624C
 *      .unk0C = D_80076250   .unk0D = D_80076251   .unk0E = D_80076252
 * 0x80076244 + 5*0x10 == 0x80076294, which is the next scalar this function clears. */

/* 2-byte stride u16 table.  Declared as an array-of-STRUCT (cookbook §18) so gcc folds
 * %lo(D_80065438) into each indexed load instead of materialising the base into a register
 * (a plain `extern u16 D_80065438[]` CSEs the two accesses into one lui/addiu/addu base). */


/* THE TAIL SCHEDULE LEVER (gcc-2.7.2 sched.c:817 true_dependence / :845 anti_dependence).
 * The `if (i == 0)` block interleaves the varying-address load `D_800A463C[k].unk00`
 * (MEM_IN_STRUCT_P=1, rtx_addr_varies_p=1) with fixed-address stores to these scalars.
 * true_dependence's last guard reads
 *      ! (MEM_IN_STRUCT_P (x) && rtx_addr_varies_p (x) && GET_MODE (x) != QImode
 *         && ! MEM_IN_STRUCT_P (mem) && ! rtx_addr_varies_p (mem))
 * so a /s VARYING load and a plain NON-/s FIXED store are declared non-aliasing — every
 * store/load edge disappears, the load floats to the top of the block and the whole tail
 * comes out permuted.  Declaring these scalars as single-field structs sets MEM_IN_STRUCT_P
 * on their MEMs too, which fails `! MEM_IN_STRUCT_P (mem)` and restores the real
 * store->load / load->store edges.  The symbol names are untouched (offset 0 of a 1-field
 * struct), so every relocation is still exactly D_8007622C / D_80076228 / ... as in the .s. */

extern Slot16 D_80076244[];
extern W32   D_80076228;
extern s32   D_8007622C[];
extern W32   D_80076238;
extern Slot16A D_80076240[];
extern W8    D_80076242;
extern W8    D_80076243;
extern W32   D_80076294;
extern s32   D_8007629C;       /* src/800.c already declares this one as `extern s32` */
extern u8    D_800BA320[];
extern H2    D_80065438[];
extern s32   D_800652F0[];
extern Ent24 D_800A463C[];
extern s32   D_800A469C;
extern s16   D_800A46A0;
extern s16   D_800A46A2;
extern u8    D_800A46B0;

extern void  func_800415A8(s32);

void func_80037144(s32 idx) {
    s32 i;
    s32 k;
    s32 t;
    s32 v;
    s32 one;
    s32 ent;

    for (i = 0; i < 5; i++) {
        if (D_80076244[i].unk0D == 0) {
            break;
        }
    }
    if (i < 5) {
        one = 1;
        D_80076244[i].unk00 = (s32)D_800BA320;
        /* scheduling barrier: the slot stores and the D_80065438 load DO disambiguate here
         * (both /s and both varying -> memrefs_conflict_p:614 falls through to
         * find_symbolic_term and the two symbols differ), so without this gcc hoists the
         * D_80065438 load above all the slot stores and permutes the head block.
         * Emits zero instructions. */
        __asm__ __volatile__("" ::: "memory");
        D_80076244[i].unk0C = 0;
        D_80076244[i].unk0D = one;
        D_80076244[i].unk04 = idx | 0x2000;
        D_80076244[i].unk0E = 4;
        v = D_800652F0[D_80065438[idx].f0];
        D_800A469C = v;
        D_80076244[i].unk08 = v;
        k = 4;
        if (D_800A46B0 == 0) {
            if (D_800A46A0 == (D_80065438[idx].f0 | 0x4000)) {
                D_80076244[i].unk04 |= 0x1000;
                goto after;
            }
            t = D_800A46A2;
            D_800A46B0 = one;
        } else {
            t = D_800A46A2;
        }
        if (t >= 0) {
            func_800415A8(t);
            D_800A46A2 = -1;
        }
    after:
        if (i == 0) {
            D_8007622C[0] = (s32)D_800BA320;
            ent = D_800A463C[k].unk00;
            D_80076228.v = (s32)D_800BA320;
            D_80076240[0].unk00 = 0;
            D_80076243.v = 1;
            D_80076242.v = 0;
            D_80076294.v = 0;
            D_80076238.v = ent;
        }
    }
    D_8007629C = 0;
}

CLEAR_TBL40(func_80037334)  /* dedup I0: shared body (src/shared/clearTbl40.h) */

extern s32 D_8007623C;
void func_80037358(int posInt) {
    D_8007623C = posInt;
}


extern u8 D_80076251;   /* Law 2: exact form from src/shared/clearTbl40.h */
extern u8 D_80076220[];
extern u8 D_80076250[];

void *func_80037368(int *out) {
    int count = 0;
    u8 *ptr = D_80076220;
    int i;

    for (i = 0; i < 0x50; i += 0x10) {
        *ptr = 0;
        ptr++;

        if ((&D_80076251)[i] != 0) {
            D_80076220[count] = D_80076250[i];
            count++;
        }
    }

    *out = count;
    return D_80076220;
}



typedef struct {
    s16 unk00;
    u8  pad02[4];
    u16 unk06;
} StructA4E88;

/* Law 2: the destination TU (src/800.c) already declares D_80065438 as an array-of-struct
 * (H2 = { u16 f0; }) rather than a plain u16[] — refuse-TYPE(D_80065438, u16 vs H2).
 * Adopt the TU's spelling verbatim; the use site indexes .f0 instead of dereferencing a u16*. */

extern StructA4E88 D_800A4E88;
extern u8           D_800BA320[];
extern Rsc16        D_80076248[];    /* .unk09 = D_80076251, .unk0A = D_80076252 */
extern u8           D_80076251;      /* Law 2: exact form from src/shared/clearTbl40.h (see func_80037368) */
extern u8           D_80076250[];
extern u8           D_80076298;
extern H2           D_80065438[];

extern void func_8002D7FC(s32 arg0);
extern void func_8002FDE8(s32 arg0, void *arg1);

void func_800373D0(void) {
    register StructA4E88 *sp2 __asm__("$18");
    register u8          *sp3 __asm__("$19");
    register Rsc16 *p __asm__("$16");
    register s32 i __asm__("$17");

    sp2 = &D_800A4E88;
    sp3 = D_800BA320;

    p = D_80076248;
    i = 0;
    do {
        if ((&D_80076251)[i] != 0) {
            if (D_80076250[i] != 0) {
                if (p->unk00 & 0x3000) {
                    sp2->unk00 = p->unk00 & 0xFFF;
                    sp2->unk06 |= 0x20;
                    func_8002D7FC((s32) sp3);
                    if (!(p->unk00 & 0x1000)) {
                        func_8002FDE8(D_80065438[sp2->unk00].f0, sp3 + 0x7000);
                    }
                }
            }
        }
        p++;
        i += 0x10;
    } while ((s32) p < (s32) &D_80076298);
}

int func_800374CC(int *out)
{
    extern W8 D_80076243;
    extern s32 D_8007623C;

    s32 x = D_80076243.v;
    if (x != 4 && x != 0 && x != 5) {
        *out = D_8007623C;
        return 0;
    }
    return 1;
}





extern s32  D_8007629C;
extern u8   D_8006AEF4;
extern u8   D_80076298;
extern Rsc16 D_80076248[];    /* .unk09 = D_80076251, .unk0A = D_80076252 */
extern Rsc12 D_80064D4A[];
extern Rsc24  D_800A4640[];
extern s16  D_800C5328[];
extern s16  D_800C532A[];

extern s32  func_8003C4F0(s32);
extern void func_800415A8(s32);
extern void func_80031A98(void);

s32 func_8003750C(void) {
    s32 i;
    s32 val;
    s32 k;
    s32 h;

    switch (D_8007629C) {
    case 0:
        if (D_8006AEF4 & 2) {
            return 0;
        }
        D_8006AEF4 |= 2;
        D_8007629C = 1;
        /* fallthrough */
    case 1:
        if (D_8006AEF4 & 1) {
            if (func_8003C4F0(0) == 0) {
                return 0;
            }
        }
        D_8007629C = D_8007629C + 1;
        /* fallthrough */
    case 2:
        for (i = 0; i < 5; i++) {
            if (D_80076248[i].unk09 == 0) {
                continue;
            }
            val = D_80076248[i].unk00;
            k = D_80076248[i].unk0A;
            if (val & 0x6000) {
                continue;
            }
            h = D_800A4640[k].unk04;
            if (h != 0 && h != D_80064D4A[val].unk00) {
                D_800C532A[D_800A4640[k].unk08 * 2] = -1;
                D_800A4640[k].unk04 = 0;
                D_800A4640[k].unk08 = 0;
            }
            if (D_800A4640[k].unk10 != 0) {
                continue;
            }
            D_800A4640[k].unk10 = 1;
            D_800C5328[D_800A4640[k].unk00 * 2] = -1;
            if (D_800A4640[i].unk02 >= 0) {
                func_800415A8(D_800A4640[i].unk02);
                D_800A4640[i].unk02 = -1;
            }
            func_80031A98();
        }
        D_8007629C = 0;
        D_80076298 = 0;
        return 1;
    default:
        return 0;
    }
}

typedef struct { u8 v; } W8_;
extern W8_ D_80076242_ __asm__("D_80076242");

extern u8  D_8006AEF4;
extern s32 func_8003C4F0(s32);
extern void func_800373D0(void);

int func_8003775C(void) {
    u32 t;

    if (D_80076242_.v != 0) {
        if (func_8003C4F0(0) == 0) {
            return 0;
        }
        D_80076242_.v = 0;
        t = D_8006AEF4;
    } else {
        t = D_8006AEF4;
    }
    D_8006AEF4 = t & 0xFC;
    func_800373D0();
    return 1;
}

/* func_800377D8 -- the CD stream loader's CdlReadN ready-callback (main/src/800.c, 316 ins).
 *
 * ⚠ BANKING PREREQUISITE (§376/§378, step 1 ONLY): src/800.c:21344 already carries
 *     extern void  func_800377D8(void);   // this loader's CdlReadN ready-callback
 *   which CONFLICTS with this definition's `(u8 arg0)`.  No-proto it before gating:
 *     tools/fix_arity_callers.py --binary main --funcs func_800377D8 --any-proto --apply ...
 *   Step 2 (cast_self_callers) is NOT needed: the only two uses (src/800.c:21488/21490)
 *   take its ADDRESS through a `(void *)` cast, they never call it.
 *
 * MATCHING NOTES -- four levers, each measured on this function:
 *
 * 1) THE SCALARS MUST NOT BE THE TU's `W8`/`W32` SINGLE-FIELD STRUCTS HERE.  With
 *    `W8 D_80076243` / `W32 D_80076228` / `W32 D_80076242` cc1 materialises each symbol's
 *    ADDRESS into a callee-saved register ($s2/$s3/$s4, frame 0x20 -> 0x28) and every access
 *    becomes `0($sN)`; the target folds `%lo` into each mem.  Cookbook index L18
 *    ("an extra `la` / the address hoisted into a callee-saved register across calls" ->
 *    §20 + gcc-2.7.2-map/cse_expr.md §H) names the antidote: the §37 asm-label alias keeps the
 *    direct `%lo` mem form.  Hence gD_/hD_/sD_ aliases -- they also cannot conflict with the
 *    TU's existing `extern W8 D_80076243;` etc. (Law 2 satisfied by construction.)
 *    D_80076294 was measured BOTH ways: as `W32` it hoists too, so it is aliased as well.
 *
 * 2) TWO ALIASES FOR D_80076240, DELIBERATELY (§326).  The target reads the counter `lhu`
 *    (u16, the +1 RMW) in cases 2/3 and `lh` (s16) for the two comparisons.  Separate decls
 *    give the two widths AND stop address-CSE from sharing one base register between them.
 *    Case 1 needs the THIRD form -- a pointer var (§20's global-RMW bullet) -- because the
 *    target keeps `&D_80076240` in $a0 across the RMW and the `sh $zero,0($a0)` at .L800379E4.
 *
 * 3) TWO ZERO-BYTE `__asm__ __volatile__("")` FENCES, for two different passes:
 *    a) in case 1's `= 1` arm: without it gcc's cross-jump merges case 1's one-insn
 *       `D_80076243 = 1; j .L80037BC0` block into case 3's identical copy (-2 ins, 314/316).
 *       gcc-2.7.2 compares a jump's predecessors against its TARGET LABEL's predecessors with
 *       a 2-insn minimum -- which is exactly why the target merges the `= 2` arm into .L80037BB8
 *       (2 insns: the `sb` + the `li 2`) but leaves the `= 1` arm and both `= 4` blocks alone.
 *    b) in the shared .L80037BC0 tail, between the two zero-stores and the D_80076294 reload:
 *       the /s-vs-fixed asymmetry in sched.c:true_dependence lets the (varying, /s) D_80076244[]
 *       loads float above the (fixed, non-/s) `sb D_80076298`/`sh D_80076240`, permuting the
 *       whole tail (11 -> 25 rows).  Same class as the sched note above func_80037144.
 *
 * 4) THE $v0/$v1 PIN IN CASE 1 (memory: "don't conclude unsteerable -- try register pins").
 *    Last 5 rows: the target emits `sh` (counter) BEFORE `sw D_80076228`, but loads
 *    D_80076228 BEFORE the counter.  Written in-place the stores keep source order (the
 *    pointer store is varying -> no disambiguation) and come out sw-then-sh; split through a
 *    temp the stores are right but sched1 swaps the two LOADS and the registers with them.
 *    Splitting AND pinning the two temps to $2/$3 gives both: the second set on each pseudo
 *    also rotates local-alloc's priority (cse_expr.md §H(2)).  0 residual.
 */
#include "psyq/libcd.h"    /* CdlLOC / CdPosToInt -- the TU already includes it */


                      /* 0x10 */
                      /* 0x10 */

extern u8      D_8006AEF4;
extern u8      D_800762A0[];
extern s32     D_8007623C;
extern s32     gD_80076228 __asm__("D_80076228");
extern s32     gD_80076238 __asm__("D_80076238");
extern Slot16A D_80076240[];
extern u16     hD_80076240 __asm__("D_80076240");
extern s16     sD_80076240 __asm__("D_80076240");
extern u8      gD_80076242 __asm__("D_80076242");
extern u8      gD_80076243 __asm__("D_80076243");
extern Slot16  D_80076244[];
extern Rsc16   D_80076248[];
extern u8      D_80076250[];
extern u8      D_80076251;
extern s32     gD_80076294 __asm__("D_80076294");
extern u8      D_80076298;

extern s32  func_80043994(void *buf, s32 n);
extern s32  func_8003C4F0(s32);
extern void func_8003C498(s32);
extern void SpuWrite(s32, s32);

void func_800377D8(u8 arg0) {
    s32 *pInt;
    u8  *pSt;
    s32 pos;
    s32 idx;
    s32 ptr;
    s32 nxt;
    u16 *pCnt;
    s32 cnt;

    if (arg0 != 1) goto err;
    if (func_80043994(D_800762A0, 3) == 0) goto err;
    pos = CdPosToInt((CdlLOC *)D_800762A0);
    pInt = &D_8007623C;
    if (pos != *pInt) goto err;
    *pInt = pos + 1;

    switch (gD_80076243) {
    case 1:
        if (func_80043994((void *)gD_80076228, 0x200) == 0) goto err;
        if (sD_80076240 == 0 && *(s32 *)gD_80076228 != 0x7671732E) {
            D_80076298 = 1;
            D_80076250[gD_80076294 * 16] = 2;
            goto err;
        }
        {
        register s32 rnxt __asm__("$2");
        register s32 rcnt __asm__("$3");
        pCnt = &hD_80076240;
        rnxt = gD_80076228 + 0x800;
        rcnt = *pCnt + 1;
        *pCnt = rcnt;
        gD_80076228 = rnxt;
        if ((s16)rcnt != 0xE) {
            return;
        }
        }
        if (D_80076248[gD_80076294].unk00 & 0x1000) {
            D_80076250[gD_80076294 * 16] = 1;
            idx = gD_80076294 + 1;
            gD_80076294 = idx;
            if (idx < 5 && (&D_80076251)[idx * 16] != 0) {
                if (D_80076248[idx].unk00 & 0x2000) {
                    gD_80076243 = 1;
                    __asm__ __volatile__("");
                } else {
                    gD_80076243 = 2;
                }
                D_80076298 = 0;
                hD_80076240 = 0;
                __asm__ __volatile__("");
                gD_80076228 = D_80076244[gD_80076294].unk00;
                gD_80076238 = D_80076244[gD_80076294].unk08;
                return;
            }
            gD_80076243 = 4;
            D_8006AEF4 = D_8006AEF4 & 0xFD;
            return;
        }
        gD_80076243 = 2;
        *pCnt = 0;
        return;

    case 2:
        if (func_80043994((void *)gD_80076228, 0x200) == 0) goto err;
        gD_80076228 = gD_80076228 + 0x800;
        hD_80076240 = hD_80076240 + 1;
        if ((s16)hD_80076240 != 7) {
            return;
        }
        gD_80076243 = 3;
        hD_80076240 = 0;
        if (gD_80076242 != 0) {
            if (func_8003C4F0(0) == 0) {
                return;
            }
            gD_80076242 = 0;
        }
        return;

    case 3:
        if (func_80043994((void *)gD_80076228, 0x200) == 0) goto err;
        hD_80076240 = hD_80076240 + 1;
        if (gD_80076242 != 0) {
            if (func_8003C4F0(0) == 0) goto err;
        }
        if (((s32 (*)(s32))func_8003C498)(gD_80076238) == 0) goto err;
        ptr = gD_80076228;
        if (sD_80076240 == *(s16 *)(ptr - 4)) {
            SpuWrite(ptr, *(s16 *)(ptr - 2));
            gD_80076242 = 1;
            D_8006AEF4 = D_8006AEF4 | 1;
            D_80076250[gD_80076294 * 16] = 1;
            idx = gD_80076294 + 1;
            gD_80076294 = idx;
            if (idx < 5 && (&D_80076251)[idx * 16] != 0) {
                if (D_80076248[idx].unk00 & 0x2000) {
                    gD_80076243 = 1;
                } else {
                    gD_80076243 = 2;
                }
                D_80076298 = 0;
                hD_80076240 = 0;
                __asm__ __volatile__("");
                gD_80076228 = D_80076244[gD_80076294].unk00;
                gD_80076238 = D_80076244[gD_80076294].unk08;
                return;
            }
            gD_80076243 = 4;
            D_8006AEF4 = D_8006AEF4 & 0xFD;
            return;
        }
        SpuWrite(ptr, 0x800);
        gD_80076242 = 1;
        D_8006AEF4 = D_8006AEF4 | 1;
        gD_80076238 = gD_80076238 + 0x800;
        return;
    }
    return;

err:
    pSt = &gD_80076243;
    if (*pSt == 0) return;
    if (*pSt == 4) return;
    if (*pSt == 5) return;
    *pSt = 5;
    D_8006AEF4 = D_8006AEF4 & 0xFD;
}


extern s32 D_800BA0F8;
void func_80037CC8(void) {
    D_800BA0F8 = 0;
}


extern u8 D_8006AEF4;
extern s32 D_800BA0F8;

int func_80037CD8(void *arg) {
    if ((D_8006AEF4 & 0x2) != 0) {
        s32 *handler = (s32 *)&D_800BA0F8;

        if (*handler != 0) {
            int result = ((int (*)(void *))*handler)(arg);

            if (result != 0) {
                u8 flags = D_8006AEF4;
                *handler = (s32)arg;
                D_8006AEF4 = flags & 0xFD;
                return 1;
            }
            return 0;
        }
    }

    D_800BA0F8 = (s32)arg;
    D_8006AEF4 &= 0xFD;
    return 1;
}

extern u8 D_8006AEF4;
extern s32 D_800BA0F8;

void func_80037D74(void) {
    D_8006AEF4 &= 0xFD;
    D_800BA0F8 = 0;
}


extern u8 *D_800762B0;
extern u8 D_800A4EFE[];
extern s32 D_80073140[];

extern u8 D_800C6DE0[];
extern u8 D_800C6DE4[];
extern u8 D_800C6DEC[];
extern u8 D_800C6DEE[];
extern u8 D_800C6E2A[];
extern u8 D_800C6E2B[];
extern u8 D_800C6E2C[];
extern u8 D_800C6E2D[];
extern u8 D_800C6E2E[];

extern u8 D_800B9EC8[];
extern u8 D_800B9ED2[];
extern u8 D_800B9ED3[];

extern s32 D_80079A68;
extern void func_8003D424(s32 *);

void func_80037D98(void) {
    s32 i;
    s32 offset;
    s32 val;
    s32 *table;

    D_800762B0 = D_800A4EFE;

    i = 0;
    table = D_80073140;
    offset = 0;
    while (i < 0x10) {
        val = *table;
        table++;
        i++;
        D_800C6E2A[offset] = 0;
        D_800C6E2B[offset] = 0;
        D_800C6E2C[offset] = 0;
        D_800C6E2D[offset] = 0;
        *(s16 *)&D_800C6DEC[offset] = 0;
        *(s16 *)&D_800C6DEE[offset] = 0;
        *(s32 *)&D_800C6DE4[offset] = 0;
        D_800C6E2E[offset] = 0;
        *(s32 *)&D_800C6DE0[offset] = val;
        offset += 0x60;
    }

    i = 0;
    offset = 0;
    for (; i < 2; i++) {
        D_800B9ED3[offset] = 0;
        D_800B9ED2[offset] = 0;
        *(s16 *)&D_800B9EC8[offset] = i;
        offset += 0x1FC;
    }

    func_8003D424(&D_80079A68);
}

extern u8 D_800C6E2E[];

void func_80037EA0(void)
{
    extern void func_8003D3B4(s32, s32);
    register u8 *p __asm__("$16");
    register s32 i __asm__("$17");
    register u32 mask __asm__("$18");

    i = 0;
    mask = 0xFFF9FFFF;
    p = D_800C6E2E;
    do {
        if (p[-4] != 0 && p[-1] == 0 && p[0] != 0) {
            func_8003D3B4(i, 8);
            *(u32 *)(p - 0x4A) &= mask;
            p[0] = 0;
        }
        i++;
        p += 0x60;
    } while (i < 0x10);
}

void func_80037F3C(void)
{
    /* TU-absent names, block scope */
    extern u8 D_800C6DD0[];
    extern void func_8003B250(s32, void *);

    register u8 *p __asm__("$16");
    register s32 i __asm__("$17");
    u8 *base;

    base = D_800C6DD0;
    i = 0;
    p = base + 0x5E;
    do {
        if (p[-4] != 0 && p[-1] != 0) {
            func_8003B250(i, base + 0x10);
            *(u32 *)(p - 0x4A) = 0;
            p[-1] = 0;
            p[0] = 0;
        }
        i++;
        p += 0x60;
        base += 0x60;
    } while (i < 0x10);
}

/* --- TU context as in src/800.c (file-scope, verbatim spellings) --- */
extern s32 D_800A2B98;
extern s32 D_800A2BA0;
extern s32 D_800C7D20;
extern s32 D_800C7D2C;
extern u8  D_800A4F1D;
extern u8 D_800C6E2E[];
extern void func_8003BE74(s32, s32);
extern void func_80037FC4(void);

void func_80037FC4(void)
{
    /* TU-absent names, block scope */
    extern u8 D_800C6DD0[];
    extern void func_80038A58(void);
    extern void func_8003D3B4(s32, s32);
    extern void func_8003C23C(s32, s32);
    extern void func_8003B250(s32, void *);

    register u8 *p __asm__("$16");
    register s32 i __asm__("$17");
    register u32 mask __asm__("$18");
    u8 *base;

    if (D_800A4F1D == 0) {
        func_80038A58();
    }

    i = 0;
    mask = 0xFFF9FFFF;
    p = D_800C6E2E;
    do {
        if (p[-4] != 0 && p[-1] == 0 && p[0] != 0) {
            func_8003D3B4(i, 8);
            *(u32 *)(p - 0x4A) &= mask;
            p[0] = 0;
        }
        i++;
        p += 0x60;
    } while (i < 0x10);

    if ((D_800A2B98 & 0xFFFF) != 0) {
        func_8003C23C(0, D_800A2B98 & 0xFFFF);
        D_800A2B98 &= 0xFF0000;
    }

    if ((D_800A2BA0 & 0xFFFF) != 0) {
        func_8003BE74(0, D_800A2BA0 & 0xFFFF);
        D_800A2BA0 &= 0xFF0000;
    }

    base = D_800C6DD0;
    i = 0;
    p = base + 0x5E;
    do {
        if (p[-4] != 0 && p[-1] != 0) {
            func_8003B250(i, base + 0x10);
            *(u32 *)(p - 0x4A) = 0;
            p[-1] = 0;
            p[0] = 0;
        }
        i++;
        p += 0x60;
        base += 0x60;
    } while (i < 0x10);

    if ((D_800C7D20 & 0xFFFF) != 0) {
        func_8003C23C(1, D_800C7D20 & 0xFFFF);
        D_800C7D20 &= 0xFF0000;
    }

    if ((D_800C7D2C & 0xFFFF) != 0) {
        func_8003BE74(1, D_800C7D2C & 0xFFFF);
        D_800C7D2C &= 0xFF0000;
    }
}

extern u8 D_800B9CD8[];

void func_8003819C(s32 a0, s32 a1, s32 a2, s32 a3) {
    u8 *base;
    s16 idx;

    idx = (s16)a1;
    if (idx <= 0) {
        base = &D_800B9CD8[((a0 << 7) - a0) << 2];
        *(s16 *)(base + (idx << 3) + 0x16) = a2;
        *(s16 *)(base + (idx << 3) + 0x14) = a3;
        *(u8 *)(base + (idx << 3) + 0x18) = 1;
        *(u8 *)(base + 0x1F4) = 1;
    }
}


extern u8 D_800B9CF0[];

s32 func_800381E4(s32 a0, s32 a1) {
    s32 v0;

    a1 = (a1 << 16) >> 13;
    v0 = (a0 << 7) - a0;
    v0 = v0 << 2;
    a1 = a1 + v0;
    return D_800B9CF0[a1];
}


extern u8 D_800B9CD8[];
extern u8 D_800C1320[];
extern u8 *D_800A6428;

extern s32 func_80038698(void *arg0);
extern s32 func_800387C0(void *arg0);
extern void func_80038838(void *arg0);

s32 func_80038210(s32 a0, s16 a1, s32 a2)
{
    u8 *entry;
    s32 i;
    s32 k;
    u8 *q;
    s32 v1;

    entry = D_800B9CD8;
    for (i = 0; i < 2; i++, entry += 0x1FC) {
        if (entry[0x1FB] == 0) {
            D_800A6428 = entry + 0x1BA;
            *(s32 *)entry = a0;
            *(s16 *)(entry + 0x1EC) = a1;
            *(s32 *)(entry + 0x1E8) = a2;
            *(u8 **)(entry + 0x1D8) = D_800C1320;
            *(u8 **)(entry + 0x1DC) = D_800C1320 + 0x20;
            *(u8 **)(entry + 0x1E0) = D_800C1320 + 0x820;
            if (func_80038698(entry) != 0) {
                return -1;
            }
            if (func_800387C0(entry) != 0) {
                return -1;
            }
            func_80038838(entry);
            v1 = *(s32 *)entry;
            entry[0x1FB] = 1;
            *(s32 *)(entry + 4) = v1;
            entry[0x1FA] = 0;
            for (k = 0xF, q = entry + 0xF; k >= 0; k--, q--) {
                q[0x1BA] = 0;
            }
            return i;
        }
    }
    return -1;
}

extern u8 D_800B9ED2[];
extern u8 D_800B9CD8[];

typedef s32 a32;

void func_80038308(s16 a0)
{
    register a32 arg0 asm("$4");
    s32 offset;

    offset = arg0 * 127;
    offset = offset * 4;
    D_800B9ED2[offset] = 1;
    func_80038908(&D_800B9CD8[offset]);
}

extern u8 D_800B9ECA[];

void func_8003834C(s32 a0, s16 a1) {
    s32 offset = ((a0 << 7) - a0) << 2;
    *(s16 *)&D_800B9ECA[offset] = a1;
}


extern u8 D_800B9ED3[];
extern u8 D_800B9ED2[];

s32 func_8003836C(s32 a0) {
    s32 index;
    u8 val;
    index = a0 * 127;
    index = index * 4;
    val = D_800B9ED3[index];
    if (val == 0) {
        return 0;
    }
    return D_800B9ED2[index];
}

extern u8 D_800B9CD8[];
extern u8 D_800A4F1D;
extern u8 D_800C6E2D[];
extern s32 D_80073140[];
extern void func_8003916C(s16 arg0);
extern void func_8002EFF8(s32 a0, s32 a1);

void func_800383A4(a0)
    s16 a0;
{
    u8 *base;
    u8 *p;
    u8 *q;
    u8 *r;
    s32 *t;
    s32 *table;
    s32 i;
    s32 j;
    s32 one;
    register s32 aa __asm__("$2");

    __asm__("sll %0, %1, 7\n\tsubu %0, %0, %1\n\tsll %0, %0, 2" : "=r"(aa) : "r"(a0));
    base = &D_800B9CD8[aa];
    p = base + 0x1A;
    i = 0;
    one = 1;
    table = D_80073140;
    D_800A4F1D = 1;
    base[0x1FA] = 0;
    do {
        q = p + 9;
        j = 0;
        r = D_800C6E2D;
        t = table;
        do {
            if (*q++ != 0) {
                r[1] = one;
                r[0] = 0;
                func_8003916C((s16)j);
                func_8002EFF8(0, *t);
            }
            t++;
            j++;
            r += 0x60;
        } while (j < 0x10);
        i++;
        p += 0x1A;
    } while (i < 0x10);
    D_800A4F1D = 0;
}

extern u8 D_800A4F1D;
extern s32 D_80073140[];
extern u8 D_800B9CD8[];
extern u8 D_800C6E2D[];
extern void func_8002EFF8(s32 a0, s32 a1);
extern void func_8003916C(s16 arg);

void func_800384A8(s16 arg0) {
    register s32 raw __asm__("$4");
    u8 *entry;
    u8 *p;
    u8 *q;
    s32 j;
    u8 *b;
    s32 *m;
    s32 *mb;
    s32 i;
    s32 one;

    entry = &D_800B9CD8[raw * 0x1FC];
    p = entry + 0x1A;
    i = 0;
    one = 1;
    mb = D_80073140;
    D_800A4F1D = 1;
    entry[0x1FA] = 0;
    for (; i < 0x10; i++) {
        q = p + 9;
        j = 0;
        b = D_800C6E2D;
        m = mb;
        for (; j < 0x10; j++) {
            if (*q++ != 0) {
                b[1] = one;
                b[0] = 0;
                func_8003916C(j);
                func_8002EFF8(0, *m);
            }
            m++;
            b += 0x60;
        }
        p += 0x1A;
    }
    D_800A4F1D = 0;
    *(s32 *)entry = *(s32 *)(entry + 4);
}

void func_800385C0(s16 a0)
{
    extern u8 D_800C6E2A[];
    extern u8 D_800B9ED2[];
    extern u8 D_800B9ED3[];
    register s32 a0v __asm__("$4");
    register u8 *v1 __asm__("$3");
    s32 a1;

    for (a1 = 0, v1 = D_800C6E2A; a1 < 0x10; a1++, v1 += 0x60) {
        if (v1[2] != 0 && *(s16 *)(*(s32 *)(v1 - 0xA) + 0x1F0) == a0v) {
            v1[2] = 0;
            v1[0] = 0;
        }
    }

    D_800B9ED2[((a0v << 7) - a0v) << 2] = 0;
    D_800B9ED3[((a0v << 7) - a0v) << 2] = 0;
}


extern u8 D_800B9E92[];

void func_80038638(s32 a0, s32 a1) {
    u8 *ptr;
    s32 offset;
    offset = a0 * 127;
    offset = offset * 4;
    ptr = D_800B9E92 + offset;
    *(ptr + a1) |= 1;
}


extern u8 D_800B9E92[];

void func_80038668(s32 a0, s32 a1) {
    s32 offset = ((a0 << 7) - a0) << 2;
    char *baseptr = (char *)D_800B9E92 + offset;
    *(baseptr + a1) &= 0xFE;
}


s32 func_80038698(void *arg0) {
    u8 *p;
    register u32 len asm("$6");
    u32 hi;
    s32 div;

    p = *(u8 **)arg0;
    *(u8 **)arg0 = p + 1;
    len = p[0];
    *(u8 **)arg0 = p + 2;
    len |= p[1] << 8;
    *(u8 **)arg0 = p + 3;
    len |= p[2] << 16;
    *(u8 **)arg0 = p + 4;
    len |= p[3] << 24;
    if (len != 0x6468544D) {
        return -1;
    }
    *(u8 **)arg0 = p + 5;
    len = p[4];
    *(u8 **)arg0 = p + 6;
    len <<= 8;
    len |= p[5];
    *(u8 **)arg0 = p + 7;
    len <<= 8;
    len |= p[6];
    *(u8 **)arg0 = p + 8;
    len <<= 8;
    len |= p[7];
    hi = p[8];
    {
        u32 s = hi << 8;
        s |= p[9];
        if (s != 0) {
            return -1;
        }
    }
    hi = p[10];
    {
        u32 t = hi << 8;
        t |= p[11];
        if ((s16)t != 1) {
            return -1;
        }
    }
    hi = p[12];
    {
        u32 u = hi << 8;
        u |= p[13];
        div = (s16)u;
    }
    if (div & 0x8000) {
        return -1;
    }
    *(u16 *)((char *)arg0 + 0x1E6) = div & 0x7FFF;
    *(u8 **)arg0 += len;
    return 0;
}

s32 func_800387C0(void *arg0) {
    u8 *p;
    s32 v;

    p = *(u8 **)arg0;
    (*(s32 *)arg0)++;
    v = p[0];
    (*(s32 *)arg0) = p + 2;
    v |= p[1] << 8;
    (*(s32 *)arg0) = p + 3;
    v |= p[2] << 16;
    (*(s32 *)arg0) = p + 4;
    v |= p[3] << 24;
    if (v != 0x6B72544D) {
        return -1;
    }
    (*(s32 *)arg0) = p + 8;
    return 0;
}


void func_80038838(void *arg0)
{
    register unsigned char *a3 asm("$7");
    register unsigned char *a1 asm("$5");
    register unsigned char *v1;
    register unsigned char *v0 asm("$2");
    register int a2 asm("$6");
    register int v0_c;
    register int const1 asm("$8");
    register int const2 asm("$9");
    register int const3 asm("$3");

    a3 = (unsigned char *)arg0 + 0x1A;
    a2 = 0;
    const1 = 0x40;
    const2 = 0x7F;
    a1 = (unsigned char *)arg0 + 0x1B;

    do {
        v1 = a3 + 0x9;
        v0_c = 0xF;
        a3[0x0] = a2;
        *(unsigned short *)(a1 + 0x1) = const1;
        a1[0x3] = const1;
        a1[0x6] = 0;
        a1[0x0] = const2;

        do {
            v1[0x0] = 0;
            v0_c--;
            v1++;
        } while (v0_c >= 0);

        a2++;
        a1 += 0x1A;
        a3 += 0x1A;
    } while (a2 < 0x10);

    a2 = 0;
    const3 = 0x4000;
    v0 = (unsigned char *)arg0;
    do {
        v0[0x18] = 0;
        *(unsigned short *)(v0 + 0x12) = const3;
        v0 += 0x8;
        a2++;
    } while (a2 <= 0);

    *(int *)((unsigned long)arg0 + 0x8) = 1;
    *(int *)((unsigned long)arg0 + 0x1D0) = 0xE10;
    *(int *)((unsigned long)arg0 + 0x1D4) = 0xE10;
    *(int *)((unsigned long)arg0 + 0x1CC) = 0xE10;
    *(unsigned char *)((unsigned long)arg0 + 0x1F4) = 0;
    *(unsigned short *)((unsigned long)arg0 + 0x1E4) = 0x78;
    *(unsigned char *)((unsigned long)arg0 + 0x1F7) = 0;
    *(unsigned char *)((unsigned long)arg0 + 0x1F8) = 0;
    *(unsigned char *)((unsigned long)arg0 + 0x1F9) = 0;
    *(unsigned char *)((unsigned long)arg0 + 0x1FA) = 0;
    *(unsigned char *)((unsigned long)arg0 + 0x1F6) = 0;
}

s32 func_800388E8(void *arg0, s16 arg1) {
    return arg1 * *(s16 *)((u8 *)arg0 + 0x10) * 4 >> 16;
}

void func_80038908(unsigned char *arg0) {
    extern short D_800A4EF8;
    extern unsigned short D_800A4EE0;
    int counter;
    int acc;
    unsigned short *ptr;

    acc = D_800A4EF8 << 7;
    acc *= D_800A4EE0;
    ptr = (unsigned short *)(arg0 + 0x12);
    counter = 0;
    acc >>= 14;
    do {
        acc *= *ptr;
        acc >>= 14;
        counter--;
        ptr += 4;
    } while (counter >= 0);
    *(unsigned short *)(arg0 + 0x10) = (unsigned short)acc;
}


extern u8 *D_800762B0;
extern u8 D_800762B4[];
extern u8 D_800C6E2A[];

void func_80038958(void) {
    register u8 *a3 __asm__("$7");
    register u8 *a2 __asm__("$6");
    register s32 a1 __asm__("$5");
    register u8 *a0 __asm__("$4");
    register s32 t0 __asm__("$8");
    register s32 v0 __asm__("$2");
    register s32 v1 __asm__("$3");

    a3 = D_800762B0;
    a2 = D_800762B4;
    a1 = 0;
    t0 = 3;
    a0 = D_800C6E2A;

    while (a1 < 0x10) {
        v0 = *a3;
        if (v0 == 0 || v0 == t0) {
            if (*a2 == 0) {
                v0 = *a0;
                a0[1] = 0;
                if (v0 != 0) {
                    v0 = *(s16 *)(a0 - 0x54);
                    v1 = v0 << 1;
                    v1 = v1 + v0;
                    v1 = v1 << 2;
                    v1 = v1 + v0;
                    v0 = *(s32 *)(a0 - 0xA);
                    v1 = v1 << 1;
                    v0 = v0 + v1;
                    v0 = v0 + a1;
                    *(u8 *)(v0 + 0x23) = 0;
                    a0[0] = 0;
                }
            }
        }
        a1++;
        a0 += 0x60;
        a3++;
        a2++;
    }
}


extern u8 *D_800762B0;
extern u8 D_800762B4[];

s32 func_80038A00(void) {
    u8 *ptr1 = D_800762B0;
    u8 *ptr2 = D_800762B4;
    s32 i = 0;

    while (i < 0x10) {
        if (*ptr1 == 0x2 && *ptr2 == 0) {
            return i;
        }
        i++;
        ptr1++;
        ptr2++;
    }
    return -1;
}

/* func_80038A58 (main, 347 ins) -- MATCH 347/347 (Fable escalation, S69e1).
 * Levers (from the S69m1 opus draft, kept verbatim):
 *  - Shape: loop 2 is func_80038958's body verbatim (same TU, same pinned regs);
 *    the two accumulator loops are func_80038908's body inlined ($s1 == base+0x10).
 *  - S5a/S336 cross-jump barrier: zero-byte asm at the bottom of the first ramp arm.
 *  - 4-pin div block (cur/quot $v1/$a1 + loop copies c/r $a0/$s0 hoisted above the
 *    `cur != 0` test); both `-` results through a $v0-pinned temp.
 *  - ONE shared counter k ($t1) for the C68/D80/E30 loops; block B's own ($a2).
 * THE ESCALATION FIX (closed the last 2, idx 178/179 — block-A acc preheader):
 *  target = `mult; addu $v1,0,0; addiu $a1,$s3,0x12; mflo`; every C spelling emits
 *  the pair swapped. ROOT CAUSE (read from tools/reference/gcc-2.7.2/sched.c
 *  priority():1425 + rank_for_schedule():2385, confirmed in the -dR bb trace):
 *  sched2 runs BACKWARD; the c2-init's ANTI-dep on `mult $a0,$v1` propagates the
 *  mult's priority 2 into it (anti cost clamps to 1, +cost-1 = +0), while the
 *  dep-free addiu stays at priority 1 -- and priority beats the LUID tie-break, so
 *  NO statement order / pin / barrier can flip it (matches the opus invariance).
 *  FIX = raise the addiu to priority 2: emit the pointer init as a non-volatile
 *  asm carrying a DEAD extra read of c2 (a priority donor):
 *      c2 = 0;
 *      __asm__("addiu %0,%1,18" : "=r"(hp2) : "r"(base), "r"(c2));
 *  The true dep on the c2-init gives it pri 2 AND blocks its release until the
 *  c2-init is placed; backward picks then land mult,addu,addiu,mflo = target.
 *  (A volatile asm CANNOT do this -- volatile = full barrier, pri 13, glues the
 *  tail behind the mflo. Non-volatile survives because its output is live.)
 *  Block B needs nothing: there the POINTER holds $v1, so the anti-dep sinks the
 *  pointer-init -- which is already the target order.
 */
extern u8 *D_800762B0;
extern u8 D_800762B4[];
extern u8 D_800B9CD8[];
extern u8 D_800C6DD0[];
extern u8 D_800C6E2A[];
extern s16 D_800A4EF8;
extern u16 D_800A4EE0;
extern u8 D_800A4F16;
extern s32 func_80038FC4(u8 **);
extern s32 func_80038FFC(s32 *);   /* §376: the definition returns s32 and takes s32* */

void func_80038A58(void)
{
    register u8 *base __asm__("$19");
    register u8 *p __asm__("$17");
    register s32 i __asm__("$18");
    register s32 one __asm__("$20");

    base = D_800B9CD8;

    {
        register u8 *q __asm__("$2");
        q = D_800762B4;
        i = 0xF;
        do {
            *q = 0;
            i--;
            q++;
        } while (i >= 0);
    }

    {
        register u8 *a3 __asm__("$7");
        register u8 *a2 __asm__("$6");
        register s32 a1 __asm__("$5");
        register u8 *a0 __asm__("$4");
        register s32 t0 __asm__("$8");
        register s32 v0 __asm__("$2");
        register s32 v1 __asm__("$3");

        a3 = D_800762B0;
        a2 = D_800762B4;
        a1 = 0;
        t0 = 3;
        a0 = D_800C6E2A;

        while (a1 < 0x10) {
            v0 = *a3;
            if (v0 == 0 || v0 == t0) {
                if (*a2 == 0) {
                    v0 = *a0;
                    a0[1] = 0;
                    if (v0 != 0) {
                        v0 = *(s16 *)(a0 - 0x54);
                        v1 = v0 << 1;
                        v1 = v1 + v0;
                        v1 = v1 << 2;
                        v1 = v1 + v0;
                        v0 = *(s32 *)(a0 - 0xA);
                        v1 = v1 << 1;
                        v0 = v0 + v1;
                        v0 = v0 + a1;
                        *(u8 *)(v0 + 0x23) = 0;
                        a0[0] = 0;
                    }
                }
            }
            a1++;
            a0 += 0x60;
            a3++;
            a2++;
        }
    }

    i = 0;
    one = 1;
    p = base + 0x10;
    do {
        if (p[0x1EB] != 0 && p[0x1EA] != 0) {
            s32 sum = *(s32 *)(p + 0x1BC) + *(s32 *)(p + 0x1C0);
            s32 lim = *(s32 *)(p + 0x1C4);
            s32 k;
            u8 flag;

            *(s32 *)(p + 0x1BC) = sum;
            if (sum >= lim) {
                register s32 cur __asm__("$3");
                register s32 quot __asm__("$5");
                register s32 c __asm__("$4");
                register s32 r __asm__("$16");
                register s32 v __asm__("$3");

                quot = sum / lim;
                cur = *(s32 *)(p - 8);
                *(s32 *)(p + 0x1BC) = sum % lim;
                c = cur;
                r = quot;
                if (cur != 0) {
                    if (quot >= cur) {
                        do {
                            if (c == r) {
                                r = 0;
                            } else {
                                r = r - c;
                            }
                            *(s32 *)(p - 8) = 0;
                            do {
                                if (p[0x1E8] != 0) {
                                    func_80038FFC((s32 *)base);
                                    if (p[0x1E9] != 0) {
                                        p[0x1EA] = 0;
                                        p[0x1E8] = 0;
                                        goto next;
                                    }
                                }
                                v = func_80038FC4((u8 **)base);
                                p[0x1E8] = one;
                            } while (v == 0);
                            *(s32 *)(p - 8) = v;
                            c = v;
                        } while (r >= v);
                        {
                            register s32 d __asm__("$2");
                            d = v - r;
                            *(s32 *)(p - 8) = d;
                        }
                    } else {
                        register s32 d2 __asm__("$2");
                        d2 = cur - quot;
                        *(s32 *)(p - 8) = d2;
                    }
                } else {
                    p[0x1EA] = 0;
                    p[0x1E8] = 0;
                }
            }

            flag = 0;
            if (p[0x1E4] != 0) {
                register u16 *hp __asm__("$8");
                register u8 *sq __asm__("$5");

                hp = (u16 *)(base + 0x12);
                k = 0;
                sq = base + 0x18;
                do {
                    if (*sq != 0) {
                        u16 cur16 = *hp;
                        flag = 1;
                        if (cur16 < *(u16 *)(sq - 2)) {
                            *hp = cur16 + *(u16 *)(sq - 4);
                            if (*hp < *(u16 *)(sq - 2)) {
                                goto cont1;
                            }
                            __asm__ __volatile__("");
                            *hp = *(u16 *)(sq - 2);
                        } else if (*(u16 *)(sq - 4) < cur16) {
                            *hp = cur16 - *(u16 *)(sq - 4);
                            if (*(u16 *)(sq - 2) < *hp) {
                                goto cont1;
                            }
                            *hp = *(u16 *)(sq - 2);
                        } else {
                            *hp = *(u16 *)(sq - 2);
                        }
                        *sq = 0;
                    }
                cont1:
                    k++;
                    sq += 8;
                    hp += 4;
                } while (k <= 0);

                {
                    register u16 *hp2 __asm__("$5");
                    register s32 c2 __asm__("$3");
                    s32 acc2;
                    acc2 = D_800A4EF8 << 7;
                    acc2 *= D_800A4EE0;
                    c2 = 0;
                    __asm__("addiu %0,%1,18" : "=r"(hp2) : "r"(base), "r"(c2));
                    acc2 >>= 14;
                    do {
                        acc2 *= *hp2;
                        acc2 >>= 14;
                        c2--;
                        hp2 += 4;
                    } while (c2 >= 0);
                    *(s16 *)p = acc2;
                }

                if (flag != 0 || D_800A4F16 != 0) {
                    register u8 *b __asm__("$5");
                    register u8 *e __asm__("$4");
                    b = D_800C6DD0;
                    k = 0;
                    e = b + 0x5A;
                    do {
                        if (*e == one) {
                            if (*(s16 *)(*(s32 *)(e - 0xA) + 0x1F0) == i) {
                                *(s16 *)(e - 0x42) = (u32)(*(s16 *)b * *(s16 *)p) >> 14;
                                *(s16 *)(e - 0x40) = (u32)(*(s16 *)(e - 0x58) * *(s16 *)p) >> 14;
                                e[3] = one;
                                *(u32 *)(e - 0x46) |= 3;
                            }
                        } else if (*e != 0) {
                            *e = one;
                        }
                        k++;
                        e += 0x60;
                        b += 0x60;
                    } while (k < 0x10);
                } else {
                    register u8 *c __asm__("$3");
                    register s32 two __asm__("$5");
                    register s32 uno __asm__("$4");

                    p[0x1E4] = 0;
                    k = 0;
                    two = 2;
                    uno = 1;
                    c = D_800C6E2A;
                    do {
                        if (*c == two && *(s16 *)(*(s32 *)(c - 0xA) + 0x1F0) == i) {
                            *c = uno;
                        }
                        k++;
                        c += 0x60;
                    } while (k < 0x10);
                }
            } else if (D_800A4F16 != 0) {
                register u16 *hp3 __asm__("$3");
                register s32 c3 __asm__("$5");
                register u8 *b2 __asm__("$5");
                register u8 *e2 __asm__("$4");
                register s32 k2 __asm__("$6");

                s32 acc3;
                acc3 = D_800A4EF8 << 7;
                acc3 *= D_800A4EE0;
                hp3 = (u16 *)(base + 0x12);
                c3 = 0;
                acc3 >>= 14;
                do {
                    acc3 *= *hp3;
                    acc3 >>= 14;
                    c3--;
                    hp3 += 4;
                } while (c3 >= 0);
                *(s16 *)p = acc3;

                b2 = D_800C6DD0;
                k2 = 0;
                e2 = b2 + 0x5A;
                do {
                    if (*e2 == one) {
                        if (*(s16 *)(*(s32 *)(e2 - 0xA) + 0x1F0) == i) {
                            *(s16 *)(e2 - 0x42) = (u32)(*(s16 *)b2 * *(s16 *)p) >> 14;
                            *(s16 *)(e2 - 0x40) = (u32)(*(s16 *)(e2 - 0x58) * *(s16 *)p) >> 14;
                            e2[3] = one;
                            *(u32 *)(e2 - 0x46) |= 3;
                        }
                    } else if (*e2 != 0) {
                        *e2 = one;
                    }
                    k2++;
                    e2 += 0x60;
                    b2 += 0x60;
                } while (k2 < 0x10);
            }
        }
    next:
        i++;
        p += 0x1FC;
        base += 0x1FC;
    } while (i < 2);

    D_800A4F16 = 0;
}


s32 func_80038FC4(u8 **a0) {
    s32 result = 0;
    u8 b;

    do {
        u8 *p = *a0;
        b = *p++;
        *a0 = p;
        result += b & 0x7F;
        if (!(b & 0x80)) {
            break;
        }
        result <<= 7;
    } while (1);

    return result;
}

s32 func_80038FFC(s32 *param_1) {
    extern void func_80039B20(s32 *, s32);
    extern void func_80039308(s32 *, s32);
    extern void func_80039C5C(s32 *, s32);
    extern void func_80039F50(s32 *, s32);
    extern void func_8003A098(s32 *, s32);
    extern void func_8003A0D0(s32 *, s32);
    extern void func_8003A0E4(s32 *, s32);
    extern void func_8003A234(s32 *);

    u8 *np;
    u8 byte;
    s32 acc;

    acc = *(u8 *)*param_1;
    if (acc & 0x80) {
        *param_1 = (s32)((u8 *)*param_1 + 1);
        *((u8 *)param_1 + 0x1F7) = (u8)acc;
    } else {
        acc = *((u8 *)param_1 + 0x1F7);
    }

    switch ((u32)acc >> 4) {
    case 8:
        func_80039B20(param_1, acc & 0xF);
        break;
    case 9:
        func_80039308(param_1, acc & 0xF);
        break;
    case 10:
        func_80039C5C(param_1, acc & 0xF);
        break;
    case 11:
        func_80039F50(param_1, acc & 0xF);
        break;
    case 12:
        func_8003A098(param_1, acc & 0xF);
        break;
    case 13:
        func_8003A0D0(param_1, acc & 0xF);
        break;
    case 14:
        func_8003A0E4(param_1, acc & 0xF);
        break;
    case 15:
        acc &= 0xF;
        if (acc == 7) {
            goto set_zero;
        }
        if (acc < 8) {
            if (acc == 0) {
                goto set_zero;
            }
            return 0;
        }
        if (acc == 15) {
            goto call_234;
        }
        return 0;
    set_zero:
        acc = 0;
    loop_start:
        while (1) {
            byte = *(u8 *)*param_1;
            np = (u8 *)*param_1 + 1;
            *param_1 = (s32)np;
            acc += byte & 0x7F;
            if (!(byte & 0x80)) {
                break;
            }
            acc <<= 7;
        }
        *param_1 = (s32)np + (s16)acc;
        break;
    call_234:
        func_8003A234(param_1);
        break;
    }
    return 0;
}

void func_8003916C(s16 arg0)
{
    extern u8 D_800C6DD0[];
    u8 *a1;
    s32 off;

    a1 = &D_800C6DD0[arg0 * 0x60];
    if (a1[0x5A] != 0) {
        off = *(s16 *)&a1[6] * 26;
        *(u8 *)(*(u32 *)&a1[0x50] + off + arg0 + 0x23) = 0;
        a1[0x5A] = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/800_c", func_800391D4);

void func_80039300(void) {
}

INCLUDE_ASM("asm/nonmatchings/800_c", func_80039308);

extern s32 D_80073140[];
extern u8 *D_800762B0;
extern s32 D_800C7D20;
extern u8 D_800762B4[];
extern s32 D_800A2B98;
extern u8 D_800C6DD0[];
extern u8 D_800C6DD4[];

void func_80039B20(s32 *arg0, s16 arg1) {
    register s32 i __asm__("$6");
    register s32 off __asm__("$7");
    u8 c;
    s32 t1;

    i = 0;
    t1 = (s32)arg0 + arg1 * 26;
    c = *(u8 *)((*arg0)++);
    off = 0;
    do {
        if (*(u8 *)(t1 + i + 0x23) != 0 && (*(s16 *)(D_800C6DD4 + off) == c)) {
            u8 *p = D_800C6DD0 + (s16)i * 0x60;
            if (p[0x5A] != 0) {
                s16 f6 = *(s16 *)(p + 6);
                s32 off2 = f6 * 26;
                s32 base = *(s32 *)(p + 0x50);
                *(u8 *)(base + off2 + (s16)i + 0x23) = 0;
                p[0x5A] = 0;
            }
            {
                s32 base1 = (s32)D_80073140;
                __asm__ __volatile__("" : "=r"(base1) : "0"(base1));
                D_800C7D20 &= ~((s32 *)base1)[i];
                D_800A2B98 |= ((s32 *)base1)[i];
            }
            D_800762B0[i] = 2;
            D_800762B4[i] = 0;
        }
        i++;
        off += 0x60;
    } while (i < 0x10);
}

void func_80039C5C(s32 *param_1) {
    *param_1 += 2;
}

extern void func_8003B45C(s32 *);
extern s32 D_80079A68;
extern s32 D_8006B008[];
extern s32 D_800A4ECC;
extern s32 D_800A4ED0;
extern u16 D_8006ADD8[];
extern u16 D_800A4ED4;
extern u16 D_800A4ED6;
extern u16 D_800A4F20;
extern u16 D_800A4F22;

void func_80039C70(u8 *arg0, s16 arg1, s16 arg2) {
    u8 *rec = arg0 + (arg1 * 0x1A + 0x1A);

    if ((*(u16 *)(rec + 6) & 0x300) != 0x300) {
        arg0[0x1F9] = 1;
    } else {
        switch (*(u8 *)(rec + 8)) {
        case 0x10: {
            s32 old = D_80079A68;
            s32 val = *(s32 *)((u8 *)D_8006B008 + ((arg2 << 16) >> 14));
            if (old != val) {
                s32 *p = &D_800A4ECC;
                D_80079A68 = val;
                *p = 1;
                D_800A4ED0 = val;
                func_8003B45C(p);
            }
            break;
        }
        case 0x11: {
            s32 *p = &D_800A4ECC;
            *p = 6;
            D_800A4ED4 = *(u16 *)((u8 *)D_8006ADD8 + ((arg2 << 16) >> 15));
            D_800A4ED6 = D_800A4ED4;
            func_8003B45C(p);
            break;
        }
        case 0x18:
            *(s32 *)(arg0 + 0xC) = *(s32 *)arg0;
            arg0[0x1F5] = arg2;
            arg0[0x1F6] = 1;
            break;
        case 0x1A: {
            u16 *p = &D_800A4F20;
            if (*p != 0) {
                arg0[0x1F9] = 1;
                D_800A4F22 = *p;
                *p = 0;
            }
            break;
        }
        case 0x12:
        case 0x13:
        case 0x14:
        case 0x15:
        case 0x16:
        case 0x17:
        case 0x19:
            break;
        }
        rec[7] &= 0xFC;
    }
}

INCLUDE_ASM("asm/nonmatchings/800_c", func_80039DEC);

void func_80039F14(u8 *arg0, s16 arg1, u8 arg2) {
    u8 b;

    arg0 += arg1 * 26;
    b = arg0[0x21];
    arg0[0x20] = arg2;
    arg0[0x22] = arg2 + 1;
    arg0[0x21] = b | 2;
}

extern void func_80039C70(u8 *arg0, s16 arg1, s16 arg2);   /* §376: matches the definition */
extern void func_80039DEC(void *arg0, s16 arg1, u8 arg2);

void func_80039F50(u8 **a0, s16 a1)
{
    register u8 **pvVar4 __asm__("$7"); /* $a3 */
    u8 *pbVar3;
    register s32 bVar1 __asm__("$4"); /* $a0 */
    u8 bVar2;
    register u8 *pbVar5 __asm__("$2"); /* $v0 */
    u8 bVar6;

    pvVar4 = a0;
    pbVar3 = *pvVar4;
    *pvVar4 = pbVar3 + 1;
    bVar1 = *pbVar3;
    *pvVar4 = pbVar3 + 2;
    bVar2 = pbVar3[1];

    switch (bVar1) {
    case 6:
        func_80039C70(pvVar4, a1, bVar2);
        break;
    case 7:
        pbVar5 = (u8 *)pvVar4 + a1 * 0x1A;
        pbVar5[0x1B] = bVar2;
        break;
    case 8:
        break;
    case 0xA:
        pbVar5 = (u8 *)pvVar4 + a1 * 0x1A;
        pbVar5[0x1E] = bVar2;
        break;
    case 0x62:
        pbVar5 = (u8 *)pvVar4 + a1 * 0x1A;
        bVar6 = pbVar5[0x21];
        pbVar5[0x20] = bVar2;
        pbVar5[0x22] = bVar2 + 1;
        pbVar5[0x21] = bVar6 | 2;
        break;
    case 0x63:
        func_80039DEC(pvVar4, a1, bVar2);
        break;
    }
}

typedef struct {
    u8 b0;
    u8 pad[25];
} A098Rec;

typedef struct {
    u8 *stream;
    u8 pad04[0x16];
    A098Rec rec[1];
} A098Ctx;

void func_8003A098(A098Ctx *arg0, s16 arg1) {
    u8 *v1;

    v1 = arg0->stream;
    arg0->stream = v1 + 1;
    arg0->rec[arg1].b0 = *v1;
}

void func_8003A0D0(s32 *arg0) {
    (*arg0)++;
}








extern u16 D_8006AB30[];
extern u16 D_8006ABD8[];
extern u8 D_800C6DD0[];

void func_8003A0E4(void *arg0, s16 arg1) {
    u8 *src;
    u8 *t2;
    u8 *t1;
    u8 *a2;
    u8 *a1;
    s32 i;
    s32 pan;
    u32 vol;
    u32 tmp;
    u32 prod;

    t2 = (u8 *)arg0 + (arg1 * 26 + 26);
    t1 = t2 + 9;
    src = *(u8 **)arg0;
    *(u32 *)arg0 = (u32)src + 1;
    *(s16 *)(t2 + 2) = src[0] & 0x7F;
    for (i = 0; i < 16; i++) {
        if (*t1++ != 0) {
            a2 = D_800C6DD0 + i * 0x60;
            vol = *(s16 *)(a2 + 4) << 8;
            pan = *(s16 *)(t2 + 2);
            if (pan >= 65) {
                vol += (u32)((pan - 64) * a2[0x59] * 4);
            } else if (pan < 64) {
                vol -= (u32)((64 - pan) * a2[0x58] * 4);
            }
            tmp = *(s32 *)(a2 + 0x54) - 0x3C00;
            vol -= tmp;
            a1 = a2 + 0x10;
            if (vol >= 0x5301) {
                *(s16 *)(a2 + 0x24) = 0x3FFF;
            } else {
                prod = D_8006AB30[vol >> 8];
                prod *= D_8006ABD8[(vol & 0xFE) / 2];
                *(s16 *)(a2 + 0x24) = prod >> 15;
            }
            *(u32 *)(a1 + 4) |= 0x10;
            a2[0x5D] = 1;
        }
    }
}



typedef struct {
    /* 0x000 */ u8 *ptr;
    /* 0x004 */ u8 pad_004[0x1D0 - 0x004];
    /* 0x1D0 */ s32 unk1D0;
    /* 0x1D4 */ u8 pad_1D4[0x1E4 - 0x1D4];
    /* 0x1E4 */ s16 unk1E4;
    /* 0x1E6 */ s16 unk1E6;
    /* 0x1E8 */ u8 pad_1E8[0x1F9 - 0x1E8];
    /* 0x1F9 */ u8 unk1F9;
} func_8003A234_Ctx;

void func_8003A234(func_8003A234_Ctx *a0) {
    u8 *a2 = a0->ptr;
    u8 v1;

    a0->ptr = a2 + 1;
    v1 = *a2;

    switch (v1) {
    case 0x20:
        a0->ptr = a2 + 3;
        break;

    case '/':
        a0->ptr = a2 + 2;
        a0->unk1F9 = 1;
        break;

    case 'Q':
        {
            register s32 num __asm__("$4");
            s32 den;
            s32 b3;
            s32 b4;
            s32 q;

            a0->ptr = a2 + 2;
            den = a2[1];
            if (den != 3) {
                a0->unk1F9 = 1;
                break;
            }
            num = 0x3938700;
            a0->ptr = a2 + 3;
            den = a2[2];
            a0->ptr = a2 + 4;
            b3 = a2[3];
            a0->ptr = a2 + 5;
            b4 = a2[4];
            den = den << 16;
            den += b3 << 8;
            den += b4;
            q = num / den;
            a0->unk1E4 = (s16)q;
            a0->unk1D0 = q * a0->unk1E6;
        }
        break;

    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 'T':
    case 0x58:
    case 0x59:
    case 0x7F:
        {
            register u8 *p __asm__("$3") = a0->ptr;
            u8 *np = p + 1;
            a0->ptr = np;
            {
                register s32 byte __asm__("$5") = p[0];
                a0->ptr = np + byte;
            }
        }
        break;

    case 0:
        a0->ptr = a2 + 2;
        {
            register s32 b1 __asm__("$5") = a2[1];
            if (b1 != 2) {
                a0->unk1F9 = 1;
                break;
            }
        }
        a0->ptr = a2 + 4;
        break;

    default:
        a0->unk1F9 = 1;
        break;
    }
}

u32 func_8003A3D8(u32 a) {
    return ((a & 0xFF) << 24) + (((a >> 8) & 0xFF) << 16) + (((a >> 16) & 0xFF) << 8) | (a >> 24);
}

s32 func_8003A404(u32 arg)
{
    u32 h = arg >> 8;
    u32 l = (arg & 0xFF) << 8;
    return (s16)((h & 0xFF) + l);
}

extern void _SpuInit(s32);

void func_8003A424(void) {
    _SpuInit(0);
}
