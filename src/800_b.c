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

s32 func_8002B0B4(s32 sel, s32 idx, u8 *out) {
    s32 kind;
    u32 res;
    s32 cnt;
    s32 ret = 0;
    s32 v;

    v = func_80061024(1, &kind, &res);
    switch (v) {
    case -1:
        switch (D_800760AC) {
        case 0:
          {
            s32 st;
            D_800760B8 = 0;
            if ((sel & 7) == 0) {
                D_800760AC++;
                break;
            }
            if ((sel & 7) == 1) {
                st = 7;
            } else if ((sel & 7) == 2) {
                st = 0x1E;
            } else if ((sel & 7) == 3) {
                st = 0x23;
            } else {
                break;
            }
            D_800760AC = st;
            D_800760B8 = sel & 0x18;
            break;
          }
        case 1:
            D_800760B0 = 0;
            func_8005FD58(0);
            D_800760AC++;
            break;
        case 3:
            if (D_8007609C[0].stat != 7) {
                goto reset;
            }
            D_800760B0 = 0;
            D_800760AC++;
            break;
        case 4:
            res = func_8006023C(D_800760B0, D_80072DFC, 1);
            if (res != 0) {
            reset:
                D_800760AC = 0;
                break;
            }
            D_800760AC++;
            /* fallthrough */
        case 5:
            func_80060404(&D_80075A40, 0x200, 0x280);
            D_800760AC++;
            break;
        case 6:
            switch (D_800760C4) {
            case 0:
                D_8007609C[D_800760B0 >> 4].stat = 8;
                D_8007609C[D_800760B0 >> 4].val = func_8002C320();
                goto close;
            case 1:
                func_800603BC();
                D_800760AC = 0;
                D_8007609C[D_800760B0 >> 4].stat = 2;
                break;
            case 3:
                func_800603BC();
                D_800760AC = 1;
                break;
            case 2:
            default:
                func_800603BC();
                D_800760AC = 0;
                D_8007609C[D_800760B0 >> 4].stat = 0;
                break;
            }
            break;
        case 7:
            if (D_8007609C[0].stat == 0) {
                D_800760AC = 1;
                break;
            }
            D_800760B0 = 0;
            D_800760B4 = 0;
            res = func_8006023C(0, D_80072DFC, 2);
            switch (res) {
            case 0:
                D_800760AC = 0xB;
                break;
            case 1:
                D_800760AC = 0;
                D_8007609C[D_800760B0 >> 4].stat = 2;
                ret = 2;
                break;
            case 2:
                D_800760AC = 0;
                D_8007609C[D_800760B0 >> 4].stat = 4;
                ret = 2;
                break;
            case 4:
                D_800760AC = 0;
                D_8007609C[D_800760B0 >> 4].stat = 3;
                ret = 2;
                break;
            case 5:
                func_800603BC();
                D_800760AC++;
                break;
            }
            break;
        case 8:
            res = func_80061114(D_800760B0, D_80072DFC, 1);
            switch (res) {
            case 0:
                D_80075840[0] = 0x53;
                D_80075840[1] = 0x43;
                D_80075840[2] = 0x13;
                D_80075840[3] = 1;
                *(Blk41 *)&D_80075840[4] = *(Blk41 *)D_80072E10;
              {
                s32 i = 0x1B;
                u8 *q;
                q = &D_80075840[0x5F];
                for (; i >= 0; i--) {
                    *q-- = 0;
                }
              }
                *(Blk32u *)&D_80075840[0x60] = *(Blk32u *)D_80063AEC;
                *(Blk128u *)&D_80075840[0x80] = *(Blk128u *)&D_80063AEC[0x2C];
                *(Blk128u *)&D_80075840[0x100] = *(Blk128u *)&D_80063AEC[0xEC];
                *(Blk128u *)&D_80075840[0x180] = *(Blk128u *)&D_80063AEC[0x1AC];
                func_80060AE0(D_800760B0, D_80072DFC, D_80075840, 0, 0x200);
                func_80016714(&D_80075A40, 0x280);
                D_800760AC++;
                break;
            case 1:
                func_800603BC();
                D_800760AC = 0;
                D_8007609C[D_800760B0 >> 4].stat = 2;
                ret = 2;
                break;
            case 2:
                func_800603BC();
                D_800760AC = 0;
                D_8007609C[D_800760B0 >> 4].stat = 4;
                ret = 2;
                break;
            case 4:
                func_800603BC();
                D_800760AC = 0;
                D_8007609C[D_800760B0 >> 4].stat = 3;
                ret = 2;
                break;
            case 6:
                func_800603BC();
                D_800760AC = 7;
                break;
            case 7:
                func_800603BC();
                D_800760AC = 0;
                D_8007609C[D_800760B0 >> 4].stat = 5;
                ret = 2;
                break;
            }
            break;
        case 9:
            func_80060AE0(D_800760B0, D_80072DFC, &D_80075A40, 0x200, 0x280);
            D_800760AC++;
            break;
        case 10:
            switch (D_800760C4) {
            case 0:
                D_8007609C[D_800760B0 >> 4].stat = 8;
                D_8007609C[D_800760B0 >> 4].val = 0;
                func_800603BC();
                D_800760AC = 7;
                break;
            case 1:
                func_800603BC();
                D_800760AC = 0;
                D_8007609C[D_800760B0 >> 4].stat = 2;
                ret = 2;
                break;
            case 2:
                func_800603BC();
                D_800760AC = 0;
                D_8007609C[D_800760B0 >> 4].stat = 4;
                ret = 2;
                break;
            case 3:
                func_800603BC();
                D_800760AC = 0;
                D_8007609C[D_800760B0 >> 4].stat = 0;
                ret = 2;
                break;
            }
            break;
        case 11:
          {
            u8 *m;
            u8 *p;
            m = (u8 *)&D_80075A40;
            __asm__ __volatile__("" : "=r"(m) : "0"(m));
            func_80016714(m, 0x80);
            p = (u8 *)&D_80075A40 + ((idx + 1) << 7);
            D_80075A40 = D_80076040;
            func_80016714(p, 0x80);
            func_80060614(p, (idx + 5) << 7, 0x80);
            D_800760AC++;
            break;
          }
        case 13:
          {
            u8 *m;
            u8 *p;
            s32 cp;
            m = D_80075FC0;
            __asm__ __volatile__("" : "=r"(m) : "0"(m));
            func_80016714(m, 0x80);
            D_80075FC0[0] = 0xFF;
            p = &D_80075FC0[0x10];
            *(Blk152 *)p = *(Blk152 *)&D_80075CC0[0x24];
            D_800760BC = func_8002B064(p);
            cp = (s32)D_80075CC0;
            __asm__ __volatile__("" : "=r"(cp) : "0"(cp));
            D_800760C0 = func_8002B08C(cp);
            *(u16 *)&D_80075FC0[4] = D_800760C0;
            *(u16 *)&D_80075FC0[2] = D_800760BC;
            func_80060614(D_80075CC0, idx * 0x300 + 0x480, 0x300);
            D_800760AC++;
            break;
          }
        case 15:
            func_800603BC();
            D_800760C4 = func_8006023C(D_800760B0, D_80072DFC, 1);
            D_800760AC++;
            break;
        case 19:
          {
            s32 sum;
            s32 cp;
            s32 end;
            func_800603BC();
            sum = 0;
            cp = (s32)D_80075CC0;
            end = cp + 0x300;
            do {
                sum += *(u8 *)cp;
                cp++;
            } while (cp < end);
            if ((sum & 0xFFFF) != D_800760C0) {
                D_8007609C[D_800760B0 >> 4].stat = 8;
                ret = 2;
                D_8007609C[D_800760B0 >> 4].val = func_8002C320();
                D_800760AC = 0;
                break;
            }
            D_800760C4 = func_8006023C(D_800760B0, D_80072DFC, 2);
            D_800760AC++;
            break;
          }
        case 21:
            func_80060614(&D_80075A40, 0x200, 0x80);
            __asm__ __volatile__("");                 /* §5a zero-byte cross-jump barrier */
            D_800760AC++;
            break;
        case 23:
            func_80060614(D_80075FC0, (idx + 5) << 7, 0x80);
            __asm__ __volatile__("" ::: "memory");    /* §5a barrier, distinct from case 21's */
            D_800760AC++;
            break;
        case 25:
            func_800603BC();
            D_800760C4 = func_8006023C(D_800760B0, D_80072DFC, 1);
            D_800760AC++;
            break;
        case 27:
            func_80060404(D_80075FC0, (idx + 5) << 7, 0x80);
            D_800760AC++;
            break;
        case 29:
          {
            s32 sum;
            s32 cp;
            s32 end;
            func_800603BC();
            sum = 0;
            cp = (s32)&D_80075FC0[0x10];
            end = cp + 0x70;
            do {
                sum += *(u8 *)cp;
                cp++;
            } while (cp < end);
            if ((sum & 0xFFFF) == D_800760BC) {
                s32 i = 0;
                u8 *p = D_80075AC0;
                p = (idx << 7) + p;
                for (; i < 0x80; i++) {
                    p[i] = D_80075FC0[i];
                }
                ret = 1;
            } else {
                ret = 2;
            }
            D_8007609C[D_800760B0 >> 4].stat = 8;
            D_8007609C[D_800760B0 >> 4].val = func_8002C320();
            D_800760AC = 0;
            break;
          }
        case 16:
        case 20:
        case 26:
        case 31:
            switch (D_800760C4) {
            case 0:
                D_800760AC++;
                break;
            case 1:
                D_8007609C[D_800760B0 >> 4].stat = 2;
                ret = 2;
                goto close;
            case 2:
                D_8007609C[D_800760B0 >> 4].stat = 4;
                ret = 2;
                goto close;
            case 4:
                D_8007609C[D_800760B0 >> 4].stat = 3;
                ret = 2;
                goto close;
            case 5:
                D_8007609C[D_800760B0 >> 4].stat = 6;
                ret = 2;
                goto close;
            }
            break;
        case 12:
        case 14:
        case 22:
        case 24:
            switch (D_800760C4) {
            case 0:
                D_800760AC++;
                break;
            case 1:
                func_800603BC();
                D_800760AC = 0;
                D_8007609C[D_800760B0 >> 4].stat = 2;
                ret = 2;
                break;
            case 2:
                func_800603BC();
                D_800760AC = 0;
                D_8007609C[D_800760B0 >> 4].stat = 4;
                ret = 2;
                break;
            case 3:
                func_800603BC();
                D_800760AC = 0;
                D_8007609C[D_800760B0 >> 4].stat = 0;
                ret = 2;
                break;
            }
            break;
        case 18:
        case 28:
        case 33:
            switch (D_800760C4) {
            case 0:
                D_800760AC++;
                break;
            case 1:
                D_8007609C[D_800760B0 >> 4].stat = 2;
                ret = 2;
                goto close;
            case 3:
                D_8007609C[D_800760B0 >> 4].stat = 0;
                ret = 2;
                goto close;
            case 2:
                D_8007609C[D_800760B0 >> 4].stat = 4;
                ret = 2;
            close:
                func_800603BC();
                goto reset;
            }
            break;
        case 30:
            if (D_8007609C[0].stat == 0) {
                D_800760AC = 1;
                break;
            }
            D_800760B0 = 0;
            D_800760B4 = 0;
            D_800760C4 = func_8006023C(0, D_80072DFC, 1);
            D_800760AC++;
            break;
        case 17:
        case 32:
            func_80060404(D_80075CC0, idx * 0x300 + 0x480, 0x300);
            D_800760AC++;
            break;
        case 2:
            D_800760AC++;
            break;
        case 34:
          {
            s32 sum;
            s32 cp;
            s32 end;
            func_800603BC();
            D_800760C0 = *(u16 *)&D_80075AC0[(idx << 7) + 4];
            sum = 0;
            cp = (s32)D_80075CC0;
            end = cp + 0x300;
            do {
                sum += *(u8 *)cp;
                cp++;
            } while (cp < end);
            if ((sum & 0xFFFF) == D_800760C0) {
                ret = 1;
            } else {
                ret = 2;
            }
            goto reset;
          }
        case 35:
            if (D_8007609C[0].stat == 0) {
                D_800760AC = 1;
                break;
            }
            D_800760B0 = 0;
            D_800760B4 = 0;
            res = func_80061524(0);
            switch (res) {
            case 0:
                ret = 1;
                D_800760AC = 0;
                D_8007609C[D_800760B0 >> 4].stat = 6;
                break;
            case 1:
                D_800760AC = 0;
                D_8007609C[D_800760B0 >> 4].stat = 2;
                ret = 2;
                break;
            case 2:
            default:
                D_800760AC = 0;
                D_8007609C[D_800760B0 >> 4].stat = 0;
                ret = 2;
                break;
            }
            break;
        }
        break;
    case 0:
        break;
    case 1:
        switch (kind) {
        case 1:
            switch (res) {
            case 0:
              {
                s32 port = D_800760B0;
                if (!((u32)D_8007609C[port >> 4].stat < 3)) {
                    break;
                }
                func_8005FFB4(port);
                D_8007609C[D_800760B0 >> 4].stat = 1;
                D_8007609C[D_800760B0 >> 4].val = 0;
                break;
              }
            case 3:
                func_8005FFB4(D_800760B0);
                D_8007609C[D_800760B0 >> 4].stat = 1;
                D_8007609C[D_800760B0 >> 4].val = 0;
                break;
            default:
                D_8007609C[D_800760B0 >> 4].stat = 2;
                D_8007609C[D_800760B0 >> 4].val = 0;
                break;
            }
            break;
        case 2:
            switch (res) {
            case 0:
            case 3:
              {
                s32 port = D_800760B0;
                res = func_80060D9C(port, D_80072DFC, &D_80076044[(port >> 4) * 0x28],
                                    &D_80076094[port >> 4], 0, 1);
                switch (res) {
                case 0:
                  {
                    s32 i;
                    u32 r;
                    port = D_800760B0;
                    i = port >> 4;
                    if (D_80076094[i] != 0) {
                        D_8007609C[i].stat = 7;
                        break;
                    }
                    D_8007609C[i].stat = 6;
                    r = func_80060D9C(port, D_80072E3C, lzss_sectorStagingBuf, &cnt, 0, 0xF);
                    switch (r) {
                    case 0:
                        if (func_8002C3B0(cnt, (u8 *)lzss_sectorStagingBuf) < 0xF) {
                            break;
                        }
                        D_8007609C[D_800760B0 >> 4].stat = 5;
                        break;
                    case 1:
                        D_8007609C[D_800760B0 >> 4].stat = 2;
                        break;
                    default:
                        D_8007609C[D_800760B0 >> 4].stat = 4;
                        break;
                    }
                    break;
                  }
                case 1:
                    D_8007609C[D_800760B0 >> 4].stat = 2;
                    break;
                default:
                    D_8007609C[D_800760B0 >> 4].stat = 4;
                    break;
                }
                break;
              }
            case 4:
                D_8007609C[D_800760B0 >> 4].stat = 3;
                break;
            case 1:
                D_8007609C[D_800760B0 >> 4].stat = 1;
                break;
            default:
                D_8007609C[D_800760B0 >> 4].stat = 4;
                break;
            }
            break;
        case 3:
            break;
        case 4:
        case 5:
        case 6:
            D_800760C4 = res;
            break;
        }
        break;
    }
    out[0] = 0;
    out[1] = D_8007609C[0].stat;
    out[4] = D_8007609C[0].val;
    out[5] = D_8007609C[0].val >> 8;
    out[6] = *(u16 *)((u8 *)D_8007609C + 6);
    out[7] = ((u8 *)D_8007609C)[7];
    return ret;
}

