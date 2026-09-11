/* Split from src/800_b.c (P31 S77): func_8002C410 is an -O0 island inside an -O2 object.
 * gcc-2.7.2 has no per-function optimize pragma, so the opt level is per FILE (§116) — the
 * function must live in its own object for the Makefile's -O0 glob to select it. The two
 * outer pieces stay -O2 and MUST keep matching: the byte-identical rebuild before any
 * banking is what proves the bounds are right. */
#include "common.h"
#include "800_shared.h"

/* P31 S72 — split out of src/800.c at the jtbl-span TU boundary (vram 0x8002B0B4-0x80035270).
 * This TU owns .rodata span B (0x80072E44-0x80073140); see config/splat.us.exe.yaml and cookbook §426.
 * Declarations shared with the sibling TUs live in src/800_shared.h. */


/* func_8002B0B4 -- the memory-card save/load state machine.  P31 S75: decompiled to C as ONE
 * function.  splat's `SaveLoadRoutine` (0x8002B154) is this function's `case 0:` body, a jump-table
 * target of jtbl_80072E44; the census of every inbound jump into 0x8002B154..0x8002C31C found only
 * this function's own `j`/`beq`s and its own table, so the pair that was carried as an unmatchable
 * no-epilogue / no-prologue fragment (cookbook S179-C, S434) is simply one 0x40 frame.  The body
 * below emits all five jump tables (jtbl_80072E44 / ED4 / EEC / F0C / F24) in target order into
 * this TU's .rodata span B.  Byte-shape notes are in the function's own header comment. */

/* func_8002B0B4 -- the memory-card save/load state machine (P31 S75, decompiled to C).
 *
 * ONE function, not two: splat named its case-0 body `SaveLoadRoutine` (0x8002B154, a jump-table
 * target of jtbl_80072E44), and the two "functions" were carried for 60+ sessions as an unmatchable
 * no-epilogue / no-prologue pair (cookbook S179-C, S434).  The census of every inbound jump into
 * 0x8002B154..0x8002C31C found exactly two sources -- func_8002B0B4's own `j`/`beq`s and its own
 * jtbl_80072E44 -- and nothing else in the binary; the "three handler pointers" at 0x80072E44 in
 * docs/memory-map.md are that jump table's first three entries.  So the interior labels are ordinary
 * `case` labels / `goto` targets of this single 0x40-frame function and the C below is the whole frame.
 *
 * Shape notes that are load-bearing for the bytes (each one measured, see cookbook S448):
 *   - `reset:` (0x8002B210) and `close:` (0x8002BE14) are explicit labels: gcc-2.7.2's cross-jump keeps
 *     the LAST identical tail, but the original keeps these EARLY blocks, so they were gotos in the source.
 *   - `ret = 2` is written AFTER the stat store in every "state = 0; stat = N; ret = 2" group, or cse
 *     folds the stat store's constant into $s2 and the tails over-merge.
 *   - the two zero-byte `__asm__ __volatile__` barriers in cases 21/23 stop a second-level cross-jump of
 *     the `jal func_80060614` tails (the original keeps all three copies: cases 11, 21, 23).
 *   - `D_80075A40` is declared as the u32 id word so `D_80075A40 = D_80076040` is a (mem sym) store the
 *     address register of `p` cannot be cse-tied to; the two `"0"(m)` launders keep a call argument out
 *     of the pseudo the post-call store would otherwise share (cookbook S153 / S164-68).
 *   - block-scoped temps per case (S48-A3); `i = 0x1B` / `i = 0` initialised BEFORE the pointer they
 *     pair with, so the shorter-lived pseudo takes $v0 (local-alloc priority).
 *   - switch indices `res`/`D_800760C4` are unsigned so gcc's case tree tests 1 first and `0` as `bltu 1`.
 */

typedef struct { s32 stat; u32 val; } CardSlot;           /* D_8007609C[port>>4], 8 bytes */
typedef struct { u8 b[41]; } Blk41;
typedef struct { u8 b[32]; } Blk32u;
typedef struct { u8 b[128]; } Blk128u;
typedef struct { u32 w[38]; } Blk152;                      /* 0x98 bytes, word aligned */

extern s32 D_800760AC;      /* state */
extern s32 D_800760B0;      /* port (0x00 / 0x10) */
extern s32 D_800760B4;
extern s32 D_800760B8;
extern u16 D_800760BC;
extern u16 D_800760C0;
extern u32 D_800760C4;
extern CardSlot D_8007609C[];
extern u8 D_80075840[];     /* memcard frame-0 header block (0x200) */
extern u32 D_80075A40;      /* save data block (0x280); [0] = id word */
extern u8 D_80075AC0[];     /* = D_80075A40 + 0x80: 4 x 0x80 slot records */
extern u8 D_80075CC0[];     /* 0x300 game-state block */
extern u8 D_80075FC0[];     /* 0x80 checksum block */
extern u32 D_80076040;
extern u8 D_80076044[];     /* 0x28-byte record per port */
extern s32 D_80076094[];
extern char D_80072DFC[];   /* "BASLUS-00726MUSASHI" */
extern u8 D_80072E10[];     /* SJIS title, 41 bytes */
extern char D_80072E3C[];   /* "*" */
extern u8 D_80063AEC[];     /* icon source: clut @0, frames @0x2C / 0xEC / 0x1AC */
extern u32 lzss_sectorStagingBuf[];

extern s32 func_80061024(s32, s32 *, s32 *);
extern void func_8005FD58(s32);
extern s32 func_8006023C(s32 port, char *name, s32 mode);
extern void func_80060404(void *buf, s32 off, s32 len);
extern void func_800603BC(void);
extern void func_80060AE0(s32 port, char *name, void *buf, s32 off, s32 len);
extern void func_80016714(void *, s32);
extern void func_80060614(void *buf, s32 off, s32 len);
extern s32 func_80061114(s32 port, char *name, s32 mode);
extern s32 func_80061524(s32);
extern void func_8005FFB4(s32 port);
extern s32 func_80060D9C(s32 port, char *name, void *a2, void *a3, s32 a4, s32 a5);
extern u16 func_8002B064(u8 *a0);
extern u16 func_8002B08C(s32 a0);
extern u32 func_8002C320(void);
extern s32 func_8002C3B0(s32 count, u8 *arr);



extern s16 D_800C5328[];
extern s16 D_800C532A[];

void func_8002C8BC(void) {
    s32 a0;
    s32 v1;

    a0 = -1;
    v1 = 0;

    do {
        *(s16 *)((u8 *)D_800C5328 + v1) = a0;
        *(s16 *)((u8 *)D_800C532A + v1) = a0;
        v1 += 4;
    } while ((u32)v1 < 0x1E4);
}


/* ---- callees ---- */
extern void func_8003A424(void);
extern void func_8003D518(void);
extern void func_8003C598(s32 *);
extern void func_8003BE24(s32);
extern void func_8002D1F0(s32);
extern void func_8003B280(s32);
extern void func_80037D98(void);
extern void func_8002CC4C(void);
extern void func_8002FAE0(void);
extern void func_80037CC8(void);
extern void func_8003BE74(s32, s32);
extern void func_8003B1EC(s32 *);
extern void func_80034C24(void);
extern void func_80037004(void);

/* src/800.c (func_80032048) already declares `extern Owner4EE8 *D_800A4EE8;`
 * where Owner4EE8 is `typedef struct Owner4EE8 {...} Owner4EE8;` defined later
 * in the TU. Spell the extern EXACTLY like the TU (bare typedef name, no
 * `struct` keyword) via a forward typedef so this compiles standalone too;
 * the incomplete typedef is later completed by the TU's own full definition
 * (identical redeclaration is legal). This is a pointer-only use here, so the
 * type's spelling has no effect on codegen. */
extern Owner4EE8 *D_800A4EE8;

/* ---- data ---- */
extern s32 D_800A4EA4;
extern s16 D_800A4EA8;
extern s16 D_800A4EAA;
extern s16 D_800A4EAC;
extern s16 D_800A4EAE;
extern s16 D_800A4EB4;
extern s16 D_800A4EB6;
extern s32 D_800A4EB8;
extern s32 D_800A4EBC;
extern s32 D_800A4EC8;

extern s32 D_800A4E68;
extern s16 D_800A4E6C;
extern s16 D_800A4E6E;
extern u8  D_800A4E70;
extern u8  D_800A4F18;
extern u8  D_800A4F19;
extern s16 D_800A4EF6;

/* D_800A463C is reached as (&D_800A4638)[1]: src/800.c declares that symbol as
 * `extern Ent24 D_800A463C[];` (anonymous typedef, defined further down the TU),
 * so a scalar redeclaration here would conflict.  Byte-identical relocation. */
extern s32 D_800A4638;

extern u8  D_800A4E7A;
extern u8  D_800A46E4;
extern s32 D_800A4654;
extern s32 D_800A466C;
extern s32 D_800A4684;
extern s32 D_800A469C;

extern s32 D_800A64B0;
extern u8  D_800A4650[];
extern s16 D_800A4644[];
extern s16 D_800A4642[];
extern u16 D_800A46E8[];

extern u8  D_800A4988[];
extern s32 D_800A4C68[];
extern u8  D_800A4C6C[];
extern u8  D_800A4C6D[];

extern s16 D_800A4EF8;
extern s16 D_800A4EFA;
extern u8  D_800A4F1B;
extern u8  D_800A46BA;
extern s32 D_800A2B98;
extern s32 D_800A2BA0;
extern s32 D_800C7D20;
extern s32 D_800C7D2C;
extern s8  D_800A4F17;
extern u16 D_800A4E8E;
extern u16 D_800A4EA2;
extern s16 D_800A4EF0;
extern s16 D_800A4EFC;
extern u16 D_800A4F20;
extern u16 D_800A4F22;
extern u8  D_800A4F1D;
extern s32 D_800A4EEC;
extern u8  D_800A4EE6;
extern u16 D_800A4EE0;
extern u16 D_800A4EE4;
extern void (*D_800A4F24)(void);
extern u8  D_800A4F16;
extern u8  D_800A4F1C;
extern u8  D_800A4F1E;

void func_8002C8F4(void)
{
    s32 sp10[2];
    s32 *p;
    u8 *q;
    s32 i;
    s32 j;
    s32 k;
    s32 n;
    s32 m;

    func_8003A424();
    func_8003D518();

    p = &D_800A4EA4;
    *p = 0x23CF;
    D_800A4EA8 = 0x3FFF;
    D_800A4EAA = 0x3FFF;
    D_800A4EB4 = 0x3FFF;
    D_800A4EB6 = 0x3FFF;
    D_800A4EAC = 0;
    D_800A4EAE = 0;
    D_800A4EB8 = 0;
    D_800A4EBC = 1;
    D_800A4EC8 = 0;

    func_8003C598(p);
    func_8003BE24(1);
    func_8002D1F0(4);
    func_8003B280(1);
    func_80037D98();

    D_800A4E68 = 0x3C;
    D_800A4E6C = 0x2F;
    D_800A4E6E = 0x2F;
    D_800A4E70 = 1;
    D_800A4F18 = 1;
    D_800A4F19 = 1;
    D_800A4EF6 = 1;
    (&D_800A4638)[1] = 0x1010;
    D_800A4638 = 0;
    D_800A4E7A = 0;
    D_800A46E4 = 0;
    D_800A4654 = 0x10000;
    D_800A466C = 0x14000;
    D_800A4684 = 0x18000;
    D_800A469C = 0x39F00;

    for (j = 0x54; j >= 0; j -= 0xC) {
        *(s32 *)((u8 *)&D_800A64B0 + j) = 0;
    }

    for (i = 0; i < 5; i++) {
        k = i * 0x18;
        D_800A4650[k] = 1;
        *(s16 *)((u8 *)D_800A4644 + k) = 0;
        *(s16 *)((u8 *)D_800A4642 + k) = -1;
    }

    for (n = 0x24C; n >= 0; n -= 0x54) {
        *(u16 *)((u8 *)D_800A46E8 + n) = 0;
    }

    m = 0x10;
    for (i = 0, q = D_800A4988 + 0x4F; i < 8; i++, m++, q += 0x54) {
        k = i * 0x48;
        q[2] = i;
        *(s16 *)(q - 0x45) = m;
        q[-1] = 0;
        *(s32 *)(q - 0x4B) = 0;
        *(s32 *)(q - 0xF) = 0;
        q[1] = 0;
        *(s32 *)((u8 *)D_800A4C68 + k) = m;
        D_800A4C6C[k] = 0;
        D_800A4C6D[k] = 0;
    }

    func_8002CC4C();

    D_800A4EFA = 0x7F;
    D_800A4EF8 = 0x7F;
    D_800A4F1B = 1;
    D_800A46BA = 0;
    D_800A2B98 = 0;
    D_800C7D20 = 0;
    D_800C7D2C = 0;
    D_800A2BA0 = 0;
    D_800A4F17 = 0;
    D_800A4E8E = 0;
    D_800A4EA2 = 0;
    D_800A4EF0 = 0;
    D_800A4EE8 = 0;
    D_800A4EFC = 0;
    D_800A4F20 = 0;
    D_800A4F22 = 0;
    D_800A4F1D = 0;
    D_800A4EEC = 0;
    D_800A4EE6 = 0;
    D_800A4EE0 = 0x4000;
    D_800A4EE4 = 0x4000;
    D_800A4F24 = 0;
    D_800A4F16 = 0;

    func_8002FAE0();
    func_80037CC8();
    func_8003BE74(0, 0xFFFFFF);

    sp10[0] = 1;
    sp10[1] = 0;
    func_8003B1EC(sp10);

    D_800A4F1C = 0;
    D_800A4F1E = 0;
    func_80034C24();
    func_80037004();
}


extern B12 *D_8006A970[];
extern s32 D_80065504[];

void func_8002CC4C(void) {
    B12 **pp;
    s32 *cnt;
    s32 off;
    B12 *p;
    s32 i;
    s32 *cp;
    s32 pad;

    (void)&pad;
    pp = D_8006A970;
    cnt = D_80065504;
    for (off = 0; off < 0x10; off += 4) {
        p = *pp;
        i = 0;
        if (*cnt > 0) {
            do { cp = cnt; } while (0);
            do {
                i++;
                p->unk0A = 0;
                p++;
            } while (i < *cp);
        }
        cnt++;
        pp++;
    }
}

extern void func_8002D4C8(s32 a0, s32 a1);

void func_8002CCB4(void) {
    func_8002D4C8(2, 0);
}

extern s32 D_800A4EA4;

void func_8002CCD8(void)
{
    s16 buf[4];
    s32 i;
    s32 depth;
    s32 mode;
    s32 *p;

    func_80042610(0);
    VSync(0);
    for (i = 0; i < 0x18; i++) {
        func_8003D3B4(i, 8);
    }
    func_8003C23C(0, 0xFFFFFF);
    func_8003D434(&buf[0], &buf[1]);
    i = 15;
    p = &D_800A4EA4;
    mode = 3;
    depth = 0x3BF1;
    while (i != 0) {
        VSync(0);
        buf[1] = buf[0] * i >> 4;
        SpuSetReverbModeDepth(buf[1], buf[1]);
        *p = mode;
        *(s16 *)((s16 *)p + 3) = *(s16 *)((s16 *)p + 2) = depth;
        func_8003C598(p);
        depth -= 0x3FF;
        i--;
    }
    SsEnd();
    func_8003D630();
    SpuQuit();
}


extern s32 D_800A4638;
extern u16 D_800A4F22;
extern s16 D_8006A990;
extern u8  D_800A4EE6;
extern u16 D_800A4EE0;
extern u16 D_800A4EE2;
extern u16 D_800A4EE4;
extern u8  D_800A4F16;
extern u8  D_800A4EFE[];
extern u16 D_800A4E8E;
extern u16 D_800A4E8A;
extern s16 D_800A4E86;
extern s8  D_800A4F17;
extern u8  D_800A4F18;
extern u8  D_8006AEF4;

extern void func_8002D904(s32);
extern s32  func_8003D25C(s32, s32, u8 *);
extern void func_80037FC4(void);
extern void func_8002EC10(void);
extern s32  func_8003836C(s32 a0);
extern void func_8002CFE4(void);
extern s32  func_8003C4F0(s32);

void func_8002CDD8(void)
{
    s32 *ctr;
    u16 tmp;
    u16 cur;
    u16 tgt;
    u8  fl;
    s16 t;

    ctr = &D_800A4638;
    tmp = D_800A4F22;
    *ctr = *ctr + 1;
    if (tmp != 0) {
        D_8006A990 = tmp;
        func_8002D904(tmp);
        D_800A4F22 = 0;
    }

    fl = D_800A4EE6;
    if (fl & 1) {
        tgt = D_800A4EE4;
        cur = D_800A4EE0;
        D_800A4F16 = 1;
        if (tgt < cur) {
            D_800A4EE0 = cur - D_800A4EE2;
            if (tgt >= D_800A4EE0) {
                D_800A4EE0 = tgt;
                D_800A4EE6 = fl & 0xFE;
            }
        } else {
            D_800A4EE0 = cur + D_800A4EE2;
            if (D_800A4EE0 >= tgt) {
                D_800A4EE0 = tgt;
                D_800A4EE6 = fl & 0xFE;
            }
        }
    }

    func_8003D25C(0, 0x17, D_800A4EFE);

    if (D_800A4E8E & 8) {
        func_80037FC4();
        t = *(s16 *)&D_800A4E8A;
        if (t != 0) {
            t--;
            D_800A4E8A = t;
            if (t == 0) {
                func_8002EC10();
            }
        }
        if ((s16)func_8003836C(D_800A4E86) == 0) {
            D_800A4E8E &= 0xFFF7;
        }
    }

    if (*(u8 *)&D_800A4F17 == 0) {
        D_800A4F18 = 0;
        func_8002CFE4();
    } else {
        D_800A4F18 = 1;
    }

    if ((D_8006AEF4 & 1) && !(D_8006AEF4 & 2)) {
        if (func_8003C4F0(0) != 0) {
            D_8006AEF4 &= 0xFE;
        }
    }
}

extern void func_80030F80(void);
extern void func_8002D320(void);
extern void func_80031BE0(void);

extern s16 D_800A4EFC;

void func_8002CFE4(void) {
    s16 *ptr = &D_800A4EFC;

    if (*ptr != 0) {
        *ptr = *ptr - 1;
    }
    func_80030F80();
    func_8002D320();
    func_80031BE0();
}

extern u8 D_800A46BA;
extern void func_8002D29C(void);

extern s32 D_800A64B0;

extern u8 D_8006A980;
extern void func_8002DF80(void);

extern void (*D_800A4F24)(void);

extern u8 D_800A4E70;
extern s32 D_800A4E68;
extern s16 D_800A4E6C;
extern void func_8002D240(s32 a0);

extern u8 D_800A4E7A;
extern s16 D_800A4E76;
extern u16 D_800A4E74;
extern s16 D_800A4E78;

void func_8002D034(void) {
    s32 *ptr;
    s32 i;

    if (D_800A46BA) {
        func_8002D29C();
    }

    ptr = &D_800A64B0;
    for (i = 0; i < 8; i++, ptr = (s32 *)((u8 *)ptr + 0xC)) {
        if (ptr[0] != 0 && --ptr[0] == 0) {
            void (*func)(void *) = (void (*)(void *))ptr[2];
            func(ptr);
        }
    }

    if ((D_8006A980 & 0xEF) != 0) {
        func_8002DF80();
    }

    if (D_800A4F24 != NULL) {
        D_800A4F24();
    }

    if (D_800A4E70 != 0) {
        if (--D_800A4E68 == 0) {
            s32 a0 = D_800A4E6C;
            D_800A4E70 = 0;
            func_8002D240(a0);
        }
    }

    {
        u8 *flagPtr;
        flagPtr = &D_800A4E7A;
    if (*flagPtr != 0) {
        if (D_800A4E76 > (s16)D_800A4E74) {
            s16 delta = D_800A4E78;
            if ((s16)D_800A4E74 < D_800A4E76 - delta) {
                D_800A4E74 = (s16)D_800A4E74 + delta;
            } else {
                D_800A4E74 = D_800A4E76;
                *flagPtr = 0;
            }
        } else {
            s16 delta = D_800A4E78;
            if (D_800A4E76 + delta < (s16)D_800A4E74) {
                D_800A4E74 = (s16)D_800A4E74 - delta;
            } else {
                D_800A4E74 = D_800A4E76;
                *flagPtr = 0;
            }
        }

        func_8002D240((s16)D_800A4E74);
    }
    }
}


extern void func_8003B45C(s32 *);

extern s32 D_800A4ECC;
extern s32 D_800A4ED0;
extern u16 D_800A4ED4;
extern u16 D_800A4ED6;

void func_8002D1F0(s32 arg0) {
    s32 *v1 = &D_800A4ECC;
    *v1 = 1;
    D_800A4ED0 = (s16)arg0;
    D_800A4ED4 = 0;
    D_800A4ED6 = 0;
    func_8003B45C(v1);
}


extern s32 D_800A4ECC;
extern u16 D_8006ADD8[];
extern u16 D_800A4E74;
extern u16 D_800A4ED4;
extern u16 D_800A4ED6;
extern void func_8003B45C(s32 *a0);

void func_8002D240(s32 a0) {
    s32 index = (a0 << 16) >> 15;
    s32 *p = &D_800A4ECC;
    u16 value = *(u16 *)((u8 *)D_8006ADD8 + index);

    *p = 0x6;
    D_800A4E74 = (u16)a0;
    D_800A4ED4 = value;
    D_800A4ED6 = value;

    func_8003B45C(p);
}

extern s32 D_800A46B4;
extern u16 D_800A46B8;
extern u16 D_800A4EF4;
extern u8 D_800A46BA;

extern int func_8003EDE8(int a0, int a1, int a2);
extern void func_8002EE90(void);

void func_8002D29C(void) {
    s32 *s1;
    s32 s0;
    s16 v0;
    s16 v1;

    s1 = &D_800A46B4;
    s0 = *s1;
    v0 = D_800A4EF4;
    func_8003EDE8(0, (s0 * v0) >> 16, (s0 * v0) >> 16);
    v1 = D_800A46B8;
    s0 -= v1;
    if (s0 <= 0) {
        D_800A46BA = 0;
        func_8002EE90();
        s0 = 0;
    }
    *s1 = s0;
}

extern u8  D_800A4C6D[];
extern s32 D_800A2B98;
extern s32 D_800A2BA0;
extern s32 D_800C7D20;
extern s32 D_800C7D2C;

void func_8002D320(void)
{
    /* TU-absent names, block scope */
    extern Slot D_800A4C28[];
    extern void func_8003D3B4(s32, s32);
    extern void func_8003C23C(s32, s32);
    extern void func_8003BE74(s32, s32);
    extern void func_8003B250(s32, void *);

    Slot *s;
    s32 i;

    /* D_800A4C6D is &D_800A4C28[0].unk45: spelled through that symbol so the relocation stays D_800A4C6D+0
     * (the plain `s = D_800A4C28;` compiles to the same instructions with a D_800A4C28+0x45 relocation). */
    s = (Slot *)(D_800A4C6D - 0x45);
    for (i = 0; i < 8; i++, s++) {
        if (s->unk45[0] != 0) {
            if (s->unk44 == 0 || (s->unk04 & 0x60000) == 0) {
                func_8003D3B4(s->unk40, 1);
            }
            s->unk45[0] = 0;
        }
    }

    if ((D_800A2B98 & 0xFF0000) != 0) {
        func_8003C23C(0, D_800A2B98 & 0xFF0000);
        D_800A2B98 = *(u16 *)&D_800A2B98;
    }
    if ((D_800A2BA0 & 0xFF0000) != 0) {
        func_8003BE74(0, D_800A2BA0 & 0xFF0000);
        D_800A2BA0 = *(u16 *)&D_800A2BA0;
    }

    s = D_800A4C28;
    for (i = 0; i < 8; s++, i++) {
        if (s->unk44 != 0) {
            s->unk44 = 0;
            func_8003B250(s->unk40, s);
            s->unk04 = 0;
        }
    }

    if ((D_800C7D20 & 0xFF0000) != 0) {
        func_8003C23C(1, D_800C7D20 & 0xFF0000);
        D_800C7D20 = *(u16 *)&D_800C7D20;
    }
    if ((D_800C7D2C & 0xFF0000) != 0) {
        func_8003BE74(1, D_800C7D2C & 0xFF0000);
        D_800C7D2C = *(u16 *)&D_800C7D2C;
    }
}

extern u8 D_800A46BA;
u8 func_8002D4B8(void) {
    return D_800A46BA;
}

extern s8 D_800A4F17;
extern u8 D_800A4F18;
extern s16 D_800A4EFC;
extern void func_8002D904(s32);
extern s32 func_8002DC68();    /* §376: def returns s32 and takes (u32, u32) */
extern void func_8002E138(s32 a0, s32 a1, s32 a2);
extern void func_80030F80(void);
extern void func_8002D320(void);
extern void func_80031BE0(void);

void func_8002D4C8(s32 arg0, s32 arg1) {
    u8 v0;
    s8 *p;

    D_800A4F17 = 1;
    if ((u16)arg0 < 0x80) {
        func_8002E138((u16)arg0, arg1 & 0xFFFF, 0);
    } else if ((u16)arg0 >= 0x100) {
        if ((u16)arg0 < 0x400) {
            func_8002D904((u16)arg0);
        } else {
            func_8002DC68((u16)arg0, arg1 & 0xFFFF);
        }
    }

    p = &D_800A4F17;
    v0 = D_800A4F18;
    *p = v0;
    if (v0 != 0) {
        s16 cnt = D_800A4EFC;
        if (cnt != 0) {
            D_800A4EFC = cnt - 1;
        }
        func_80030F80();
        func_8002D320();
        func_80031BE0();
        D_800A4F18 = 0;
        *p = 0;
    }
}

extern s8 D_800A4F17;
extern u8 D_800A4F18;
extern s16 D_800A4EFC;

void func_8002D59C(s32 arg0, s32 arg1, s32 arg2) {
    u16 id;
    u8 v0;
    s8 *p;

    *(u8 *)&D_800A4F17 = 1;
    id = arg0 & 0xFFFF;
    if (id < 0x80) {
        func_8002E138(id, arg1 & 0xFFFF, arg2 & 0xFFFF);
    } else if (id >= 0x100) {
        if (id < 0x400) {
            func_8002D904(id);
        } else {
            func_8002DC68(id | (arg2 << 16), arg1 & 0xFFFF);
        }
    }

    p = &D_800A4F17;
    v0 = D_800A4F18;
    *p = v0;
    if (v0 != 0) {
        s16 cnt = D_800A4EFC;
        if (cnt != 0) {
            D_800A4EFC = cnt - 1;
        }
        func_80030F80();
        func_8002D320();
        func_80031BE0();
        D_800A4F18 = 0;
        *p = 0;
    }
}

extern s8 D_800A4F17;

s32 func_8002D678(s32 a0, s32 a1) {
    extern s32 func_8002DC68();    /* §376: def returns s32 and takes (u32, u32) */

    u32 id;
    s32 ret;

    D_800A4F17 = 1;
    id = a0 & 0xFFFF;
    if (id >= 0x400) {
        ret = ((s32 (*)())func_8002DC68)(id, a1 & 0xFFFF);
        if (ret != 0) {
            ret |= id << 16;
        }
        return ret;
    }
    return 0;
}


extern u8 D_8006451C[];
extern s8 D_800A4F17;
extern u8 D_800A4F18;
extern s16 D_800A4EFC;

extern s32 func_8002F4E4(u8 *);
extern void func_8003324C(s32);
extern void func_80030F80(void);
extern void func_8002D320(void);
extern void func_80031BE0(void);

void func_8002D6D8(u32 a0) {
    s32 id;
    u8 v0;
    s8 *p = &D_800A4F17;

    *p = 1;
    id = a0 >> 16;
    a0 = (u16)a0;
    if ((u16)id < 0x100) {
        return;
    }
    {
        u8 *q = &D_8006451C[(u16)id * 4];
        if ((*q & 0x7F) == 6) {
            id = func_8002F4E4(q);
            if ((u16)id == 0) {
                return;
            }
        }
    }

    if (a0 == 0) {
        return;
    }
    a0--;
    if (*(u16 *)((u8 *)&D_800A4F17 + a0 * 0x54 - 0x82B) == (u16)id) {
        func_8003324C((u16)a0);
    }

    v0 = D_800A4F18;
    *p = v0;
    if (v0 != 0) {
        s16 v0s = D_800A4EFC;
        if (v0s != 0) {
            D_800A4EFC = v0s - 1;
        }
        func_80030F80();
        func_8002D320();
        func_80031BE0();
        D_800A4F18 = 0;
        *p = 0;
    }
}

void func_8002D7F4(void) {
}

extern s32 D_800A4E7C;
void func_8002D7FC(s32 arg0) {
    D_800A4E7C = arg0;
}

extern u16 D_800A4E8E;
extern s16 D_8006A990;

u16 func_8002D80C(void) {
    return (D_800A4E8E & 1) ? D_8006A990 : 0;
}

extern s16 D_8006A990;
void func_8002D834(void) {
    D_8006A990 = 0;
}

extern s32 D_800760E0;

s32 func_8002D844(s32 arg0) {
    D_800760E0 = arg0;
    return arg0;
}

extern s16 D_800760E4;
extern void func_8003D650(int a0, int a1, int a2);
extern int func_8003EDE8(int a0, int a1, int a2);

int func_8002D858(void) {
    D_800760E4 = 100;
    func_8003D650(0, 1, 0);
    func_8003EDE8(0, D_800760E4, D_800760E4);
    return D_800760E4;
}

s32 func_8002D8A8(void) {
    extern void (*D_800A4F24)(void);
    extern s16 D_800760EC;
    extern s16 D_800760E8;
    extern void func_8002FA3C(void);

    D_800760EC = 6;
    D_800A4F24 = func_8002FA3C;
    D_800760E8 = 0;
    return 0x10;
}

extern void (*D_800A4F24)(void);
extern int func_8003EDE8(int a0, int a1, int a2);

int func_8002D8D4(void) {
    D_800A4F24 = NULL;
    func_8003EDE8(0, 0, 0);
    return 0;
}

#include "common.h"

