#include "common.h"

/* ==== Phase-26 §8b carried decl layer (jr_isolate_all.py) ===================
 * The file-scope decl environment from earlier code regions of this object —
 * file-local types, col-0 decls, DEFINE_func macro externs, and each earlier
 * definition's implied prototype (types first, then decls in original order).
 * Decls emit no code => byte-neutral. See cookbook §8c. */
extern void (*D_800D3598[])(void);
extern void func_800CEED0(void);
extern u8 D_800B9A11;
extern s32 D_800EC694;
extern s32 D_800EC68C;
extern s16 D_800EC678;
extern s32 D_800EC67C;
extern s32 D_800EC680;
extern s32 D_800EC690;
extern s32 D_800EC698;
extern s32 D_800EC688;
extern s32 D_800EC684;
extern u8 D_800DA48C[];
extern void func_8001C044(void);
extern void func_80015310(void);
extern void func_8002D858(void);
extern s32 func_800D1E18(void);
extern void func_800CFB3C();
extern void func_800118AC(void);
extern void func_800CEF04(void);
extern void func_8001A9F8(s32 a0);
extern s32 CdReadRequest(s32 *a0, void *a1, s32 a2, s32 a3);
extern s32 D_800AE858;
extern void func_800CEFBC(void);
extern s32 D_800B9A18;
extern s32 D_800EC6A0;
extern s32 D_800EC6A4;
extern unsigned char D_800DA48C[];
extern void func_800D1E58(void);
extern void func_800CFFEC(void);
extern void func_800CF010(void);
extern void func_800CF3E8(void);
extern s32 func_800CFC1C();
extern void func_800CF078(void);
extern s32 func_800149E0(s32);
extern s32 func_80014B10(s32);
extern void func_8002D4C8(s32, s32);
extern void func_800CFE00(void);
extern void func_800CF104(void);
extern void func_80059888(void *a0, s32 a1, s32 a2, s32 a3);
extern void func_800CF300(void);
extern void func_800146B0(s32);
extern void func_800118AC();
extern void func_800CF370(void);
extern s8 D_800D52BC[];
extern u16 D_800B99E6;
extern u16 D_800B99E8;
extern void func_800183E0(s32 a0);
extern void func_800CF3A4(void);
extern s32 D_800EC69C;
extern void func_800599B8();
extern void func_800CFB3C(u16 *arg0);
extern s32 func_800CFC1C(u16 *param_1);
extern void func_800599B8(u16 *, u16 *);
extern u16 D_800AF7BC;
extern u16 D_800AF7BE;
extern u16 D_800AF7C0;
extern void GsInitGraph2(s32 w, s32 h, s32 mode, s32 a3, s32 st);
extern void func_80053EEC(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80059234(s32 a0);
extern void func_80053218(void);
extern void func_800147B8(void);
extern u8 D_800AF6DC;
extern u8 D_800AF680;
/* ==== end §8b carried decl layer ==== */

/* func_800D0D6C -- md_MAIN_003, -O0 (frame-pointer prologue; the subseg builds -O2,
 * so banking needs the _o0 carve or the §265 verbatim-asm form -- ADDENDUM (d) to §261a).
 *
 * Builds four 0x18-byte SPRT-with-own-tpage prims at fixed addresses and addPrim()s
 * them onto OT word[0] of the frame's ordering table (D_800AA60C + gameFrame*0x4000),
 * in the order prim3, prim4, prim2, prim1. Direct sibling of boot's func_8001212C.
 *
 * -O0 spellings that are load-bearing (all byte-proven, reloc_identity AGREE 76/76):
 *  - `register u8 *base = D_800AF630;` far-offset base: ADDENDUM (c) to §261a -- lands
 *    caller-saved ($v0) with no calls, and the >0x7FFF member access assembles to
 *    lui $at,1 / addu $at,$v0,$at / lhu -0x5C2E($at).
 *  - `* 0x4000` and `* 20` are MULTIPLIES, not shifts: expand_mult's
 *    `accum = copy_to_mode_reg (mode, op0)` is what emits the `addu $a0,$v1,$zero`
 *    copy of the index before the sll (ADDENDUM (b) to §261a, mirror direction).
 *    `<< 14` folds that copy away (-1 ins each, 4 sites).
 *  - the OT address is `index * 0x4000 + (u32)D_800AA60C`, with the base CAST TO AN
 *    INTEGER and written SECOND. Any pointer-typed spelling routes through c-typeck's
 *    pointer_int_sum, which puts the pointer operand FIRST unconditionally (it swaps
 *    `int + ptr` back to `ptr + int`), emitting the lui/addiu anchor before the sll.
 *  - the 24-bit `addr` bitfield reproduces libgpu's setaddr()/getaddr() RMW and, more
 *    importantly, FIXES THE OPERAND ORDER of the final `or`: store_fixed_bit_field
 *    expands the VALUE first and the destination read-modify second, then emits
 *    `ior(masked_dest, value)`. Hand-written `X = (X & 0xFF000000) | (Y & 0xFFFFFF)`
 *    gets the reverse order and the whole tail drifts (162-ins residual on the prior draft).
 *  - every `sh` destination is s16, not u16: a u16 lvalue truncates -0xA0 to the
 *    unsigned constant 0xFF60, which assembles as `ori $v1,$zero,0xff60` instead of
 *    the target's `addiu $v1,$zero,-0xA0` (4 sites).
 *  - the OT expression is spelled out at each of the 8 uses, not held in a local:
 *    the target frame is 8 bytes (only the $fp save), so no local may take a slot.
 */

extern u8 D_800AF630[];
extern u8 D_800AA60C[];

extern u32 D_800EC8B4;
extern u8  D_800EC8B7;
extern u32 D_800EC8B8;
extern u8  D_800EC8BC;
extern u8  D_800EC8BD;
extern u8  D_800EC8BE;
extern u8  D_800EC8BF;
extern s16 D_800EC8C0;
extern s16 D_800EC8C2;
extern u8  D_800EC8C4;
extern u8  D_800EC8C5;
extern s16 D_800EC8C6;
extern s16 D_800EC8C8;
extern s16 D_800EC8CA;

extern u32 D_800EC8CC;
extern u8  D_800EC8CF;
extern u32 D_800EC8D0;
extern u8  D_800EC8D4;
extern u8  D_800EC8D5;
extern u8  D_800EC8D6;
extern u8  D_800EC8D7;
extern s16 D_800EC8D8;
extern s16 D_800EC8DA;
extern u8  D_800EC8DC;
extern u8  D_800EC8DD;
extern s16 D_800EC8DE;
extern s16 D_800EC8E0;
extern s16 D_800EC8E2;

extern s16 D_800EC894;

extern u32 D_800EC944;
extern u8  D_800EC947;
extern u32 D_800EC948;
extern u8  D_800EC94C;
extern u8  D_800EC94D;
extern u8  D_800EC94E;
extern u8  D_800EC94F;
extern s16 D_800EC950;
extern s16 D_800EC952;
extern u8  D_800EC954;
extern u8  D_800EC955;
extern s16 D_800EC956;
extern s16 D_800EC958;
extern s16 D_800EC95A;

extern u32 D_800EC98C;
extern u8  D_800EC98F;
extern u32 D_800EC990;
extern u8  D_800EC994;
extern u8  D_800EC995;
extern u8  D_800EC996;
extern u8  D_800EC997;
extern s16 D_800EC998;
extern s16 D_800EC99A;
extern u8  D_800EC99C;
extern u8  D_800EC99D;
extern s16 D_800EC99E;
extern s16 D_800EC9A0;
extern s16 D_800EC9A2;

void func_800D0D6C(void) {
    typedef struct {
        unsigned int addr : 24;
        unsigned int len : 8;
    } PrimTag;

    register u8 *base = D_800AF630;

    D_800EC8B7 = 5;
    D_800EC8B8 = 0xE100010A;
    D_800EC8BF = 0x64;
    D_800EC8BE = 0x80;
    D_800EC8BD = 0x80;
    D_800EC8BC = 0x80;
    D_800EC8C0 = -0xA0;
    D_800EC8C2 = -0x78;
    D_800EC8C4 = 0;
    D_800EC8C5 = 0;
    D_800EC8C6 = 0x7800;
    D_800EC8C8 = 0x100;
    D_800EC8CA = 0xF0;

    D_800EC8CF = 5;
    D_800EC8D0 = 0xE100010E;
    D_800EC8D7 = 0x64;
    D_800EC8D6 = 0x80;
    D_800EC8D5 = 0x80;
    D_800EC8D4 = 0x80;
    D_800EC8D8 = 0x60;
    D_800EC8DA = -0x78;
    D_800EC8DC = 0;
    D_800EC8DD = 0;
    D_800EC8DE = 0x7800;
    D_800EC8E0 = 0x40;
    D_800EC8E2 = 0xF0;

    D_800EC947 = 5;
    D_800EC948 = 0xE100000F;
    D_800EC94F = 0x64;
    D_800EC94E = 0x80;
    D_800EC94D = 0x80;
    D_800EC94C = 0x80;
    D_800EC950 = -0x50;
    D_800EC952 = 0x20;
    D_800EC954 = 0;
    D_800EC955 = 0;
    D_800EC956 = 0x7800;
    D_800EC958 = 0x78;
    D_800EC95A = 0x3C;
    D_800EC956 = 0x7A00;

    ((PrimTag *)&D_800EC944)->addr =
        ((PrimTag *)(*(u16 *)(base + 0xA3D2) * 0x4000 + (u32)D_800AA60C))->addr;
    ((PrimTag *)(*(u16 *)(base + 0xA3D2) * 0x4000 + (u32)D_800AA60C))->addr =
        (u32)&D_800EC944;

    D_800EC98F = 5;
    D_800EC990 = 0xE100000F;
    D_800EC997 = 0x64;
    D_800EC996 = 0x80;
    D_800EC995 = 0x80;
    D_800EC994 = 0x80;
    D_800EC998 = -0x6E;
    D_800EC99A = D_800EC894 * 20 + 0x20;
    D_800EC99C = 0;
    D_800EC99D = 0x3C;
    D_800EC99E = 0x7800;
    D_800EC9A0 = 0x1E;
    D_800EC9A2 = 0x14;
    D_800EC99E = 0x7A00;

    ((PrimTag *)&D_800EC98C)->addr =
        ((PrimTag *)(*(u16 *)(base + 0xA3D2) * 0x4000 + (u32)D_800AA60C))->addr;
    ((PrimTag *)(*(u16 *)(base + 0xA3D2) * 0x4000 + (u32)D_800AA60C))->addr =
        (u32)&D_800EC98C;

    ((PrimTag *)&D_800EC8CC)->addr =
        ((PrimTag *)(*(u16 *)(base + 0xA3D2) * 0x4000 + (u32)D_800AA60C))->addr;
    ((PrimTag *)(*(u16 *)(base + 0xA3D2) * 0x4000 + (u32)D_800AA60C))->addr =
        (u32)&D_800EC8CC;

    ((PrimTag *)&D_800EC8B4)->addr =
        ((PrimTag *)(*(u16 *)(base + 0xA3D2) * 0x4000 + (u32)D_800AA60C))->addr;
    ((PrimTag *)(*(u16 *)(base + 0xA3D2) * 0x4000 + (u32)D_800AA60C))->addr =
        (u32)&D_800EC8B4;
}