/* RESOLVED (P31 S75): the deferral below is kept verbatim for the record.  The "three entry
 * points" are jtbl_80072E44 entries 0/1/2 (cases 0, 1, 2 of the state switch), the "multi-entry"
 * shape was the splat symbol boundary, and the memcard helpers stayed extern (their formats are
 * still Q#5).  The function is decompiled as func_8002B0B4 above. */
/* DEFERRED: SaveLoadRoutine (0x8002B154) — Phase 7 (session G), per Drew, to Q#5.
 * Original intent: the save / PS1 memory-card handler. Referenced by saveHeaderTemplate
 *   (0x80072DF0) via THREE entry-point pointers: 0x8002B154 / 0x8002B1AC / 0x8002BEA4.
 *   Dispatch branches on (selector & 7) (case 0 -> +1 counter; 1 -> 7; 2 -> 0x1E; 3 -> 0x23).
 * Why deferred (NOT a clean state machine like the 3 CD loaders drafted this session):
 *   - splat emits ONE 1139-instruction stub spanning 0x8002B154-0x8002C31C with a SINGLE `jr $ra`
 *     => it is effectively one large MULTI-ENTRY function (the 3 saveHeaderTemplate entries share a
 *     return; the caller passes args in $s0/$s3) — awkward to express in C at all.
 *   - Ghidra mis-analyses it: get_code(0x8002B154) returns only a tiny fragment using unaff_s0/
 *     unaff_s3 (caller-set regs), so there is no faithful whole-function decompile to translate.
 *   - It is the save-data/memcard format, explicitly Phase-3 Q#5 "format still TBD" — a different
 *     subsystem from the file/overlay loader cluster (which IS drafted: CdReadStateMachine,
 *     CdReadSectorReadyCB, StreamLoadStateMachine here + the matched CdReadRequest/CdQueueBusy/…).
 *   - External helpers it calls (uncharacterised): func_800603BC (x20), func_80060614, func_8006023C,
 *     func_80060D9C, func_80060AE0, func_8005FFB4, func_8005FD58, func_80061114/524, func_80016714(bzero).
 * Re-enable / revisit when Q#5 (save/memcard format) is studied: FIRST fix the Ghidra function
 *   boundary (make 0x8002B154 span the whole 1139 ins, or model the 3 entry points), re-decompile,
 *   characterise the func_80060xxx memcard helpers, THEN draft. A wrong faithful-looking draft here
 *   would be worse than this honest stub (P9/G3). The default build is byte-identical via this stub. */