/* func_8002D904 (main, 217 ins) — byte MATCH.  Levers that closed it, in the order they paid:
 *
 * 1. NON-/s TABLE LOADS ARE THE WHOLE SCHEDULE (worth 26 of 41 residuals).  gcc-2.7.2's
 *    expand_expr INDIRECT_REF sets MEM_IN_STRUCT_P whenever "the address was computed by
 *    addition" — so `D_80068B5E[i][0]`, `((u16*)D_80068B5E)[i*8]` and every other indexed
 *    spelling is /s AND varying, which true_dependence/anti_dependence then declare
 *    non-aliasing against the plain fixed-address scalar stores around it (cf. the W16 note
 *    at src/800.c:21942).  The load floats to the top of the block and permutes the whole
 *    tail.  Assigning the address to a POINTER VARIABLE first makes the INDIRECT_REF's
 *    operand a VAR_DECL, not a PLUS_EXPR — MEM_IN_STRUCT_P stays 0, the real store->load
 *    edges come back, and the load sits exactly where the target has it.  combine folds the
 *    pointer back into the MEM, so it costs ZERO instructions.  (b5e / b66 below.)
 * 2. `s16 b = a;` BEFORE the guard, not after (+2 ins, and the $v0/$a1 split).  gcc-2.7.2
 *    collapses `(short)x` on an SImode pseudo to nothing at expand time (convert_modes sees
 *    oldmode == GET_MODE(x) == SImode and returns x), so NO cast at the call site can emit
 *    the target's `sll/sra`.  The extension only survives when a genuinely HImode local is
 *    assigned in one block and consumed in a distant one.  And the copy must sit ABOVE
 *    `if (a < 0)` so `a`'s live range overlaps `b`'s — otherwise they coalesce and the
 *    `addu $a1,$v0,$zero` disappears.
 * 3. `id = arg0 & 0xFFFF;` ABOVE the func_8002EE64 call (worth the last 3 residuals).  That
 *    makes the pseudo cross a call, so global-alloc gives it a CALLEE-SAVED reg ($s1) instead
 *    of $a2; sched1 then sinks the `andi` back below the `jal` on its own.  The 0x134 test
 *    deliberately re-spells `(arg0 & 0xFFFF)` — the target recomputes it from $s2 at 8002DB14
 *    because $s1 has been reused for &D_800A4E86 by then.
 * 4. §333 frame arithmetic: .frame wants vars=8 (0x28 = 16 args + 16 regs + 8), which four
 *    saved regs alone do not explain — an unreferenced trailing aggregate supplies it.
 * 5. Address-of locals (pa2/p86/q86/p8e) are the TU's own house idiom (src/800.c:17641,
 *    17665, 17787): with -G0 gcc emits each global reference as one `lh sym` macro, so there
 *    is no address subexpression for CSE to hoist across blocks — only an explicit pointer
 *    produces the target's `lui/addiu` base registers ($t0, $s1, $s0, $a0).
 * 6. `p86` is assigned AFTER the func_80038210 call so the `lui/addiu $s1` pair lands after
 *    the `jal` rather than being hoisted into the pre-call slot.
 *
 * Declarations follow src/800.c verbatim (§376): D_80068B60 is `u8[]` at 0x10 stride
 * (src/800.c:21368), D_80068B66 is `u16[][8]` (17731), D_80065438 is `H2[]` (21967) — the H2
 * typedef below is the TU's own (src/800.c:226) and harvest_verify strips it on splice —
 * and func_8003834C is (s32, s16) per its definition at src/800.c:22556.
 * Verified: match_one MATCH 217/217; blocker_probe real-cc1 whole-TU MATCH 217 ins, no
 * blockers; reloc_identity AGREE (50 relocs); all four internal `j` targets checked by hand
 * (§195-D: the 26-bit field is masked, so match_one cannot see them) — 0xf4 / 0xf0 / 0x328 /
 * 0x300, identical to the target's .L8002D9F8 / .L8002D9F4 / .L8002DC2C / .L8002DC04.
 */



