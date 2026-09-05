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

/* func_800D12D0 -- md_MAIN_003, -O0 (frame-pointer prologue: sw $fp / addu $fp,$sp,$zero).
 * Direct sibling of func_800D0D6C (src/md_MAIN_003/md_MAIN_003_o0c.c): eight 0x18-byte
 * SPRT-with-own-tpage prims at fixed addresses, addPrim()'d onto OT word[0] of the frame's
 * ordering table (D_800AA60C + gameFrame*0x4000), linked in the order 944, 98C, 92C, 914,
 * 8FC, 8E4, 8CC, 8B4.
 *
 * BANKING NOTE: the subseg md_MAIN_003_jr_800D12D0 builds -O2. This MATCH cannot bank until
 * the function lives in an -O0 object (tools/o0_subsplit.py plus the Makefile "_o0?" glob at
 * Makefile:724, which already covers the md module dirs). Cookbook 362 trap class.
 *
 * -O0 spellings that are load-bearing (inherited from the byte-proven func_800D0D6C, cookbook
 * 261a ADDENDA (b)/(c)/(d)); one NEW one found here:
 *  - "register u8 *base = D_800AF630;" lands in $v0 (caller-saved, no calls), and the
 *    >0x7FFF member access assembles to lui $at,1 + addu $at,$v0,$at + lhu -0x5C2E($at).
 *  - "0x4000" and "20" are MULTIPLIES, not shifts: expand_mult's copy_to_mode_reg emits the
 *    "addu $a0,$v1,$zero" copy of the index before the sll.
 *  - the OT address is index * 0x4000 + (u32)D_800AA60C, base CAST TO AN INTEGER and written
 *    SECOND (a pointer-typed spelling routes through pointer_int_sum and swaps the operands).
 *  - the 24-bit "addr" bitfield reproduces libgpu setaddr()/getaddr() AND fixes the operand
 *    order of the final "or".
 *  - every sh destination is s16, not u16 (a u16 lvalue turns -0x140/-0xF0/-0xA0/-0xBE into
 *    "ori $v1,$zero,imm" instead of the target's "addiu $v1,$zero,-imm").
 *  - NEW HERE: the three colour bytes come from ONE "lbu D_800EC890" feeding THREE "sb"s, so
 *    they are a CHAINED assignment "B+8 = B+9 = B+10 = D_800EC890;" -- gcc expands innermost
 *    first, which produces the target's B+10, B+9, B+8 store order. Three separate statements
 *    would emit three loads (+16 instructions).
 */

extern u8 D_800AF630[];
extern u8 D_800AA60C[];

extern u8  D_800EC890;
extern s16 D_800EC894;

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

extern u32 D_800EC8E4;
extern u8  D_800EC8E7;
extern u32 D_800EC8E8;
extern u8  D_800EC8EC;
extern u8  D_800EC8ED;
extern u8  D_800EC8EE;
extern u8  D_800EC8EF;
extern s16 D_800EC8F0;
extern s16 D_800EC8F2;
extern u8  D_800EC8F4;
extern u8  D_800EC8F5;
extern s16 D_800EC8F6;
extern s16 D_800EC8F8;
extern s16 D_800EC8FA;

extern u32 D_800EC8FC;
extern u8  D_800EC8FF;
extern u32 D_800EC900;
extern u8  D_800EC904;
extern u8  D_800EC905;
extern u8  D_800EC906;
extern u8  D_800EC907;
extern s16 D_800EC908;
extern s16 D_800EC90A;
extern u8  D_800EC90C;
extern u8  D_800EC90D;
extern s16 D_800EC90E;
extern s16 D_800EC910;
extern s16 D_800EC912;

extern u32 D_800EC914;
extern u8  D_800EC917;
extern u32 D_800EC918;
extern u8  D_800EC91C;
extern u8  D_800EC91D;
extern u8  D_800EC91E;
extern u8  D_800EC91F;
extern s16 D_800EC920;
extern s16 D_800EC922;
extern u8  D_800EC924;
extern u8  D_800EC925;
extern s16 D_800EC926;
extern s16 D_800EC928;
extern s16 D_800EC92A;

extern u32 D_800EC92C;
extern u8  D_800EC92F;
extern u32 D_800EC930;
extern u8  D_800EC934;
extern u8  D_800EC935;
extern u8  D_800EC936;
extern u8  D_800EC937;
extern s16 D_800EC938;
extern s16 D_800EC93A;
extern u8  D_800EC93C;
extern u8  D_800EC93D;
extern s16 D_800EC93E;
extern s16 D_800EC940;
extern s16 D_800EC942;

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

