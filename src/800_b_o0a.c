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

extern void PushMatrix();
extern void PopMatrix();
extern s32 rand();
extern s32 getchar();

void func_8002C410(void)
{
    func_80059888(0, 0, 0, 0);
    func_800596F4(0);
    func_800599B8(0, 0);
    MoveImage(0, 0, 0);
    GetClut(0, 0);
    GetTPage(0, 0, 0, 0);
    AddPrim(0, 0);
    func_8005A600(0, 0, 0, 0, 0);
    SetLineF2(0);
    SetLineG2(0);
    SetPolyF3(0);
    SetPolyFT4(0);
    SetSemiTrans(0, 0);
    MulMatrix0(0, 0, 0);
    func_80048D9C(0, 0);
    func_80048EAC(0, 0);
    MulRotMatrix(0);
    SetMulMatrix(0, 0);
    SetMulRotMatrix(0);
    ApplyRotMatrix(0, 0);
    ApplyRotMatrixLV(0, 0);
    func_800484EC(0, 0, 0);
    ApplyMatrixSV(0, 0, 0);
    ApplyTransposeMatrixLV(0, 0, 0);
    func_8004978C(0, 0);
    RotMatrixYXZ(0, 0);
    func_80049CAC(0, 0);
    RotMatrixX(0, 0);
    RotMatrixY(0, 0);
    RotMatrixZ(0, 0);
    func_8004901C(0, 0);
    func_8004974C(0, 0);
    CompMatrix(0, 0, 0);
    CompMatrixLV(0, 0, 0);
    func_8004914C(0);
    func_800491AC(0);
    PushMatrix(0);
    PopMatrix(0);
    ReadRotMatrix(0);
    func_8004921C(0, 0);
    ReadGeomOffset(0, 0);
    func_800491EC(0);
    RotTransPers(0, 0, 0, 0);
    RotTransSV(0, 0, 0);
    Square12(0, 0);
    Square0(0, 0);
    func_800495EC(0, 0, 0);
    RotTransPers4(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    RotNclip4(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    VectorNormalSS(0, 0);
    func_80047D3C(0);
    SquareRoot12(0);
    gteMIMefunc(0, 0, 0, 0);
    func_80047948(0);
    func_8004787C(0);
    csqrt(0);
    ratan2(0, 0);
    SsUtKeyOnV(0, 0, 0, 0, 0, 0, 0, 0);
    SsUtKeyOffV(0);
    SsGetCurrentPoint(0, 0);
    func_8005C324(0, 0, 0);
    func_8005C2C8(0, 0);
    rand(0);
    func_8005C4CC(0);
    getchar(0);
    func_8005C388(0);
    strcpy(0, 0);
}