extern void func_8002EE64(void);
extern s32  func_80038210(s32, s16, s32);
extern void func_8003819C(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80038308(s16 a0);
extern void func_8003834C(s32, s16);
extern void func_80038638(s32, s32);

extern s16 D_800A4642[];
extern s16 D_80068B5C[][8];
extern u16 D_80068B5E[][8];
extern u8  D_80068B60[];
extern s16 D_80068B62[][8];
extern u16 D_80068B66[][8];
extern H2  D_80065438[];
extern s32 D_800652F0[];
extern s32 D_800760E0;
extern s32 D_800A4E7C;
extern s16 D_800A4E84;
extern s16 D_800A4E86;
extern u16 D_800A4E8A;
extern u16 D_800A4E8C;
extern u16 D_800A4E8E;
extern s16 D_800A4E9A;
extern u16 D_800A4EA0;
extern u16 D_800A4EA2;
extern u8  D_800A4F1C;
extern u8  D_800A4F1E;

void func_8002D904(s32 arg0) {
    s32 i;
    s32 p;
    s32 a;
    s16 b;
    s32 t;
    s32 id;
    s32 q;
    u16 f;
    u16 *pa2;
    u16 *b5e;
    u16 *b66;
    s32 pad[2];         /* §333: unreferenced — supplies the target's vars=8 */

    id = arg0 & 0xFFFF; /* above the call on purpose: pins `id` to a callee-saved reg */
    func_8002EE64();
    i = id - 0x100;
    a = D_800A4642[D_80068B5C[i][0] * 12];
    b = a;              /* above the guard on purpose: keeps `a` and `b` from coalescing */
    if (a < 0) {
        return;
    }
    if ((D_800A4E8E & 0x20) == 0) {
        return;
    }
    if (D_800A4F1E != 0) {
        return;
    }

    if (id == 0x18E) {
        p = D_800760E0;
    } else if (D_80068B62[i][0] != 0) {
        t = *(s32 *)(D_800A4E7C + D_80068B62[i][0] * 4);
        if (t == 0) {
            return;
        }
        p = D_800A4E7C + t + 4;
    } else {
        p = D_800A4E7C + 0x10;
    }

    pa2 = &D_800A4EA2;
    q = D_800652F0[D_80065438[*(s16 *)(D_80068B60 + i * 0x10)].f0];
    if ((*pa2 & 4) != 0 && D_800A4EA0 == i) {
        D_800A4EA0 = 0;
        D_800A4E8E = *pa2;
        *pa2 = 0;
        D_800A4E8E |= 4;
        D_800A4E8C = i;
        D_800A4E8A = 0;
        D_800A4E86 = D_800A4E9A;
        b5e = (u16 *)((u8 *)D_80068B5E + D_800A4E8C * 0x10);
        D_800A4E84 = *b5e;
        func_8003819C(D_800A4E86, 0, 0x4000, 0x111);
        func_8003834C(D_800A4E86, D_800A4E84);
        func_80038308(D_800A4E86);
    } else {
        s16 *p86;
        s16 *q86;
        s32 r;

        r = func_80038210(p, b, q);
        p86 = &D_800A4E86;      /* after the call: keeps lui/addiu $s1 out of the pre-call slot */
        *p86 = r;
        if (*p86 == -1) {
            return;
        }
        if ((arg0 & 0xFFFF) == 0x134) {   /* re-spelled, not `id`: the target recomputes it */
            if ((D_800A4F1C & 2) == 0) {
                func_80038638(*p86, 4);
            }
            if ((D_800A4F1C & 4) == 0) {
                func_80038638(*p86, 5);
                func_80038638(*p86, 6);
                func_80038638(*p86, 7);
            }
            if ((D_800A4F1C & 8) == 0) {
                func_80038638(*p86, 8);
            }
        }
        {
            u16 *p8e = &D_800A4E8E;

            f = *p8e & 0x20;
            *p8e = f | 4;
            b5e = (u16 *)((u8 *)D_80068B5E + i * 0x10);
            D_800A4E84 = *b5e;
            D_800A4E8C = i;
            b66 = (u16 *)((u8 *)D_80068B66 + i * 0x10);
            if ((*b66 & 1) != 0) {
                *p8e = f | 0x104;
            } else {
                *p8e = f | 4;
            }
        }
        q86 = &D_800A4E86;
        func_8003834C(*q86, D_800A4E84);
        D_800A4E8A = 0;
        func_80038308(*q86);
    }
    D_800A4E8E |= 9;
}


/* func_8002DC68 -- the 0x400+ message dispatcher: takes the D_8006451C record for
 * (param_1 & 0xFFFF), optionally follows one level of indirection (kind 6), raises the
 * D_800A4F17 reentrancy lock, and switches on the record's low-6-bit kind (1..18).
 *
 * Case 12's `(param_2 << 25) >> 25` is NOT decoration -- it is the byte lever (cookbook
 * candidate: "defeat CSE with a shift pair combine folds back into the mask").  The target
 * computes `andi $s2,0x7F` TWICE: once into $v1 for the `sltu` and again into $v0, which
 * reorg then steals for the `beqz`'s delay slot.  Written as `param_2 & 0x7F` on both sides,
 * cse merges the two `(and:SI ...)` into one pseudo, the store reuses $v1 and the delay slot
 * goes empty -- exactly the 2-instruction residual this function sat at (idx 156 nop vs
 * `andi $v0,$s2,0x7F`, idx 158 `sb $v1` vs `sb $v0`).  cse sees the shift pair as an unrelated
 * expression, and combine's simplify_shift_const turns it back into `andi ...,0x7F` afterwards,
 * so the second mask survives to fill the slot.  Byte-verified both ways round (the shift pair
 * on the compare side matches identically).
 *
 * NOTE for the gate (§378): src/800_b.c already carries four `extern void func_8002DC68(s32, s32);`
 * decls (lines 851, 928, 1249, 2007) plus call sites at 868, 905, 936 (already self-cast) and
 * inside func_8002F248.  This definition returns s32, so the §376/§378 chain
 * (fix_arity_callers --any-proto -> cast_self_callers) has to run before the whole-binary gate. */
extern s16 D_800A4EFC;
extern u8  D_8006451C[];
extern u8  D_800A4F1B;
extern s8  D_800A4F17;
extern u8  D_8006A980;
extern s16 D_8006A982;
extern u8  D_8006A984;
extern u8  D_8006A988[];

extern s32  func_8002F4E4(u8 *);
extern void func_8002F248(s32, s32);
extern void func_8002F714(s32, s32);
extern s32  func_80032048(u32, u8 *, u32);
extern s32  func_800322A8(u32, u8 *, u32);
extern s32  func_800324A4(u32, u8 *, u32, s32);
extern s32  func_80032774(u32, u8 *, u32);
extern s32  func_80034314(u32, u8 *, u32);

s32 func_8002DC68(u32 param_1, u32 param_2) {
    u8 *p;
    u8 *lk;
    s32 ret;
    s8 old;
    u16 val;
    u32 m7;

    if (D_800A4EFC != 0) {
        return 0;
    }
    p = &D_8006451C[(param_1 & 0xFFFF) * 4];
    if (D_800A4F1B == 0 && (*p & 0x80) == 0) {
        return 0;
    }
    if ((*p & 0x3F) == 6) {
        s32 id = func_8002F4E4(p) & 0xFFFF;
        if (id == 0) {
            return 0;
        }
        p = &D_8006451C[id * 4];
    }
    lk = (u8 *)&D_800A4F17;
    old = *lk;
    *lk = 1;
    ret = 0;
    switch (*p & 0x3F) {
    case 1:
        ret = func_80032048(param_1, p, param_2 & 0xFFFF);
        break;
    case 9:
        ret = func_800324A4(param_1, p, param_2 & 0xFFFF, 0);
        break;
    case 7:
        ret = func_800324A4(param_1, p, param_2 & 0xFFFF, 1);
        break;
    case 10:
        func_800322A8(param_1, p, param_2 & 0xFFFF);
        /* fallthrough */
    case 8:
        ret = func_80032774(param_1, p, param_2 & 0xFFFF);
        break;
    case 5:
        ret = func_80034314(param_1, p, param_2 & 0xFFFF);
        break;
    case 2:
        func_8002F248((s32)p, param_2 & 0xFFFF);
        break;
    case 11:
        if ((D_8006A980 & 4) != 0) {
            val = D_8006A982 + D_8006A988[param_2 & 7] - 2;
        } else {
            D_8006A980 |= 4;
            val = D_8006A988[param_2 & 7];
        }
        D_8006A982 = val;
        m7 = param_2 & 7;
        if (m7 == 6) {
            D_8006A980 |= 1;
        } else if (m7 == 2) {
            D_8006A980 |= 2;
        }
        break;
    case 12:
        D_8006A980 |= 8;
        if (D_8006A984 < (param_2 & 0x7F)) {
            D_8006A984 = (u8)((param_2 << 25) >> 25);
        }
        break;
    case 13:
        ret = func_80032048((param_1 & 0xFFFF) | 0x08F40000, p, 0xFFFF);
        break;
    case 14:
        ret = func_80032048((param_1 & 0xFFFF) | 0x0A8A0000, p, 0xFFFF);
        break;
    case 15:
        ret = func_80032048((param_1 & 0xFFFF) | 0x08960000, p, 0xFFFF);
        break;
    case 17:
        func_8002F714(p[3], param_2 & 0xFFFF);
        break;
    case 16:
        ret = func_80032048((param_1 & 0xFFFF) | 0x0B7D0000, p, 0xFFFF);
        break;
    case 18:
        ret = func_80032048((param_1 & 0xFFFF) | 0x04F30000, p, 0xFFFF);
        break;
    }
    D_800A4F17 = old;
    return ret;
}


extern u8 D_8006A980;
extern s16 D_8006A982;
extern u8 D_8006A984;
extern s8 D_800A4F17;
extern u8 D_800A4F18;
extern s16 D_800A4EFC;

extern s32 func_8002DC68();    /* §376: def returns s32 and takes (u32, u32) */
extern void func_8002E138(s32 a0, s32 a1, s32 a2);
extern void func_80030F80(void);
extern void func_8002D320(void);
extern void func_80031BE0(void);

void func_8002DF80(void) {
    u8 v1;

    v1 = D_8006A980;
    if ((v1 & 0x7) != 0) {
        if ((v1 & 0x1) != 0 && (v1 & 0x2) != 0) {
            func_8002DC68(0x719, 0);
            D_8006A980 &= 0xF8;
        }

        if ((D_8006A980 & 0x7) != 0) {
            s16 val = D_8006A982;
            s32 a0;

            if (val <= 0) {
                a0 = 0x710;
            } else if (val >= 4) {
                a0 = 0x712;
            } else {
                a0 = 0x711;
            }

            func_8002DC68(a0, 0);
            D_8006A982 = 0;
            D_8006A980 &= 0xF8;
        }
    }

    v1 = D_8006A980;
    if ((v1 & 0x8) != 0) {
        u8 a1 = D_8006A984;

        if (a1 != 0) {
            func_8002DC68(0xA75, a1 | 0x1000);
            D_8006A984 = 0;
            D_8006A980 |= 0x10;
        } else {
            u8 v0;

            D_8006A980 = v1 & 0xEF;
            D_800A4F17 = 1;
            func_8002E138(4, 0xA75, 0);
            v0 = D_800A4F18;
            D_800A4F17 = v0;

            if (v0 != 0) {
                s16 v0s = D_800A4EFC;

                if (v0s != 0) {
                    D_800A4EFC = v0s - 1;
                }

                func_80030F80();
                func_8002D320();
                func_80031BE0();
                D_800A4F18 = 0;
                D_800A4F17 = 0;
            }
        }

        D_8006A980 &= 0xF7;
    }
}

extern s16 D_8006A982;
extern u8  D_8006A96E;
extern u8  D_8006A980;
extern u8  D_8006A984;
extern s16 D_8006A990;
extern u8  D_8006A994[];
extern s16 D_800A4E86;
extern u16 D_800A4E8C;
extern u16 D_800A4E8E;
extern u16 D_800A4EE0;
extern u8  D_800A4EE6;
extern s16 D_800A4EF6;
extern s16 D_800A4EF8;
extern s16 D_800A4EFA;
extern s16 D_800A4EFC;
extern u8  D_800A4F16;
extern u8  D_800A4F19;
extern u8  D_800A4F1B;
extern u8  D_800A4F1C;
extern u8  D_800A4F1E;
extern u16 D_800A4F20;

extern void func_8002D904(s32);
extern void func_8002E5BC(void);
extern void func_8002E5F8(void);
extern void func_8002E638(s32 a0);
extern void func_8002E700(s32 a0);
extern void func_8002E79C(s32 a0);
extern void func_8002E818(s32 a0);
extern void func_8002E8DC(s32 a0);
extern void func_8002E94C(s32 a0);
extern void func_8002EB10(void);
extern void func_8002EBAC(void);
extern void func_8002EC10(void);
extern void func_8002EDE4(void);
extern void func_8002EE90(void);
extern void func_8002EEB8(void);
extern void func_8002EED8(s32 a0);
extern void func_8002EFD0(void);
extern void func_8002F0D0(void);
extern void func_80031CC8(void);
extern void func_80031DEC(void);
extern void func_80031E94(void);
extern void func_80031F14(void);
extern void func_80031FC8(void);
extern void func_8003491C(s32 arg0);
extern void func_80038668(s32 a0, s32 a1);

void func_8002E138(s32 a0, s32 a1, s32 a2) {
    if ((u16)a0 == 0x7F) {
        return;
    }

    switch ((u16)a0 - 1) {
    case 0:
        func_8002E638(a1 & 0xFFFF);
        break;
    case 7:
        func_8002E700(a1 & 0xFFFF);
        break;
    case 1:
        func_8002F0D0();
        func_8002EDE4();
        D_800A4F1B = 1;
        D_800A4EE0 = 0x4000;
        D_800A4F1C = 0;
        D_8006A96E = 0;
        D_8006A980 = 0;
        D_8006A982 = 0;
        D_8006A984 = 0;
        D_800A4EE6 = 0;
        D_800A4EFC = 0x1E;
        D_800A4F1E = 0;
        break;
    case 2:
        func_8002F0D0();
        func_80031CC8();
        D_800A4EFC = 0;
        break;
    case 3:
        func_8002EED8((a1 & 0xFFFF) | (a2 << 16));
        break;
    case 4:
        func_8002EE90();
        break;
    case 5:
    case 15:
    case 30:
        D_800A4EF6 = 2;
        break;
    case 6:
    case 16:
    case 31:
        D_800A4EF6 = 1;
        break;
    case 10:
        if (D_800A4F19 != 0) {
            func_8002E5BC();
        }
        break;
    case 11:
        if (D_800A4F19 == 0) {
            func_8002E5F8();
        }
        break;
    case 12:
        func_8003491C((a1 & 0xFFFF) | (a2 << 16));
        break;
    case 13:
        func_8002EB10();
        break;
    case 14:
        func_8002EBAC();
        break;
    case 17:
        func_8002E79C(a1 & 0xFFFF);
        break;
    case 18:
        func_8002E8DC(a1 & 0xFFFF);
        break;
    case 19:
        func_80031F14();
        func_8002E818(0);
        break;
    case 20:
        func_80031FC8();
        func_8002E94C(0);
        break;
    case 21:
        func_8002EEB8();
        break;
    case 22:
        func_8002EC10();
        break;
    case 23:
    case 25:
        func_80031DEC();
        break;
    case 24:
    case 26:
        func_80031E94();
        break;
    case 27:
        func_8002EFD0();
        break;
    case 28:
        D_800A4F1B = 0;
        break;
    case 29:
        D_800A4F1B = 1;
        break;
    case 32: {
        s16 t = D_8006A994[a1 & 7];
        D_800A4F16 = 1;
        D_800A4EF8 = t;
        break;
    }
    case 33:
        D_800A4EFA = D_8006A994[a1 & 7];
        break;
    case 34:
        {
            u8 *p = &D_800A4F1C;
            *p |= 1;
            if (D_800A4E8C + 0x100 == 0x134) {
                func_80038668(D_800A4E86, 3);
            }
        }
        break;
    case 35:
        {
            u8 *p = &D_800A4F1C;
            *p |= 2;
            if (D_800A4E8C + 0x100 == 0x134) {
                func_80038668(D_800A4E86, 4);
            }
        }
        break;
    case 36:
        {
            u8 *p = &D_800A4F1C;
            *p |= 4;
            if (D_800A4E8C + 0x100 == 0x134) {
                func_80038668(D_800A4E86, 5);
                func_80038668(D_800A4E86, 6);
                func_80038668(D_800A4E86, 7);
            }
        }
        break;
    case 37:
        {
            u8 *p = &D_800A4F1C;
            *p |= 8;
            if (D_800A4E8C + 0x100 == 0x134) {
                func_80038668(D_800A4E86, 8);
            }
        }
        break;
    case 38:
        if ((D_800A4E8E & 1) != 0) {
            D_8006A990 = 0;
            D_800A4F20 = a1;
        } else {
            func_8002D904(a1 & 0xFFFF);
        }
        break;
    case 41:
        D_800A4F1C = 0;
        break;
    case 39:
        D_800A4F1E = 1;
        break;
    case 40:
        D_800A4F1E = 0;
        func_80031CC8();
        break;
    }
}

extern u8 D_800A4F19;
extern void CdMix(u8 *);

void func_8002E5BC(void) {
    u8 sp10[4];

    sp10[0] = 0x5A;
    sp10[1] = 0x5A;
    sp10[2] = 0x5A;
    sp10[3] = 0x5A;
    CdMix(sp10);
    D_800A4F19 = 0;
}

extern u8 D_800A4F19;
extern void CdMix(u8 *);

void func_8002E5F8(void) {
    u8 sp10[4];

    sp10[0] = 0x80;
    sp10[1] = 0;
    sp10[2] = 0x80;
    sp10[3] = 0;
    CdMix(sp10);
    D_800A4F19 = 1;
}


extern u16 D_800A4E8E;
extern s16 D_800A4E86;
extern s32 D_80078F10;
extern u16 D_8006A99C[];
extern u16 D_800A46B8;
extern u8 D_8006AEEC;
extern s32 D_800A46B4;
extern u8 D_800A46BA;
extern u16 D_800A4EF4;

extern s32 func_8003836C(s32 a0);
extern void func_8002E700(s32 a0);

void func_8002E638(s32 a0) {
    s32 s0;
    s16 temp;
    u16 a0_masked;
    u16 v1;

    s0 = a0;

    if ((D_800A4E8E & 4) != 0) {
        temp = D_800A4E86;
        if ((func_8003836C(temp) << 16) != 0) {
            func_8002E700(s0 & 0xFFFF);
            return;
        }
    }

    if (D_80078F10 == 0) {
        return;
    }

    a0_masked = s0 & 0xFFFF;

    if (a0_masked < 5) {
        v1 = *(u16 *)((u8 *)D_8006A99C + a0_masked * 4);
    } else {
        v1 = 0x1F;
    }

    D_800A46B8 = v1;
    v1 = D_8006AEEC;
    D_800A46B4 = 0xFFFF;
    D_800A46BA = 1;
    D_800A4EF4 = v1;
}


extern u16 D_800A4E8E;
extern u16 D_800A4E8A;
extern s16 D_800A4E86;
extern s16 D_8006A9BC[];
extern u16 D_8006A9B0[];

extern s32 func_8003836C(s32 a0);
extern void func_8003819C(s32 a0, s32 a1, s32 a2, s32 a3);

void func_8002E700(s32 a0)
{
    u16 index;

    if ((D_800A4E8E & 0x4) == 0)
        return;

    if ((s16)func_8003836C(D_800A4E86) == 0)
        return;

    index = (u16)a0;
    if (index >= 5)
        index = 4;

    func_8003819C(D_800A4E86, 0, 0, D_8006A9BC[index]);
    D_800A4E8A = D_8006A9B0[index];
}

void func_8002E79C(s32 a0)
{
    extern u8  D_800A4EE6;
    extern u16 D_800A4EE0;
    extern u16 D_800A4EE2;
    extern u16 D_800A4EE4;
    extern u16 D_8006A9C8[];
    u8 *fl;
    u16 v;

    fl = &D_800A4EE6;
    if (!(*fl & 2)) {
        *fl |= 2;
        if (!(*fl & 4)) {
            v = (u16)a0;
            if (v >= 5) {
                v = 4;
            }
            D_800A4EE0 = 0x4000;
            D_800A4EE4 = 0x2FFF;
            D_800A4EE2 = D_8006A9C8[v];
            *fl |= 3;
        }
    }
}

void func_8002E818(s32 a0)
{
    extern u16 D_800A4E8E;
    extern u16 D_800A4E8C;
    extern u8  D_800A4EE6;
    extern u16 D_800A4EE0;
    extern u16 D_800A4EE2;
    extern u16 D_800A4EE4;
    extern u16 D_8006A9D4[];
    extern void func_8002EA10(void);
    u8 *a1;
    u8 fl;
    u8 nw;
    u16 v;

    if ((D_800A4E8E & 0x4) != 0 && D_800A4E8C == 0x3E) {
        func_8002EA10();
    }

    a1 = &D_800A4EE6;
    fl = *a1;
    if (!(fl & 4)) {
        nw = fl | 4;
        *a1 = nw;
        if (!(nw & 2)) {
            if ((u16)a0 >= 5) {
                a0 = 4;
            }
            D_800A4EE0 = 0x4000;
            D_800A4EE4 = 0x2000;
            v = D_8006A9D4[(u16)a0];
            *a1 = fl | 5;
            D_800A4EE2 = v;
        }
    }
}

void func_8002E8DC(s32 a0)
{
    extern u8  D_800A4EE6;
    extern u16 D_800A4EE2;
    extern u16 D_800A4EE4;
    extern u16 D_8006A9E0[];
    u8 *p;
    u8 fl;
    u8 nw;
    u16 v;

    p = &D_800A4EE6;
    fl = *p;
    if (fl & 2) {
        nw = fl & 0xFD;
        *p = nw;
        if (!(fl & 4)) {
            if ((u16)a0 >= 5) {
                a0 = 4;
            }
            D_800A4EE4 = 0x4000;
            v = D_8006A9E0[(u16)a0];
            *p = nw | 1;
            D_800A4EE2 = v;
        }
    }
}

void func_8002E94C(s32 a0)
{
    extern u16 D_800A4E8E;
    extern u16 D_800A4E8C;
    extern u8  D_800A4EE6;
    extern u16 D_800A4EE4;
    extern u16 D_800A4EE2;
    extern u16 D_8006A9EC[];
    extern void func_8002EAB0(void);
    u8 *a1;
    u8 fl;
    u8 clr;
    u16 v;

    if ((D_800A4E8E & 0x4) != 0 && D_800A4E8C == 0x3E && (D_800A4E8E & 0x10) != 0) {
        func_8002EAB0();
    }

    a1 = &D_800A4EE6;
    fl = *a1;
    if (fl & 0x4) {
        clr = fl & 0xFB;
        *a1 = clr;
        if (!(fl & 0x2)) {
            if ((u16)a0 >= 5) {
                a0 = 4;
            }
            D_800A4EE4 = 0x4000;
            v = D_8006A9EC[(u16)a0];
            *a1 = clr | 0x1;
            D_800A4EE2 = v;
        }
    }
}

extern u16 D_800A4E8E;
extern s16 D_800A4E86;

extern s32  func_8003836C(s32 a0);
extern s32  func_800381E4(s32 a0, s32 a1);
extern void func_8002EC10(void);
extern void func_800383A4(s16 a0);

void func_8002EA10(void) {
    u16 *s0;
    u16 v0;
    s32 ret;

    s0 = &D_800A4E8E;
    v0 = *s0;
    if (v0 & 4) {
        ret = func_8003836C(D_800A4E86);
        if ((ret << 16) != 0) {
            if (func_800381E4(D_800A4E86, 0) != 0) {
                func_8002EC10();
            } else {
                func_800383A4(D_800A4E86);
                *s0 = *s0 | 0x10;
            }
        }
    }
}


extern u16   D_800A4E8E;
extern s16   D_800A4E86;
extern void func_80038308(s16 a0);

void func_8002EAB0(void) {
    u16 *s0;
    u16 v0;

    s0 = &D_800A4E8E;
    v0 = *s0;
    if ((v0 & 0x10) != 0) {
        func_80038308(D_800A4E86);
        v0 = *s0;
        v0 = (v0 | 0x9) & 0xFFEF;
        *s0 = v0;
    }
}

extern u16 D_800A4E8E;
extern s16 D_800A4E86;

extern s32  func_8003836C(s32 a0);
extern s32  func_800381E4(s32 a0, s32 a1);
extern void func_8002EC10(void);
extern void func_800383A4(s16 a0);
extern void func_80036F18(void);

void func_8002EB10(void) {
    u16 v0;
    s32 ret;

    v0 = D_800A4E8E;
    if (v0 & 4) {
        ret = func_8003836C(D_800A4E86);
        if ((ret << 16) != 0) {
            if (func_800381E4(D_800A4E86, 0) != 0) {
                func_8002EC10();
            } else {
                func_800383A4(D_800A4E86);
                D_800A4E8E = D_800A4E8E | 0x10;
            }
        }
    }
    func_80036F18();
}


extern void func_80036D58(s16);
extern void func_80038308(s16 arg0);
extern u16 D_800A4E8E;
extern s16 D_800A4E86;

void func_8002EBAC(void) {
    u16 v0;

    ((void (*)())func_80036D58)(0);

    if (D_800A4E8E & 0x10) {
        func_80038308(D_800A4E86);

        v0 = D_800A4E8E;
        v0 |= 0x9;
        v0 &= 0xFFEF;
        D_800A4E8E = v0;
    }
}


extern u16 D_800A4E8E;
extern s16 D_800A4E86;
extern u16 D_800A4E8C;
extern u16 D_800A4F20;
extern u16 D_800A4F22;
extern u16 D_800A4E8A;
extern u16 D_80068B66[][8];
extern u16 D_800A4EA2;
extern s16 D_800A4E9A;
extern u16 D_800A4EA0;

extern s32 func_8003836C(s32 a0);
extern void func_800383A4(s16 a0);
extern void func_800384A8(s16 a0);
extern void func_800385C0(s16 a0);

void func_8002EC10(void) {
    u16 v0;
    s16 *s0;

    D_800A4F20 = 0;
    D_800A4F22 = 0;
    D_800A4E8A = 0;

    if (D_800A4E8E & 4) {
        if ((s16)func_8003836C(D_800A4E86) && (D_80068B66[D_800A4E8C][0] & 1)) {
            if (D_800A4EA2 & 4) {
                func_800385C0(D_800A4E9A);
                D_800A4EA2 &= 0xFEE8;
            }

            func_800383A4(D_800A4E86);

            v0 = D_800A4E8E;
            D_800A4E8E = v0 & 0xFFFD;
            D_800A4EA2 = v0 & 0xFFFD;
            D_800A4E9A = D_800A4E86;
            D_800A4EA0 = D_800A4E8C;
            D_800A4E8E = v0 & 0xFEF9;
            return;
        }

        s0 = &D_800A4E86;
        if ((s16)func_8003836C(*s0)) {
            func_800384A8(*s0);
        }

        D_800A4E8E &= 0xFEE8;
        func_800385C0(*s0);
    }
}


extern void func_8002EC10(void);
extern void func_800385C0(s16);
extern u16 D_800A4EA2;
extern s16 D_800A4E9A;

void func_8002ED90(void) {
    u16* ptr;

    func_8002EC10();

    ptr = &D_800A4EA2;
    if (*ptr & 0x4) {
        func_800385C0(D_800A4E9A);
        *ptr = 0;
    }
}

extern void func_8002EE90(void);
extern void func_80031CC8(void);
extern void func_8002EC10(void);
extern void func_800385C0(s16);
extern u16 D_800A4EA2;
extern s16 D_800A4E9A;
extern u8  D_800A4EE6;
extern s16 D_800A4EF6;

void func_8002EDE4(void) {
    func_8002EE90();
    func_80031CC8();
    func_8002EC10();

    if (D_800A4EA2 & 0x4) {
        func_800385C0(D_800A4E9A);
        D_800A4EA2 = 0;
    }

    D_800A4EF6 = 1;
    D_800A4EE6 &= 0xF9;
}

extern void func_80036EB4(void);
extern void func_8002EC10(void);

struct func_8002EE64_b { u8 c; };

void func_8002EE64(void) {
    s32 g1, g2, g3, g4;
    struct func_8002EE64_b b;

    b.c = 0x88;
    ((void (*)(s32, s32, s32, s32, struct func_8002EE64_b))func_80036EB4)(g1, g2, g3, g4, b);
    func_8002EC10();
}


extern void func_80036EE8(void);
extern void func_8002EC10(void);

void func_8002EE90(void) {
    func_80036EE8();
    func_8002EC10();
}

void func_8002EEB8(void) {
    func_80036EE8();
}

extern u8 D_8006451C[];
extern s8 D_800A4F17;

extern s32 func_8002F4E4(u8 *);
extern void func_80033398(u32);
extern void func_800346D0(s32);
extern void func_8002F714(s32, s32);

void func_8002EED8(s32 a0)
{
    u8 *rec;
    s16 ret;
    u8 old;

    if ((s16)a0 < 0x100) {
        return;
    }

    rec = &D_8006451C[(s16)a0 * 4];
    if ((*rec & 0x7F) == 6) {
        ret = func_8002F4E4(rec);
        if (ret == 0) {
            return;
        }
        rec = &D_8006451C[ret * 4];
    }

    old = *(u8 *)&D_800A4F17;
    *(u8 *)&D_800A4F17 = 1;

    switch (*rec & 0x3F) {
    case 5:
        func_800346D0(a0);
        break;
    case 1:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 18:
        func_80033398(a0);
        break;
    case 17:
        func_8002F714(rec[3], 0x1000);
        break;
    }

    *(u8 *)&D_800A4F17 = old;
}


extern void func_80034844(void);
extern void func_80031B7C(void);

void func_8002EFD0(void)
{
    func_80034844();
    func_80031B7C();
}


extern s32 D_800A2B98;
extern s32 D_800C7D20;

void func_8002EFF8(s32 a0, s32 a1)
{
    s32 v0;
    s32 v1;
    s32 a0_tmp;

    v0 = 1;

    if (a0 == v0) {
        v1 = D_800A2B98;
        a0_tmp = D_800C7D20;
        v1 = v1 & (~a1);
        a0_tmp = a0_tmp | a1;
        D_800A2B98 = v1;
        D_800C7D20 = a0_tmp;
    } else {
        v0 = ~a1;
        v1 = D_800C7D20;
        a0_tmp = D_800A2B98;
        v1 = v1 & v0;
        a0_tmp = a0_tmp | a1;
        D_800C7D20 = v1;
        D_800A2B98 = a0_tmp;
    }
}


extern s32 D_800A2BA0;
extern s32 D_800C7D2C;

void func_8002F064(s32 a0, s32 a1) {
    s32 v0;
    s32 v1;
    s32 out_a0;

    if (a0 == 1) {
        v0 = ~a1;
        v1 = D_800A2BA0;
        out_a0 = D_800C7D2C;
        v1 = v1 & v0;
        out_a0 = out_a0 | a1;
        D_800A2BA0 = v1;
        D_800C7D2C = out_a0;
    } else {
        v1 = D_800C7D2C;
        out_a0 = D_800A2BA0;
        v1 = v1 & (~a1);
        out_a0 = out_a0 | a1;
        D_800C7D2C = v1;
        D_800A2BA0 = out_a0;
    }
}

extern s32 D_800A64B0;

void func_8002F0D0(void) {
    s32 i = 0x54;
    do {
        *(s32 *)((s32)&D_800A64B0 + i) = 0;
        i -= 0xC;
    } while (i >= 0);
}


extern s32 D_800A64B0;

void *func_8002F0F4(void) {
    s32 *ptr = (s32 *)&D_800A64B0;
    s32 i = 0;

    while (i < 8) {
        s32 val = *ptr;
        if (val == 0) {
            return (void *)ptr;
        }
        i++;
        ptr = (s32 *)((s32)ptr + 0xC);
    }

    return 0;
}

void func_8002F12C(s32 a0) {
    extern s32 func_8002DC68();    /* §376: def returns s32 and takes (u32, u32) */
    func_8002DC68(*(s32 *)(a0 + 4), 0);
}

extern u8 D_800A4694[];

void func_8002F150(s32 arg0) {
    struct F150Rec {
        u8 pad[0x0E];
        u8 flg[8];
        u8 tail[0x3E];
    };
    struct F150Slot {
        u8 pad[0x20];
        u32 u20;
        u32 u24;
        u32 u28;
        u32 u2C;
        u16 u30;
        u8 mid[5];
        u8 u37;
        u8 u38;
        u8 tail[0x1B];
    };

    struct F150Rec *rec = (struct F150Rec *)D_800A4694 + arg0;
    struct F150Slot *slots = (struct F150Slot *)(D_800A4694 + 0x2F4);
    s32 i;
    s32 val;

    for (i = 0, val = -0x18; i < 8; i++) {
        if (rec->flg[i]) {
            slots[i].u28 = slots[i].u20 - 0x100;
            slots[i].u37 |= 1;
            slots[i].u30 = 0;
            slots[i].u38 = 0;
            slots[i].u2C = val;
        }
    }
}

typedef struct F1ccRec {
    u8 pad[0x0E];
    u8 flg[8];
    u8 tail[0x3E];
} F1ccRec;

typedef struct F1ccSlot {
    u8 pad[0x20];
    u32 u20;
    u32 u24;
    u32 u28;
    u32 u2C;
    u16 u30;
    u8 mid[5];
    u8 u37;
    u8 u38;
    u8 tail[0x1B];
} F1ccSlot;

extern u8 D_800A4694[];

void func_8002F1CC(s32 arg0) {
    F1ccRec *sp = (F1ccRec *)D_800A4694 + arg0;
    F1ccSlot *slots = (F1ccSlot *)(D_800A4694 + 0x2F4);
    s32 i;
    s32 val;

    for (i = 0, val = 0x18; i < 8; i++) {
        if (sp->flg[i]) {
            slots[i].u28 = slots[i].u20 + 0x100;
            slots[i].u37 |= 1;
            slots[i].u30 = 0;
            slots[i].u38 = 0;
            slots[i].u2C = val;
        }
    }
}


void func_8002F248(s32 arg0, s32 arg1) {
    extern s32 D_800A4EEC;
    extern u8 D_8006A9F8[];
    extern u8 D_800A4694[];
    extern s32 func_8002DC68();    /* §376: def returns s32 and takes (u32, u32) */
    extern s32 func_800331D4(s32);
    s32 i;
    s32 idx;
    F1ccRec *rec;
    F1ccSlot *slots;

    switch (*(u8 *)(arg0 + 3)) {
    case 0:
        D_800A4EEC = D_800A4EEC * 0x41C64E6D + 0x3039;
        switch (((u32)D_800A4EEC >> 16) & 0x7) {
        case 0:
        case 3:
            func_8002DC68(0x67C, 0);
            break;
        case 1:
        case 2:
            func_8002DC68(0x689, 0);
            break;
        case 4:
        case 5:
            func_8002DC68(0x67B, 0);
            break;
        }
        break;
    case 1:
        func_8002DC68((u16)arg1, 0);
        break;
    case 2:
        idx = func_800331D4(0x95C);
        if (idx) {
            rec = (F1ccRec *)D_800A4694 + idx;
            slots = (F1ccSlot *)(D_800A4694 + 0x2F4);
            for (i = 0; i < 8; i++) {
                if (rec->flg[i]) {
                    slots[i].u30 = 0;
                    slots[i].u38 = 0;
                    slots[i].u2C = -0x18;
                    slots[i].u28 = slots[i].u20 - 0x100;
                    slots[i].u37 |= 1;
                }
            }
        }
        break;
    case 3:
        idx = func_800331D4(0x95C);
        if (idx) {
            rec = (F1ccRec *)D_800A4694 + idx;
            slots = (F1ccSlot *)(D_800A4694 + 0x2F4);
            for (i = 0; i < 8; i++) {
                if (rec->flg[i]) {
                    slots[i].u30 = 0;
                    slots[i].u38 = 0;
                    slots[i].u2C = 0x18;
                    slots[i].u28 = slots[i].u20 + 0x100;
                    slots[i].u37 |= 1;
                }
            }
        }
        break;
    case 4:
        D_800A4EEC = D_800A4EEC * 0x41C64E6D + 0x3039;
        switch (((u32)D_800A4EEC >> 16) & 0x7) {
        case 0:
        case 3:
            func_8002DC68(0xAFD, 0);
            break;
        case 1:
        case 2:
        case 5:
            func_8002DC68(0xAFF, 0);
            break;
        case 4:
            func_8002DC68(0xAFE, 0);
            break;
        }
        break;
    case 5:
        func_8002DC68(0xB06, 0);
        func_8002DC68(0xB07, 0);
        break;
    case 6:
        func_8002DC68(0xB06, 0);
        func_8002DC68(0xC60, 0);
        break;
    case 7:
        D_800A4EEC = D_800A4EEC * 0x41C64E6D + 0x3039;
        func_8002DC68(*(u16 *)(D_8006A9F8 + (((u32)D_800A4EEC >> 15) & 0x1E)), 0);
        break;
    }
}


/* func_8002F4E4 -- 6-level gauntlet lookup into the D_800A4EE8 owner block.
 *
 * TU-placement note (src/800.c): this function's INCLUDE_ASM sits at ~line 9410,
 * BEFORE the file declares `typedef struct Owner4EE8 {...}` (~9756, whose first
 * 0x14 bytes are an opaque pad00 that THIS function is the one to break out into
 * fields) and BEFORE `typedef ... Rsc24` / `extern Rsc24 D_800A4640[];` (~10860/10885).
 * So local equivalents are declared here.
 *
 * The two object externs are declared at BLOCK scope on purpose. A second
 * FILE-scope declaration of D_800A4640 / D_800A4EE8 with a different (local)
 * struct type is a hard error under the pinned cc1 ("conflicting types for
 * `D_800A4640'", rc=33) once the real ones appear later in the TU; the same
 * pair at block scope is only a warning ("type mismatch with previous external
 * decl") and compiles clean. Codegen is identical either way -- verified.
 */

/* D_800A4640 element -- same layout as the TU's own `Rsc24` (src/800.c ~13288,
 * declared later in the file than this function's INCLUDE_ASM slot, so it
 * can't be named directly here). Spelled with the TU's own typedef NAME
 * ("Rsc24", block-scoped -- shadows harmlessly, since the file-scope typedef
 * of the same name/shape doesn't exist yet at this point in the TU) and the
 * TU's own field-list TEXT verbatim, with no inline offset comments: the
 * reconciler's cosmetic-typedef check is a literal body-text comparison
 * against src/800.c's `Rsc24`, and per-field offset comments here (the TU's
 * copy has only one trailing offset tag, after the closing brace, not one
 * per field) made the two bodies textually differ and tripped
 * refuse-DIFFERENT-STRUCT even though the layouts are identical
 * field-for-field. */

/* opaque — matches the TU's `typedef struct Owner4EE8 Owner4EE8;` spelling
 * (src/800.c ~13559) exactly so this local decl is droppable at bank time in
 * favor of the TU's real `typedef struct Owner4EE8 { u8 pad00[0x14]; Rec14
 * **unk14; } Owner4EE8;`. This function only ever touches fields that live
 * inside pad00, so it pointer-casts through the opaque type at each byte
 * offset (same pattern as func_80034314 / func_8002C8F4) rather than naming
 * a same-named struct with a conflicting layout. */

extern s16 D_800A4EF0;

s32 func_8002F4E4(u8 *a0) {
    extern Rsc24 D_800A4640[];
    extern Owner4EE8 *D_800A4EE8;
    Owner4EE8 *a2;
    s32 idx;
    s32 lvl;
    s32 val;
    s32 idx2;
    s32 word;
    s32 rowBytes;
    u16 *row;

    if (D_800A4EF0 == 0) {
        return 0;
    }

    a2 = D_800A4EE8;
    if (a2 == 0) {
        return 0;
    }

    idx = a0[2];
    lvl = D_800A4640[idx].unk00;

    if (lvl < *(s16 *)((u8 *)a2 + 0x04)) {
        return 0;
    }
    lvl -= *(s16 *)((u8 *)a2 + 0x04);

    if (lvl >= *(s16 *)((u8 *)a2 + 0x02)) {
        return 0;
    }

    val = (*(s16 **)((u8 *)a2 + 0x08))[lvl];
    if (val == 0) {
        return 0;
    }

    idx2 = a0[3];
    if (idx2 >= *(s16 *)((u8 *)a2 + 0x0C)) {
        return 0;
    }
    val -= 1;

    /* Row stride is in BYTES and must stay bound to unk0E: writing
     * idx2 * (unk0E * 2) inline lets gcc reassociate it to
     * (idx2 * 2) * unk0E (sll a0 then mult) -- the separate rowBytes
     * local pins mult $a0,$v0 with $v0 = unk0E*2, as the target has.
     * The `row` pointer temp is also load-bearing: it is what keeps val
     * in $a1 and puts val*2 into a fresh $v0. NO register pins -- pinning
     * val to $5 (first-pass attempt) makes the shift go in-place into $a1
     * and reorders the mult delay shadow (sll before lw). Cookbook lever C:
     * the fix was to UNPIN.
     */
    rowBytes = *(s16 *)((u8 *)a2 + 0x0E) * 2;
    row = (u16 *)((u8 *)(*(u16 **)((u8 *)a2 + 0x10)) + idx2 * rowBytes);
    word = row[val];

    if (word != 0x7F) {
        return word;
    }

    return 0;
}


extern s16 D_800A4EF0;
extern void func_8002F620(void);

void func_8002F5C8(u8 *a0) {
    extern Owner4EE8 *D_800A4EE8;
    s16 *p = &D_800A4EF0;
    u16 temp;

    if (*p != 0) {
        func_8002F620();
    }
    temp = *(u16 *)a0;
    D_800A4EE8 = a0;
    *p = temp;
}


extern s16 D_800A4EF0;
extern void func_80031D70(void);

void func_8002F620(void) {
    D_800A4EF0 = 0;
    func_80031D70();
}

extern s16 D_800A4EF0;
s16 func_8002F648(void) {
    return D_800A4EF0;
}

extern u8  D_800A4698;
extern s16 D_800A4688;

s32 func_8002F658(void) {
    if (D_800A4698 != 0) {
        return -1;
    }
    return D_800A4688;
}


extern u8  D_800A4698;
extern s16 D_800A4688;
extern s16 D_800C5328[];
extern s16 D_800A46A2;
extern u8  D_800A46B0;

extern void func_800415A8(s32);

void func_8002F67C(void) {
    u8 *p = &D_800A4698;
    s32 v0;
    s32 t;

    if (*p == 0) {
        v0 = D_800A4688;
        *(s16 *)((u8 *)D_800C5328 + (v0 << 2)) = -1;
        *p = 1;
    }

    t = D_800A46A2;
    if (t >= 0) {
        func_800415A8(t);
        D_800A46A2 = -1;
    }

    if (D_800A46B0 == 0) {
        D_800A46B0 = 1;
    }
}


extern u8 D_800760D0;
extern u8 D_800760D4;
extern u8 D_800760D8;
extern u8 D_800760DC;
extern u8 D_8006A96E;
extern void (*D_800A4F24)(void);

extern void func_8002F80C(void);

void func_8002F714(s32 a0, s32 a1) {
    switch (a0 & 0xFFFF) {
        case 0:
            D_800760D0 = a1 & 0x7F;
            D_800A4F24 = func_8002F80C;
            D_8006A96E |= 1;
            break;
        case 1:
            D_800760D4 = a1 & 0x7F;
            D_800A4F24 = func_8002F80C;
            D_8006A96E |= 2;
            break;
        case 2:
            D_800760D8 = a1 & 0x7F;
            D_800A4F24 = func_8002F80C;
            D_8006A96E |= 4;
            break;
        case 3:
            D_800760DC = a1 & 0x7F;
            D_800A4F24 = func_8002F80C;
            D_8006A96E |= 8;
            break;
    }
}

extern u8 D_8006A96E;
extern s16 D_8006A96C;
extern u8 D_800760D0;
extern u8 D_800760D4;
extern u8 D_800760D8;
extern u8 D_800760DC;
extern s8 D_800A4F17;
extern u8 D_800A4F18;
extern s16 D_800A4EFC;
extern void (*D_800A4F24)(void);

extern s32 func_8002DC68();    /* §376: def returns s32 and takes (u32, u32) */
extern void func_8002E138(s32 a0, s32 a1, s32 a2);
extern void func_80030F80(void);
extern void func_8002D320(void);
extern void func_80031BE0(void);

void func_8002F80C(void) {
    u8 flag;
    s16 max;
    u8 a0;
    u8 v0;

    flag = 0;
    max = 0;
    if ((D_8006A96E & 1) != 0) {
        flag = 1;
        max = D_800760D0;
    }
    if ((D_8006A96E & 2) != 0) {
        flag = 1;
        if (max < D_800760D4) {
            max = D_800760D4;
        }
    }
    if ((D_8006A96E & 4) != 0) {
        flag = 1;
        if (max < D_800760D8) {
            max = D_800760D8;
        }
    }
    if ((D_8006A96E & 8) != 0) {
        flag = 1;
        if (max < D_800760DC) {
            max = D_800760DC;
        }
    }

    a0 = D_8006A96E;
    D_8006A96E = a0 & 0xF0;

    if (flag != 0) {
        D_8006A96C = 0x10;
        if (max != 0) {
            func_8002DC68(0xBEB, max | 0x1000);
            D_8006A96E |= 0x10;
            return;
        }
        if ((a0 & 0x10) == 0) {
            return;
        }
        D_800A4F17 = 1;
        func_8002E138(4, 0xBEB, 0);
        v0 = D_800A4F18;
        D_800A4F17 = v0;
        if (v0 != 0) {
            s16 c = D_800A4EFC;
            if (c != 0) {
                D_800A4EFC = c - 1;
            }
            func_80030F80();
            func_8002D320();
            func_80031BE0();
            D_800A4F18 = 0;
            D_800A4F17 = 0;
        }
    } else {
        s16 t = D_8006A96C;
        if (t == 0) {
            return;
        }
        t = t - 1;
        D_8006A96C = t;
        if (t != 0) {
            return;
        }
        if ((a0 & 0x10) == 0) {
            return;
        }
        D_800A4F17 = 1;
        func_8002E138(4, 0xBEB, 0);
        v0 = D_800A4F18;
        D_800A4F17 = v0;
        if (v0 != 0) {
            s16 c = D_800A4EFC;
            if (c != 0) {
                D_800A4EFC = c - 1;
            }
            func_80030F80();
            func_8002D320();
            func_80031BE0();
            D_800A4F18 = 0;
            D_800A4F17 = 0;
        }
    }

    D_800A4F24 = 0;
    D_8006A96E = D_8006A96E & 0xEF;
}

void func_8002FA3C(void) {
    extern s16 D_800760E8;
    extern s16 D_800760E4;
    extern s16 D_800760EC;
    extern void (*D_800A4F24)(void);
    extern int func_8003EDE8(int a0, int a1, int a2);
    u16 w;
    s16 t;

    w = *(u16 *)&D_800760E8;
    w = w + 1;
    D_800760E8 = (s16)w;
    if ((s16)w < 0x10) {
        if (D_800760E4 > D_800760EC) {
            D_800760E4 = t = D_800760E4 - D_800760EC;
            func_8003EDE8(0, t, t);
            return;
        }
    }
    func_8003EDE8(0, 0, 0);
    D_800A4F24 = NULL;
}


extern s16 D_800A46CC;

void func_8002FAE0(void) {
    D_800A46CC = 0;
    func_8002C8BC();
}



extern void func_800301A4(void);
extern int  func_80037CD8(void *arg);
extern void func_80031A98(void);
extern void func_8002EC10(void);
extern void func_800415A8(s32);



extern Elm12 D_80064D49[];
extern u8    D_80064D4D[];
extern Ent24 D_800A463C[];
extern Rsc24 D_800A4640[];
extern s16   D_800A4642[];
extern u8    D_800A4650[];
extern s32   D_800A46C8;
extern s16   D_800A46CC;
extern s16   D_800C5328[];
extern u8    D_8006AEF4;

int func_8002FB08(int entry) {
    s32 idx12;
    s32 b;
    s32 idx24;
    s16 h;
    s32 b2;
    s32 idx24b;
    s16 v;
    s16 a4;

    if (func_80037CD8((void *)func_800301A4) == 0) {
        return 0;
    }
    idx12 = entry * 12;
    b = D_80064D49[entry].unk00;
    idx24 = b * 24;
    D_800A46C8 = *(s32 *)((u8 *)D_800A463C + idx24);
    if (D_800A4650[idx24] == 0) {
        h = *(s16 *)((u8 *)D_800A4640 + idx24);
        D_800C5328[h * 2] = -1;
    }
    func_80031A98();
    b2 = D_80064D4D[idx12];
    if (b2 != 0) {
        idx24b = b2 * 24;
        v = *(s16 *)((u8 *)D_800A4642 + idx24b);
        if (v >= 0) {
            func_8002EC10();
            a4 = *(s16 *)((u8 *)D_800A4642 + idx24b);
            func_800415A8(a4);
            *(s16 *)((u8 *)D_800A4642 + idx24b) = -1;
            *(s16 *)((u8 *)D_800A4640 + idx24b) = -1;
        }
        D_800A4650[idx24b] = 1;
    }
    D_800A46CC = 0;
    D_8006AEF4 |= 2;
    return 1;
}


extern s32  func_8003C4F0(s32);
extern void func_8003C498(s32);
extern void SpuWrite(s32, s32);
extern void func_80037D74(void);
extern u8   D_8006AEF4;
extern s32  D_800A46C8;

int   func_8002FC64(int nbytes, u32 *src);   /* stage/copy a payload run */
int   func_8002FC64(int nbytes, u32 *src)
{
    s32 s2 = nbytes;
    u32 *s1 = src;
    s32 *s0;
    s32 result;

    if (D_8006AEF4 & 1) {
        if (func_8003C4F0(0) == 0) {
            func_80037D74();
            return 0;
        }
    }

    s0 = (s32 *)(&D_800A46C8);
    result = ((s32 (*)(s32))func_8003C498)(*s0);

    if (result != 0) {
        SpuWrite((s32)s1, s2);
        *s0 += s2;
        D_8006AEF4 |= 1;
        return 1;
    }

    func_80037D74();
    return 0;
}


extern s16 D_800A46CC;
extern u8  D_8006AEF4;

extern void  func_80037D74(void);
extern s32   func_8003C4F0(s32);
extern s32   func_8002FF0C(s32, s32);
extern void  func_8002D240(s32 a0);

int func_8002FD14(int buf, int len) {
    s32 result;
    s32 temp;

    if (D_800A46CC == 0) {
        func_80037D74();
        temp = func_8003C4F0(0);
        if (temp != 0) {
            D_8006AEF4 &= 0xFE;
            result = func_8002FF0C(buf, len);
        } else {
            result = 0;
        }
    } else {
        result = func_8002FF0C(buf, len);
    }

    if (result != 0) {
        if (buf == 0x1A) {
            func_8002D240(0x28);
        }
        return result;
    }

    return 0;
}

extern void func_80037D74(void);

void func_8002FDC8(void) {
    func_80037D74();
}

extern s32 D_800A469C;
extern s16 D_800A46A0;
extern s16 D_800A46A2;
extern u8  D_800A46B0;
extern s32 D_800652F0[];

extern void func_8002ED90(void);
extern void func_800415A8(s32);
extern s16  func_80041A80(s32, s32, s32);
extern s16  func_800419B0(s32);

/* func_8002FDE8 -- start resource `idx` playing out of the buffer `data`.
 *
 * Byte-shape notes (each measured against asm/nonmatchings/800_b_2/func_8002FDE8.s):
 *   - `extern s16 D_800A46D2;` at BLOCK SCOPE, exactly as func_8002FF0C and func_800301C8 do
 *     below: this TU declares the symbol `extern s16 D_800A46D2[]` further down, and the ARRAY
 *     spelling makes cse cache the address in a callee-saved register across the func_800419B0
 *     call; the target keeps two independent %hi/%lo accesses (the `sh` at 0x2066C and the `lh`
 *     at 0x206C8), which only the scalar spelling emits.  This was the residual that held the
 *     function at closeness 35 for four prior attempts.
 *   - the FIRST zero-byte fence (cookbook S194-A, AFTER placement) keeps `idx | 0x4000` at the
 *     head of the join block, which is what lets reorg steal it into the `bltz` delay slot and
 *     eager-duplicate it on the taken path (0x20618 / 0x20630).  Without it the function is
 *     2 instructions short.
 *   - `one` is a real local, and the fence sits BETWEEN its assignment and the first store:
 *     the `li` must be the block's first insn while the `sb` sinks below the index computation.
 *     Writing the literal 1 at all three sites instead costs 10 mismatched.
 *   - `i4 = idx * 4;` is a separate statement.  The `sb D_800A46B0` and the `lw D_800652F0`
 *     carry a memory dependence, so sched1 orders them by LUID; splitting the index out gives
 *     the `sll` a lower LUID than the `sb` and reproduces `sll / addu $a0 / sb / lw`.
 *   - the SECOND fence is the S47 live-length slider.  `data` (2 refs / 15 insns, pri 1333) and
 *     the `1` constant (4 refs / 58 insns, pri 1379) are adjacent in global.c's allocno_compare,
 *     so the constant allocated first and took $s1.  One extra static insn where the constant is
 *     live and `data` is dead lengthens it to 59 (pri 1355 -> ties/loses) and hands $s1 back to
 *     `data`, $s2 to the constant, exactly as the target.
 *   - the third `return 1` is spelled inside the `== -1` arm, not as a trailing fallthrough:
 *     the other spelling inverts the final `beq` into a `bne` and swaps the two tail blocks.
 */
s32 func_8002FDE8(s32 idx, s32 data) {
    /* block scope -- see the note above */
    extern s16 D_800A46D2;
    s16 r;
    s32 one;
    s32 i4;

    func_8002ED90();
    if (D_800A46A2 >= 0) {
        func_800415A8(D_800A46A2);
        D_800A46A2 = -1;
    }
    D_800A46A0 = idx | 0x4000;
    one = 1;
    D_800A46B0 = one;
    i4 = idx * 4;
    D_800A469C = *(s32 *)((u8 *)D_800652F0 + i4);
    r = func_80041A80(data, -1, D_800A469C);
    D_800A46D2 = r;
    D_800A46A2 = r;
    if (r == -1) {
        D_800A46B0 = one;
        return 1;
    }
    if (func_800419B0(r) == -1) {
        func_800415A8(D_800A46D2);
        D_800A46A2 = -1;
        D_800A46B0 = one;
        return 1;
    }
    D_800A46B0 = 0;
    return 1;
}

/* func_8002FF0C -- start playback of resource `entry` from the buffer `arg`.
 *
 * Byte-shape notes (each measured, see the S76y notes):
 *   - `i` and `idx24` are two SEPARATE `b * 24` locals: the join at the second `if`
 *     ends cse's extended block, so the target computes b*24 twice ($a0 then $s0).
 *   - `idx24 = (b * 3) << 3;` -- a top-level LSHIFT_EXPR expands INTO the variable's
 *     own pseudo, so no `move` copy survives into the join block; written `b * 24`
 *     the copy costs a sixth callee-saved register and a 0x30 frame.
 *   - `q = D_800A46CE` is a real pointer local: the target holds &D_800A46CE in $s4
 *     across the call and derives the D_800A4642 store from it (`addiu $v1,$s4,-0x96`
 *     / `addu $v1,$s0,$v1` / `sh $v0,0xA($v1)`), so the store is written off `q`.
 *   - the first zero-byte fence (cookbook S194-A, AFTER placement) keeps the
 *     D_800C532A store ahead of the two zeroing stores; the second one keeps the
 *     D_800A464C store ahead of the D_80064D4E load.
 *   - the `"memory"` clobber after the `w` store is NOT a scheduling lever: it
 *     invalidates cse's memory table so `D_800A46D2` is RE-READ for the
 *     func_800419B0 argument (`lui $a0` / `lh $a0`) instead of being folded to the
 *     sign-extension of `r`.  Without it the function is exactly 2 instructions short.
 */

#ifndef BFM_800_SHARED_H
#endif

extern Elm12 D_80064D49[];
extern u8    D_80064D4A[];
extern u8    D_80064D4E[];
extern Ent24 D_800A463C[];
extern Rsc24 D_800A4640[];
extern s16   D_800A4642[];
extern s16   D_800A4644[];
extern s16   D_800A4648[];
extern s32   D_800A464C[];
extern u8    D_800A4650[];
extern s32   D_800A46BC;
extern s16   D_800A46CC;
extern s16   D_800A46CE[];
extern s16   D_800A46D0;
extern s16   D_800A4EF6;
extern s16   D_800C5328[];
extern s16   D_800C532A[];

extern void func_80031A98(void);
extern s16  func_80041A80(s32, s32, s32);
extern s16  func_800419B0(s32);
extern s32  func_80030730(void);
extern s32  func_80030A14(void);
extern void func_800415A8(s32);

s32 func_8002FF0C(s32 a0, s32 a1) {
    /* block scope: src/800_b.c declares this symbol `extern s16 D_800A46D2[]`
     * further down the TU, and the ARRAY spelling materialises the address into
     * a register (`la`) for both the store and the re-read -- the target keeps
     * two independent %hi/%lo accesses, which only the scalar spelling emits. */
    extern s16 D_800A46D2;
    s32 b;
    s32 i;
    s32 idx24;
    s32 j12;
    s32 v1;
    s16 t;
    s16 r;
    s16 *q;
    u8  *w;
    u8  *base;
    s32 res;

    if (D_800A46CC == 0) {
        b = D_80064D49[a0].unk00;
        i = b * 24;
        v1 = *(s16 *)((u8 *)D_800A4644 + i);
        if (v1 != 0 && v1 != D_80064D4A[a0 * 12]) {
            t = *(s16 *)((u8 *)D_800A4648 + i);
            *(s16 *)((u8 *)D_800C532A + t * 4) = -1;
            __asm__ __volatile__("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B tus9)
            *(s16 *)((u8 *)D_800A4644 + i) = 0;
            *(s16 *)((u8 *)D_800A4648 + i) = 0;
        }
        idx24 = (b * 3) << 3;
        if (D_800A4650[idx24] == 0) {
            t = *(s16 *)((u8 *)D_800A4640 + idx24);
            *(s16 *)((u8 *)D_800C5328 + t * 4) = -1;
            func_80031A98();
        }
        q = D_800A46CE;
        j12 = a0 * 12;
        *q = b;
        *(s16 *)((u8 *)D_800A4640 + idx24) = a0;
        D_800A46D0 = a0;
        D_800A46BC = a1;
        *(s32 *)((u8 *)D_800A464C + idx24) = a1;
        __asm__ __volatile__("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B tus9)
        if (D_80064D4E[j12] != 0) {
            D_800A4EF6 = D_80064D4E[j12];
        }
        r = func_80041A80(a1, -1, *(s32 *)((u8 *)D_800A463C + idx24));
        D_800A46D2 = r;
        base = (u8 *)q - 0x96;
        w = idx24 + base;
        *(s16 *)(w + 0xA) = r;
        __asm__ __volatile__("" ::: "memory");  // !FAKE: barrier memory — NEEDED DIFFERS (P36 rung B tus9)
        if (r == -1 || func_800419B0(D_800A46D2) == -1) {
            D_800A4650[idx24] = 1;
            return 1;
        }
        D_800A46CC = 1;
    }
    res = 0;
    switch (D_800A46CC) {
    case 1:
        res = func_80030730();
        break;
    case 2:
        res = func_80030A14();
        break;
    }
    if (res != 0) {
        s16 *p = &D_800A46D2;
        func_800415A8(*p);
        *p = -1;
        *(s16 *)((u8 *)D_800A4642 + *(s16 *)D_800A46CE * 24) = -1;
        return 1;
    }
    return 0;
}

extern u8  D_8006AEF4;
extern s16 D_800A46CC;

s32 aF800301A4(void) __asm__("func_800301A4");
s32 aF800301A4(void) {
    u8 t;

    t = D_8006AEF4;
    D_800A46CC = 0;
    D_8006AEF4 = t & ~2;
    return 1;
}

/* Elm12 / Ent24 / Rsc24 live in src/800_shared.h, which src/800_b.c includes.  The guard makes
 * this draft compile STANDALONE (match_one adds only common.h) while emitting nothing once it is
 * spliced into the TU -- a C89 typedef redefinition is a hard gcc-2.7.2 error (cookbook §423),
 * and this `#ifndef BFM_800_SHARED_H` idiom is already the house spelling in this TU. */
#ifndef BFM_800_SHARED_H


#endif

/* Every one of these is copied verbatim from src/800_b.c's own file-scope block (~L3489-3505,
 * above the stub), so the spliced draft re-declares nothing incompatibly. */
extern Elm12 D_80064D49[];
extern u8    D_80064D4A[];
extern Ent24 D_800A463C[];
extern Rsc24 D_800A4640[];
extern s16   D_800A4642[];
extern s16   D_800A4644[];
extern s16   D_800A4648[];
extern s32   D_800A464C[];
extern u8    D_800A4650[];
extern s32   D_800A46BC;
extern s32   D_800A46C0;
extern s32   D_800A46C4;
extern s16   D_800A46CC;
extern s16   D_800A46CE[];
extern s16   D_800A46D0;
extern s16   D_800C5328[];
extern s16   D_800C532A[];
extern u8    D_8006AEF4;

/* not declared anywhere in src/800_b.c */
extern s32 (*D_8006AA14[])(void);
extern s32   SsVabOpenHeadSticky();

extern void func_800301A4(void);
extern void func_80031A98(void);
extern int  func_80037CD8(void *arg);
extern void func_800415A8(s32);

int func_800301C8(int entry, s32 a1, s32 a2) {
    /* block scope, exactly as func_8002FF0C does two functions up: src/800_b.c declares this
     * symbol `extern s16 D_800A46D2[]` FURTHER DOWN the TU (L3733), and the ARRAY spelling makes
     * cse cache the address in a callee-saved register (`la $s1`) across the func_800415A8 call
     * for both the read and the write -- the target keeps two independent %hi/%lo accesses,
     * which only the scalar spelling emits. */
    extern s16 D_800A46D2;
    s16 *p;
    s32 bs;
    s16 e;
    s32 b;
    s32 h;
    s32 k;
    s32 k2;
    s32 vab;
    u8  fl;
    s32 ret;
    s32 v;

    if (D_800A46CC == 0) {
        D_800A46C4 = 0;
        D_800A46CE[0] = D_80064D49[entry].unk00;
        D_800A46C0 = a2;
        D_800A46BC = a1;
        b = D_800A46CE[0];
        k = b * 24;
        h = *(s16 *)((u8 *)D_800A4644 + k);
        *(s32 *)((u8 *)D_800A464C + k) = a1;
        if (h != 0) {
            if (h != D_80064D4A[entry * 12]) {
                s32 n = *(s16 *)((u8 *)D_800A4648 + k);
                D_800C532A[n * 2] = -1;
                do {  // !FAKE: do-while — sched1 LOOP-note barrier, sched.c:2058-2074: keeps the zero stores after the D_800C532A store (the Rsc24 field spelling D_800A4640[b].unk04/.unk08 needs none; identical only after linking) (P36 S104 e23 minimum-lever)
                    *(s16 *)((u8 *)D_800A4644 + k) = 0;
                    *(s16 *)((u8 *)D_800A4648 + k) = 0;
                } while (0);
            }
        }
        {
            s32 m3;
            m3 = (b << 1) + b;
            k2 = m3 << 3;
        }
        if (D_800A4650[k2] == 0) {
            s32 n = *(s16 *)((u8 *)D_800A4640 + k2);
            D_800C5328[n * 2] = -1;
            func_80031A98();
            func_800415A8(*(s16 *)((u8 *)D_800A4642 + k2));
        }
        p = &D_800A46D0;
        e = entry;
        *p = e;
        *(s16 *)((u8 *)D_800A4640 + k2) = e;
        D_800A4650[k2] = 1;
        vab = SsVabOpenHeadSticky(a1, -1, *(s32 *)((u8 *)D_800A463C + k2));
        bs = (s32)p - 0x98;
        {
            s32 adr;
            adr = k2 + bs;
            D_800A46D2 = vab;
            *(s16 *)(adr + 0xA) = vab;
        }
        if ((s16)vab == -1) {
            D_800A4650[k2] = 1;
            return 1;
        }
        if (func_80037CD8((void *)func_800301A4) == 0) {
            D_800A46CC = 1;
            return 0;
        }
        fl = D_8006AEF4;
        fl |= 2;
        D_8006AEF4 = fl;
        if (fl & 1) {
            D_800A46CC = 2;
            return 0;
        }
        D_800A46CC = 3;
        return 0;
    } else {
        ret = D_8006AA14[D_800A46CC]();
        if (ret != 0) {
            v = D_800A46D2;
            if (v >= 0) {
                func_800415A8(v);
                D_800A46D2 = -1;
                *(s16 *)((u8 *)D_800A4642 + D_800A46CE[0] * 24) = -1;
            }
        }
        return ret;
    }
}

extern void func_800301A4(void);
extern s32 func_80037CD8(void *arg);
extern s16 D_800A46CC;
extern u8 D_8006AEF4;

s32 func_80030470(void) {
    s16 *p;

    if (func_80037CD8((void *) func_800301A4) != 0) {
        p = &D_800A46CC;
        *p += 1;
        D_8006AEF4 |= 2;
    }
    return 0;
}

extern u8  D_8006AEF4;
extern s16 D_800A46CC;
extern s32 func_8003C4F0(s32);

s32 func_800304C8(void) {
    s16 *p;

    if (D_8006AEF4 & 1) {
        if (func_8003C4F0(0) != 0) {
            D_8006AEF4 &= 0xFE;
        }
    } else {
        p = &D_800A46CC;
        (*p)++;
    }
    return 0;
}

extern s16 D_800A46CC;
extern u8  D_800A4650[];
extern s16 D_800A4642[];
extern s16 D_800A46CE[];
extern s32 D_800A46C0;
extern s32 D_800A46C4;

extern s16 func_80042154();

s32 func_80030538(void) {
    s32 idx;
    s16 ret;

    idx = D_800A46CE[0];
    ret = func_80042154(D_800A46C0 + D_800A46C4, 0x8000, *(s16 *)((u8 *)D_800A4642 + idx * 24));
    switch (ret) {
    case -2: {
        s16 t2 = D_800A46CC + 1;
        s32 t1 = D_800A46C4 + 0x8000;
        D_800A46C4 = t1;
        D_800A46CC = t2;
        goto L_zero;
    }
    case -1:
        D_800A4650[idx * 24] = 1;
        D_800A46CC = D_800A46CC + 2;
        return 1;
    default: {
        s16 *p = &D_800A46CC;
        *p = *p + 2;
        goto L_zero;
    }
    }
L_zero:
    return 0;
}

extern s32 D_800A46C0;
extern s32 D_800A46C4;
extern s16 D_800A46CC;
extern s16 D_800A46CE[];
extern s16 D_800A4642[];
extern u8  D_800A4650[];

extern s16 func_80042374(s32);
extern s16 func_80042154();

s32 func_80030634(void) {
    s32 t;
    s32 k;
    s16 r;
    s16 *pcc;

    if (func_80042374(0) != 0) {
        t = D_800A46CE[0] * 3;
        k = t << 3;
        r = func_80042154((u8 *)(D_800A46C0 + D_800A46C4), 0x8000,
                           *(s16 *)((u8 *)D_800A4642 + k));
        switch (r) {
        case -2:
            D_800A46C4 = D_800A46C4 + 0x8000;
            break;
        case -1:
            D_800A4650[k] = 1;
            D_800A46CC++;
            break;
        default:
            pcc = &D_800A46CC;
            (*pcc)++;
            break;
        }
    }
    return 0;
}





typedef struct {
    u8  unk00[4];
    u8  unk04;
    u8  unk05[11];
    u16 unk10;
    u16 unk12;
    u8  unk14[2];
    s16 unk16;
    u8  unk18[8];
} Blk28;                       /* 0x20 */

extern u8    D_8006AEF4;
extern s16   D_800A46CC;
extern s16   D_800A46CE[];
extern s16   D_800A46D2[];
extern Rsc24 D_800A4640[];
extern A12   D_80064D44[];
extern s32   D_80065504[];
extern B12 *D_8006A970[];
extern s32   D_800760F0;
extern s32   D_800760F4;
extern s16   D_800C5328[];
extern s16   D_800C532A[];

extern s16  func_80042374(s32);
extern void func_80037D74(void);
extern s16  func_8003F144(s32, s32, s32, C24 *);
extern s32  func_8003F380(s32, s32);

s32 func_80030730(void) {
    Blk28 sp10;
    A12 *e;
    B12 *p;
    u8 *q;
    s16 *pd;
    s16 *pcc;
    s32 n;
    s32 n0;
    s32 k;
    s32 i;
    s32 res;

    if (func_80042374(0) == 0) {
        return 0;
    }
    D_8006AEF4 &= 0xFC;
    func_80037D74();

    k = D_800A46CE[0] * 24;
    D_800760F0 = 0;
    e = &D_80064D44[D_800A46CE[1]];
    n0 = e->pad04[0];
    D_800760F4 = n0;
    if (n0 == 0) {
        *(u8 *)((u8 *)D_800A4640 + k + 0x10) = 0;
        D_800A46CC = 0;
        return 1;
    }
    q = e->unk00;
    if (D_80065504[D_800A46CE[0]] < n0) {
        D_800760F4 = D_80065504[D_800A46CE[0]];
    }
    p = D_8006A970[D_800A46CE[0]];
    n = 10;
    if (D_800760F4 < 11) {
        if (e->unk06 != 0) {
            *(s16 *)((u8 *)D_800A4640 + k + 0x06) = e->unk07;
            D_800A4640[D_800A46CE[0]].unk04 = e->unk06;
            D_800A4640[D_800A46CE[0]].unk08 = e->unk08;
            D_800C532A[e->unk08 * 2] = D_800A46CE[0];
        }
        n = D_800760F4;
        D_800760F4 = 0;
        D_800C5328[D_800A46CE[1] * 2] = D_800A46CE[0];
    } else {
        D_800760F4 -= 10;
    }

    for (i = 0; i < n; i++, q += 2, p++) {
        pd = D_800A46D2;
        if (func_8003F144(*pd, q[0], q[1], (C24 *)&sp10) == 0) {
            res = func_8003F380(*pd, sp10.unk16);
            if (res >= 0) {
                p->unk0A = 1;
                p->unk04 = sp10.unk04 << 8;
                p->unk00 = res;
                p->unk06 = sp10.unk10;
                p->unk08 = sp10.unk12;
            }
        }
    }

    if (D_800760F4 == 0) {
        D_800A4640[D_800A46CE[0]].unk10 = 0;
        D_800A46CC = 0;
        return 1;
    }
    pcc = &D_800A46CC;
    D_800760F0 = D_800760F0 + 10;
    (*pcc)++;
    return 0;
}


/* 0x0C stride record at D_80064D44 (D_80064D4A == this + 6, cf. src/800.c Rsc12) */

/* 0x0C stride record pointed at by D_8006A970[] */

/* 0x18 scratch filled by func_8003F144 */

extern s16 D_800A46CC;
extern s16 D_800A46CE[];
extern s16 D_800A46D0;
extern s16 D_800A46D2[];

extern s16 D_800A4644[];
extern s16 D_800A4646[];
extern s16 D_800A4648[];
extern u8  D_800A4650[];

extern s16 D_800C5328[];
extern s16 D_800C532A[];

extern A12  D_80064D44[];
extern B12 *D_8006A970[];

extern s32 D_800760F0;
extern s32 D_800760F4;

extern s16 func_80042374(s32);
extern s16 func_8003F144(s32, s32, s32, C24 *);
extern s32 func_8003F380(s32, s32);

s32 func_80030A14(void) {
    C24 sp10;
    A12 *e;
    u8 *p;
    B12 *q;
    s32 count;
    s32 i;
    s32 r;
    s32 t;

    if (func_80042374(0) == 0) {
        return 0;
    }

    e = &D_80064D44[D_800A46D0];
    p = e->unk00 + D_800760F0 * 2;
    q = &D_8006A970[D_800A46CE[0]][D_800760F0];
    t = D_800A46CE[0] * 24;

    if (D_800760F4 < 11) {
        if (e->unk06 != 0) {
            *(s16 *)((u8 *)D_800A4646 + t) = e->unk07;
            D_800A4644[D_800A46CE[0] * 12] = e->unk06;
            D_800A4648[D_800A46CE[0] * 12] = e->unk08;
            D_800C532A[e->unk08 * 2] = D_800A46CE[0];
        }
        count = D_800760F4;
        D_800760F4 = 0;
        D_800C5328[D_800A46D0 * 2] = D_800A46CE[0];
    } else {
        count = 10;
        D_800760F4 -= 10;
    }

    for (i = 0; i < count; i++, p += 2, q++) {
        if (func_8003F144(D_800A46D2[0], p[0], p[1], &sp10) == 0) {
            r = func_8003F380(D_800A46D2[0], sp10.unk16);
            if (r >= 0) {
                q->unk0A = 1;
                q->unk04 = sp10.unk04 << 8;
                q->unk00 = r;
                q->unk06 = sp10.unk10;
                q->unk08 = sp10.unk12;
            }
        }
    }

    if (D_800760F4 == 0) {
        D_800A4650[D_800A46CE[0] * 24] = 0;
        D_800A46CC = 0;
        return 1;
    }

    D_800760F0 += 10;
    return 0;
}

/* TU decls (src/800.c): `extern u8 D_800A4988[];` already exists above this
 * function's INCLUDE_ASM line (src/800.c:16205), and `typedef struct Ent30D80
 * {...} Ent30D80;` is defined at the top of the file (src/800.c:7-19) --
 * copied locally here so this draft compiles standalone.
 *
 * func_80030D80's FIRST declaration in the TU is this function's own extern
 * (nothing declares it earlier in src/800.c), and it must be byte-identical
 * to its later definition at src/800.c:18516: `void func_80030D80(Ent30D80
 * *arg0, s16 arg1)`. The original draft declared it `void func_80030D80(void
 * *, s16)`, which conflicts with that definition under real cc1
 * (t.c:18285: conflicting types for `func_80030D80'). Fix: adopt the TU's
 * Ent30D80 * parameter type verbatim and cast at the single call site
 * (bestp is still plain u8 * everywhere else in this function).
 */

extern u8 D_800A4988[];

extern void func_80030D80(Ent30D80 *arg0, s16 arg1);

s32 func_80030CA4(u16 arg0)
{
    u8 *base;
    u8 *p;
    s32 i;
    s32 one;
    s32 besti;
    u8 *bestp;
    u16 best;
    u8 first;

    (void)&besti;
    (void)&bestp;
    (void)&best;
    (void)&first;

    base = D_800A4988;
    i = 0;
    one = 1;
    p = base + 8;
    first = 0;

    for (; i < 8; i++, p += 0x54, base += 0x54) {
        if (p[0x46] == 0) {
            return i + 1;
        }
        if (first == 0) {
            best = *(u16 *)p;
            first = (u8)one;
            besti = i;
            bestp = base;
        } else if (*(u16 *)p < best) {
            best = *(u16 *)p;
            besti = i;
            bestp = base;
        }
    }

    if ((u16)arg0 < best) {
        return 0;
    }

    func_80030D80((Ent30D80 *)bestp, 1);
    *(u8 *)(base + 0x4E) = 0;
    besti = besti + 1;
    return besti;
}



typedef struct Blk48_30D80 {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ u8 pad04[0x3D];
    /* 0x41 */ u8 unk41;
    /* 0x42 */ u8 pad42[6];
} Blk48_30D80;

extern s8 D_800A4F17;
extern s32 D_800C7D20;
extern s32 D_80073140[];
extern Blk48_30D80 D_800A4C2C[];

extern void func_8002EFF8(s32 a0, s32 a1);
extern void func_80031988(Ent30D80 *arg0);

void func_80030D80(Ent30D80 *arg0, s16 arg1) {
    u8 old;
    u8 flag;

    old = *(u8 *)&D_800A4F17;
    *(u8 *)&D_800A4F17 = 1;

    if (arg0->unk00 != 0) {
        flag = 1;
        arg0->unk00 = 0;
    } else if (arg0->unk4E >= 2 && (D_800C7D20 & D_80073140[arg0->unk0A])) {
        D_800A4C2C[arg0->unk51].unk41 = 1;
        D_800A4C2C[arg0->unk51].unk00 &= 0xFFF9FFFF;
        flag = 1;
        func_8002EFF8(0, D_80073140[arg0->unk0A]);
    } else {
        flag = 0;
        if (arg1 != 0) {
            arg0->unk50 = 1;
            D_800A4C2C[arg0->unk51].unk41 = 1;
            D_800A4C2C[arg0->unk51].unk00 &= 0xFFF9FFFF;
            func_8002EFF8(0, D_80073140[arg0->unk0A]);
        } else {
            s32 mask = D_80073140[arg0->unk0A];
            arg0->unk50 = 0;
            func_8002EFF8(0, mask);
            func_80031988(arg0);
        }
    }

    if (arg0->unk40 != 0) {
        arg0->unk40(arg0->unk51, arg0->unk44);
    }
    arg0->unk40 = 0;
    if (flag) {
        arg0->unk4E = 0;
    }

    *(u8 *)&D_800A4F17 = old;
}

#include "common.h"

/* func_80030F80 -- MATCH, 343/343 (Fable escalation S69e1; was NEAR closeness 3).
 * All j destinations, jal order, and HI16/LO16 symbol order verified with
 * objdump -r against the .s (law 1c: match_one masks relocs).
 *
 * TU decls already in src/800.c (do NOT duplicate at bank time):
 *   extern u8 D_800A4988[]; extern u8 D_800A4F19; extern s32 D_80073140[];
 *   extern u16 D_8006AA30[]; extern const u16 D_8007319E[]; extern u16 D_8007321E;
 *   extern u8 D_800A4C6D[]; extern s32 D_800C7D2C;
 *   extern void func_8002EFF8(s32 a0, s32 a1);  (file scope, src/800.c:18923)
 *   extern void func_80031988(Ent30D80 *arg0);  (file scope, src/800.c:18924)
 *   `typedef struct Obj {...} Obj;` is defined AFTER this function (src/800.c:18968)
 *   and func_800314DC is defined at :19003 as `void func_800314DC(Obj *p)`, so this
 *   draft forward-declares the TAG at file scope (`struct Obj;`) and prototypes
 *   `func_800314DC(struct Obj *)` -- compatible with the later definition (Sec 376/378).
 *   Same trick for `struct Ent30D80` (complete at src/800.c:11).
 *   NEW to the TU: `extern const u16 D_800731A0[];` (real dlabel, asm/data/6324C.data.s:699).
 *
 * THE LEVERS (each byte-load-bearing; measured 316 -> 3):
 *  1. ONE ANCHOR SYMBOL. Every address in this function is spelled as an offset from
 *     D_800A4988, so cse.c's use_related_value/get_related_value can express each one
 *     as `addiu $reg,$s6,K` off the FIRST materialised address. That is why the target
 *     shows `lui $s6,%hi(D_800A4EFE)` (= D_800A4988+0x576) with $s2/$s7/$s0 derived from
 *     it, but keeps D_80073140 / D_800731A0 / D_8007319E as full lui/addiu pairs:
 *     get_related_value only relates `(const (plus SYMBOL int))` to the SAME symbol, never
 *     two different symbols. Spelling D_800A4EFE / D_800A4EFA / D_800A4C28 / D_800A4F19 as
 *     their own externs costs +1 insn each and loses the whole derived chain.
 *  2. POINTER LOCALS, NOT ARRAY SUBSCRIPTS, for the loop-invariant bases (sv/w/q/r/tbl).
 *     `D_800A4EFE[u]` compiles to the 3-insn split address (lui $at; addu $at,$at,$u;
 *     lbu %lo(sym)($at)); a pointer local puts the base in a pseudo and gives the target's
 *     2-insn `addu $v0,$s6,$a0; lbu $v1,0($v0)`.
 *  3. THE PRE-LOOP STATEMENT ORDER *IS* THE PREHEADER ORDER (sv, p, i=0, tbl, w, q, r):
 *     sched1 keeps ties in LUID order, so this reproduces $s6,$s2,$s5,$s4,$s7,$fp exactly.
 *     `r = D_8007319E` is the 7th and last invariant: global.c runs out of callee-saved
 *     registers, local-alloc's REG_EQUIV note survives, and reload REMATERIALISES it inline
 *     as `lui $t0/addiu $t0` -- exactly the target's un-hoisted pair at 0x80031344.
 *  4. ONE `w` POINTER SERVES THREE THINGS (master volume `*(s16*)w`, the stereo flag
 *     `w[0x1F]`, and the voice-slot base `(s32)w - 0x2D2`), which is what makes it worth a
 *     callee-saved register ($s7) and what produces `addiu $v1,$s7,-0x2D2` in-loop.
 *     `vb` must be s32 (not u8*) so `k + vb` keeps the target's `addu $a0,$s3,$v1`
 *     operand order -- pointer arithmetic gets canonicalised to pointer-first.
 *  5. `i * 0x48` (a GIV), not a `k` biv: a biv's `k = 0` is pre-loop code and lands BEFORE
 *     the address-giv init; as a giv both inits are emitted by strength_reduce and come out
 *     in the target's `addiu $s0,$s6,-0x56C` / `addu $s3,$zero,$zero` order.
 *  6. ONE `p` BIV WITH BYTE OFFSETS. Two source pointers (base and base+0xA) make loop.c
 *     invent a third giv at +0x40; one biv + `p[K]` lets combine_givs settle on the +0xA
 *     group ($s0) while the biv itself ($s2) keeps the offset-0 loads and the call args.
 *  7. `m = (m * X) >> 7;` as ONE expression (not `m = m * X; m = m >> 7;`): the product
 *     needs its own pseudo to get the target's `mflo $t0` / `srl $a1,$t0,7` pair.
 *  8. `mask = tbl[...]; p[0x50] = 0; func_8002EFF8(0, mask);` at 0x80031400 -- with the
 *     store AFTER the loads it can no longer fill the lhu's load-delay slot and dbr takes it
 *     for the jal's. At `case 3` the same rewrite instead lets cse reuse the switch's own
 *     `lhu $a0` (-2 insns), so that site keeps `p[0x50] = 0;` FIRST: the store's varying
 *     address makes cse invalidate_memory and forces the target's reload.
 *  9. The switch is a real `switch` on cases 3 / 0 / 2 IN THAT SOURCE ORDER with 3 falling
 *     through into 0 -- expand_end_case reorder_insns puts the balanced compare tree
 *     (beq 2 / slti 3 / beqz 0 / bne 3) ahead of the bodies, which is the target's layout.
 * 10. `flag = 1;` sits OUTSIDE the inner `if` in the 0x4C and 0x37&2 blocks (its constant
 *     is what `sb $s1,0x46($s0)` and `D_800A4C6D[k] = 1` reuse) but INSIDE the 0x4F one --
 *     that is exactly which branches get the `addiu $s1,$zero,1` delay slot and which a nop.
 * 11. `if ((s16)h <= 0)` on the u16 0x4A field (sll 16 + bgtz), and the 0x1C sign test
 *     written `>= 0` with the ADD arm first, so the target's `bltz` picks the sub arm.
 *
 * 12. THE DISPATCH-BLOCK MEMORY CLOBBER (closed the old case-3 residual, 3 -> 0).
 *     The target needs case 3's u16 index RELOADED (cse invalidation) while the sb
 *     stays AFTER the lw (mask idiom order), and needs case 2 to keep FOLDING the
 *     dispatch-loaded index into its call arg. Ruled out by reading the pinned gcc:
 *      - volatile-cast index load: forces the reload but loop.c:339
 *        init_recog_no_volatile makes every DEST_ADDR giv rewrite of a volatile mem
 *        fail recog -- the address stays biv-based (`lhu 10($s2)`, not `0($s0)`).
 *        A volatile mem can NEVER join a giv group. (find_mem_givs does record it.)
 *      - asm clobber at the case-3 head: reload+giv fine, but reorg.c stop_search_p
 *        halts fill_slots_from_thread at ANY asm insn (asm_noperands>=0), so the
 *        `addu $a0,$zero,$zero` never hoists into the bne's delay slot (+1 len).
 *     THE FIX (all three pieces load-bearing):
 *        idx = *(u16 *)(p + 0xA);          <- named local; case 2 passes idx (the
 *        dsp = sv[idx];                       fold, done by hand; matches the target's
 *        __asm__("" : : : "memory");          $a0 live range).  dsp MUST be s32 (u8
 *        switch (dsp) { ... }                 costs an `andi 0xff`).
 *     The NON-volatile clobber invalidates cse's memory table at zero bytes, sits in
 *     the DISPATCH block (outside every case's delay-slot thread), and goes AFTER the
 *     lbu (between lhu and its first use it would eat the load-delay nop at final).
 *     Case 3 then re-reads memory -> real reload; mask idiom keeps the sb by the jal.
 * 13. THE q/r HOIST FLIP: the two new pseudos flipped the razor-thin global-alloc tie
 *     between the 6th/7th pre-loop invariants -- $fp took r and q rematerialised,
 *     INVISIBLE under match_one (HI16/LO16 masked; shapes shift only at the remat
 *     site, seen as a bogus 7-row 'schedule' diff at the q/r lookups). Caught with
 *     objdump -r. Swapping the init order (r 6th, q 7th) flips it back. Lever 3's
 *     preheader-order law still holds: the emitted preheader shows only the WINNERS.
 */

struct Obj;
struct Ent30D80;

extern u8  D_800A4988[];
extern u8  D_800A4F19;
extern s32 D_80073140[];
extern u16 D_8006AA30[];
extern const u16 D_8007319E[];
extern const u16 D_800731A0[];
extern u16 D_8007321E;
extern u8  D_800A4C6D[];
extern s32 D_800C7D2C;

extern void func_8002EFF8(s32 a0, s32 a1);
extern void func_8003D3B4(s32, s32);
extern void func_800314DC(struct Obj *);
extern void func_800316F8(s32);   /* §376: the definition takes s32; cast at the use site */
extern void func_80031988(struct Ent30D80 *);

typedef struct VoiceF80 {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ u8  pad0C[0x34];
    /* 0x40 */ s32 unk40;
    /* 0x44 */ u8  unk44;
    /* 0x45 */ u8  pad45[3];
} VoiceF80; /* 0x48 */

void func_80030F80(void)
{
    u8 *p;
    u8 *sv;
    u8 *w;
    const u16 *q;
    const u16 *r;
    s32 *tbl;
    s32 vb;
    s32 mask;
    VoiceF80 *e;
    u32 m;
    u32 v;
    s16 n;
    s16 t;
    u8 flag;
    u8 st;
    s32 dsp;
    u16 idx;
    u16 h;
    s32 i;

    sv = D_800A4988 + 0x576;
    p = D_800A4988;
    i = 0;
    tbl = D_80073140;
    w = D_800A4988 + 0x572;
    r = D_8007319E;
    q = D_800731A0;
    for (; i < 8; i++, p += 0x54) {
        flag = 0;
        p[0x4E] &= 0x7F;
        if (p[0x4E] != 0) {
            *(s32 *)(p + 0x4) += 1;
            if (*(s32 *)p != 0) {
                *(s32 *)p -= 1;
                if (*(s32 *)p == 0) {
                    func_8002EFF8(1, tbl[*(u16 *)(p + 0xA)]);
                    func_800316F8((s32)p);
                }
            } else {
                if (p[0x4E] >= 2) {
                    p[0x4E] -= 1;
                } else {
                    idx = *(u16 *)(p + 0xA);
                    dsp = sv[idx];
                    __asm__("" : : : "memory");  // !FAKE: barrier memory — NEEDED DIFFERS (P36 rung B tus9)
                    switch (dsp) {
                    case 3:
                        mask = tbl[*(u16 *)(p + 0xA)];
                        p[0x50] = 0;
                        func_8002EFF8(0, mask);
                        /* fallthrough */
                    case 0:
                        p[0x4E] = 0;
                        if (*(s32 *)(p + 0x40) != 0) {
                            (*(void (**)(s32, s32))(p + 0x40))(p[0x51], *(s32 *)(p + 0x44));
                        }
                        *(s32 *)(p + 0x40) = 0;
                        break;
                    case 2:
                        if (p[0x50] != 0) {
                            func_8003D3B4(idx, 1);
                            p[0x50] = 0;
                        }
                        break;
                    }
                }
                if (p[0x4C] != 0) {
                    h = *(u16 *)(p + 0x4A) - 0x220;
                    *(u16 *)(p + 0x4A) = h;
                    flag = 1;
                    if ((s16)h <= 0) {
                        *(u16 *)(p + 0x4A) = 0;
                        p[0x4C] = 0;
                        p[0x50] = 1;
                        D_800A4C6D[i * 0x48] = 1;
                        func_8002EFF8(0, tbl[*(u16 *)(p + 0xA)]);
                    }
                }
                if (p[0x4F] != 0) {
                    flag = 1;
                    p[0x4F] = 0;
                }
                if (p[0x37] & 2) {
                    if (*(s32 *)(p + 0x1C) >= 0) {
                        *(s32 *)(p + 0x18) += *(u16 *)(p + 0x32);
                        if (*(s32 *)(p + 0x18) >= *(s32 *)(p + 0x1C)) {
                            *(s32 *)(p + 0x18) = *(s32 *)(p + 0x1C);
                            p[0x37] &= 0xFD;
                        }
                    } else {
                        *(s32 *)(p + 0x18) -= *(u16 *)(p + 0x32);
                        if (*(s32 *)(p + 0x18) <= *(s32 *)(p + 0x1C)) {
                            *(s32 *)(p + 0x18) = *(s32 *)(p + 0x1C);
                            p[0x37] &= 0xFD;
                        }
                    }
                    flag = 1;
                }
                if ((D_800A4F19 != 0 && p[0x53] != 0) || flag) {
                    n = p[0x35];
                    if (n != 0) {
                        t = n + (*(s32 *)(p + 0x18) >> 8);
                        n = t;
                        if (p[0x53] != 0) {
                            t = p[0x53] + t;
                            if (t < 0x42) {
                                n = 1;
                            } else {
                                t -= 0x40;
                                n = t;
                                if (t >= 0x80) {
                                    n = 0x7F;
                                }
                            }
                        }
                    }
                    if (flag || n != p[0x52]) {
                        m = D_8006AA30[p[0x34]];
                        m = (m * *(s16 *)w) >> 7;
                        m = (m * *(s16 *)(p + 0x48)) >> 7;
                        if (flag) {
                            m = (m * ((s16)*(u16 *)(p + 0x4A) >> 7)) >> 8;
                        }
                        vb = (s32)w - 0x2D2;
                        e = (VoiceF80 *)(i * 0x48 + vb);
                        e->unk00 = tbl[*(u16 *)(p + 0xA)];
                        if (n != 0) {
                            if (w[0x1F] != 0) {
                                v = (m * q[0x7F - n]) >> 14;
                                e->unk08 = v;
                                v = (m * r[n]) >> 14;
                                e->unk0A = v;
                            } else {
                                v = (m * D_8007321E) >> 14;
                                e->unk0A = v;
                                e->unk08 = v;
                            }
                        } else {
                            v = m;
                            e->unk0A = v;
                            e->unk08 = v;
                        }
                        e->unk40 = *(u16 *)(p + 0xA);
                        if (e->unk44 != 0) {
                            e->unk04 |= 3;
                        } else {
                            e->unk44 = 1;
                            e->unk04 = 3;
                        }
                        p[0x52] = n;
                    }
                }
                func_800314DC((struct Obj *)p);
                h = *(u16 *)(p + 0x12);
                if (h != 0) {
                    h -= 1;
                    *(u16 *)(p + 0x12) = h;
                    if (h == 0) {
                        func_80031988((struct Ent30D80 *)p);
                        mask = tbl[*(u16 *)(p + 0xA)];
                        p[0x50] = 0;
                        func_8002EFF8(0, mask);
                        if (*(s32 *)(p + 0x40) != 0) {
                            (*(void (**)(s32, s32))(p + 0x40))(p[0x51], *(s32 *)(p + 0x44));
                        }
                        *(s32 *)(p + 0x40) = 0;
                    }
                }
            }
        } else {
            st = sv[*(u16 *)(p + 0xA)];
            if (st == 0 || st == 3) {
                D_800C7D2C &= ~tbl[*(u16 *)(p + 0xA)];
            }
        }
    }
}



typedef struct Obj {
    /* 0x00 */ u8 unk00[0xA];
    /* 0x0A */ u16 unk0A;
    /* 0x0C */ u16 unk0C;
    /* 0x0E */ u16 unk0E;
    /* 0x10 */ u16 unk10;
    /* 0x12 */ u8 unk12[0x12];
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ u16 unk30;
    /* 0x32 */ u8 unk32[0x5];
    /* 0x37 */ u8 unk37;
    /* 0x38 */ u8 unk38;
    /* 0x39 */ u8 unk39;
    /* 0x3A */ s16 unk3A;
    /* 0x3C */ s16 unk3C;
    /* 0x3E */ u8 unk3E[0x13];
    /* 0x51 */ u8 unk51;
    /* 0x52 */ u8 unk52[2];
} Obj;


/* 0x0C stride record pointed at by D_8006A970[] -- must match src/800.c's B12
   (same name, same offsets/widths) since the destination TU already declares
   this struct and symbol. */

extern Slot D_800A4C28[];
extern s32 D_80073140[];
extern B12 *D_8006A970[];
extern u16 D_8006AB30[];
extern u16 D_8006AB32[];

void func_800314DC(Obj *p) {
    Slot *e;
    s32 *r;
    u16 h;
    u32 t;
    u32 d;
    u32 q;

    if (!(p->unk37 & 1)) {
        return;
    }

    if (p->unk30 != 0) {
        p->unk30--;
        return;
    }

    if (p->unk2C < 0) {
        p->unk24 += p->unk2C;
        if (p->unk24 <= p->unk28) {
            p->unk24 = p->unk28;
            p->unk37 &= 0xFE;
        }
    } else {
        p->unk24 += p->unk2C;
        if (p->unk24 >= p->unk28) {
            p->unk24 = p->unk28;
            p->unk37 &= 0xFE;
        }
    }

    if (!(p->unk37 & 1) && p->unk38 != 0) {
        if (p->unk24 != p->unk3C) {
            p->unk28 = p->unk3C;
            if (p->unk3C < p->unk24) {
                p->unk2C = -p->unk3A;
            } else {
                p->unk2C = p->unk3A;
            }
        }
        p->unk38 = 0;
        p->unk37 |= 1;
    }

    e = &D_800A4C28[p->unk51];
    /* two statements: the pointer's uses all fold into one address, but reload still gives it the
       8-byte stack slot the target's frame carries (S103 c35 / S104 d25, reload1.c:2331-2352) */
    r = D_80073140;
    r += p->unk0A;
    e->unk00 = *r;
    h = D_8006A970[p->unk10][p->unk0C].unk04;
    t = h;
    t = (t & 0xFF00) + ((s8)t * 2);
    e->unk18 = h;
    t -= 0x3C00;
    d = p->unk24;
    d -= t;
    if (d >= 0x5300) {
        e->unk14 = 0x3FFF;
    } else {
        q = D_8006AB30[d >> 8] * (0x100 - (d & 0xFF));
        q += D_8006AB32[d >> 8] * (d & 0xFF);
        e->unk14 = q >> 8;
    }
    e->unk40 = p->unk0A;
    if (e->unk44 != 0) {
        e->unk04 |= 0x10;
    } else {
        e->unk44 = 1;
        e->unk04 = 0x10;
    }
}

void func_800316F8(s32 arg0)
{
    s32 base;
    u16 *ptr;
    u16 speed;
    u16 delta;
    s32 tmp;
    s32 tmp1;

    base = arg0;
    delta = 0;
    ptr = *(u16 **)(base + 0x14);
    speed = 0;
    *(u8 *)(base + 0x37) = 0;
    *(u32 *)(base + 0x18) = 0;
    *(u32 *)(base + 0x20) = *(u32 *)(base + 0x24);
    if (ptr == NULL) {
        return;
    }
    switch (*ptr) {
    case 1:
        speed = ptr[1];
        delta = ptr[2];
        *(u16 *)(base + 0x30) = 0;
        *(u8 *)(base + 0x38) = 1;
        *(u16 *)(base + 0x3A) = ptr[3];
        *(u16 *)(base + 0x3C) = ptr[4];
        *(u16 *)(base + 0x12) = ptr[7];
        break;
    case 9:
        speed = ptr[1];
        tmp1 = ptr[2];
        *(u16 *)(base + 0x30) = 0;
        *(u8 *)(base + 0x38) = 1;
        *(u16 *)(base + 0x3A) = ptr[3];
        *(u16 *)(base + 0x3C) = ptr[4] + *(u32 *)(base + 0x20);
        delta = tmp1 + *(u32 *)(base + 0x20);
        *(u16 *)(base + 0x12) = ptr[7];
        break;
    case 6:
        speed = ptr[2];
        delta = ptr[3];
        *(u16 *)(base + 0x30) = 0;
        *(u8 *)(base + 0x38) = 1;
        *(u16 *)(base + 0x3A) = ptr[4];
        *(u16 *)(base + 0x3C) = ptr[5];
        *(u16 *)(base + 0x12) = ptr[8];
        goto L188c;
    case 10:
        speed = ptr[2];
        tmp = ptr[3];
        *(u16 *)(base + 0x30) = 0;
        *(u8 *)(base + 0x38) = 1;
        *(u16 *)(base + 0x3A) = ptr[4];
        *(u16 *)(base + 0x3C) = ptr[5] + *(u32 *)(base + 0x20);
        *(u16 *)(base + 0x12) = ptr[8];
        goto L18ac;
    case 0:
        *(u8 *)(base + 0x38) = 0;
        speed = ptr[1];
        delta = ptr[2];
        *(u16 *)(base + 0x12) = ptr[5];
        *(u16 *)(base + 0x30) = 0;
        break;
    case 7:
        *(u8 *)(base + 0x38) = 0;
        speed = ptr[1];
        delta = ptr[2] + *(u32 *)(base + 0x20);
        *(u16 *)(base + 0x12) = ptr[5];
        *(u16 *)(base + 0x30) = 0;
        break;
    case 5:
        *(u8 *)(base + 0x38) = 0;
        speed = ptr[2];
        delta = ptr[3];
        *(u16 *)(base + 0x12) = ptr[6];
    L188c:
        *(u16 *)(base + 0x30) = ptr[1];
        break;
    case 8:
        *(u8 *)(base + 0x38) = 0;
        speed = ptr[2];
        tmp = ptr[3];
        *(u16 *)(base + 0x12) = ptr[6];
    L18ac:
        delta = tmp + *(u32 *)(base + 0x20);
        *(u16 *)(base + 0x30) = ptr[1];
        break;
    case 2:
        *(u8 *)(base + 0x38) = 0;
        goto L18f4;
    case 3:
        *(u8 *)(base + 0x37) |= 2;
        *(u32 *)(base + 0x1C) = (s32)(s16)ptr[2] << 8;
        *(u16 *)(base + 0x32) = ptr[3];
        *(u8 *)(base + 0x38) = 0;
    L18f4:
        *(u16 *)(base + 0x12) = ptr[1];
        *(u16 *)(base + 0x30) = 0;
        return;
    case 4:
        *(u8 *)(base + 0x37) |= 2;
        *(u32 *)(base + 0x1C) = (s32)(s16)ptr[1] << 8;
        *(u16 *)(base + 0x32) = ptr[2];
        *(u8 *)(base + 0x38) = 0;
        *(u16 *)(base + 0x30) = 0;
        return;
    }
    if (speed == 0) {
        return;
    }
    if (*(s32 *)(base + 0x24) == delta) {
        return;
    }
    *(u32 *)(base + 0x28) = delta;
    *(u8 *)(base + 0x37) |= 1;
    if (delta < *(s32 *)(base + 0x24)) {
        *(u32 *)(base + 0x2C) = -speed;
    } else {
        *(u32 *)(base + 0x2C) = speed;
    }
}


void func_80031988(Ent30D80 *arg0) {
    u16 *rec;
    s32 n;
    s32 base;

    rec = *(u16 **)((u8 *)arg0 + 0x14);
    if (rec != NULL) {
        n = *rec;
        switch (n) {
        case 0:
            n = rec[3];
            rec = (u16 *)rec[4];
            break;
        case 7:
            base = *(s32 *)((u8 *)arg0 + 0x20);
            n = rec[3] + base;
            rec = (u16 *)rec[4];
            break;
        case 5:
            n = rec[4];
            rec = (u16 *)rec[5];
            break;
        case 8:
            base = *(s32 *)((u8 *)arg0 + 0x20);
            n = rec[4] + base;
            rec = (u16 *)rec[5];
            break;
        case 1:
            n = rec[5];
            rec = (u16 *)rec[6];
            break;
        case 9:
            base = *(s32 *)((u8 *)arg0 + 0x20);
            n = rec[5] + base;
            rec = (u16 *)rec[6];
            break;
        case 6:
            n = rec[6];
            rec = (u16 *)rec[7];
            break;
        case 10:
            base = *(s32 *)((u8 *)arg0 + 0x20);
            n = rec[6] + base;
            rec = (u16 *)rec[7];
            break;
        default:
            return;
        }
        if (*(s32 *)((u8 *)arg0 + 0x24) != (n & 0xFFFF)) {
            *(u8 *)((u8 *)arg0 + 0x38) = 0;
            *(s32 *)((u8 *)arg0 + 0x28) = n & 0xFFFF;
            *(u8 *)((u8 *)arg0 + 0x37) |= 1;
            if (*(s32 *)((u8 *)arg0 + 0x24) > (n & 0xFFFF)) {
                *(s32 *)((u8 *)arg0 + 0x2C) = -(s32)rec;
            } else {
                *(s32 *)((u8 *)arg0 + 0x2C) = (s32)rec;
            }
        }
    }
}

/* TU decls (src/800.c): `typedef struct Ent30D80 { ... } Ent30D80;`
 * already exists above this function's INCLUDE_ASM line — reproduced here
 * verbatim (field-for-field identical) for standalone compilation; do not
 * duplicate in the TU when banking (see func_8003324C's banking note). */

extern s16 D_800C5328[];
extern s16 D_800C532A[];
extern u8  D_800A4988[];
extern u8  D_800A46B0;
extern void func_80030D80(Ent30D80 *arg0, s16 arg1);

void func_80031A98(void)
{
    u8 *p;
    s32 i;
    s32 w;
    u16 h;

    for (p = D_800A4988, i = 0; i < 8; i++, p += 0x54) {
        if (p[0x4E] != 0) {
            if (p[0x36] != 0) {
                w = *(s16 *)((u8 *)D_800C532A + (*(u16 *)(p + 0xE) << 2));
                goto chk;
            }
            h = *(u16 *)(p + 0xE);
            if (h & 0x80) {
                if (D_800A46B0 != 0)
                    func_80030D80((Ent30D80 *)p, 1);
            } else {
                w = *(s16 *)((u8 *)D_800C5328 + (h << 2));
            chk:
                if (w >= 0)
                    continue;
                func_80030D80((Ent30D80 *)p, 1);
            }
        }
    }
}


extern u8 D_800A49D2[];

void func_80031B7C(void) {
    s32 i = 0;
    s32 one = 1;
    s32 full = 0x7FFF;
    u8 *p = D_800A49D2;

loop:
    if (p[4] && !p[2] && p[3]) {
        p[2] = one;
        *(u16 *)p = full;
    }
    p += 0x54;
    i++;
    if (i < 8) goto loop;
}


extern s8 D_800A4F17;
extern u16 D_800A2BB0[];
extern u16 D_800BA108[];

extern void func_8003388C();   /* §376: def is (Ent388C *, s32); no-proto keeps the typedef out of scope here */

void func_80031BE0(void)
{
    u8 *e;
    s32 i;

    if (*(u8 *)&D_800A4F17 != 0) {
        return;
    }

    e = (u8 *)&D_800A4F17 - 0x82F;

    for (i = 0; i < 8; i++, e += 0x54) {
        u16 v1;

        D_800A2BB0[i] = *(u16 *)(e + 4);
        D_800BA108[i] = *(u16 *)(e + 6);

        v1 = *(u16 *)(e + 0) & 0x3F;
        switch (v1) {
        case 1:
            if (*(u16 *)(e + 8) != 0) {
                *(u16 *)(e + 8) = *(u16 *)(e + 8) - 1;
            }
            break;
        case 0:
            break;
        case 5:
            func_8003388C(e, i);
            break;
        }
    }
}

void func_80031CC8(void) {
    extern u16 D_800A46E8[];
    extern void func_8003350C(s32 a0, s32 a1);
    extern void func_80034650(u8 *a0, s32 a1);
    u8 *p;
    s32 i;

    p = (u8 *)D_800A46E8;
    i = 0;
    do {
        switch (*(u16 *)p & 0x3F) {
        case 1:
            if (p[0xA] != 0) {
                func_8003350C(i, 1);
            }
            break;
        case 5:
            func_80034650(p, 0);
            break;
        }
        i += 1;
        p += 0x54;
    } while (i < 8);
}

void func_80031D70(void) {
    extern u16 D_800A46E8[];
    extern void func_8003350C(s32 a0, s32 a1);
    u16 *p;
    s32 i;

    p = D_800A46E8;
    i = 0;
    do {
        if (((*p & 0x3F) == 1) && (*(u8 *)(p + 5) != 0)) {
            func_8003350C(i, 0);
        }
        i += 1;
        p += 0x2A;
    } while (i < 8);
}

void func_80031DEC(void) {
    extern u16 D_800A46E8[];
    extern void func_8003350C(s32 a0, s32 a1);
    extern void func_80034A54(s32 a0);
    u16 *p;
    s32 i;
    p = D_800A46E8;
    i = 0;
    do {
        switch (*p & 0x3F) {
        case 1:
            if ((*p & 0x40) == 0) {
                func_8003350C(i, 1);
            }
            break;
        case 5:
            func_80034A54((s32)p);
            break;
        }
        i += 1;
        p += 0x2A;
    } while (i < 8);
}

void func_80031E94(void) {
    extern u16 D_800A46E8[];
    extern void func_80034A9C(void *a0);
    u16 *p;
    s32 i;

    p = D_800A46E8;
    i = 0;
    do {
        if ((*p & 0x3F) != 1 && (*p & 0x3F) == 5) {
            func_80034A9C(p);
        }
        i += 1;
        p += 0x2A;
    } while (i < 8);
}

extern u16 D_800A46E8[];
extern void func_8003350C(s32, s32);
extern void func_80034AE0(void *);

void func_80031F14(void) {
    u8 *p;
    s32 i;

    p = (u8 *)D_800A46E8;
    i = 0;
    do {
        switch (*(u16 *)p & 0x3F) {
        case 1:
            if (p[0xA] != 0 && (*(u16 *)p & 0x40) == 0) {
                func_8003350C(i, 1);
            }
            break;
        case 5:
            func_80034AE0(p);
            break;
        }
        i += 1;
        p += 0x54;
    } while (i < 8);
}

void func_80031FC8(void) {
    extern u16 D_800A46E8[];
    extern void func_80034B0C(s32 a0);
    u16 *p;
    s32 i;

    p = D_800A46E8;
    i = 0;
    do {
        switch (*p & 0x3F) {
        case 1:
            break;
        case 5:
            func_80034B0C((s32)p);
            break;
        }
        i += 1;
        p += 0x2A;
    } while (i < 8);
}


/* 0x14-byte record, indexed by p[3]. D_80068304 and D_800A4EE8->unk14 are both
 * arrays of pointers to arrays of these. */

/* slot record inside D_800A46E8 (stride 0x54) */


extern Rec14 *D_80068304[];
extern Owner4EE8 *D_800A4EE8;
extern s16 D_800A4EF0;
extern u16 D_800A46E8[];
extern s8 D_800A4F17;

extern s32 func_800331D4(s32);
extern s32 func_8003310C(s32);
extern void func_800335B8(s32, s32);
extern void func_8003324C(s32);
extern void func_80032A74(Slot54 *, s32, Rec14 *, s32);

s32 func_80032048(u32 arg0, u8 *p, u32 flags) {
    Rec14 *rec;
    Slot54 *e;
    s32 idx;
    s32 ret;
    u32 x;
    u32 y;
    u32 v;
    u8 old;
    u8 b1;
    u8 b2;
    u32 b3;
    u32 b0;

    y = arg0 >> 16;
    b1 = p[1];
    b2 = p[2];
    b3 = p[3];

    if (b1 == 0) {
        rec = &D_80068304[b2][b3];
    } else {
        if (D_800A4EF0 != b1) {
            return 0;
        }
        if (D_800A4EE8 == 0) {
            return 0;
        }
        rec = D_800A4EE8->unk14[b2];
        rec += b3;
    }

    old = *(u8 *)&D_800A4F17;
    *(u8 *)&D_800A4F17 = 1;

    ret = 0;
    v = rec->unk00;
    if ((u16)flags == 0xFFFF) {
        flags = 0;
        x = (u16)y;
        y = 0;
    } else {
        x = arg0;
    }

    idx = func_800331D4(x);
    if (idx == 0) {
        if (flags & 0x4000) {
            if ((flags & 0x3000) == 0) {
                goto done;
            }
        } else if (flags & 0x1000) {
            if ((flags & 0x7F) < 0x30) {
                v >>= 1;
            }
        }
        idx = func_8003310C(v);
        if (idx == 0) {
            goto done;
        }
        ret = idx;
        idx = ret - 1;
        e = (Slot54 *)((u8 *)D_800A46E8 + idx * 0x54);
    } else {
        if (flags & 0x4000) {
            func_800335B8(idx - 1, (u16)flags);
            goto done;
        }
        idx--;
        e = (Slot54 *)((u8 *)D_800A46E8 + idx * 0x54);
        if (e->unk08 != 0) {
            goto done;
        }
        ret = idx + 1;
        func_8003324C((u16)idx);
    }

    b0 = p[0];
    e->unk04 = x;
    e->unk06 = y;
    e->unk02 = v;
    e->unk00 = (b0 & 0xC0) | 1;
    e->unk08 = rec->unk0C;
    e->unk0A = 5;
    func_80032A74(e, idx, rec, (u16)flags);

done:
    *(u8 *)&D_800A4F17 = old;
    return ret;
}


/* ---- declarations copied verbatim from the destination TU (src/800.c, the
 * block that precedes the already-matched sibling func_80032048) ----
 *
 * BANKING NOTE: src/800.c ALREADY has every typedef (Rec14 / Slot54 /
 * Owner4EE8, lines 7327-7350) and every extern below (lines 7353-7363),
 * immediately above `INCLUDE_ASM(... func_800322A8)` at line 7456.  They are
 * reproduced here only so this file compiles standalone under match_one.
 * When banking, replace the INCLUDE_ASM with the FUNCTION BODY ONLY (plus the
 * SLOT_BASE #define) -- re-emitting the typedefs would be a C89 redefinition
 * error.  src/800.c has NO prior declaration of func_800322A8, so there is no
 * DEF-side signature wall (cookbook Sec.20). */

/* 0x14-byte record, indexed by p[3]. D_80068304 and D_800A4EE8->unk14 are both
 * arrays of pointers to arrays of these. */

/* slot record inside D_800A46E8 (stride 0x54) */


extern Rec14 *D_80068304[];
extern Owner4EE8 *D_800A4EE8;
extern s16 D_800A4EF0;
extern u16 D_800A46E8[];
extern s8 D_800A4F17;

extern s32 func_800331D4(s32);
extern s32 func_8003310C(s32);
extern void func_8003324C(s32);
extern void func_80032A74(Slot54 *, s32, Rec14 *, s32);

/* The slot table base D_800A46E8 sits 0x82F bytes below the D_800A4F17 lock
 * byte and the original code derives one from the other (`addiu v1,s1,-0x82F`),
 * i.e. they live in one object.  Spelling it this way is what makes gcc CSE the
 * two symbol addresses into a single base register instead of emitting a second
 * lui/addiu pair (worth 2 instructions plus the whole callee-save ranking). */
#define SLOT_BASE ((u8 *)&D_800A4F17 - 0x82F)

/* SECOND-PASS LEVER (sched.md S13, the bb0 head-skip escape).  A first pass got
 * to 3-off with a pure prologue-schedule residual: sched2 emitted
 * `sw s5 / move s5 / srl` where the target has `srl / sw s5 / move s5`.
 * Cause (read off the -dS dumps, not guessed): sched.c:3189-3213 pins the
 * LEADING RUN of `pseudo = hard-arg-reg` param copies out of sched1's pool, so
 * the a2->flags copy always kept a LOWER LUID than the `srl`; at sched2's T-15
 * all three candidates tie at priority 1 and rank_for_schedule falls through to
 * the LUID tie-break (2.7.2 sched.c:2428, highest LUID picked first = placed
 * last), which put the srl last of the three.
 * Fix: take the third parameter through a BODY-LOCAL copy declared AFTER
 * `y = arg0 >> 16`.  The head copy `pseudo = $a2` becomes a nop-move at reload
 * (local-alloc ties the once-used incoming pseudo to $a2) and the REAL
 * `move s5,a2` materialises at its statement position, where the S2 birthing
 * boost sinks it below the srl -- giving it the HIGHER LUID.  sched2 then picks
 * it first, `sw s5` follows on the potential-hazard rule, and the srl lands at
 * position 3.  Do NOT reorder `flags = arg2;` above `y = arg0 >> 16;`. */
s32 func_800322A8(u32 arg0, u8 *p, u32 arg2) {
    Rec14 *rec;
    Slot54 *e;
    s32 idx;
    s32 ret;
    u16 y;
    u32 x;
    u32 flags;
    u32 v;
    u8 old;
    u8 b1;
    u8 b2;
    u32 b3;
    u32 b0;

    y = arg0 >> 16;
    flags = arg2;
    x = arg0;
    b1 = p[1];
    b2 = p[2];
    b3 = p[3];

    if (b1 == 0) {
        rec = &D_80068304[b2][b3];
    } else {
        if (D_800A4EF0 != b1) {
            return 0;
        }
        if (D_800A4EE8 == 0) {
            return 0;
        }
        rec = D_800A4EE8->unk14[b2];
        rec += b3;
    }

    old = *(u8 *)&D_800A4F17;
    *(u8 *)&D_800A4F17 = 1;

    ret = 0;
    v = rec->unk00;

    idx = func_800331D4((u16)arg0);
    if (idx == 0) {
        if (flags & 0x4000) {
            if ((flags & 0x3000) == 0) {
                goto done;
            }
        }
        idx = func_8003310C(v);
        if (idx == 0) {
            goto done;
        }
        ret = idx;
        idx = ret - 1;
        e = (Slot54 *)(SLOT_BASE + idx * 0x54);
    } else {
        idx--;
        e = (Slot54 *)(SLOT_BASE + idx * 0x54);
        if (e->unk08 != 0) {
            goto done;
        }
        ret = idx + 1;
        func_8003324C((u16)idx);
    }

    b0 = p[0];
    e->unk04 = x;
    e->unk06 = y;
    e->unk02 = v;
    e->unk00 = (b0 & 0xC0) | 1;
    e->unk08 = rec->unk0C;
    e->unk0A = 5;
    func_80032A74(e, idx, rec, (u16)flags);

done:
    *(u8 *)&D_800A4F17 = old;
    return ret;
}


/* MATCH: 180/180 instructions, byte-exact (relocation-masked).
 *
 * S53 RECOVERY (compile conflict on func_80032A74's signature): the reported
 * conflict was func_80032774's draft, which independently invented a
 * DIFFERENT-WIDTH Slot54 (u16/u16/u16 fields + 0x48 pad, vs. this draft's
 * s16/s16/s16/u16/s8).  Three drafts (func_800322A8, func_800324A4 here, and
 * func_80032774) all declare `extern void func_80032A74(Slot54 *, s32,
 * Rec14 *, s32);`, so all three Slot54 spellings must be textually identical
 * for the merged TU to compile.  This draft's Slot54/Rec14/Owner4EE8 and the
 * func_80032A74 prototype were ALREADY the canonical spelling (byte-identical
 * to src/800.c's incumbent, banked for the sibling func_80032048) -- no
 * change was needed here.  func_80032774's recovered draft (S53) was the one
 * fixed: it now reuses this canonical Slot54 for the extern prototype and
 * keeps its own different-width view under a separate name (Slot54View),
 * cast at use.  All three now agree with each other and with the TU.
 *
 * Notes for the banker:
 *   - src/800.c ALREADY declares Rec14 / Slot54 / Owner4EE8, D_80068304,
 *     D_800A4EE8, D_800A4EF0, D_800A46E8, D_800A4F17, func_8003310C,
 *     func_8003324C and func_80032A74 (they were added for the matched
 *     func_80032048, immediately above this function's INCLUDE_ASM).  Delete
 *     the duplicated declaration block below when banking; keep only the
 *     LOCKBYTE / SLOTBASE macros (or inline them).
 *   - src/800.c has NO prior prototype for func_800324A4, so the signature
 *     below is unconstrained (no DEF-side wall here).
 *
 * The three levers that made it match (pass 2; pass 1 stopped at 4 diffs):
 *   1. ONE-SYMBOL BASE (kept from pass 1, but re-spelled).  The target derives
 *      the slot array AND the lock byte from a single lui/addiu pair
 *      ("addiu $a2,$v1,-0x82F" / "addiu $a0,$v1,-0x824"), which gcc-2.7.2's
 *      cse.c can only do when both constants share a symbol_ref
 *      (related_value chains are per-symbol).  Pass 1 used D_800A46E8 as the
 *      base and wrote the lock byte as +0x82F; that links to the same bytes
 *      but emits the relocation against the WRONG symbol.  The target's own
 *      relocation lines are %hi/%lo(D_800A4F17) for the shared base and for
 *      the closing sb, and %hi/%lo(D_800A46E8) for the two `e` computations,
 *      so the base is spelled &D_800A4F17 here and the array is derived from
 *      it (-0x82F, register-relative, no relocation).  Verified with
 *      `objdump -dr`: la $3,D_800A4F17 / la $3,D_800A46E8 x2 / sb $12,D_800A4F17,
 *      no addends anywhere.
 *   2. STATEMENT ORDER, NOT A PIN, for the prologue weave (target idx 5/6:
 *      "sw $s4" before "srl").  sched2 is a BACKWARD list scheduler; every
 *      insn in bb0 has priority 1, so the order is decided by
 *      potential_hazard (stores win) then by LUID.  `sw $s4,0x30($sp)` only
 *      becomes ready once `maxp = 0` (the insn that clobbers $s4) is
 *      scheduled, so moving `maxp = 0;` ABOVE `y = t >> 16;` swaps their
 *      LUIDs, delays the store's readiness by one tick and puts the srl in
 *      the target's slot.  (cookbook S1/S7; 4 diffs -> 2.)
 *   3. NO $5 PIN ON b1 -- widen b3 instead.  Pass 1 pinned b1 to $a1 to fix
 *      the b1/b3 register pair, but a pinned hard-reg dest fails
 *      birthing_insn_p's `reg_n_sets == 1` gate, so b1's lbu lost the sched1
 *      birthing boost while b2's kept it; b2's load then sank BELOW b1's and
 *      the two lbu's came out swapped (idx 16/17) -- unfixable by statement
 *      order (all 120 permutations tried, floor of 2).  The real cause is a
 *      global-alloc density tie (K2): with `u8 b3` the sll/addu uses are
 *      subregs and b3's allocno loses to b1's, so b1 grabs $a0 first.
 *      Declaring b3 as u32 (like the sibling func_80032048 does) makes the
 *      uses full-SI, raises b3's allocno density above b1's, and b3 wins $a0
 *      / b1 gets $a1 with NO pin at all -- which also restores the natural
 *      lbu order.  (Prompt lever B: the interloper was the narrow type.)
 *
 * The `t` pin on $4 is still required -- see its comment below.
 */

/* 0x14-byte record, indexed by p[3]. D_80068304 and D_800A4EE8->unk14 are both
 * arrays of pointers to arrays of these. */

/* slot record inside D_800A46E8 (stride 0x54) */


extern Rec14 *D_80068304[];
extern Owner4EE8 *D_800A4EE8;
extern s16 D_800A4EF0;
extern u16 D_800A46E8[];
extern s8 D_800A4F17;

/* D_800A4F17 == (u8 *)D_800A46E8 + 0x82F.  Both the lock byte and the slot
 * array walked by the search loop must come off the SAME symbol_ref or cse
 * emits a second lui/addiu pair (181 insns).  The target's relocation is on
 * D_800A4F17, so that is the base here. */
#define LOCKBYTE (*(u8 *)&D_800A4F17)
#define SLOTBASE ((u8 *)&D_800A4F17 - 0x82F)

extern s32 func_8003310C(s32);
extern void func_8003324C(s32);
extern void func_80032A74(Slot54 *, s32, Rec14 *, s32);

s32 func_800324A4(u32 arg0, u8 *p, u32 flags, s32 arg3) {
    Rec14 *rec;
    Slot54 *e;
    u8 *q;
    s32 i;
    s32 idx;
    s32 ret;
    s32 count;
    s32 minp;
    s32 maxp;
    s32 pr;
    u16 x;
    /* t: keeps the raw incoming arg0 in $a0 so the "srl $t4, $a0, 16" that
     * feeds the y spill reads $a0 and not $fp.  Without it cse collapses
     * x into the parameter pseudo, the shift reads the callee-saved home and
     * the $s7/$fp pair flips (v <-> arg0) -- 9 diffs.  Emits no instruction. */
    u32 t;
    u16 y;
    s32 v;
    u8 old;
    u8 b0;
    u8 b1;
    u8 b2;
    /* b3 is u32, NOT u8: the width is what wins it $a0 ahead of b1.  See the
     * header note (lever 3) -- with u8 it loses the allocno density race and
     * the b1/b3 pair comes out swapped. */
    u32 b3;

    t = arg0;
    x = arg0;
    b2 = p[2];
    b1 = p[1];
    b3 = p[3];
    /* maxp = 0 must precede the shift: it gates when "sw $s4" becomes ready
     * in sched2 (lever 2). */
    maxp = 0;
    y = t >> 16;

    if (b1 == 0) {
        rec = &D_80068304[b2][b3];
    } else {
        if (D_800A4EF0 != b1) {
            return 0;
        }
        if (D_800A4EE8 == 0) {
            return 0;
        }
        rec = D_800A4EE8->unk14[b2];
        rec += b3;
    }

    ret = 0;
    idx = 0;
    count = 0;

    old = LOCKBYTE;
    LOCKBYTE = 1;

    v = rec->unk00;

    q = SLOTBASE;
    minp = 0x80;
    for (i = 0; i < 8; i++, q += 0x54) {
        if ((*(u16 *)q & 0x3F) == 1 && *(u16 *)(q + 4) == (u16)x) {
            pr = q[0xB] & 0x7F;
            if (pr < minp) {
                idx = i + 1;
                minp = pr;
            }
            if (pr >= maxp) {
                maxp = pr;
            }
            count++;
        }
    }

    if (count <= arg3) {
        idx = 0;
    } else if ((s32)(flags & 0x7F) < minp) {
        goto done;
    }

    if (idx == 0) {
        if (flags & 0x4000) {
            if ((flags & 0x3000) == 0) {
                goto done;
            }
        }
        idx = func_8003310C(v);
        if (idx == 0) {
            goto done;
        }
        ret = idx;
        idx = ret - 1;
        e = (Slot54 *)((u8 *)D_800A46E8 + idx * 0x54);
    } else {
        idx--;
        e = (Slot54 *)((u8 *)D_800A46E8 + idx * 0x54);
        if (e->unk08 != 0) {
            goto done;
        }
        ret = idx + 1;
        func_8003324C((u16)idx);
    }

    if (flags & 0x1000) {
        ((u8 *)e)[0xB] = flags & 0x7F;
        if ((s32)(flags & 0x7F) < maxp) {
            flags |= 0x8000;
        }
    }

    b0 = p[0];
    e->unk04 = x;
    e->unk06 = y;
    e->unk02 = v;
    e->unk00 = (b0 & 0xC0) | 1;
    e->unk08 = rec->unk0C;
    e->unk0A = 5;
    func_80032A74(e, idx, rec, (u16)flags);

done:
    LOCKBYTE = old;
    return ret;
}


/* 0x14-byte record, indexed by p[3]. D_80068304 and D_800A4EE8->unk14 are both
 * arrays of pointers to arrays of these. Identical to the TU's already-banked
 * Rec14 (src/800.c, func_80032048's block) — kept verbatim, not renamed. */

/* Canonical TU spelling of the slot record inside D_800A46E8 (stride 0x54),
 * as already banked by func_80032048 in src/800.c. This function's own view
 * of the same bytes needs different field widths/signs (see Slot54View
 * below), so THIS typedef only exists to keep func_80032A74's prototype
 * byte-identical to the TU's — the callee is called through a cast, never
 * accessed directly as `Slot54` in this file. */

/* This function's own overlay of the same 0x54-byte slot record: it needs
 * unsigned 16-bit loads (lhu, not lh) on unk00/unk04/unk06 to byte-match, and
 * an extra unk0B field the TU's Slot54 doesn't expose. Different tag name so
 * it does NOT collide with the TU's `Slot54` typedef above; pointers are
 * cast to `Slot54 *` only at the func_80032A74 call site. */
typedef struct Slot54View {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ u16 unk04;
    /* 0x06 */ u16 unk06;
    /* 0x08 */ u16 unk08;
    /* 0x0A */ s8  unk0A;
    /* 0x0B */ u8  unk0B;
    /* 0x0C */ u8  pad0C[0x48];
} Slot54View; /* 0x54 */


extern Rec14 *D_80068304[];
extern Owner4EE8 *D_800A4EE8;
extern s16 D_800A4EF0;
extern u16 D_800A46E8[];

#define SLOTS ((Slot54View *)D_800A46E8)
/* &D_800A4F17 expressed as an offset inside the D_800A46E8 object: the target
 * derives both loop pointers from this one materialised address
 * (addiu $a2,$v1,-0x82F / addiu $a1,$v1,-0x824). */
#define PFLAG ((s8 *)((u8 *)D_800A46E8 + 0x82F))

extern s32 func_8003310C(s32);
extern void func_800335B8(s32, s32);
extern void func_8003324C(s32);
extern void func_80032A74(Slot54 *, s32, Rec14 *, s32);

s32 func_80032774(u32 arg0, u8 *p, u32 flags)
{
    Rec14 *rec;
    Slot54View *e;
    Slot54View *q;
    s32 ret;
    s32 best;
    s32 cnt;
    s32 i;
    s32 mn;
    s32 mx;
    s32 t;
    s32 yy;
    s32 f4000;
    u32 x;
    u16 y;
    u16 v;
    u8 old;
    u8 b0;
    u8 b1;
    u8 b2;
    s32 b3;

    b2 = p[2];
    b1 = p[1];
    b3 = p[3];
    mx = 0;
    y = arg0 >> 16;
    x = arg0;

    if (b1 == 0) {
        rec = &D_80068304[b2][b3];
    } else {
        if (D_800A4EF0 != b1) {
            return 0;
        }
        if (D_800A4EE8 == 0) {
            return 0;
        }
        rec = D_800A4EE8->unk14[b2];
        rec += b3;
    }

    yy = y;
    ret = 0;
    best = 0;
    cnt = 0;
    old = *PFLAG;
    *PFLAG = 1;
    q = SLOTS;
    mn = 0x80;
    v = rec->unk00;
    for (i = 0, f4000 = flags & 0x4000; i < 8; i++, q++) {
        if ((q->unk00 & 0x3F) == 1 && q->unk04 == (u16)x) {
            if (yy == 0 || q->unk06 == yy) {
                if (f4000) {
                    func_800335B8(i, (u16)flags);
                }
                goto done;
            }
            t = q->unk0B & 0x7F;
            if (t < mn) {
                best = i + 1;
                mn = t;
            }
            if (mx <= t) {
                mx = t;
            }
            cnt++;
        }
    }

    if (cnt < 2) {
        best = 0;
    } else if ((s32)(flags & 0x7F) < mn) {
        goto done;
    }

    if (best == 0) {
        if (flags & 0x4000) {
            if ((flags & 0x3000) == 0) {
                goto done;
            }
        }
        best = func_8003310C(v);
        if (best == 0) {
            goto done;
        }
        ret = best;
        best = ret - 1;
        e = &SLOTS[best];
    } else {
        ret = best;
        best = ret - 1;
        e = &SLOTS[best];
        if (e->unk08 != 0) {
            goto done;
        }
        func_8003324C((u16)best);
    }

    if (flags & 0x1000) {
        e->unk0B = flags & 0x7F;
        if ((s32)(flags & 0x7F) < mx) {
            flags |= 0x8000;
        }
    }

    b0 = p[0];
    e->unk04 = x;
    e->unk06 = y;
    e->unk02 = v;
    e->unk00 = (b0 & 0xC0) | 1;
    e->unk08 = rec->unk0C;
    e->unk0A = 5;
    func_80032A74((Slot54 *)e, best, rec, (u16)flags);

done:
    *PFLAG = old;
    return ret;
}

/* =====================================================================================
 * S85 (2026-09-06, P32 T4c hand pass) — BANKED byte-identical, 422/422, frame 0x78 exact.
 *
 * The one residual of every earlier pass (idx 244 `lh` vs `lhu`, or the 8-byte frame gap in
 * the `u16` spelling) was a MISSED PRODUCER of a no-traffic stack slot, not a wall.  The frame
 * was bought by the three-statement chain in the `dd->unk06` arm:
 *     gx = dd->unk07;  gx -= 0x100;  flag = (u32)sub < (u32)(u8)gx;
 * which compiles to exactly the `lbu` the direct spelling compiles to, and leaves the pseudo
 * `gx` as a GHOST: combine merges the self-update `gx -= 0x100` into the `(u8)gx` use (the low
 * byte does not depend on it), and because the deleted insn's dest also appears in its source
 * (`i2dest_in_i2src`, combine.c:2306) the reference bookkeeping is skipped; the load then merges
 * into the rewritten use as `lbu`, decrementing `reg_n_sets` from the stale 2 to 1, so
 * `reg_n_refs` is never zeroed.  regclass never saw an insn for `gx` (class "ST_REGS or none"),
 * global does not allocate it, and reload's initial `alter_reg` loop (reload1.c:658) mints an
 * 8-byte slot for it in regno order — after the a0/a1/a2 parameter spills, i.e. at 0x48.
 * Reproducers + the census: .run/P32/t4e/ghost/ (k4/k5/k7/k14/k16/k17 mint it; byte-store hosts
 * k8/k11-k13/k15/k18 do not); cookbook §501-Q.  The S79/S84 paragraphs below are kept as the
 * record of the search; their "CLOSED"/"PROVED" verdicts are SUPERSEDED by this block.
 * ===================================================================================== */
/* =====================================================================================
 * S79 — [SUPERSEDED S85: the orphan producer is the ghost chain above] RESULT UNCHANGED AT closeness 1/422; the residual was believed EXPLAINED
 * AND THE ORPHAN SEARCH CLOSED.  ~200 byte-probes, all with the pinned cc1
 * (cpp -Iinclude | cc1 -quiet -O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker),
 * oracle = `vars=` off the .frame line (NOT the `(use (reg))` count — see INSTRUMENT below).
 *
 * THE FRAME ARITHMETIC IS EXACT AND LEAVES EXACTLY ONE ORPHAN TO BUY (§165-03):
 *   target .frame $sp,0x78  regs=10/0  args=16  =>  vars = 0x40 = 64
 *   64 = 0x20 (the ONE declared local, sp10) + 8*3 (the a0/a1/a2 reload spills at
 *        0x30/0x38/0x40, all referenced) + 8*1 (ONE never-referenced slot at 0x48).
 *   sp10 must be 0x1C..0x20 bytes: 0x18 puts the first spill at 0x28, 0x24 puts it at 0x38;
 *   only [0x1C,0x20] CEIL_ROUNDs frame_offset to the target's 0x30.  A declared pad can
 *   therefore NEVER buy the 8 bytes here — any pad lands before the spills and moves
 *   `sw $a0,0x30($sp)`.  (§162i1/§226/§333 are all inapplicable to this function.)
 *
 * WHY THE ORPHAN AND THE `lhu` ARE MUTUALLY EXCLUSIVE (the new, general result):
 *   `extendhisi2` in mips.md is an EXPAND that does force_not_mem at -O2, so EVERY
 *   `int x = <s16 mem>` is movhi + ashl16 + ashr16 and combine 3-way-merges it to `lh`.
 *   In a SINGLE-USE merge, newi2pat==0 so elim_i2/elim_i1 DROP both intermediates' death
 *   notes -> no orphan.  An orphan needs the HImode load's reg to carry a SECOND use, which
 *   forces the i3_subst_into_i2 path (newi2pat != 0 -> elim_i2 == 0) and strands the ashift
 *   intermediate.  `zero_extendhisi2` is a define_INSN that takes memory, so every unsigned
 *   promotion is one insn and can never orphan (14 u16/u32/s32/QI respellings measured: 0).
 *   => an orphan in this function REQUIRES an `lh`, and the target's idx-244 load is `lhu`.
 *
 * THE SITE CENSUS (why no other site can pay for it).  The target has 8 `lh`s
 *   (D_800C5328, D_800C532A, D_800A4646, D_800A46A2 x2, sp10.unk16, D_800A4EFA,
 *    ch->unk48, D_800A4EF6) and every one is SINGLE-USE, so each is a note-dropping
 *   3->1 merge.  The only two values in the whole body with a free narrow second use are
 *     - `vo->unk18` (mask + a QImode `(s8)` use) -> orphan only in the `lh` spelling, and
 *     - `n` (int uses + the `sh $s2,0x10($s0)` HImode store) -> `s16 n` costs +4 ins and
 *       TWO orphans (426 ins, near 395); an s16 shadow of n (nh/n pair, both directions)
 *       is 2 orphans / near 387.  Measured, not assumed.
 *
 * MEASURED-INERT THIS SESSION (do not re-try):
 *   * 100-variant local-retyping sweep (20 locals x 6 widths): only `n`->s16/s8 (2 orphans,
 *     near 395/397) and `b`->s8 (1 orphan, near 273) move `vars`; nothing is free.
 *   * splitting `(s8)u18` into its own s32 temp DOES buy the orphan and the exact 0x78 frame
 *     (vars=64, near 5) — but combine then re-derives the byte straight from memory as a
 *     second load `lb $v0,0x18($s1)`; 8 spellings (u32/s32/s16 base, <<1 vs *2, compound,
 *     `(u8)`/`&0xFFFF` launders) all keep the `lb`.  Best of that family: near 5.
 *   * `__asm__ __volatile__("" ::: "memory")` between the load and the use DOES block the
 *     3-way merge and restores `lhu` at zero instruction cost — near 22, frame 0x70, and
 *     the orphan dies with the merge.  Same for §148-C's zero-emission ref slider
 *     `__asm__ ("" :: "r"(u18))` placed BEFORE the expression (near 22, vars 56).
 *     Placed AFTER, the slider keeps the orphan but costs a `move` (423 ins, near 184).
 *     This is the tension in its sharpest form: the extra HImode use that BLOCKS the merge
 *     (giving `lhu`) is the same use that must SURVIVE the merge to strand the intermediate.
 *   * `?:`-accumulator respellings of the four selects (ch->unk48, ch->unk24, ch->unk4D,
 *     vv), s16 temps at every single-use `lh` site, un-hoisting the clear loop (index /
 *     pointer / 4 forms), and 6 zero-emission ref sliders at other sites: all vars=56.
 *   * volatile s16 local: vars=64 but near 192 (it is a DECLARED local, wrong stratum).
 *
 * INSTRUMENT CORRECTION (worth banking): §172's "count standalone `(use (reg))` in the
 *   .combine dump" UNDER-COUNTS.  A minimal §167-10 reproducer
 *   (`s16 c = A; if (c != 0) A = c - 1;`) emits `vars= 8` with ZERO `(use (reg))` insns —
 *   the stranded pseudo is simply absent from every post-combine dump while flow's stale
 *   `reg_n_refs` keeps it an allocno (`; ST_REGS or none` in -dl, §165-03).  Also: the
 *   naive grep counts hard-reg return USEs (`(use (reg/i:SI 2 v0))`) — 54 hits across
 *   src/800_b_2.c collapse to 11 real pseudo orphans.  USE `vars=` AS THE ORACLE.
 *
 * WHAT IS LEFT (for whoever picks this up): the 8 bytes are almost certainly NOT a combine
 *   orphan.  §172's producer 3 — a caller-save area, `assign_stack_local(SImode,4,0)`,
 *   allocated inside reload's loop (reload1.c:1445) and therefore AFTER the alter_reg slots
 *   (reload1.c:658) — lands exactly at 0x48 and MIPS_STACK_ALIGN rounds vars 0x3C -> 0x40,
 *   reproducing 64 with no instruction anywhere.  That is a register-allocation event, not a
 *   spelling one; the C axis for it (one more call-crossing value competing for the 9
 *   callee-saved regs this function already uses in full) was not found.  Next probe worth
 *   running: an A/B that adds one genuine call-crossing value and reads `vars` + the
 *   `.greg` "Spilling reg" lines, rather than any further respelling of the 0x18 read.
 * ===================================================================================== */
/* func_80032A74 - NEAR, closeness 1 / 422 ins (frame 0x78 exact, every immediate, every stack
 * offset, every branch target and 421 of 422 registers exact).  Residual: idx 244 `lh` vs `lhu`.
 *
 * ===================================================================================
 * THE LEVER THAT TOOK THIS FROM 12 -> 1 (new; not in the cookbook as of S77):
 *   HOIST A GLOBAL ARRAY'S BASE INTO A FILE-SCOPE-TYPED POINTER LOCAL ASSIGNED *BEFORE*
 *   THE LOOP.  That single move reproduces the target's `lui $t0/addiu $t0/addu` shape
 *   for three different symbols AND puts them all in $t0, with no asm launder and no
 *   register pin.  Mechanism, read out of the gcc-2.7.2 source (tools/reference/gcc-2.7.2):
 *
 *   1. local-alloc.c:472 - a pseudo is a LOCAL-ALLOC CANDIDATE only if
 *        `reg_basic_block[i] >= 0 && reg_n_deaths[i] == 1`
 *      i.e. it lives in ONE basic block and dies ONCE.  `&D_800A4C28[idx]` written inline
 *      makes a 2-ref, one-block pseudo -> local-alloc hands it the LOWEST free hard reg
 *      (find_free_reg scans regno 0..31; MIPS defines no REG_ALLOC_ORDER) -> $v1.
 *   2. Assigning the base to a local BEFORE the `for(;;)` makes it multi-block, so
 *      local-alloc skips it; global-alloc cannot place it either (all ten callee-saved
 *      registers are already taken and update_equiv_regs doubled its live length), so
 *      `reg_renumber < 0`.
 *   3. update_equiv_regs (local-alloc.c:1030) has already attached REG_EQUIV (symbol_ref)
 *      because the pseudo is set once from a constant -> reload1.c DELETES the initialising
 *      insn (zero cost, so the hoist is FREE) and reload.c substitutes the symbol at every
 *      use, reloading it into a SPILL register.  $t0 is this function's first spill reg
 *      (it is also what carries `lw $t0,0x30($sp)`, `addiu $t0,$zero,1`, `mflo $t0`) - which
 *      is exactly why the target shows the symbols and the parm reloads sharing $t0, and why
 *      `register s32 x __asm__("$8")` can NEVER reproduce it: a hard-reg user variable makes
 *      reload move every spill to $t1 (measured: +30 rows).
 *   4. `addu $s1,$v0,$t0` operand order comes from writing `idx * 0x48 + (s32)vB`, not
 *      `vB + idx * 0x48`.
 *   5. `const` on the two tables is LOAD-BEARING (dropping it costs 14 rows of scheduling
 *      around the mult/mflo pair) - the original declared them const.
 *
 * OTHER LEVERS RETAINED FROM THE PREVIOUS 408->12 RUN:
 *   - `vol` and `m` are ONE variable (both live in $a0 over disjoint ranges).
 *   - `register s32 base __asm__("$2")` on the 0x18-lerp base: without it the addu/addiu/subu
 *      chain lands in $v1 (+3 rows).
 *   - a zero-byte `__asm__ __volatile__("")` after `vo->unk04 = 0x6009F` stops sched1 hoisting
 *      the D_800A4EF6 `lh` above the three stores (-7 rows), and one after `ch->unk14 = t32`.
 *   - use the PARAMETERS directly (no `e = arg0` copies) so the reload spill slots stay
 *     0x30/0x38/0x40; the 8-byte clear loop is a POINTER loop with `i = 7;` FIRST (S211).
 *
 * ===================================================================================
 * THE ONE REMAINING ROW, and why it is a genuine wall for this spelling
 *   idx 244   mine `lh $v0,0x18($s1)`   target `lhu $v0,0x18($s1)`
 *
 * The target frame is 0x78: sp10 at 0x10-0x2F, the three parm spills at 0x30/0x38/0x40, and a
 * NEVER-REFERENCED 8-byte slot at 0x48.  The only producer of that slot reachable from C here
 * is a S172 combine USE-orphan, and the only site in this function that orphans is
 * `s16 u18 = vo->unk18` with BOTH an int (sign) promotion and a QImode use - which forces the
 * load to be `extendhisi2_internal` = `lh`.  Spelling the int use as `(u16)u18 & 0xFF00` gives
 * the target's `lhu` and is byte-identical in all 422 instructions - but the orphan vanishes,
 * the frame drops to 0x70 and 22 stack-offset rows break (that draft is kept at
 * .run/S77w/opus/scratch_func_80032A74/v2.c).  Measured dead ends for a substitute orphan
 * (each checked by counting standalone `(insn N P X (use (reg ...)))` in the cc1 `-dc` dump):
 *   - every u16/s16/s8/QImode respelling of the vo->unk18 site (14 forms) -> 0 orphans;
 *   - `s16 n` (D_800C5328/D_800C532A) -> 2 orphans but a `lhu`+`lh` DOUBLE LOAD, +4 ins;
 *   - an s16 temp at that site whose only uses are promotions -> folds, 0 orphans;
 *   - an s16 local for the func_8003F144 return -> 0 orphans.
 * Every other `lh` in the target (D_800A4646, D_800A46A2 x2, sp10.unk16, D_800A4EFA,
 * ch->unk48, D_800A4EF6) has a SINGLE consumer, and S172's rule is that a single-use load
 * 3-way-merges and orphans nothing.  A declared 8-byte dead local cannot substitute: expand-time
 * locals precede the reload spills and push $a0 from 0x30 to 0x38.
 */
/* func_80032A74 - NEAR, closeness 12 / 422 ins (length exact, frame exact).
 *
 * LEVERS PROVEN THIS SESSION (each byte-measured with tools/match_one.py; start 408 -> 12):
 *  1. FRAME +8 (vars 56 -> 64) = ONE combine USE-orphan (cookbook S172 producer 2).  The target's
 *     frame is  0x10..0x2F C24 local | 0x30/0x38/0x40 parm spills | 0x48 NEVER-REFERENCED.  A
 *     declared dead local CANNOT do it (expand-time locals precede reload spills - measured: it
 *     pushes a0 from 0x30 to 0x38), and neither can `asm("":: "m"(pad))` (mark_addressable puts it
 *     in the locals region too).  What does: an `s16` LOCAL read from memory and promoted to int
 *     TWICE, sited after a CODE_LABEL -> expand emits movhi + ashift/ashiftrt, combine merges them
 *     into one `lh` and orphans the HImode pseudo as `(insn (use (reg:SI N)))`, which alter_reg
 *     still gives an 8-byte slot.  Instrument: count standalone `(use (reg` insns in the .combine
 *     dump (tools/cc1_dumps.sh).  ZERO-extending (u16) temps merge cleanly and orphan NOTHING -
 *     the ashift/ashiftrt PAIR is the whole mechanism.  Single-use s16 temps also orphan nothing.
 *     COST: the only site available here is `vo->unk18`, where the target loads `lhu` - so idx 244
 *     is `lh` vs `lhu`, the one structural row left.  A 2-use `lh` site would be free; the only
 *     other one is `n` (D_800C5328) and typing it s16 costs +4 ins.
 *  2. `vol` AND `m` ARE ONE VARIABLE.  The target holds both in $a0 across disjoint ranges; two
 *     separate C variables give two allocnos ($v1 and $a1).  Merging them is what puts the whole
 *     volume chain in $a0.
 *  3. THE S153 LAUNDER'S REAL COST IS AN ALLOCNO, AND THE FIX IS A PIN ON A DEAD TEMP.  Removing
 *     the launder (plain `D_8007319E[pan]`) fixes m/$a0, the `li 0x100` delay-slot schedule and the
 *     D_800A4EF6 hoist all at once - but folds the address back to the 3-insn $at macro form (-2
 *     ins).  Keeping the launder, the symbol pseudo has priority log2(refs)*refs/live_length ~ 0.67
 *     and OUTRANKS the long-lived `vol` (~0.19), so it steals $a0 and pushes the whole chain to $a1
 *     (+17 rows).  `register s32 bp __asm__("$10")` parks it on a register nothing else wants:
 *     $a0 goes back to vol/m and reload keeps $t0.  Do NOT pin it to $8: reload then picks $t1 for
 *     every parm reload (measured +14 rows, net worse).  $9 costs 2 rows (the mflo temp at idx 272
 *     moves $t1 -> $t2); $10 costs none.
 *  4. A zero-byte `__asm__ __volatile__("")` after `vo->unk04 = 0x6009F;` stops sched1 hoisting the
 *     D_800A4EF6 `lh` above the three stores (-7 rows).
 *  5. S219: `vol *= 0x70; vol >>= 7;` (compound) vs `vol = (vol*0x70)>>7;` decides whether the
 *     `<<4` intermediate lands in $a0 or $v0 (-2 rows).
 *
 * REMAINING RESIDUAL (12), all REGISTER-NAMING, nothing structural:
 *   - 3 rows: the D_800A4C28 base is $v1, target $t0.
 *   - 8 rows: the laundered table base is $t1/$t2, target $t0 - and $t0 is unreachable because the
 *     same $t0 is reload's spill register for the three parm reloads; a hard-reg var there evicts
 *     reload.  In the target BOTH uses coexist, which means those symbol pseudos are NOT allocnos -
 *     they are reload rematerialisations of a reg_equiv_constant.  Every C spelling tried
 *     (array[i], &array[i], scalar `extern u16 D;` + `&D + off`, S195-H's struct-cast force_reg,
 *     const u16* local, S239 integer-space, one-table-two-index) folds to the $at macro form; only
 *     the launder produces the 4-insn shape, and the launder always creates an allocno.
 *   - 1 row: idx 244 `lh` vs `lhu` (see lever 1).
 */

 /* 0x0C */
 /* 0x0C */
 /* 0x20 */
 /* 0x14 */


/* ---- views this function needs (new names, no TU collision) ---- */

/* the caller's 0x54 request slot (Slot54, seen past its declared tail) */
typedef struct {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ u16 unk02;
    /* 0x04 */ u8  pad04[6];
    /* 0x0A */ u8  unk0A;
    /* 0x0B */ u8  pad0B[1];
    /* 0x0C */ u16 unk0C;
    /* 0x0E */ u8  unk0E[8];
} Req32A74;

/* the 0x14 record walked by this loop (Rec14, byte-resolved) */
typedef struct {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ u16 unk02;
    /* 0x04 */ u16 unk04;
    /* 0x06 */ u8  unk06;
    /* 0x07 */ u8  unk07;
    /* 0x08 */ u8  unk08;
    /* 0x09 */ u8  unk09;
    /* 0x0A */ u8  unk0A;
    /* 0x0B */ u8  unk0B;
    /* 0x0C */ u8  pad0C[4];
    /* 0x10 */ s32 unk10;
} Rec32A74; /* 0x14 */

/* the 0x54 mixer channel at D_800A4988 (cf. Chan336A8) */
typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ u16 unk08;
    /* 0x0A */ u16 unk0A;
    /* 0x0C */ u16 unk0C;
    /* 0x0E */ u16 unk0E;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ u8  pad18[0xC];
    /* 0x24 */ s32 unk24;
    /* 0x28 */ u8  pad28[0xC];
    /* 0x34 */ u8  unk34;
    /* 0x35 */ u8  unk35;
    /* 0x36 */ u8  unk36;
    /* 0x37 */ u8  pad37[9];
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ s16 unk48;
    /* 0x4A */ s16 unk4A;
    /* 0x4C */ u8  unk4C;
    /* 0x4D */ u8  unk4D;
    /* 0x4E */ u8  unk4E;
    /* 0x4F */ u8  unk4F;
    /* 0x50 */ u8  pad50[2];
    /* 0x52 */ u8  unk52;
    /* 0x53 */ u8  unk53;
} Chan32A74; /* 0x54 */

/* the 0x48 voice at D_800A4C28 (Slot, byte-resolved) */
typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ u16 unk08;
    /* 0x0A */ u16 unk0A;
    /* 0x0C */ u16 unk0C;
    /* 0x0E */ u16 unk0E;
    /* 0x10 */ u8  pad10[4];
    /* 0x14 */ u16 unk14;
    /* 0x16 */ u8  pad16[2];
    /* 0x18 */ u16 unk18;
    /* 0x1A */ u8  pad1A[2];
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ u8  pad20[0x1A];
    /* 0x3A */ u16 unk3A;
    /* 0x3C */ u16 unk3C;
    /* 0x3E */ u8  pad3E[2];
    /* 0x40 */ s32 unk40;
    /* 0x44 */ u8  unk44;
    /* 0x45 */ u8  unk45;
    /* 0x46 */ u8  pad46[2];
} Voice32A74; /* 0x48 */

extern s16 D_800C5328[];
extern s16 D_800C532A[];
extern s16 D_800A4646[];
extern A12   D_80064D44[];
extern B12 *D_8006A970[];
extern Slot D_800A4C28[];
extern u8 D_800A4988[];
extern s32 D_80073140[];
extern s16 D_800A46A2;
extern s16 D_800A4EF6;
extern s16 D_800A4EFA;
extern u8 D_800A4F19;
extern u8 D_800A4F1E;
extern u16 D_8006AA30[];
extern u16 D_8006AB30[];
extern u16 D_8006AB32[];
extern const u16 D_8007319E[];
extern const u16 D_800731A0[];
extern u16 D_8007321E;
extern u8 D_8006AED8[];
extern s16  func_8003F144(s32, s32, s32, C24 *);
extern s32 func_8003F380(s32, s32);
extern s32 func_80030CA4(u16);
extern void func_8002EFF8(s32, s32);
extern void func_8002F064(s32, s32);
extern void func_800316F8(s32);
extern void func_80033324(s32, s32);

void func_80032A74(Slot54 *arg0, s32 arg1, Rec14 *arg2, s32 flags) {
#define REQ ((Req32A74 *)arg0)
#define REC ((Rec32A74 *)arg2)
    C24 sp10;

    Chan32A74 *ch;
    Voice32A74 *vo;
    A12 *dd;
    B12 *q;
    u8 *cp;
    const u16 *tA;
    const u16 *tB;
    u8 *vB;
    s32 i2;
    u16 v;
    u32 vv;
    s32 idx;
    s32 w;
    s32 n;
    s32 flag;
    s32 h;
    s32 i;
    s32 b;
    s32 sub;
    u8 pan;
    u32 vol;
    u32 mp;
    u32 qq;
    s32 tb;
    u32 d;
    register s32 base __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus9)
    u16 t16;
    s32 t8;
    s32 t32;
    u32 gx;

    tA = D_8007319E;
    tB = D_800731A0;
    vB = (u8 *)D_800A4C28;
    v = REQ->unk02;
    i = 7;
    cp = (u8 *)arg0 + 7;
    do {
        cp[0xE] = 0;
        i--;
        cp--;
    } while (i >= 0);
    REQ->unk0C = 0;

    for (;;) {
        b = REC->unk08;
        flag = 0;
        if ((b & 0x80) == 0) {
            dd = &D_80064D44[b];
            sub = REC->unk09;
            if (dd->unk06 != 0) {
                gx = dd->unk07;
                gx -= 0x100;
                flag = (u32)sub < (u32)(u8)gx;
            }
            n = D_800C5328[b * 2];
            if (n < 0) {
                if (flag == 0) {
                    break;
                }
                n = D_800C532A[b * 2];
                if (n < 0) {
                    break;
                }
                if (sub >= D_800A4646[n * 12]) {
                    break;
                }
            }
        } else {
            n = 4;
        }
        if ((flags & 0x1000) && (flags & 0x7F) < 0x30U) {
            v >>= 1;
            flags = (flags & 0xFF80) | (0x2F - ((0x2F - (flags & 0x7F)) >> 1));
        }
        idx = func_80030CA4(v);
        if (idx != 0) {
            idx--;
            vo = (Voice32A74 *)(idx * 0x48 + (s32)vB);
            if ((b & 0x80) == 0) {
                q = &D_8006A970[n][REC->unk09];
                vo->unk1C = q->unk00;
                vo->unk18 = q->unk04;
                vo->unk3A = q->unk06;
                vo->unk3C = q->unk08;
            } else {
                if (func_8003F144(D_800A46A2, b & 0x7F, REC->unk09, &sp10) != 0) {
                    goto next;
                }
                h = func_8003F380(D_800A46A2, sp10.unk16);
                if (h < 0) {
                    goto next;
                }
                tb = sp10.unk04;
                vo->unk1C = h;
                vo->unk18 = tb << 8;
                vo->unk3A = sp10.unk10;
                vo->unk3C = sp10.unk12;
            }
            w = idx + 0x10;
            vo->unk00 = D_80073140[w];
            ch = (Chan32A74 *)(D_800A4988 + idx * 0x54);
            ch->unk4C = 0;
            ch->unk4A = 0x7FFF;
            if (REQ->unk00 & 0x80) {
                ch->unk4D = 0;
            } else {
                ch->unk4D = 1;
            }
            t16 = REC->unk02;
            ch->unk04 = 0;
            ch->unk08 = v;
            ch->unk0A = w;
            ch->unk00 = t16;
            t8 = REC->unk09;
            ch->unk0E = b;
            ch->unk36 = flag;
            ch->unk10 = n;
            ch->unk12 = 0;
            ch->unk0C = t8;
            t32 = REC->unk10;
            ch->unk4F = 0;
            ch->unk4E = 0x85;
            ch->unk14 = t32;
            __asm__ __volatile__("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B tus9)
            vol = REC->unk06;
            if (D_800A4F1E != 0) {
                vol *= 0x70;
                vol >>= 7;
            }
            if (flags & 0x1000) {
                ch->unk48 = flags & 0x7F;
            } else {
                ch->unk48 = 0x7F;
            }
            ch->unk34 = vol & 0x7F;
            pan = REC->unk07;
            ch->unk35 = pan;
            if (flags & 0x8000) {
                ch->unk24 = REC->unk04 - 0x80;
            } else {
                ch->unk24 = REC->unk04;
            }
            ch->unk40 = (s32)func_80033324;
            ch->unk44 = arg1;
            if ((flags & 0x2000) && pan != 0) {
                if ((flags & 0x3000) == 0x3000) {
                    ch->unk53 = D_8006AED8[(u32)(flags & 0xF00) >> 8];
                } else {
                    ch->unk53 = flags & 0x7F;
                }
            } else {
                ch->unk53 = 0;
            }
            if (REC->unk02 == 0) {
                func_800316F8(ch);
            }
            {
                u16 u18 = vo->unk18;
                base = (u18 & 0xFF00) + (s8)u18 * 2;
            }
            base -= 0x3C00;
            d = ch->unk24;
            d -= base;
            if (d >= 0x5300) {
                vo->unk14 = 0x3FFF;
            } else {
                qq = D_8006AB30[d >> 8];
                qq = qq * (0x100 - (d & 0xFF));
                vo->unk14 = (qq + D_8006AB32[d >> 8] * (d & 0xFF)) >> 8;
            }
            vol = D_8006AA30[ch->unk34];
            mp = vol * D_800A4EFA;
            vol = mp >> 7;
            mp = vol * ch->unk48;
            vol = mp >> 7;
            if (pan != 0) {
                if (ch->unk53 != 0) {
                    pan += ch->unk53;
                    if (pan >= 0x42) {
                        pan -= 0x40;
                        if (pan >= 0x80) {
                            pan = 0x7F;
                        }
                    } else {
                        pan = 1;
                    }
                }
                if (D_800A4F19 != 0) {
                    vv = (vol * tA[pan]) >> 14;
                    vo->unk0A = vv;
                    vv = (vol * tB[0x7F - pan]) >> 14;
                    vo->unk08 = vv;
                } else {
                    vv = (vol * D_8007321E) >> 14;
                    vo->unk0A = vv;
                    vo->unk08 = vv;
                }
            } else {
                vv = vol;
                vo->unk08 = vv;
                vo->unk0A = vv;
            }
            ch->unk52 = pan;
            vo->unk0C = 0;
            vo->unk0E = 0;
            vo->unk04 = 0x6009F;
            __asm__ __volatile__("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B tus9)
            if (D_800A4EF6 > REC->unk0A) {
                func_8002F064(1, vo->unk00);
            } else {
                func_8002F064(0, vo->unk00);
            }
            t16 = ch->unk0A;
            vo->unk45 = 0;
            vo->unk44 = 1;
            vo->unk40 = t16;
            if (REC->unk02 == 0) {
                func_8002EFF8(1, vo->unk00);
            }
            REQ->unk0C++;
            REQ->unk0E[idx] = 1;
        }
    next:
        if (REC->unk0B == 0) {
            break;
        }
        arg2++;
        v = REC->unk00;
    }
    if (REQ->unk0C == 0) {
        REQ->unk00 = 0;
    } else {
        REQ->unk0A = 4;
    }
}

#undef REQ
#undef REC

extern u16 D_800A46E8[];
extern void func_8003324C(s32);

s32 func_8003310C(s32 arg0) {
    struct {
        u8 found;
        s32 r;
        u16 vmin;
    } st;
    u16 *p;
    u16 *q;
    s32 i;

    p = D_800A46E8;
    i = 0;
    st.found = 0;

    for (; i < 8;) {
        q = p + 1;
        if (*p == 0) {
            return i + 1;
        }
        if (!st.found) {
            st.found = 1;
            st.vmin = *q;
            st.r = i;
        } else {
            if (*q < st.vmin) {
                st.vmin = *q;
                st.r = i;
            }
        }
        i++;
        p += 0x2A;
    }

    if ((u16)arg0 < st.vmin) {
        return 0;
    }
    func_8003324C((u16)st.r);
    return st.r + 1;
}

extern u16 D_800A46E8[];

s32 func_800331D4(s32 arg0) {
    u16 *p;
    s32 i;

    p = D_800A46E8;
    for (i = 0; i < 8; i++, p += 0x2A) {
        if ((*p & 0x3F) == 1 && p[2] == (arg0 & 0xFFFF) && (((u32)arg0 >> 16) == 0 || ((u32)arg0 >> 16) == p[3])) {
            return ++i;
        }
    }
    return 0;
}


/* func_8003324C — MATCH (54 ins).
 *
 * D_800A46E8 is an array of 0x54-byte slot records; records [8..15] (base
 * +0x2A0 == 8 * 0x54) are Ent30D80 entities. Switch on (rec->flags & 0x3F):
 * case 1 walks the 8 per-slot "dirty" bytes at e[i + 0xE], clearing each set
 * one, blanking the matching entity's unk40 callback, and calling
 * func_80030D80 on it when unk4E is set; then zeroes the flags halfword.
 * case 5 tail-calls func_80034650(e, 0).
 *
 * Second pass over the 2-instruction NEAR draft (target: `sw $zero,0x40($s0)`
 * in the beqz delay slot, then `addu $a0,$s0,$zero`; the first draft emitted
 * the pair in the opposite order with $a0 as the store base). It was NOT a
 * scheduler tie-break — four independent source-level levers, each verified
 * load-bearing by ablation:
 *
 *  1. `p->unk40 = 0;` sits BEFORE the `if (p->unk4E)`, not inside it. reorg
 *     may only steal a store into a delay slot BACKWARD (from before the
 *     branch) — a forward/fall-through steal of a store is unsafe. So the
 *     target's `sw` in the beqz slot proves the store precedes the test in
 *     source order. (Cookbook §175 lever A: statement order.)
 *  2. `register Ent30D80 *p __asm__("$16")`. Hoisting the store out of the
 *     inner `if` gives p three in-loop uses, and loop.c then splits it into
 *     two induction variables (+0x2A0 for the call argument, +0x2EE for the
 *     0x40/0x4E address giv) — 58 ins. loop.c's biv/giv detection only
 *     considers PSEUDO registers, so pinning p to a hard reg disables strength
 *     reduction for it outright and leaves the single `addiu $s0,$s0,0x54`.
 *     This also drops the first draft's copy-fence: every access now goes
 *     through $s0 and the `addu $a0,$s0,$zero` is emitted last, as the target
 *     has it. Ablating the pin: 58 ins.
 *  3. `__asm__ ("" :: "r"(base));` after p's initialisation. With p pinned,
 *     `addiu p, base, 0x2A0` is base's last use, so the allocator ties base to
 *     $s0 and performs the add in place ("lui $s0 / addiu $s0,$s0,0x2A0"),
 *     wrecking the prologue. The zero-instruction asm extends base past the
 *     add and breaks the tie. Ablating it: 8 mismatches.
 *  4. `off` computed into its own local BEFORE `base` is loaded. Otherwise the
 *     %hi/%lo pair is scheduled above the `andi $a0,$a0,0xFFFF`, base then
 *     conflicts with the incoming argument's live range and lands in $a1
 *     instead of $a0. Ablating it: 8 mismatches.
 *
 * Banking note for src/800.c: `typedef struct Ent30D80`, `extern u16
 * D_800A46E8[];` and `void func_80030D80(Ent30D80 *, s16)` already exist
 * ABOVE the INCLUDE_ASM line — do not duplicate them. Only
 * `extern void func_80034650(u8 *, s32);` is new (func_80034650 is still
 * INCLUDE_ASM further down the TU). The TU's existing
 * `extern void func_8003324C(s32);` matches this definition's signature.
 */


extern u16 D_800A46E8[];

extern void func_80030D80(Ent30D80 *arg0, s16 arg1);
extern void func_80034650(u8 *, s32);

void func_8003324C(s32 arg0) {
    u8 *base;
    u8 *e;
    s32 off;
    Ent30D80 *p;
    s32 i;

    off = (u16)arg0 * 0x54;
    base = (u8 *)D_800A46E8;
    e = base + off;

    switch (*(u16 *)e & 0x3F) {
    case 1:
        p = (Ent30D80 *)(base + 0x2A0);
        for (i = 0; i < 8; i++) {
            if ((e + i)[0xE] != 0) {
                (e + i)[0xE] = 0;
                p[i].unk40 = 0;
                if (p[i].unk4E != 0) {
                    func_80030D80(&p[i], 0);
                }
            }
        }
        *(u16 *)e = 0;
        break;
    case 5:
        func_80034650(e, 0);
        break;
    }
}

extern u16 D_800A46E8[];

void func_80033324(s32 a0, s32 a1) {
    u8 *e = (u8 *)D_800A46E8 + a1 * 0x54;
    u16 t;

    if ((*(u16 *)e & 0x3F) == 1) {
        *(u8 *)(e + a0 + 0xE) = 0;
        t = *(u16 *)(e + 0xC) - 1;
        *(u16 *)(e + 0xC) = t;
        if (t != 0) {
            return;
        }
        if (*(u8 *)(e + 0xA) != 5) {
            *(u8 *)(e + 0xA) = 0;
            *(u16 *)e = 0;
        }
    }
}


/* TU decls (src/800.c): `typedef struct Ent30D80 { ... } Ent30D80;` and
 * `extern void func_80030D80(Ent30D80 *arg0, s16 arg1);` already exist
 * above this function's INCLUDE_ASM line (see func_80030D80's own
 * definition and func_8003324C's banking note) — reproduced here verbatim
 * for standalone compilation. Do not duplicate in the TU when banking. */

extern u16 D_800A46E8[];

extern void func_80030D80(Ent30D80 *arg0, s16 arg1);
/* TU already declares func_80034650 as (u8 *, s32) above func_8003324C
 * (src/800.c) — a `void *` redeclaration here would conflict with it. */
extern void func_80034650(u8 *a0, s32 a1);

void func_80033398(u32 arg0)
{
    /* RC-12 / cookbook §136d-1: the $0-add OPAQUE COPY.
     * The target's `addu $s7,$a0,$zero` must NOT be cse-linked to the
     * parameter, so that `srl $s6,$a0,16` keeps reading the raw incoming
     * $a0 (the parm pseudo dies at the srl and local-alloc gives it $a0,
     * deleting the real parm copy).  A plain `s7v = arg0;` makes
     * cse.c make_regs_eqv head-promote s7v to canonical and canon_reg
     * rewrites the srl to `srl $s6,$s7,16` (the 1-ins residual). */
    register s32 zr __asm__("$0");  // !FAKE: pin $0 — NEEDED DIFFERS (P36 rung B tus9)
    u32 s7v;
    u8 *s5v;
    s32 s4v;
    u32 s6v;
    u8 *fpv;
    register u8 *s3v __asm__("$19");  // !FAKE: pin $19 — NEEDED DIFFERS (P36 rung B tus9)
    u8 *s2v;
    s32 s1v;
    register u8 *s0v __asm__("$16");  // !FAKE: pin $16 — NEEDED DIFFERS (P36 rung B tus9)
    s32 t0;

    s7v = arg0 + zr;
    s5v = (u8 *)D_800A46E8;
    s4v = 0;
    s6v = arg0 >> 16;
    fpv = s5v + 0x2A0;
    s3v = s5v + 6;

    for (; s4v < 8; s3v += 0x54, s5v += 0x54) {
        if ((*(u16 *)s5v & 0x3F) == 1 &&
            *(u16 *)(s3v - 2) == (u16)s7v &&
            (s6v == 0 || *(u16 *)s3v == s6v)) {
            s2v = (u8 *)D_800A46E8 + (u32)(u16)s4v * 0x54;
            t0 = *(u16 *)s2v & 0x3F;
            switch (t0) {
            case 1:
                s1v = 0;
                s0v = fpv;
                for (; s1v < 8; s1v++, s0v += 0x54) {
                    u8 *p = s2v + s1v;
                    if (p[0xE] != 0) {
                        p[0xE] = 0;
                        *(u32 *)(s0v + 0x40) = 0;
                        if (s0v[0x4E] != 0) {
                            func_80030D80((Ent30D80 *)s0v, 0);
                        }
                    }
                }
                *(u16 *)s2v = 0;
                break;
            case 5:
                func_80034650(s2v, 0);
                break;
            default:
                s4v++;
                continue;
            }
        }
        s4v++;
    }
}


extern u16 D_800A46E8[];
extern void func_80030D80(Ent30D80 *arg0, s16 arg1);

void func_8003350C(s32 arg0, s32 arg1) {
    u8 *base;
    u8 *e;
    s32 off;
    Ent30D80 *p;
    s32 i;

    off = arg0 * 0x54;
    base = (u8 *)D_800A46E8;
    e = base + off;
    p = (Ent30D80 *)(base + 0x2A0);
    for (i = 0; i < 8; i++) {
        if ((e + i)[0xE] != 0) {
            (e + i)[0xE] = 0;
            p[i].unk40 = 0;
            if (p[i].unk4E != 0) {
                func_80030D80(&p[i], arg1);
            }
        }
    }
    *(u16 *)e = 0;
}


/* TU decls (src/800.c): `extern u16 D_800A46E8[];`, `extern void func_800335B8(s32, s32);` */
extern u16 D_800A46E8[];

void func_800335B8(s32 a0, s32 flags) {
    u8 *e = (u8 *)D_800A46E8 + a0 * 0x54;
    u8 *p;
    u8 *rec;
    s32 n;
    s32 i;
    u16 val = flags;

    if ((*(u16 *)e & 0x3F) != 1) {
        return;
    }

    if (flags & 0x1000) {
        n = *(u16 *)(e + 0xC);
        p = (u8 *)D_800A46E8 + 0x2A0;
        for (i = 0; i < 8; i++) {
            if (n == 0) {
                return;
            }
            if ((e + i)[0xE] != 0) {
                rec = p + i * 0x54;
                n--;
                *(u16 *)(rec + 0x48) = flags & 0x7F;
                rec[0x4F] = 1;
            }
        }
    } else if (flags & 0x2000) {
        n = *(u16 *)(e + 0xC);
        p = (u8 *)D_800A46E8 + 0x2A0;
        for (i = 0; i < 8; i++) {
            if (n == 0) {
                return;
            }
            if ((e + i)[0xE] != 0) {
                rec = p + i * 0x54;
                if (rec[0x35] != 0) {
                    rec[0x53] = val & 0x7F;
                }
                n--;
            }
        }
    }
}


/* func_800336A8 — MATCH (121 ins).
 *
 * Second-pass fix over the 49/-1 NEAR draft. The whole residual was ONE unfilled
 * branch-delay slot: the target leaves `beqz $v0, .L80033818` (the D_800A4F19 test)
 * with a `nop`, our build let reorg.c's EAGER FALLTHROUGH STEAL pull the then-arm's
 * head insn `sll $v0,$v1,1` into it (dbr dump: insn 241 folded into a SEQUENCE with
 * jump_insn 234).
 *
 * Lever: reorg.c `stop_search_p` (2.7.2:675) returns TRUE for an `ASM_INPUT` insn, so
 * `fill_slots_from_thread`'s trial loop terminates on the FIRST insn of the thread and
 * never reaches the `sll`. A zero-byte `__asm__ __volatile__("")` planted as the first
 * statement of the then-arm therefore kills the steal and restores the `nop` — with no
 * emitted instruction of its own (cookbook D3 lever (c), "make the join head ineligible",
 * generalised: make it un-searchable).
 *
 * Also removed the first draft's `register u16 *p __asm__("$6")` pin — byte-verified
 * unnecessary once the slot is fixed, so this body is PIN-FREE (§42e sibling-TU safe).
 *
 * Structural levers kept from pass 1 (each byte-load-bearing):
 *  - byte-arithmetic index `(Chan336A8 *)(D_800A4988 + i*0x54)` keeps the t1/t3/t4 layout;
 *  - `q = D_8007319E + 1; q[0x7F - n]` reproduces cse's related-value `addiu $t6,$t5,2`;
 *  - inverted clamp `if (n >= 0x42) ... else n = 1;` for the bnez/else-last layout;
 *  - one `v` funnelling all three store paths so cross-jumping merges the trailing `sh`;
 *  - `extern const u16 D_8007319E[]` (D_8007321E must stay non-const) lets the second
 *    table load hoist across `sh $v0,0xA($a3)` and interleave into the first mult.
 */

typedef struct {
    /* 0x00 */ u8 pad00[0x0A];
    /* 0x0A */ u16 unk0A;
    /* 0x0C */ u8 pad0C[0x28];
    /* 0x34 */ u8 unk34;
    /* 0x35 */ u8 unk35;
    /* 0x36 */ u8 pad36[0x1C];
    /* 0x52 */ u8 unk52;
    /* 0x53 */ u8 pad53[1];
} Chan336A8; /* size 0x54 */

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ u8 pad0C[0x34];
    /* 0x40 */ s32 unk40;
    /* 0x44 */ u8 unk44;
    /* 0x45 */ u8 pad45[3];
} Voice336A8; /* size 0x48 */

typedef struct {
    /* 0x00 */ u8 pad00[0x16];
    /* 0x16 */ u8 unk16;
    /* 0x17 */ u8 pad17[1];
    /* 0x18 */ u16 unk18;
    /* 0x1A */ u8 pad1A[2];
    /* 0x1C */ u16 unk1C[12];
    /* 0x34 */ u8 pad34[4];
    /* 0x38 */ u8 unk38;
    /* 0x39 */ u8 pad39[1];
    /* 0x3A */ u8 unk3A[8];
} Req336A8;

extern u8 D_800A4988[];
extern s32 D_80073140[];
extern u16 D_8006AA30[];
extern const u16 D_8007319E[];
extern u16 D_8007321E;
extern u8 D_800A4F19;

void func_800336A8(Req336A8 *arg)
{
    Chan336A8 *ch;
    Voice336A8 *vo;
    u16 *p;
    const u16 *q;
    u32 m;
    u32 n;
    u32 v;
    s32 i;
    s32 j;

    for (i = 0; i < 8; i++) {
        if (arg->unk3A[i] == 0) {
            continue;
        }
        ch = (Chan336A8 *)(D_800A4988 + i * 0x54);
        vo = (Voice336A8 *)(D_800A4988 + 0x2A0 + i * 0x48);
        vo->unk00 = D_80073140[ch->unk0A];
        m = ch->unk34;
        m = D_8006AA30[m];
        m = m * *(s16 *)(D_800A4988 + 0x572);
        m = m >> 7;
        if (arg->unk16 != 0) {
            m = m * arg->unk18;
            m = m >> 15;
        }
        p = arg->unk1C;
        for (j = 2; j >= 0; j--, p += 4) {
            m = m * *p;
            m = m >> 14;
        }
        n = ch->unk35;
        if (n != 0) {
            if (arg->unk38 != 0) {
                n += arg->unk38;
                if (n >= 0x42) {
                    n -= 0x40;
                    if (n >= 0x80) {
                        n = 0x7F;
                    }
                } else {
                    n = 1;
                }
            }
            ch->unk52 = n;
            if (D_800A4F19 != 0) {
                v = (m * D_8007319E[n]) >> 14;
                vo->unk0A = v;
                q = D_8007319E + 1;
                v = (m * q[0x7F - n]) >> 14;
                vo->unk08 = v;
            } else {
                v = (m * D_8007321E) >> 14;
                vo->unk0A = v;
                vo->unk08 = v;
            }
        } else {
            v = m;
            vo->unk0A = v;
            vo->unk08 = v;
        }
        vo->unk40 = ch->unk0A;
        if (vo->unk44 != 0) {
            vo->unk04 |= 3;
        } else {
            vo->unk04 = 3;
            vo->unk44 = 1;
        }
    }
}

/* func_8003388C -- MATCH (663 ins).  Sequencer tick: ramps -> command-stream
 * interpreter (switch 0x80..0x87 through jtbl_80073120) -> voice/channel setup.
 *
 * §405-A CHECKED: the .rodata jump table my compile emits is byte-identical to the
 * target's (entries 0x27c/0x304/0x370/0x380/0x434/0x3c8/0x460/0x484) -- note the SOURCE
 * case order must be 0x80,0x81,0x82,0x83,**0x85,0x84**,0x86,0x87: gcc emits case BODIES
 * in source order while entry i points at case i, and the target's 0x84 body sits AFTER
 * its 0x85 body.  §409 law 1 CHECKED: all 46 jal/HI16/LO16 relocations verified in order
 * against the .s with objdump -r (match_one masks them).
 *
 * THE LEVERS (each byte-load-bearing, measured 437 -> 0):
 *  1. BLOCKS AT THE END ARE REAL `goto` TARGETS.  pend83 / pend85 / set36 / advance are
 *     placed after the last statement, exactly where the target's 0x8003427C / 0x8003428C /
 *     0x800342A0 / 0x800342AC blocks are; gcc-2.7.2 has no block reordering, so an inline
 *     `if (...) { ...; return; }` inside the switch would emit them in place instead.
 *  2. CASE 0x80's BYTE SPLIT NEEDS FOUR PSEUDOS OFF A SELF-UPDATING ACCUMULATOR.
 *     `c0 = op; op >>= 8; c1 = op; ...` -- writing `c1 = c0 >> 8; c2 = c1 >> 8;` lets cse
 *     fold the chain to `sra op,16` (no chain, no copies); writing the stores between the
 *     shifts lets copy-prop delete the copies.  c2's copy must come AFTER c0's two stores
 *     (that is what lets $v0 be reused), and c0/c1/c2/c3 are pinned $2/$3/$2/$4 because
 *     global.c has no coalescing and picks the mirror assignment otherwise.
 *  3. ONE SIGNED `op`, ONE UNSIGNED SWITCH SUBJECT.  `op` is s32 (case 0x80/0x81 `op >> 16`
 *     and case 0x84 `op >> 8` are `sra`); the dispatch is `(u32)op >> 24` to get `srl`.
 *  4. §429-style SINGLE-SET LOCALS: `t` (ramp `h` widened) and `t18` (the 0x18 field) must
 *     be DIFFERENT locals -- sharing one costs the $v1/$a1 pair in the ramp loop.  Same for
 *     `n86`/`x86` in case 0x86 and `pr1`/`pr2` for the two D_8007319E/D_800731A0 products.
 *  5. THE $s3 COPY (`addu $s3,$v0,$zero` for cmd->unk09) is not expressible in plain C --
 *     cse propagates any `lvl = tmp`.  A zero-byte `__asm__ __volatile__("" : "=r"(t):"0"(t))`
 *     makes the temp opaque, so the load keeps its own pseudo and the copy survives.
 *     That one instruction was worth ~80 diff rows of index shift.
 *  6. THE FINAL FENCE.  `__asm__ __volatile__("")` after `vo->unk04 = 0x6009F;` is a sched1
 *     barrier: it keeps the `lui/lh %hi/%lo(D_800A4EF6)` pair BELOW the three stores while
 *     the flipped comparison `D_800A4EF6 > cmd->unk0C` makes gcc expand that operand first
 *     (do_compare_and_jump expands TREE_OPERAND 0 first).  Flip without fence = +3, fence
 *     without flip = +3, both = 0.
 *  7. `m` pinned $3 / `v` pinned $2 / `sum` pinned $3 / `base`,`q` pinned $2 (the last two
 *     are func_800314DC's own lerp pins, cookbook: same idiom, same registers).
 *  8. `t24 = cmd->unk06 + e->unk52;` hoisted above the ch->unk40 stores gives the two loads
 *     the lower LUID that wins sched1's priority tie, and `ch->unk12` before `ch->unk4F/48`
 *     is the store order the target actually has.
 *  9. `amt = amt * 112; amt = amt >> 7;` as TWO statements (the product needs to land in
 *     amt's own register); the D_8007319E/D_800731A0 products stay ONE expression.
 * 10. The `res`/`e->unk50 < amt` shapes: `if (A < B) x = B - A; else x = 0;` is what reorg
 *     collapses into `sltu/bnez/subu(delay)/addu zero` -- the "x = B-A; if (...) x = 0;"
 *     form cannot put the subu in the delay slot (it feeds the sltu).
 */



typedef struct {
    /* 0x00 */ u16 cur;
    /* 0x02 */ u16 step;
    /* 0x04 */ u16 tgt;
    /* 0x06 */ u8  act;
    /* 0x07 */ u8  pad07;
} Ramp388C; /* 0x08 */

typedef struct {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ u16 unk02;
    /* 0x04 */ u16 unk04;
    /* 0x06 */ u16 unk06;
    /* 0x08 */ u8  unk08;
    /* 0x09 */ u8  unk09;
    /* 0x0A */ u8  unk0A;
    /* 0x0B */ u8  unk0B;
    /* 0x0C */ u8  unk0C;
    /* 0x0D */ u8  unk0D;
    /* 0x0E */ u8  pad0E[2];
    /* 0x10 */ s32 unk10;
} Cmd388C; /* 0x14 */

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ u8  pad02[6];
    /* 0x08 */ u16 unk08;
    /* 0x0A */ u8  pad0A[2];
    /* 0x0C */ u32 *unk0C;
    /* 0x10 */ u8  *unk10;
    /* 0x14 */ u16 unk14;
    /* 0x16 */ u8  unk16;
    /* 0x17 */ u8  unk17;
    /* 0x18 */ u16 unk18;
    /* 0x1A */ u16 unk1A;
    /* 0x1C */ Ramp388C unk1C[3];
    /* 0x34 */ u16 unk34;
    /* 0x36 */ u8  unk36;
    /* 0x37 */ u8  pad37[1];
    /* 0x38 */ u8  unk38;
    /* 0x39 */ u8  unk39;
    /* 0x3A */ u8  unk3A[8];
    /* 0x42 */ u8  pad42[2];
    /* 0x44 */ u32 *unk44;
    /* 0x48 */ u8  unk48;
    /* 0x49 */ u8  pad49[1];
    /* 0x4A */ u16 unk4A;
    /* 0x4C */ u8  unk4C;
    /* 0x4D */ u8  unk4D;
    /* 0x4E */ u8  unk4E;
    /* 0x4F */ u8  unk4F;
    /* 0x50 */ u16 unk50;
    /* 0x52 */ s16 unk52;
} Ent388C;

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ u16 unk08;
    /* 0x0A */ u16 unk0A;
    /* 0x0C */ u16 unk0C;
    /* 0x0E */ u16 unk0E;
    /* 0x10 */ u16 unk10;
    /* 0x12 */ u16 unk12;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ u8  pad18[0x0C];
    /* 0x24 */ s32 unk24;
    /* 0x28 */ u8  pad28[0x0C];
    /* 0x34 */ u8  unk34;
    /* 0x35 */ u8  unk35;
    /* 0x36 */ u8  unk36;
    /* 0x37 */ u8  pad37[9];
    /* 0x40 */ void (*unk40)(u8 *, s32);
    /* 0x44 */ s32 unk44;
    /* 0x48 */ u16 unk48;
    /* 0x4A */ u16 unk4A;
    /* 0x4C */ u8  unk4C;
    /* 0x4D */ u8  unk4D;
    /* 0x4E */ u8  unk4E;
    /* 0x4F */ u8  unk4F;
    /* 0x50 */ u8  pad50[2];
    /* 0x52 */ u8  unk52;
    /* 0x53 */ u8  unk53;
} Chan388C; /* 0x54 */

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ s16 unk0C;
    /* 0x0E */ s16 unk0E;
    /* 0x10 */ u8  pad10[4];
    /* 0x14 */ s16 unk14;
    /* 0x16 */ u8  pad16[2];
    /* 0x18 */ u16 unk18;
    /* 0x1A */ u8  pad1A[2];
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ u8  pad20[0x1A];
    /* 0x3A */ s16 unk3A;
    /* 0x3C */ s16 unk3C;
    /* 0x3E */ u8  pad3E[2];
    /* 0x40 */ s32 unk40;
    /* 0x44 */ u8  unk44;
    /* 0x45 */ u8  unk45;
    /* 0x46 */ u8  pad46[2];
} Voice388C; /* 0x48 */