void func_800D12D0(void) {
    typedef struct {
        unsigned int addr : 24;
        unsigned int len : 8;
    } PrimTag;

    register u8 *base = D_800AF630;

    D_800EC8B7 = 5;
    D_800EC8B8 = 0xE100008A;
    D_800EC8BF = 0x64;
    D_800EC8BC = D_800EC8BD = D_800EC8BE = D_800EC890;
    D_800EC8C0 = -0x140;
    D_800EC8C2 = -0xF0;
    D_800EC8C4 = 0;
    D_800EC8C5 = 0x10;
    D_800EC8C6 = 0x7800;
    D_800EC8C8 = 0x100;
    D_800EC8CA = 0xF0;

    D_800EC8CF = 5;
    D_800EC8D0 = 0xE100008C;
    D_800EC8D7 = 0x64;
    D_800EC8D4 = D_800EC8D5 = D_800EC8D6 = D_800EC890;
    D_800EC8D8 = -0x40;
    D_800EC8DA = -0xF0;
    D_800EC8DC = 0;
    D_800EC8DD = 0x10;
    D_800EC8DE = 0x7800;
    D_800EC8E0 = 0x100;
    D_800EC8E2 = 0xF0;

    D_800EC8E7 = 5;
    D_800EC8E8 = 0xE100008E;
    D_800EC8EF = 0x64;
    D_800EC8EC = D_800EC8ED = D_800EC8EE = D_800EC890;
    D_800EC8F0 = 0xC0;
    D_800EC8F2 = -0xF0;
    D_800EC8F4 = 0;
    D_800EC8F5 = 0x10;
    D_800EC8F6 = 0x7800;
    D_800EC8F8 = 0x80;
    D_800EC8FA = 0xF0;

    D_800EC8FF = 5;
    D_800EC900 = 0xE100009A;
    D_800EC907 = 0x64;
    D_800EC904 = D_800EC905 = D_800EC906 = D_800EC890;
    D_800EC908 = -0x140;
    D_800EC90A = 0;
    D_800EC90C = 0;
    D_800EC90D = 0;
    D_800EC90E = 0x7800;
    D_800EC910 = 0x100;
    D_800EC912 = 0xF0;

    D_800EC917 = 5;
    D_800EC918 = 0xE100009C;
    D_800EC91F = 0x64;
    D_800EC91C = D_800EC91D = D_800EC91E = D_800EC890;
    D_800EC920 = -0x40;
    D_800EC922 = 0;
    D_800EC924 = 0;
    D_800EC925 = 0;
    D_800EC926 = 0x7800;
    D_800EC928 = 0x100;
    D_800EC92A = 0xF0;

    D_800EC92F = 5;
    D_800EC930 = 0xE100009E;
    D_800EC937 = 0x64;
    D_800EC934 = D_800EC935 = D_800EC936 = D_800EC890;
    D_800EC938 = 0xC0;
    D_800EC93A = 0;
    D_800EC93C = 0;
    D_800EC93D = 0;
    D_800EC93E = 0x7800;
    D_800EC940 = 0x80;
    D_800EC942 = 0xF0;

    D_800EC947 = 5;
    D_800EC948 = 0xE100000F;
    D_800EC94F = 0x64;
    D_800EC94C = D_800EC94D = D_800EC94E = D_800EC890;
    D_800EC950 = -0xA0;
    D_800EC952 = 0x64;
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
    D_800EC994 = D_800EC995 = D_800EC996 = D_800EC890;
    D_800EC998 = -0xBE;
    D_800EC99A = D_800EC894 * 20 + 0x64;
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

    ((PrimTag *)&D_800EC92C)->addr =
        ((PrimTag *)(*(u16 *)(base + 0xA3D2) * 0x4000 + (u32)D_800AA60C))->addr;
    ((PrimTag *)(*(u16 *)(base + 0xA3D2) * 0x4000 + (u32)D_800AA60C))->addr =
        (u32)&D_800EC92C;

    ((PrimTag *)&D_800EC914)->addr =
        ((PrimTag *)(*(u16 *)(base + 0xA3D2) * 0x4000 + (u32)D_800AA60C))->addr;
    ((PrimTag *)(*(u16 *)(base + 0xA3D2) * 0x4000 + (u32)D_800AA60C))->addr =
        (u32)&D_800EC914;

    ((PrimTag *)&D_800EC8FC)->addr =
        ((PrimTag *)(*(u16 *)(base + 0xA3D2) * 0x4000 + (u32)D_800AA60C))->addr;
    ((PrimTag *)(*(u16 *)(base + 0xA3D2) * 0x4000 + (u32)D_800AA60C))->addr =
        (u32)&D_800EC8FC;

    ((PrimTag *)&D_800EC8E4)->addr =
        ((PrimTag *)(*(u16 *)(base + 0xA3D2) * 0x4000 + (u32)D_800AA60C))->addr;
    ((PrimTag *)(*(u16 *)(base + 0xA3D2) * 0x4000 + (u32)D_800AA60C))->addr =
        (u32)&D_800EC8E4;

    ((PrimTag *)&D_800EC8CC)->addr =
        ((PrimTag *)(*(u16 *)(base + 0xA3D2) * 0x4000 + (u32)D_800AA60C))->addr;
    ((PrimTag *)(*(u16 *)(base + 0xA3D2) * 0x4000 + (u32)D_800AA60C))->addr =
        (u32)&D_800EC8CC;

    ((PrimTag *)&D_800EC8B4)->addr =
        ((PrimTag *)(*(u16 *)(base + 0xA3D2) * 0x4000 + (u32)D_800AA60C))->addr;
    ((PrimTag *)(*(u16 *)(base + 0xA3D2) * 0x4000 + (u32)D_800AA60C))->addr =
        (u32)&D_800EC8B4;
}


#include "common.h"

extern s32 D_800D3630[];
extern u8  D_800D3618[];
extern u8  D_800D3620[];
extern s32 D_800D3624[];

extern void func_8001534C(s32 idx, s32 a1, s16 x, s16 y, u8 arg4, u8 arg5);

void func_800D1D14(s32 arg0, s32 arg1) {
    if (arg1 == 0) {
        func_8001534C(*(s16 *) &D_800D3630[arg0], (s32) D_800D3618, 0, 0, 0, 0);
    } else {
        func_8001534C(*(s16 *) &D_800D3630[arg0], D_800D3624[arg0], 0x50, D_800D3620[arg0], 0, 0);
    }
}