/* The S73 verbatim-asm transcription of SaveLoadRoutine + its four re-emitted jump tables lived
 * here until S75 (cookbook S265 lane; see S434/S447 for the wall history).  Superseded by the C. */


extern u8 D_80075AC0[];

u32 func_8002C320(void) {
    register u32 result __asm__("$8") = 0;
    int count = 0;
    register u32 bit1 __asm__("$14") = 1;
    register u32 bit2 __asm__("$13") = 2;
    register u32 shift __asm__("$7") = 0;
    u8 *base = D_80075AC0;
    u8 *ptr_data = base + 0x10;
    u8 *ptr_check = base + 0x2;
    u8 *ptr_byte = base;
    u32 sum;
    u32 masked;
    int j;
    u16 val;

    for (; count < 4; count++) {
        if (*ptr_byte != 0) {
            val = *(u16 *)ptr_check;
            sum = 0;

            for (j = 0; j < 0x70; j++) {
                sum += ptr_data[j];
            }
            masked = sum & 0xFFFF;

            if (val == masked) {
                result |= bit1 << shift;
            } else {
                result |= bit2 << shift;
            }
        }

        shift += 8;
        ptr_data += 0x80;
        ptr_check += 0x80;
        ptr_byte += 0x80;
    }

    return result;
}

s32 func_8002C3B0(s32 count, u8 *arr) {
    s32 i;
    s32 total = 0;
    for (i = 0; i < count; i++, arr += 0x28) {
        s32 v = *(s32 *)(arr + 0x18);
        s32 t;
        if (v >= 0) {
            t = v;
        } else {
            t = v + 0x1FFF;
        }
        t >>= 13;
        if (v & 0x1FFF) {
            total += t + 1;
        } else {
            total += t;
        }
    }
    return total;
}