extern s16 D_800A4EF0;
extern s16 D_800C5328[];
extern s16 D_800A46A2;
extern u8  D_800A4988[];
extern B12 *D_8006A970[];
extern s32 D_80073140[];
extern u16 D_8006AB30[];
extern u16 D_8006AB32[];
extern u8  D_800A4F1E;
extern u16 D_8006AA30[];
extern s16 D_800A4EFA;
extern u8  D_800A4F19;
extern const u16 D_8007319E[];
extern const u16 D_800731A0[];
extern u16 D_8007321E;
extern s16 D_800A4EF6;

extern void func_80034650(u8 *, s32);
extern void func_800336A8();
extern s32  func_80030CA4(u16);
extern s16  func_8003F144(s32, s32, s32, C24 *);
extern s32  func_8003F380(s32, s32);
extern void func_800316F8(s32);
extern void func_8002F064(s32, s32);
extern void func_8002EFF8(s32, s32);
extern void func_800342E8(u8 *, s32);

void func_8003388C(Ent388C *arg, s32 arg1)
{
    Cmd388C rec;
    C24 sp28;
    s32 pad[4];
    Ent388C *e;
    Cmd388C *cmd;
    Chan388C *ch;
    Voice388C *vo;
    Ramp388C *r;
    B12 *b;
    u32 *p;
    s32 op;
    register s32 c0 __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus9)
    s32 c1;
    register s32 c2 __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus9)
    register s32 c3 __asm__("$4");  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B tus9)
    s32 mask;
    s32 vi;
    s32 bank;
    s32 lvl;
    s32 res;
    register s32 base __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus9)
    register s32 sum __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus9)
    s32 t24;
    s32 tmp9;
    u32 t, t18, d, amt, res2;
    register u32 v __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus9)
    register u32 m __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus9)
    register u32 q __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus9)
    u16 h;
    u32 b04;
    u16 h2;
    s32 n84;
    u32 n86;
    register u32 x86 __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus9)
    u8 flag;
    s32 called;
    s32 lv;
    register u32 tv __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus9)
    register u32 pr1 __asm__("$5");  // !FAKE: pin $5 — NEEDED DIFFERS (P36 rung B tus9)
    register u32 pr2 __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus9)
    register u32 pr3 __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus9)
    u32 i;

    e = arg;
    if (e->unk34 != 0 && e->unk34 != D_800A4EF0) {
        func_80034650((u8 *)e, 0);
        return;
    }
    if (e->unk08 != 0) {
        e->unk08 = e->unk08 - 1;
    }

    r = e->unk1C;
    flag = 0;
    for (i = 0; i < 3; i++, r++) {
        if (r->act != 0) {
            flag = 1;
            h = r->cur;
            t = h;
            if (t == r->tgt) {
                r->act = 0;
            } else if (t < r->tgt) {
                r->cur = h + r->step;
                if (r->cur >= 0x4000) {
                    r->cur = 0x3FFF;
                }
                if (r->tgt < r->cur) {
                    r->cur = r->tgt;
                }
            } else {
                if (t >= r->step) {
                    r->cur = h - r->step;
                } else {
                    r->cur = 0;
                }
                if (r->cur < r->tgt) {
                    r->cur = r->tgt;
                }
            }
        }
    }

    called = 0;
    if (e->unk16 != 0) {
        if (e->unk18 > e->unk1A) {
            e->unk18 = e->unk18 - e->unk1A;
            func_800336A8((void *)e);
            called = 1;
        } else {
            func_80034650((u8 *)e, 1);
            return;
        }
    } else if (flag != 0) {
        func_800336A8((void *)e);
        called = 1;
    }

    if (e->unk39 != e->unk38) {
        if (called == 0) {
            func_800336A8((void *)e);
        }
        e->unk39 = e->unk38;
    }

    if (e->unk36 != 0) {
        for (i = 0; i < 8; i++) {
            if (e->unk3A[i] != 0) {
                return;
            }
        }
        e->unk00 = 0;
        return;
    }

    e->unk14 = e->unk14 - 1;
    if (e->unk14 != 0) {
        return;
    }

    if (e->unk48 != 0) {
        p = e->unk0C;
        for (;;) {
            op = *p;
            switch ((u32)op >> 24) {
            case 0x80:
                p++;
                rec.unk06 = op;
                rec.unk08 = op >> 16;
                op = *p;
                p++;
                rec.unk02 = op;
                rec.unk00 = op >> 16;
                op = *p;
                p++;
                c0 = op;
                op >>= 8;
                c1 = op;
                op >>= 8;
                c3 = (u32)op >> 8;
                rec.unk0C = c0;
                e->unk4F = c0;
                c2 = op;
                rec.unk0B = c1;
                e->unk4E = c1;
                rec.unk0A = c2;
                e->unk4D = c2;
                rec.unk09 = c3;
                e->unk4C = c3;
                h2 = *(u16 *)p;
                p++;
                rec.unk04 = h2;
                e->unk4A = h2;
                op = *p;
                p++;
                rec.unk0D = 0;
                rec.unk10 = op;
                goto done;
            case 0x81:
                p++;
                rec.unk06 = op;
                rec.unk08 = op >> 16;
                op = *p;
                rec.unk02 = op;
                rec.unk00 = op >> 16;
                rec.unk0C = e->unk4F;
                rec.unk0B = e->unk4E;
                rec.unk0A = e->unk4D;
                rec.unk09 = e->unk4C;
                rec.unk04 = e->unk4A;
                p++;
                rec.unk10 = 0;
                rec.unk0D = 0;
                goto done;
            case 0x82:
                p++;
                e->unk17 = op;
                e->unk44 = p;
                continue;
            case 0x83:
                if (e->unk17 != 0) {
                    e->unk17 = e->unk17 - 1;
                    if (e->unk17 == 0) {
                        p++;
                        continue;
                    }
                }
                if ((op & 0xFFFFFF) != 0) {
                    goto pend83;
                }
                p = e->unk44;
                continue;
            case 0x85:
                if (e->unk17 != 0) {
                    e->unk17 = e->unk17 - 1;
                    if (e->unk17 == 0) {
                        p++;
                        e->unk50 = 0;
                        e->unk52 = 0;
                        continue;
                    }
                }
                e->unk52 = e->unk52 + (s8)op * 16;
                e->unk50 = e->unk50 + (s8)(op >> 8);
                mask = op & 0xFF0000;
                if (mask != 0) {
                    goto pend85;
                }
                p = e->unk44;
                continue;
            case 0x84:
                p++;
                e->unk1C[0].act = 1;
                e->unk1C[0].step = op >> 8;
                n84 = op & 0x7F;
                e->unk1C[0].tgt = (n84 * 16383) >> 7;
                continue;
            case 0x86:
                n86 = op & 0x7F;
                x86 = (n86 * 16383) >> 7;
                p++;
                e->unk1C[0].act = 0;
                e->unk1C[0].tgt = x86;
                e->unk1C[0].cur = x86;
                continue;
            case 0x87:
                for (i = 0; i < 8; i++) {
                    if (e->unk3A[i] != 0) {
                        goto set36;
                    }
                }
                e->unk00 = 0;
                return;
            }
        }
    done:
        e->unk0C = p;
        cmd = &rec;
    } else {
        cmd = (Cmd388C *)e->unk0C;
    }

    if (cmd->unk06 == 0) {
        goto after;
    }
    vi = func_80030CA4(cmd->unk04);
    if (vi == 0) {
        goto after;
    }
    lvl = cmd->unk0A;
    vi = vi - 1;
    if ((lvl & 0x80) == 0) {
        bank = D_800C5328[lvl * 2];
    } else {
        bank = 4;
    }
    if (bank < 0) {
        goto after;
    }
    ch = (Chan388C *)(D_800A4988 + vi * 0x54);
    vo = (Voice388C *)(D_800A4988 + 0x2A0 + vi * 0x48);
    if ((lvl & 0x80) == 0) {
        b = &D_8006A970[bank][cmd->unk0B];
        vo->unk1C = b->unk00;
        vo->unk18 = b->unk04;
        vo->unk3A = b->unk06;
        vo->unk3C = b->unk08;
    } else {
        if (func_8003F144(D_800A46A2, lvl & 0x7F, cmd->unk0B, &sp28) != 0) {
            goto after;
        }
        res = func_8003F380(D_800A46A2, sp28.unk16);
        if (res < 0) {
            goto after;
        }
        b04 = sp28.unk04;
        vo->unk1C = res;
        vo->unk18 = b04 << 8;
        vo->unk3A = sp28.unk10;
        vo->unk3C = sp28.unk12;
    }

    vo->unk44 = 1;
    vo->unk40 = ch->unk0A;
    vo->unk45 = 0;
    ch->unk4C = 0;
    ch->unk4A = 0x7FFF;
    ch->unk4D = 0;
    ch->unk00 = 0;
    ch->unk04 = 0;
    ch->unk08 = cmd->unk04;
    ch->unk0C = cmd->unk0B;
    ch->unk0E = lvl;
    ch->unk36 = 0;
    ch->unk10 = bank;
    ch->unk14 = cmd->unk10;
    tmp9 = cmd->unk09;
    __asm__ __volatile__("" : "=r"(tmp9) : "0"(tmp9));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B tus9)
    lvl = tmp9;
    ch->unk35 = lvl;
    ch->unk52 = lvl;
    if (e->unk38 != 0 && lvl != 0) {
        sum = lvl + e->unk38;
        if ((u8)sum < 0x42) {
            lvl = 1;
        } else {
            lvl = sum - 0x40;
            if ((u8)lvl >= 0x80) {
                lvl = 0x7F;
            }
        }
    }

    t24 = cmd->unk06 + e->unk52;
    ch->unk40 = func_800342E8;
    ch->unk44 = arg1;
    ch->unk4E = 0x85;
    ch->unk53 = 0;
    ch->unk24 = t24;
    ch->unk12 = cmd->unk02;
    ch->unk4F = 0;
    ch->unk48 = 0;
    arg->unk3A[vi] = 1;
    func_800316F8((s32)ch);

    vo->unk00 = D_80073140[ch->unk0A];
    t18 = vo->unk18;
    base = (t18 & 0xFF00) + ((s8)t18 * 2);
    base -= 0x3C00;
    d = ch->unk24;
    d -= base;
    if (d >= 0x5300) {
        res2 = 0x3FFF;
    } else {
        q = D_8006AB30[d >> 8];
        q = q * (0x100 - (d & 0xFF));
        pr3 = D_8006AB32[d >> 8] * (d & 0xFF);
        res2 = (q + pr3) >> 8;
    }
    vo->unk14 = res2;

    amt = cmd->unk08;
    if (e->unk50 < amt) {
        amt = amt - e->unk50;
    } else {
        amt = 0;
    }
    if (D_800A4F1E != 0) {
        amt = amt * 112;
        amt = amt >> 7;
    }
    ch->unk34 = amt;
    m = D_8006AA30[amt];
    m = m * D_800A4EFA;
    m = m >> 7;
    if (e->unk16 != 0) {
        m = m * e->unk18;
        m = m >> 15;
    }
    r = e->unk1C;
    for (i = 0; i < 3; i++, r++) {
        m = m * r->cur;
        m = m >> 14;
    }
    lv = lvl & 0xFF;
    if (lv != 0) {
        if (D_800A4F19 != 0) {
            tv = D_8007319E[lv];
            pr1 = m * tv;
            v = pr1 >> 14;
            vo->unk0A = v;
            pr2 = m * D_800731A0[0x7F - lv];
            v = pr2 >> 14;
            vo->unk08 = v;
        } else {
            v = (m * D_8007321E) >> 14;
            vo->unk0A = v;
            vo->unk08 = v;
        }
    } else {
        v = m;
        vo->unk08 = v;
        vo->unk0A = v;
    }
    vo->unk0C = 0;
    vo->unk0E = 0;
    vo->unk04 = 0x6009F;
    __asm__ __volatile__("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B tus9)
    if (D_800A4EF6 > cmd->unk0C) {
        func_8002F064(1, vo->unk00);
    } else {
        func_8002F064(0, vo->unk00);
    }
    func_8002EFF8(1, vo->unk00);

after:
    if (cmd->unk00 == 0) {
        for (i = 0; i < 8; i++) {
            if (e->unk3A[i] != 0) {
                goto set36;
            }
        }
        e->unk00 = 0;
        return;
    }
    e->unk14 = cmd->unk00;
    if (e->unk48 != 0) {
        return;
    }
    if (cmd->unk0D == 0) {
        goto advance;
    }
    if (e->unk17 != 0) {
        e->unk17 = e->unk17 - 1;
        if (e->unk17 == 0) {
            goto advance;
        }
    }
    e->unk0C = (u32 *)((u8 *)arg->unk10 + (cmd->unk0D * 20 - 20));
    return;
pend83:
    e->unk14 = op;
    e->unk0C = e->unk44;
    return;
pend85:
    e->unk14 = mask >> 16;
    e->unk0C = e->unk44;
    return;
set36:
    e->unk36 = 1;
    return;
advance:
    cmd++;
    e->unk0C = (u32 *)cmd;
}

extern u16 D_800A46E8[];

void func_800342E8(u8 *a0, s32 a1) {
    u32 t = a1 * 84 + (u32)D_800A46E8;
    *(u8 *)(t + (u32)a0 + 0x3A) = 0;
}


/* TU decls already present in src/800.c (do NOT duplicate at bank time):
 *   extern u16 D_800A46E8[];
 *   extern s16 D_800A4EF0;
 *   extern Owner4EE8 *D_800A4EE8;   (typedef `Owner4EE8`, defined in src/800.c
 *       as { u8 pad00[0x14]; Rec14 **unk14; } — this function never touches
 *       unk14; it reads offset 0x18 via a raw (u8*) pointer-cast, so it needs
 *       Owner4EE8 only as an OPAQUE type. refuse-BROKE-MATCH note: the batch
 *       reconciler tried to canonicalize this offset-0x18 access into a named
 *       struct field (extending Owner4EE8's size), which shifted bytes in a
 *       sibling already-matched user of the struct — do NOT add a field for
 *       0x18 to Owner4EE8; keep the byte-offset cast below instead.)
 *   extern s32 func_8003310C(s32);
 */

/* 0xC-byte sound-instrument record, indexed by p[3]. */
typedef struct Rec12 {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ u16 unk04;
    /* 0x06 */ u16 unk06;
    /* 0x08 */ u8  unk08;
    /* 0x09 */ u8  pad09[3];
} Rec12; /* 0xC */

typedef struct Snd54Sub {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ u8  unk06;
    /* 0x07 */ u8  pad07;
} Snd54Sub; /* 0x8 */

/* the 0x54-stride voice slot inside D_800A46E8 */
typedef struct Snd54 {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ u16 unk08;
    /* 0x0A */ u8  pad0A[2];
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ u8  unk16;
    /* 0x17 */ u8  unk17;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ Snd54Sub unk1C[3];
    /* 0x34 */ s16 unk34;
    /* 0x36 */ u8  unk36;
    /* 0x37 */ u8  unk37;
    /* 0x38 */ u8  unk38;
    /* 0x39 */ u8  unk39;
    /* 0x3A */ u8  unk3A[8];
    /* 0x42 */ u8  pad42[6];
    /* 0x48 */ u8  unk48;
    /* 0x49 */ u8  pad49[7];
    /* 0x50 */ s16 unk50;
    /* 0x52 */ s16 unk52;
} Snd54; /* 0x54 */

/* opaque — matches the TU's `typedef struct Owner4EE8 Owner4EE8;` spelling
 * exactly so this local decl is droppable at bank time in favor of the TU's;
 * this function only pointer-casts through it (offset 0x18), never names a
 * field, so the incomplete type is sufficient and adds no struct layout. */

extern Rec12 D_80068A54[];
extern u8 D_8006AED8[];
extern u16 D_800A46E8[];
extern Owner4EE8 *D_800A4EE8;
extern s16 D_800A4EF0;

extern s32 func_8003310C(s32);
extern s32 func_800348A8(u32);
extern void func_80034650(u8 *, s32);

s32 func_80034314(u32 arg0, u8 *p, u32 arg2) {
    u32 flags;
    Snd54 *e;
    Rec12 *rec;
    u8 *q;
    s16 *pa;
    s32 idx;
    s32 ret;
    s32 i;
    s32 j;
    s32 b1;
    u32 x;
    u32 y;

    y = arg0 >> 16;
    flags = arg2;
    x = arg0;
    b1 = p[1];
    if (b1 == 0) {
        rec = &D_80068A54[p[3]];
    } else {
        if (D_800A4EE8 == 0) {
            return 0;
        }
        if (D_800A4EF0 != b1) {
            return 0;
        }
        rec = *(Rec12 **)((u8 *)D_800A4EE8 + 0x18) + p[3];
    }

    idx = func_800348A8(arg0);
    if (idx != 0) {
        ret = idx;
        idx--;
        e = (Snd54 *)((u8 *)D_800A46E8 + idx * 0x54);
        if (flags & 0x1000) {
            e->unk1C[0].unk06 = 1;
            e->unk1C[0].unk02 = 0x100;
            e->unk1C[0].unk04 = ((s32)(flags & 0x7F) * 0x3FFF) >> 7;
            if (flags & 0x2000) {
                e->unk38 = D_8006AED8[(flags >> 8) & 0xF];
            } else {
                e->unk38 = 0;
                e->unk39 = 0;
            }
            return ret;
        }
        if (e->unk08 != 0) {
            return 0;
        }
        func_80034650(e, 0);
    } else {
        idx = func_8003310C(rec->unk04);
        if (idx == 0) {
            return 0;
        }
        ret = idx;
        idx--;
        e = (Snd54 *)((u8 *)D_800A46E8 + idx * 0x54);
    }

    e->unk37 = rec->unk08;
    e->unk34 = b1;
    e->unk0C = rec->unk00;
    e->unk02 = rec->unk04;
    e->unk10 = e->unk0C;
    e->unk04 = x;
    e->unk06 = y;
    e->unk14 = 1;
    e->unk17 = p[2];
    e->unk16 = 0;
    e->unk18 = 0x7FFF;
    e->unk08 = rec->unk06;
    e->unk50 = 0;
    e->unk52 = 0;

    if (rec->unk08 & 0x10) {
        e->unk48 = 1;
    } else {
        e->unk48 = 0;
    }

    if (rec->unk08 & 4) {
        e->unk1A = 0x400;
    } else if (rec->unk08 & 8) {
        e->unk1A = 0x200;
    } else {
        e->unk1A = 0x5F;
    }
    e->unk36 = 0;

    pa = &e->unk1C[0].unk00;
    for (i = 0; i < 3; i++, pa = (s16 *)((u8 *)pa + 8)) {
        pa[1] = 0x100;
        *((u8 *)pa + 6) = 0;
        if (i != 0) {
            pa[0] = 0x3FFF;
            pa[2] = 0x3FFF;
        } else if (flags & 0x1000) {
            pa[0] = ((flags & 0x7F) * 0x3FFF) >> 7;
            pa[2] = ((flags & 0x7F) * 0x3FFF) >> 7;
            if (flags & 0x2000) {
                u8 tv = D_8006AED8[(flags >> 8) & 0xF];
                e->unk38 = tv;
                e->unk39 = tv;
            }
        } else {
            pa[0] = 0x3FFF;
            pa[2] = 0x3FFF;
            e->unk38 = 0;
            e->unk39 = 0;
        }
    }

    q = e->unk3A;
    for (j = 7; j >= 0; j--) {
        *q++ = 0;
    }

    e->unk00 = 5;
    return ret;
}


extern u8 D_800A4988[];

void func_80030D80(Ent30D80 *arg0, s16 arg1);

void func_80034650(u8 *param_1, s32 param_2)
{
    s32 i;
    s32 pm;

    pm = (param_2 & 0xFF) << 16;
    for (i = 0; i < 8; i++) {
        if (*(param_1 + i + 0x3A) != 0) {
            func_80030D80((Ent30D80 *)(D_800A4988 + i * 0x54), pm >> 16);
        }
    }
    *(u16 *)param_1 = 0;
}

/* TU decls (src/800.c): `typedef struct Ent30D80 {...} Ent30D80;` and
 * `extern void func_80030D80(Ent30D80 *arg0, s16 arg1);` already exist
 * above this function's INCLUDE_ASM line (see func_8003324C / func_80033398
 * banking notes) — reproduced here verbatim for standalone compilation.
 * Do not duplicate in the TU when banking. */

typedef struct {
    u8 pad[0x3A];
    u8 flg[8];
    u8 tail[0x12];
} S54;

extern u16 D_800A46E8[];
extern void func_80030D80(Ent30D80 *arg0, s16 arg1);

void func_800346D0(s32 arg0) {
    S54 *p;
    S54 *q;
    Ent30D80 *e;
    Ent30D80 *ebase;
    s32 i;
    s32 j;
    s32 lo;
    s32 hi;

    p = (S54 *)D_800A46E8;
    i = 0;
    lo = (arg0 << 16) >> 16;
    hi = arg0 >> 16;
    ebase = (Ent30D80 *)((u8 *)D_800A46E8 + 0x2A0);
    q = (S54 *)((u8 *)D_800A46E8 + 6);
    do {
        if (*(u16 *)p == 5 && *((u16 *)q - 1) == lo && (hi == 0 || hi == *(u16 *)q)) {
            j = 0;
            e = ebase;
            do {
                if (p->flg[j] != 0) {
                    func_80030D80(e, 0);
                }
                j++;
                e++;
            } while (j < 8);
            *(u16 *)p = 0;
        }
        i++;
        q++;
        p++;
    } while (i < 8);
}

typedef struct {
    u16 state;      /* 0x00 */
    u16 unk02;
    u16 id;         /* 0x04 */
    u16 group;      /* 0x06 */
    u16 unk08;
    s8  unk0A;
    u8  unk0B;
    u8  pad0C[0xA];
    u8  active;     /* 0x16 */
    u8  pad17[0x3D];
} Sl;               /* 0x54 */

extern u16 D_800A46E8[];

void func_800347C8(s32 arg0) {
    Sl *e;
    s32 i;

    e = (Sl *)D_800A46E8;
    for (i = 0; i < 8; i++, e++) {
        if (e->state == 5 && e->id == (s16)arg0 &&
            ((arg0 >> 16) == 0 || (arg0 >> 16) == e->group)) {
            e->active = 1;
        }
    }
}


extern u16 D_800A46E8[];

void func_80034844(void)
{
    u8 *p = (u8 *)D_800A46E8;
    s32 i;

    for (i = 0; i < 8; i++, p += 0x54) {
        if (*(u16 *)p == 5 && !(p[0x37] & 2)) {
            p[0x16] = 1;
            *(u16 *)(p + 0x1A) = 0x220;
        }
    }
}

extern u16 D_800A46E8[];

s32 func_800348A8(u32 arg0) {
    u16 *p;
    s32 i;

    p = D_800A46E8;
    for (i = 0; i < 8; i++, p += 0x2A) {
        if (p[0] == 5 && p[2] == (arg0 & 0xFFFF) && ((arg0 >> 16) == 0 || p[3] == (arg0 >> 16))) {
            return ++i;
        }
    }
    return 0;
}

extern u8 D_8006451C[];
extern s8 D_800A4F17;

extern s32 func_8002F4E4(u8 *);

void func_8003491C(s32 arg0)
{
    u16 id;
    s32 raw;
    s32 t;
    s16 lo;
    s16 hi;
    u8 *p;
    u8 old;
    u8 *e;
    s32 i;

    id = arg0 + 0;
    lo = (s16)arg0;
    p = &D_8006451C[lo * 4];
    hi = (s16)((u32)arg0 >> 16);
    if ((*p & 0x7F) == 6) {
        raw = func_8002F4E4(p);
        t = (s16)raw;
        id = raw + 0;
        if (t == 0) {
            return;
        }
        p = &D_8006451C[t * 4];
    }
    if ((s16)id < 0x100) {
        return;
    }
    old = *(u8 *)&D_800A4F17;
    *(u8 *)&D_800A4F17 = 1;
    if ((*p & 0x7F) != 1 && (*p & 0x7F) == 5) {
        e = (u8 *)&D_800A4F17 - 0x82F;
        for (i = 0; i < 8; i++, e += 0x54) {
            if (*(u16 *)e == 5 && *(u16 *)(e + 4) == lo) {
                if (hi == 0 || hi == *(u16 *)(e + 6)) {
                    e[0x16] = 1;
                }
            }
        }
    }
    *(u8 *)&D_800A4F17 = old;
}



extern s8 D_800A4F17;

void func_80034A54(s32 a0) {
    s32 self = a0;
    u8 v0 = *(u8 *)(self + 0x37);

    if ((v0 & 0x1) != 0) {
        s8 *p = &D_800A4F17;
        s8 old = *p;
        *p = 1;
        *(u8 *)(self + 0x32) = 1;
        *(s16 *)(self + 0x2E) = 0x3FF;
        *(s16 *)(self + 0x30) = 0xFFF;
        *p = old;
    }
}


extern s8 D_800A4F17;

void func_80034A9C(void *a0) {
    void *a1 = a0;
    u8 *v1;
    u8 old;

    if (*(u16 *)((u8 *)a1 + 0x30) == 0x3FFF) {
        return;
    }
    v1 = (u8 *)&D_800A4F17;
    old = *v1;
    *v1 = 1;
    *(s8 *)((u8 *)a1 + 0x32) = 1;
    *(s16 *)((u8 *)a1 + 0x2E) = 0x3FF;
    *(s16 *)((u8 *)a1 + 0x30) = 0x3FFF;
    *v1 = old;
}


extern s8 D_800A4F17;

void func_80034AE0(void *a0)
{
    s8 *v1;
    s8 orig;

    v1 = &D_800A4F17;
    orig = *v1;
    *v1 = 1;
    *(s8 *)(a0 + 0x2A) = 1;
    *(s16 *)(a0 + 0x26) = 0x3FF;
    *(s16 *)(a0 + 0x28) = 0;
    *v1 = orig;
}


extern s8 D_800A4F17;

void func_80034B0C(s32 a0) {
    s8 *p = &D_800A4F17;
    s8 old = *p;
    *p = 1;
    *(u8 *)(a0 + 0x2A) = 1;
    *(s16 *)(a0 + 0x26) = 0x3FF;
    *(s16 *)(a0 + 0x28) = 0x3FFF;
    *p = old;
}

extern s32 D_8006AEF8;
extern s32 D_8006AEFC;
extern u8 D_8007620C;

s32 func_80034B3C(void)
{
    u8 flags;

    if (D_8006AEF8 != D_8006AEFC) {
        flags = D_8007620C;
        if (flags & 0x80) {
            return 2;
        }
        if (flags & 0x20) {
            return 4;
        }
        return 1;
    }
    D_8007620C = 0;
    return 0;
}

extern s32 D_8006AEF8;
extern s32 D_8006AEFC;
extern u8 D_80076214;
extern u8 D_8007620C;
/* CD read-queue status: head==tail (D_8006AEF8/FC equal) => idle; flags D_80076214 (a
 * pending/error byte) and D_8007620C (bit7/bit5) classify the busy/result state.
 * Returns 0=idle done, 8=had pending, 2/4/1=busy variants. */
s32 CdQueueBusy(void) {
    if (D_8006AEF8 != D_8006AEFC) {
        if (D_80076214 == 0) {
            if (D_8007620C & 0x80) {
                return 2;
            }
            if (D_8007620C & 0x20) {
                return 4;
            }
            return 1;
        }
    } else {
        D_8007620C = 0;
        if (D_80076214 == 0) {
            return 0;
        }
    }
    D_80076214 = 0;
    return 8;
}


extern s32 D_8006AEF8;
extern s32 D_8006AEFC;
extern u8 D_8006AEF4;
extern u8 D_800A63E4;
extern void *streamLoad_savedReadyCB;
extern u8 streamLoad_cbActive;
extern int streamLoad_state;
extern int D_800A6544;
extern s32 D_8006AEE8;
extern s32 D_800A63E8;
extern s32 D_8007610C;
extern u8 D_8006AEF5;
extern u8 D_8007620C;
extern s32 D_80076114;
extern u8 D_80076214;
extern s32 D_80078F10;
extern void D_800C7D30();
extern int CdGetToc(void (*func)());
extern s32 D_800A5BC8;
extern s32 D_800C6D28;

void func_80034C24(void) {
    s32 *p = &D_80078F10;
    s32 i;

    D_8006AEF8 = 0;
    D_8006AEFC = 0;
    D_8006AEF4 = 0;
    D_800A63E4 = 0;
    streamLoad_savedReadyCB = 0;
    streamLoad_cbActive = 0;
    streamLoad_state = 0;
    D_800A6544 = 0;
    D_8006AEE8 = 0;
    D_800A63E8 = 0;
    D_8007610C = 0;
    D_8006AEF5 = 0;
    D_8007620C = 0;
    D_80076114 = 0;
    D_80076214 = 0;

    for (i = 0; i < 5; i++) {
        p[i] = 0;
    }

    D_800A5BC8 = CdGetToc(D_800C7D30);
    D_800C6D28 = 0;
}


extern u8 D_8006AEF5;
extern s32 D_8006AEF8;
extern s32 D_8006AEFC;
extern u8 D_80076118[];

s32 func_80034CF0(u8 *p) {
    s32 idx = D_8006AEFC;
    u8 saved = D_8006AEF5;
    s32 limit = D_8006AEF8;
    u8 *self;
    s32 f28;
    s32 oldIdx;
    s32 ret;

    D_8006AEF5 = 1;
    idx = idx + 1;
    if (idx >= 4) {
        idx = 0;
    }

    if (idx == limit) {
        D_8006AEF5 = saved;
        return 0;
    }

    self = D_80076118 + D_8006AEFC * 0x30;

    *(s32 *)(self + 0x8) = *(s32 *)(p + 0x8);
    *(s32 *)(self + 0xC) = *(s32 *)(p + 0xC);
    *(s32 *)(self + 0x10) = *(s32 *)(p + 0x10);
    *(s32 *)(self + 0x14) = *(s32 *)(p + 0x14);
    *(s32 *)(self + 0x18) = *(s32 *)(p + 0x18);
    *(s32 *)(self + 0x1C) = *(s32 *)(p + 0x1C);
    *(s32 *)(self + 0x20) = *(s32 *)(p + 0x20);
    *(s32 *)(self + 0x24) = *(s32 *)(p + 0x24);
    f28 = *(s32 *)(p + 0x28);

    self[0] = 1;
    self[1] = 0;
    self[2] = 0;
    self[3] = 0;
    self[7] = 1;

    oldIdx = D_8006AEFC;
    D_8006AEFC = idx;
    D_8006AEF5 = saved;

    ret = oldIdx + 1;
    *(s32 *)(self + 0x28) = f28;
    *(s32 *)(self + 0x2C) = oldIdx;
    return ret;
}

extern u8 D_8006AEF5;
extern s32 D_8006AEF8;
extern s32 D_8006AEFC;
extern u8 D_80076118[];

void func_80034DFC(short arg0) {
    u8 *cur;
    u8 *src;
    u8 saved;
    s32 i;
    s32 next;
    s32 nn;

    if (arg0 == 0) {
        return;
    }
    i = (short)(arg0 - 1);
    cur = D_80076118 + i * 0x30;
    saved = D_8006AEF5;
    D_8006AEF5 = 1;
    if (cur[0] != 0) {
        cur[0] = 0;
        cur[1] = 1;
        if (i != D_8006AEF8 && cur[7] != 0) {
            next = i + 1;
            goto check;
            for (;;) {
                src = D_80076118 + next * 0x30;
                cur[0] = src[0];
                cur[1] = src[1];
                cur[2] = src[2];
                cur[3] = src[3];
                cur[4] = src[4];
                cur[5] = src[5];
                cur[6] = src[6];
                cur[7] = src[7];
                *(s32 *)(cur + 0x08) = *(s32 *)(src + 0x08);
                *(s32 *)(cur + 0x0C) = *(s32 *)(src + 0x0C);
                *(s32 *)(cur + 0x10) = *(s32 *)(src + 0x10);
                *(s32 *)(cur + 0x14) = *(s32 *)(src + 0x14);
                *(s32 *)(cur + 0x18) = *(s32 *)(src + 0x18);
                *(s32 *)(cur + 0x1C) = *(s32 *)(src + 0x1C);
                *(s32 *)(cur + 0x20) = *(s32 *)(src + 0x20);
                *(s32 *)(cur + 0x24) = *(s32 *)(src + 0x24);
                nn = next + 1;
                *(s32 *)(cur + 0x28) = *(s32 *)(src + 0x28);
                *(s32 *)(cur + 0x2C) = *(s32 *)(src + 0x2C);
                ((void (*)(s32, s32)) *(s32 *)(src + 0x28))(nn, i + 1);
                i = next;
                cur = src;
                next = nn;
            check:
                if (next >= 4) {
                    next = 0;
                }
                if (next == D_8006AEFC) {
                    break;
                }
            }
            D_8006AEFC = i;
            D_80076118[i * 0x30] = 0;
        }
    }
    D_8006AEF5 = saved;
}


extern u8 D_8006AEF5;
extern s32 D_8006AEF8;
extern s32 D_8006AEFC;
extern u8 D_80076118[];
extern u8 D_80076138[];
extern s32 D_80076114;
extern u8 D_8007620C;

void func_8003500C(void) {
    if (D_8006AEF5 != 0) {
        return;
    }

    if (D_8006AEFC != D_8006AEF8) {
        s32 idx = D_8006AEF8;
        u8 *self = D_80076118 + idx * 0x30;

        if (self[0] != 0) {
            s32 (*fn8)(void *) = *(s32 (**)(void *))(self + 8);
            register s32 type __asm__("$2") = self[4];  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus9)

            D_80076114 = type;
            if (fn8(self) == 0) {
                return;
            }

            {
                s32 (*fn1C)(s32) = *(s32 (**)(s32))(self + 0x1C);
                register s32 type2 __asm__("$5") = self[4];  // !FAKE: pin $5 — NEEDED DIFFERS (P36 rung B tus9)

                D_80076114 = type2;
                if (fn1C != NULL) {
                    fn1C(*(s32 *)(D_80076138 + D_8006AEF8 * 0x30));
                }
            }

            self[0] = 0;
            self[1] = 0;
            D_8006AEF8 += 1;
            if ((u32)D_8006AEF8 >= 4) {
                D_8006AEF8 = 0;
            }
            if (D_8006AEF8 == D_8006AEFC) {
                D_80076114 = 0;
            }
            return;
        } else {
            if (self[1] != 0 && self[7] == 0) {
                s32 (*fn24)(void *) = *(s32 (**)(void *))(self + 0x24);

                if (fn24 != NULL) {
                    fn24(self);
                }
                if (self[2] != 0) {
                    return;
                }
            }

            self[1] = 0;
            D_8006AEF8 += 1;
            if ((u32)D_8006AEF8 >= 4) {
                D_8006AEF8 = 0;
            }
            if (D_8006AEF8 == D_8006AEFC) {
                D_80076114 = 0;
            } else {
                D_80076114 = 1;
            }
            return;
        }
    } else {
        D_8007620C = 0;
    }
}

extern s32 D_80076218;

s32 func_800351E8(s32 arg0)
{
    D_80076218 = arg0;
    return arg0 & -((u32)(arg0 - 0x1010) <= 0x7EFF0);
}


extern s32 D_80076218;

extern void func_8003C498(s32);
extern void SpuWrite(s32, s32);

void func_80035210(s32 a0, s32 a1)
{
    register s32 v1 __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus9)

    v1 = D_80076218;
    func_8003C498(v1);
    SpuWrite(a0, a1);
    v1 = D_80076218;
    D_80076218 = v1 + a1;
}
