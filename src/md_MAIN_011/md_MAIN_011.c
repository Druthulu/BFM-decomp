#include "common.h"

#include "common.h"

extern u8 D_800AF630[];

typedef struct { void (*fn)(void); } FnEntry;
extern FnEntry D_800D4C54[];

void func_800CEE74(void) {
    register u8 *base = (u8 *)D_800AF630;
    if (*(u16 *)(base + 0xA3B4) < 5u) {
        D_800D4C54[*(u16 *)(base + 0xA3B4)].fn();
    }
}


void func_800CEF00(void) {
    typedef struct { s32 m; } S70;
    extern u8 D_800AF630[];
    extern u8 D_800D31FC[];
    extern u8 D_800D31F8[];
    extern u8 D_800D3248[];
    extern u8 D_800D3208[];
    extern u8 D_800D3214[];
    extern u8 D_800D3220[];
    extern u8 D_800D3228[];
    extern u8 D_800D3230[];
    extern u8 D_800D3238[];
    extern u8 D_800D3250[];
    extern u8 D_800D3258[];
    extern u8 D_800D3264[];
    extern u8 D_800D3278[];
    extern u8 D_800D3284[];
    extern s32 D_800D4C88;
    extern s32 D_800D4C8C;
    extern s32 D_800D4C90;
    extern s32 D_800D4C94;
    extern u8 D_800D4B64[];
    extern S70 D_800D4B70[];
    extern u16 D_800D4C80;
    extern u16 D_800D4C84;
    extern u16 D_800D4CA4;
    extern u16 D_800D4CA0;
    extern u16 D_800D4C9C;
    extern u16 D_800D4C98;
    extern s32 D_800D3344;
    register u8 *v0 = D_800AF630;

    v0[0xA3E1] = 1;
    func_8001C044();
    func_80015310();
    func_80011B7C(0);
    func_8001534C(0, D_800D31FC, 0x40, 0x1E, 0, 0);
    func_8001534C(1, D_800D31F8, 0x34, 0x46, 0, 0);
    func_8001534C(9, D_800D3248, 0x40, 0x46, 0, 0);
    func_8001534C(2, D_800D3208, 0x40, 0x5E, 0, 0);
    func_8001534C(3, D_800D3214, 0x40, 0x6A, 0, 0);
    func_8001534C(4, D_800D3220, 0x40, 0x76, 0, 0);
    func_8001534C(5, D_800D3228, 0x40, 0x82, 0, 0);
    func_8001534C(6, D_800D3230, 0x40, 0x8E, 0, 0);
    func_8001534C(7, D_800D3238, 0x40, 0x9A, 0, 0);
    func_8001534C(0xA, D_800D3250, 0x74, 0x46, 0, 0);
    func_8001534C(0xB, D_800D3258, 0x74, 0x52, 0, 0);
    func_8001534C(0xE, D_800D3264, 0x40, 0xA6, 0, 0);
    func_8001534C(0xF, D_800D3278, 0x40, 0xB2, 0, 0);
    func_8001534C(0x10, D_800D3284, 0x40, 0xBE, 0, 0);
    D_800D4C88 = 0;
    D_800D4C8C = 0;
    D_800D4C90 = 0;
    D_800D4C94 = 0;
    *(u16 *)&v0[0xA3DE] = 0;
    func_8001534C(0xC, &D_800D4B64[D_800D4C88 * 20], 0xA4, 0x46, 0x44, 0);
    func_8001534C(0xD, D_800D4B70[D_800D4C88 * 5].m + D_800D4C8C * 36, 0xA4, 0x52, 0x44, 0);
    D_800D4C80 = 0;
    D_800D4C84 = 0;
    D_800D4CA4 = 0;
    D_800D4CA0 = 0;
    D_800D4C9C = 0;
    D_800D4C98 = 0;
    func_80029514(D_800D3344);
    func_800118AC();
}


INCLUDE_RODATA("asm/md_MAIN_011/nonmatchings/md_MAIN_011", D_800CEDF8);

INCLUDE_ASM("asm/md_MAIN_011/nonmatchings/md_MAIN_011", func_800CF28C);

void func_800CFB88(void) {
    extern s32 D_800D4C90;
    extern void *D_800D32F8[];
    extern void func_8001534C(int, void *, int, int, int, int);
    func_8001534C(0x1C, D_800D32F8[D_800D4C90], 0x78, 0x82, 0, 0);
}


void func_800CFBF0(void) {
    extern s32 D_800D4C94;
    extern s32 D_800D3314[];
    func_8001534C(0x1A, D_800D3314[D_800D4C94], 0x90, 0x9A, 0, 0);
}


extern s32 func_800167F0(s32 a0);

void func_800CFC58(void) {
    if ((func_800167F0(4) & 0xffff) != 0) {
        func_800118AC();
        func_80011B7C(0);
        func_8001C044();
        func_80015310();
    }
}


void func_800CFCBC(void) {
    extern s32 D_800D4C94;
    extern void func_800D0964(void);
    extern void func_800D0BDC(void);
    extern void func_800D1254(void);
    extern void func_800D1B00(void);
    extern void func_800D235C(void);
    extern void func_800D2BC4(void);

    if (D_800D4C94 != 0) {
        if (D_800D4C94 > 0) {
            func_800D0964();
        }
        if (D_800D4C94 >= 2) {
            func_800D0BDC();
        }
        if (D_800D4C94 >= 3) {
            func_800D1254();
        }
        if (D_800D4C94 >= 4) {
            func_800D1B00();
        }
        if (D_800D4C94 >= 5) {
            func_800D235C();
        }
        if (D_800D4C94 >= 6) {
            func_800D2BC4();
        }
    }
}


INCLUDE_ASM("asm/md_MAIN_011/nonmatchings/md_MAIN_011", func_800CFDB4);

extern u8 D_800AF630[];

void func_800D03F8(void) {
    register u8 *v0 = D_800AF630;

    *(u16 *)(v0 + 0xA3B6) = 1;
}


void func_800D0430(void) {
}




extern s16 D_800D4C80;
extern FnEntry D_800D4C68[];

void func_800D0450(void) {
    if (D_800D4C80 < 5) {
        D_800D4C68[D_800D4C80].fn();
    }
}


extern void func_80136EC4(void);

void func_800D04C4(void) {
    func_80136EC4();
}


INCLUDE_ASM("asm/md_MAIN_011/nonmatchings/md_MAIN_011", func_800D04F4);

s32 func_800D0828(s32 arg0) {
    return 1;
}


void func_800D0858(void) {
    extern s32 func_800149E0(s32 a0);
    extern s32 func_80014B10(s32 a0);
    extern u16 D_800D4C9C;
    extern u16 D_800D4C98;
    extern u16 D_800D4CA0;
    extern u16 D_800D4CA4;

    D_800D4C9C = func_800149E0(0);
    D_800D4C98 = func_80014B10(0);
    if (D_800D4C98 != 0) {
        if (D_800D4C98 == D_800D4CA0) {
            if (--D_800D4CA4 == 0) {
                D_800D4C9C = D_800D4C98 & 0xF000;
                D_800D4CA4 = 3;
            }
        } else {
            D_800D4CA0 = D_800D4C98;
            D_800D4CA4 = 6;
        }
    } else {
        D_800D4CA0 = 0;
        D_800D4CA4 = 12;
    }
}


void func_800D0964(void) {
    typedef struct {
        u32 pad00;      /* 0x00 */
        u32 unk04;      /* 0x04 */
        u32 unk08;      /* 0x08 */
        u32 unk0C;      /* 0x0C */
        u32 unk10;      /* 0x10 */
        u32 unk14;      /* 0x14 */
        u32 unk18;      /* 0x18 */
        u32 unk1C;      /* 0x1C */
        u32 unk20;      /* 0x20 */
        u32 unk24;      /* 0x24 */
        u32 unk28;      /* 0x28 */
        u32 unk2C;      /* 0x2C */
        u32 unk30;      /* 0x30 */
        s16 unk34;      /* 0x34 */
        u8  unk36;      /* 0x36 */
        u8  unk37;      /* 0x37 */
        s16 unk38;      /* 0x38 */
        s16 unk3A;      /* 0x3A */
        s16 unk3C;      /* 0x3C */
        s16 unk3E;      /* 0x3E */
        s16 unk40;      /* 0x40 */
        u8  unk42;      /* 0x42 */
        u8  unk43;      /* 0x43 */
        u8  unk44;      /* 0x44 */
        u8  unk45;      /* 0x45 */
        u8  unk46;      /* 0x46 */
        u8  unk47;      /* 0x47 */
        u8  unk48;      /* 0x48 */
        u8  unk49;      /* 0x49 */
        u8  unk4A;      /* 0x4A */
        u8  unk4B;      /* 0x4B */
        u8  unk4C;      /* 0x4C */
        u8  pad4D[3];   /* 0x4D */
        u32 unk50;      /* 0x50 */
        u32 unk54;      /* 0x54 */
        u32 unk58;      /* 0x58 */
        u32 unk5C;      /* 0x5C */
        u32 unk60;      /* 0x60 */
        u32 unk64;      /* 0x64 */
        u8  unk68;      /* 0x68 */
        u8  pad69[3];   /* 0x69 */
        u32 unk6C;      /* 0x6C */
        u32 unk70;      /* 0x70 */
        u32 unk74;      /* 0x74 */
        u32 unk78;      /* 0x78 */
        u32 unk7C;      /* 0x7C */
        u32 unk80;      /* 0x80 */
        u32 unk84;      /* 0x84 */
        u32 unk88;      /* 0x88 */
        u32 unk8C;      /* 0x8C */
        u32 unk90;      /* 0x90 */
        u32 unk94;      /* 0x94 */
    } Gs_80078E78_init;
    extern u8 D_80078E78[];
    Gs_80078E78_init *p = (Gs_80078E78_init *)D_80078E78;

    p->unk04 = 0;
    p->unk08 = 0;
    p->unk0C = 0;
    p->unk10 = 0;
    p->unk14 = 100;
    p->unk18 = 0x01FE0000;
    p->unk1C = 0;
    p->unk20 = 0;
    p->unk24 = 0x00640000;
    p->unk28 = 0;
    p->unk2C = 0x00640000;
    p->unk30 = 0;
    p->unk34 = 1;
    p->unk36 = 1;
    p->unk37 = 1;
    p->unk38 = 0x81E;
    p->unk3A = 150;
    p->unk3C = 150;
    p->unk3E = 150;
    p->unk40 = 150;
    p->unk42 = 0;
    p->unk43 = 0;
    p->unk44 = 3;
    p->unk45 = 0;
    p->unk46 = 0;
    p->unk47 = 0;
    p->unk48 = 0;
    p->unk49 = 0;
    p->unk4A = 0;
    p->unk4B = 0;
    p->unk4C = 0;
    p->unk50 = 0;
    p->unk54 = 0;
    p->unk58 = 0;
    p->unk5C = 0;
    p->unk60 = 0;
    p->unk64 = 0;
    p->unk68 = 0;
    p->unk6C = 0;
    p->unk70 = 0;
    p->unk74 = 0;
    p->unk78 = 0;
    p->unk7C = 0;
    p->unk80 = 0;
    p->unk84 = 0;
    p->unk88 = 0;
    p->unk8C = 0;
    p->unk90 = 0;
    p->unk94 = 0;
}


void func_800D0BDC(void) {
    typedef struct {
        s32 pad00;
        s32 unk04;
        s32 unk08;
        s32 unk0C;
        s32 unk10;
        s32 unk14;
        s32 unk18;
        s32 unk1C;
        s32 unk20;
        s32 unk24;
        s32 unk28;
        s32 unk2C;
        s32 unk30;
        s16 unk34;
        u8 unk36;
        u8 unk37;
        s16 unk38;
        s16 unk3A;
        s16 unk3C;
        s16 unk3E;
        s16 unk40;
        u8 unk42;
        u8 unk43;
        u8 unk44;
        u8 unk45;
        u8 unk46;
        u8 unk47;
        u8 unk48;
        u8 unk49;
        u8 unk4A;
        u8 unk4B;
        u8 unk4C;
        s32 unk50;
        s32 unk54;
        s32 unk58;
        s32 unk5C;
        s32 unk60;
        s32 unk64;
        u8 unk68;
        s32 unk6C;
        s32 unk70;
        s32 unk74;
        s32 unk78;
        s32 unk7C;
        s32 unk80;
        s32 unk84;
        s32 unk88;
        s32 unk8C;
        s32 unk90;
        s32 unk94;
    } S;
    extern u8 D_80078E78[];
    extern u8 D_8010F476;
    extern u8 D_8010F47E;
    extern u8 D_8010F486;
    extern u8 D_8010F48E;
    extern u8 D_8010F496;
    extern u8 D_8010F49E;
    extern u16 D_8010F474;
    extern u16 D_8010F47C;
    extern u16 D_8010F484;
    extern u16 D_8010F48C;
    extern u16 D_8010F494;
    extern u16 D_8010F49C;
    extern u16 D_800A6588;
    extern u16 D_800A658A;
    extern u16 D_800A658C;
    extern u16 D_800A658E;
    extern u16 D_800A6590;
    extern u16 D_800A6592;
    extern void func_80029124(s32, s32);
    extern void func_800291A0(s32, s32);
    S *p = (S *)D_80078E78;

    p->unk04 = 0;
    p->unk08 = 0xA;
    p->unk0C = 0;
    p->unk10 = 0;
    p->unk14 = 0x64;
    p->unk18 = 0x01FE0000;
    p->unk1C = 0;
    p->unk20 = 0;
    p->unk24 = 0x00640000;
    p->unk28 = 0;
    p->unk2C = 0x00640000;
    p->unk30 = 0;
    p->unk34 = 1;
    p->unk36 = 1;
    p->unk37 = 1;
    p->unk38 = 0x81E;
    p->unk3A = 0x96;
    p->unk3C = 0x96;
    p->unk3E = 0x96;
    p->unk40 = 0x96;
    p->unk42 = 0;
    p->unk43 = 0;
    p->unk44 = 3;
    p->unk45 = 0;
    p->unk46 = 0;
    p->unk47 = 0;
    p->unk48 = 1;
    p->unk49 = 0;
    p->unk4A = 0;
    p->unk4B = 0;
    p->unk4C = 0;
    p->unk50 = 0;
    p->unk54 = 0;
    p->unk58 = 0;
    p->unk5C = 0;
    p->unk60 = 0;
    p->unk64 = 0;
    p->unk68 = 0;
    p->unk6C = 3;
    p->unk70 = 0;
    p->unk74 = 3;
    p->unk78 = 0;
    p->unk7C = 3;
    p->unk80 = 0;
    p->unk84 = 3;
    p->unk88 = 0;
    p->unk8C = 0;
    p->unk90 = 0x6D6;
    p->unk94 = 0x6D6;
    func_80029124(0x7F, 1);
    func_80029124(0x80, 1);
    func_80029124(0x84, 1);
    func_800291A0(0x3B, 3);
    func_800291A0(0x3C, 3);
    func_800291A0(0x3D, 3);
    func_800291A0(0x3E, 3);
    func_800291A0(0x3F, 3);
    func_800291A0(0x40, 0);
    func_800291A0(0x41, 0);
    func_800291A0(0x42, 0);
    func_800291A0(0x43, 0);
    func_800291A0(0x44, 0);
    func_800291A0(0x45, 0);
    func_800291A0(0x46, 0);
    func_800291A0(0x47, 0);
    func_800291A0(0x48, 0);
    func_800291A0(0x49, 0);
    func_800291A0(0x4A, 0);
    func_800291A0(0x4B, 0);
    func_800291A0(0x4C, 0);
    func_800291A0(0x4D, 0);
    func_800291A0(0x4E, 0);
    func_800291A0(0x4F, 0);
    func_800291A0(0x50, 0);
    func_800291A0(0x51, 0);
    func_800291A0(0x52, 0);
    func_800291A0(0x53, 0);
    func_800291A0(0x54, 0);
    func_800291A0(0x55, 0);
    func_800291A0(0x56, 0);
    func_800291A0(0x57, 0);
    func_800291A0(0x58, 0);
    func_800291A0(0x59, 0);
    func_800291A0(0x5A, 0);
    func_800291A0(0x5B, 0);
    func_800291A0(0x5C, 0);
    func_800291A0(0x5D, 0);
    func_800291A0(0x5E, 0);
    func_800291A0(0x5F, 0);
    func_800291A0(0x60, 0);
    func_800291A0(0x61, 0);
    func_800291A0(0x62, 0);
    func_800291A0(0x2E, 1);
    func_800291A0(0x63, (D_8010F476 | 0x80) & 0xFF);
    func_800291A0(0x65, (D_8010F47E | 0x80) & 0xFF);
    func_800291A0(0x66, (D_8010F486 | 0x80) & 0xFF);
    func_800291A0(0x67, (D_8010F48E | 0x80) & 0xFF);
    func_800291A0(0x68, (D_8010F496 | 0x80) & 0xFF);
    func_800291A0(0x69, (D_8010F49E | 0x80) & 0xFF);
    D_800A6588 = D_8010F474;
    D_800A658A = D_8010F47C;
    D_800A658C = D_8010F484;
    D_800A658E = D_8010F48C;
    D_800A6590 = D_8010F494;
    D_800A6592 = D_8010F49C;
}


INCLUDE_ASM("asm/md_MAIN_011/nonmatchings/md_MAIN_011", func_800D1254);

#include "common.h"

extern u8 D_80078E78[];
extern void func_80029124(s32 a0, s32 a1);
extern void func_800291A0(s32 a0, s32 a1);
extern u8 D_8010F4D6;
extern u8 D_8010F4DE;
extern u8 D_8010F4EE;
extern u8 D_8010F4E6;
extern u8 D_8010F5AE;
extern u8 D_8010F4F6;
extern u8 D_8010F4FE;
extern u16 D_8010F4D4;
extern u16 D_8010F4DC;
extern u16 D_8010F4EC;
extern u16 D_8010F4E4;
extern u16 D_8010F5AC;
extern u16 D_8010F4F4;
extern u16 D_8010F4FC;
extern u16 D_800A65A0;
extern u16 D_800A65A2;
extern u16 D_800A65A6;
extern u16 D_800A65A4;
extern u16 D_800A65D6;
extern u16 D_800A65A8;
extern u16 D_800A65AA;

void func_800D1B00(void) {
    typedef struct {
        s32 pad00;
        s32 f04; s32 f08; s32 f0C; s32 f10; s32 f14; s32 f18;
        s32 f1C; s32 f20; s32 f24; s32 f28; s32 f2C; s32 f30;
        u16 f34;
        u8 f36; u8 f37;
        u16 f38; u16 f3A; u16 f3C; u16 f3E; u16 f40;
        u8 f42; u8 f43; u8 f44; u8 f45; u8 f46; u8 f47; u8 f48; u8 f49; u8 f4A; u8 f4B; u8 f4C;
        s32 f50; s32 f54; s32 f58; s32 f5C; s32 f60; s32 f64;
        u8 f68;
        s32 f6C; s32 f70; s32 f74; s32 f78; s32 f7C; s32 f80; s32 f84; s32 f88; s32 f8C; s32 f90; s32 f94;
    } St78;

    St78 *p = (St78 *)D_80078E78;

    p->f04 = 0;
    p->f08 = 0x258;
    p->f0C = 0x1A;
    p->f10 = 2;
    p->f14 = 0x64;
    p->f18 = 0x1FE0000;
    p->f1C = 0;
    p->f20 = 0;
    p->f24 = 0x640000;
    p->f28 = 0;
    p->f2C = 0x640000;
    p->f30 = 0;
    p->f34 = 1;
    p->f36 = 1;
    p->f37 = 1;
    p->f38 = 0x81E;
    p->f3A = 0x15E;
    p->f3C = 0x15E;
    p->f3E = 0x1C2;
    p->f40 = 0x1C2;
    p->f42 = 0;
    p->f43 = 0;
    p->f44 = 3;
    p->f45 = 0;
    p->f46 = 0;
    p->f47 = 0;
    p->f48 = 1;
    p->f49 = 0;
    p->f4A = 0;
    p->f4B = 0;
    p->f4C = 0;
    p->f50 = 0;
    p->f54 = 0;
    p->f58 = 0;
    p->f5C = 0;
    p->f60 = 0;
    p->f64 = 0;
    p->f68 = 0;
    p->f6C = 0x13;
    p->f70 = 0;
    p->f74 = 0x13;
    p->f78 = 0;
    p->f7C = 0x13;
    p->f80 = 0;
    p->f84 = 0x13;
    p->f88 = 0;
    p->f8C = 0;
    p->f90 = 0x5C44;
    p->f94 = 0x5C44;

    func_80029124(0xF5, 1);
    func_80029124(0x106, 1);
    func_80029124(0xF8, 1);
    func_80029124(0xFF, 1);
    func_80029124(0xF9, 1);
    func_80029124(0x105, 1);
    func_80029124(0x100, 1);
    func_80029124(0xFD, 1);
    func_80029124(0xFE, 1);
    func_80029124(0xFB, 1);
    func_80029124(0xF4, 1);
    func_80029124(0xF6, 1);
    func_80029124(0x17, 1);
    func_80029124(0x20, 1);
    func_80029124(0x1E, 1);
    func_80029124(0x83, 1);
    func_80029124(0x85, 1);
    func_80029124(0x86, 1);
    func_80029124(0x87, 1);
    func_80029124(0x8B, 1);
    func_80029124(0xB6, 1);
    func_80029124(0x1B, 1);
    func_80029124(0x48, 1);
    func_80029124(0x49, 1);
    func_80029124(0x4B, 1);

    func_800291A0(0x3B, 5);
    func_800291A0(0x3C, 3);
    func_800291A0(0x3D, 4);
    func_800291A0(0x3E, 3);
    func_800291A0(0x3F, 3);
    func_800291A0(0x40, 2);
    func_800291A0(0x41, 2);
    func_800291A0(0x42, 2);
    func_800291A0(0x43, 3);
    func_800291A0(0x44, 2);
    func_800291A0(0x45, 2);
    func_800291A0(0x46, 3);
    func_800291A0(0x47, 3);
    func_800291A0(0x48, 3);
    func_800291A0(0x49, 2);
    func_800291A0(0x4A, 3);
    func_800291A0(0x4B, 2);
    func_800291A0(0x4C, 3);
    func_800291A0(0x4D, 5);
    func_800291A0(0x4E, 2);
    func_800291A0(0x4F, 3);
    func_800291A0(0x50, 3);
    func_800291A0(0x51, 2);
    func_800291A0(0x52, 2);
    func_800291A0(0x53, 0);
    func_800291A0(0x54, 0);
    func_800291A0(0x55, 2);
    func_800291A0(0x56, 0);
    func_800291A0(0x57, 2);
    func_800291A0(0x58, 0);
    func_800291A0(0x59, 2);
    func_800291A0(0x5A, 3);
    func_800291A0(0x5B, 0);
    func_800291A0(0x5C, 0);
    func_800291A0(0x5D, 0);
    func_800291A0(0x5E, 3);
    func_800291A0(0x5F, 2);
    func_800291A0(0x60, 0);
    func_800291A0(0x61, 0);
    func_800291A0(0x62, 3);
    func_800291A0(0x2E, 3);

    func_800291A0(0x71, (D_8010F4D6 | 0x80) & 0xFF);
    func_800291A0(0x72, (D_8010F4DE | 0x80) & 0xFF);
    func_800291A0(0x73, (D_8010F4EE | 0x80) & 0xFF);
    func_800291A0(0x74, (D_8010F4E6 | 0x80) & 0xFF);
    func_800291A0(0x75, (D_8010F5AE | 0x80) & 0xFF);
    func_800291A0(0x76, (D_8010F4F6 | 0x80) & 0xFF);
    func_800291A0(0x6D, (D_8010F4FE | 0x80) & 0xFF);

    D_800A65A0 = D_8010F4D4;
    D_800A65A2 = D_8010F4DC;
    D_800A65A6 = D_8010F4EC;
    D_800A65A4 = D_8010F4E4;
    D_800A65D6 = D_8010F5AC;
    D_800A65A8 = D_8010F4F4;
    D_800A65AA = D_8010F4FC;

    func_80029124(0x101, 1);
    func_80029124(0x102, 1);
    func_80029124(0x103, 1);
    func_80029124(0x104, 1);
    func_80029124(0xB3, 1);
}


typedef struct {
    s32 unk00;
    s32 unk04;
    s32 unk08;
    s32 unk0C;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    s32 unk30;
    s16 unk34;
    u8 unk36;
    u8 unk37;
    s16 unk38;
    s16 unk3A;
    s16 unk3C;
    s16 unk3E;
    s16 unk40;
    u8 unk42;
    u8 unk43;
    u8 unk44;
    u8 unk45;
    u8 unk46;
    u8 unk47;
    u8 unk48;
    u8 unk49;
    u8 unk4A;
    u8 unk4B;
    u8 unk4C;
    u8 unk4D;
    s32 unk50;
    s32 unk54;
    s32 unk58;
    s32 unk5C;
    s32 unk60;
    s32 unk64;
    u8 unk68;
    u8 pad69[3];
    s32 unk6C;
    s32 unk70;
    s32 unk74;
    s32 unk78;
    s32 unk7C;
    s32 unk80;
    s32 unk84;
    s32 unk88;
    s32 unk8C;
    s32 unk90;
    s32 unk94;
} Gs_80078E78;

extern u8 D_80078E78[];
extern void func_80029124(s32 arg0, s32 arg1);
extern void func_800291A0(s32 arg0, s32 arg1);
extern u16 D_8010F504;
extern u16 D_8010F50C;
extern u16 D_8010F514;
extern u16 D_8010F51C;
extern u16 D_8010F524;
extern u16 D_8010F52C;
extern u16 D_800A65AC;
extern u16 D_800A65AE;
extern u16 D_800A65B0;
extern u16 D_800A65B2;
extern u16 D_800A65B4;
extern u16 D_800A65B6;
extern u8 D_8010F506;
extern u8 D_8010F50E;
extern u8 D_8010F516;
extern u8 D_8010F51E;
extern u8 D_8010F526;
extern u8 D_8010F52E;

void func_800D235C(void) {
    Gs_80078E78 *st;

    st = (Gs_80078E78 *)D_80078E78;
    st->unk04 = 0;
    st->unk08 = 0x384;
    st->unk0C = 0x20;
    st->unk10 = 3;
    st->unk14 = 0x64;
    st->unk18 = 0x1FE0000;
    st->unk1C = 0;
    st->unk20 = 0;
    st->unk24 = 0x640000;
    st->unk28 = 0;
    st->unk2C = 0x640000;
    st->unk30 = 0;
    st->unk34 = 1;
    st->unk36 = 1;
    st->unk37 = 1;
    st->unk38 = 0x81E;
    st->unk3A = 0x19F;
    st->unk3C = 0x19F;
    st->unk3E = 0x1F4;
    st->unk40 = 0x1F4;
    st->unk42 = 0;
    st->unk43 = 0;
    st->unk44 = 3;
    st->unk45 = 0;
    st->unk46 = 0;
    st->unk47 = 0;
    st->unk48 = 1;
    st->unk49 = 0;
    st->unk4A = 0;
    st->unk4B = 0;
    st->unk4C = 0;
    st->unk6C = 0x18;
    st->unk70 = 0;
    st->unk74 = 0x18;
    st->unk78 = 0;
    st->unk7C = 0x18;
    st->unk80 = 0;
    st->unk84 = 0x18;
    st->unk88 = 0;
    st->unk8C = 0;
    st->unk90 = 0x7E90;
    st->unk94 = 0x7E90;
    st->unk50 = 0;
    st->unk54 = 0;
    st->unk58 = 0;
    st->unk5C = 0;
    st->unk60 = 0;
    st->unk64 = 0;
    st->unk68 = 0;
    func_80029124(0x10D, 1);
    func_80029124(0x107, 1);
    func_80029124(0x18, 1);
    func_80029124(0x1D, 1);
    func_80029124(0x21, 1);
    func_80029124(0x81, 1);
    func_80029124(0x8C, 1);
    func_80029124(0xC7, 1);
    func_80029124(0xC8, 1);
    func_80029124(0xC9, 1);
    func_80029124(0xCA, 1);
    func_80029124(0xCB, 1);
    func_80029124(0xCC, 1);
    func_80029124(0xCD, 1);
    func_80029124(0xCE, 1);
    func_80029124(0xCF, 1);
    func_80029124(0xD0, 1);
    func_80029124(0xD1, 1);
    func_80029124(0xD2, 1);
    func_80029124(0xD3, 1);
    func_80029124(0xD4, 1);
    func_80029124(0xD5, 1);
    func_80029124(0xD6, 1);
    func_80029124(0xD7, 1);
    func_80029124(0xD8, 1);
    func_80029124(0xD9, 1);
    func_80029124(0x9B, 1);
    func_80029124(0x81, 1);
    func_800291A0(0x3B, 9);
    func_800291A0(0x3C, 3);
    func_800291A0(0x3D, 4);
    func_800291A0(0x3E, 3);
    func_800291A0(0x3F, 3);
    func_800291A0(0x40, 2);
    func_800291A0(0x41, 2);
    func_800291A0(0x42, 2);
    func_800291A0(0x43, 3);
    func_800291A0(0x44, 2);
    func_800291A0(0x45, 2);
    func_800291A0(0x46, 3);
    func_800291A0(0x47, 3);
    func_800291A0(0x48, 3);
    func_800291A0(0x49, 2);
    func_800291A0(0x4A, 4);
    func_800291A0(0x4B, 2);
    func_800291A0(0x4C, 3);
    func_800291A0(0x4D, 5);
    func_800291A0(0x4E, 2);
    func_800291A0(0x4F, 3);
    func_800291A0(0x50, 4);
    func_800291A0(0x51, 2);
    func_800291A0(0x52, 3);
    func_800291A0(0x53, 2);
    func_800291A0(0x54, 3);
    func_800291A0(0x55, 3);
    func_800291A0(0x56, 2);
    func_800291A0(0x57, 2);
    func_800291A0(0x58, 2);
    func_800291A0(0x59, 3);
    func_800291A0(0x5A, 3);
    func_800291A0(0x5B, 0);
    func_800291A0(0x5C, 0);
    func_800291A0(0x5D, 2);
    func_800291A0(0x5E, 3);
    func_800291A0(0x5F, 2);
    func_800291A0(0x60, 2);
    func_800291A0(0x61, 0);
    func_800291A0(0x62, 3);
    func_800291A0(0x2E, 4);
    func_800291A0(0x78, ((D_8010F506 | 0x80) & 0xFF));
    func_800291A0(0x79, ((D_8010F50E | 0x80) & 0xFF));
    func_800291A0(0x7A, ((D_8010F516 | 0x80) & 0xFF));
    func_800291A0(0x7C, ((D_8010F51E | 0x80) & 0xFF));
    func_800291A0(0x7D, ((D_8010F526 | 0x80) & 0xFF));
    func_800291A0(0x7E, ((D_8010F52E | 0x80) & 0xFF));
    D_800A65AC = D_8010F504;
    D_800A65AE = D_8010F50C;
    D_800A65B0 = D_8010F514;
    D_800A65B2 = D_8010F51C;
    D_800A65B4 = D_8010F524;
    D_800A65B6 = D_8010F52C;
    func_80029124(0xC4, 1);
    func_80029124(0xC5, 1);
    func_80029124(0xC6, 1);
    func_80029124(0x56, 1);
    func_80029124(0x57, 1);
    func_80029124(0x58, 1);
}


typedef struct {
    s8 pad00[4];
    s32 unk04;
    s32 unk08;
    s32 unk0C;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    s32 unk30;
    s16 unk34;
    u8 unk36;
    u8 unk37;
    s16 unk38;
    s16 unk3A;
    s16 unk3C;
    s16 unk3E;
    s16 unk40;
    u8 unk42;
    u8 unk43;
    u8 unk44;
    u8 unk45;
    u8 unk46;
    u8 unk47;
    u8 unk48;
    u8 unk49;
    u8 unk4A;
    u8 unk4B;
    u8 unk4C;
    s32 unk50;
    s32 unk54;
    s32 unk58;
    s32 unk5C;
    s32 unk60;
    s32 unk64;
    u8 unk68;
    s32 unk6C;
    s32 unk70;
    s32 unk74;
    s32 unk78;
    s32 unk7C;
    s32 unk80;
    s32 unk84;
    s32 unk88;
    s32 unk8C;
    s32 unk90;
    s32 unk94;
} S2BC4;

void func_800D2BC4(void) {
    extern u8 D_80078E78[];
    extern void func_80029124(s32, s32);
    extern void func_800291A0(s32, s32);
    extern u8 D_8010F536;
    extern u16 D_8010F534;
    extern u16 D_800A65B8;
    S2BC4 *p = (S2BC4 *)D_80078E78;

    p->unk04 = 0;
    p->unk08 = 0x4B0;
    p->unk0C = 0x23;
    p->unk10 = 7;
    p->unk14 = 0x64;
    p->unk18 = 0x1FE0000;
    p->unk1C = 0;
    p->unk20 = 0;
    p->unk24 = 0x640000;
    p->unk28 = 0;
    p->unk2C = 0x640000;
    p->unk30 = 0;
    p->unk34 = 1;
    p->unk36 = 1;
    p->unk37 = 1;
    p->unk38 = 0x81E;
    p->unk3A = 0x1D1;
    p->unk3C = 0x1D1;
    p->unk3E = 0x1F4;
    p->unk40 = 0x1F4;
    p->unk42 = 0;
    p->unk43 = 0;
    p->unk44 = 3;
    p->unk45 = 0;
    p->unk46 = 0;
    p->unk47 = 0;
    p->unk48 = 1;
    p->unk49 = 0;
    p->unk4A = 0;
    p->unk4B = 0;
    p->unk4C = 0;
    p->unk50 = 0;
    p->unk54 = 0;
    p->unk58 = 0;
    p->unk5C = 0;
    p->unk60 = 0;
    p->unk64 = 0;
    p->unk68 = 0;
    p->unk6C = 0x1C;
    p->unk70 = 0;
    p->unk74 = 0x1C;
    p->unk78 = 0;
    p->unk7C = 0x1C;
    p->unk80 = 0;
    p->unk84 = 0x1C;
    p->unk88 = 0;
    p->unk8C = 0;
    p->unk90 = 0x9C72;
    p->unk94 = 0x9C72;

    func_80029124(0x19, 1);
    func_80029124(0x1D, 1);
    func_80029124(0x21, 1);
    func_80029124(0x8D, 1);
    func_80029124(0x89, 1);
    func_80029124(0xBD, 1);
    func_80029124(0xBE, 1);
    func_80029124(0xBF, 1);
    func_80029124(0xC0, 1);
    func_80029124(0xC1, 1);
    func_80029124(0xC2, 1);
    func_80029124(0xC3, 1);
    func_80029124(0x4A, 1);
    func_80029124(0x4C, 1);

    func_800291A0(0x3B, 0xD);
    func_800291A0(0x3C, 3);
    func_800291A0(0x3D, 4);
    func_800291A0(0x3E, 3);
    func_800291A0(0x3F, 3);
    func_800291A0(0x40, 2);
    func_800291A0(0x41, 2);
    func_800291A0(0x42, 2);
    func_800291A0(0x43, 3);
    func_800291A0(0x44, 2);
    func_800291A0(0x45, 2);
    func_800291A0(0x46, 3);
    func_800291A0(0x47, 3);
    func_800291A0(0x48, 3);
    func_800291A0(0x49, 2);
    func_800291A0(0x4A, 4);
    func_800291A0(0x4B, 2);
    func_800291A0(0x4C, 3);
    func_800291A0(0x4D, 5);
    func_800291A0(0x4E, 2);
    func_800291A0(0x4F, 3);
    func_800291A0(0x50, 4);
    func_800291A0(0x51, 2);
    func_800291A0(0x52, 3);
    func_800291A0(0x53, 2);
    func_800291A0(0x54, 3);
    func_800291A0(0x55, 3);
    func_800291A0(0x56, 2);
    func_800291A0(0x57, 2);
    func_800291A0(0x58, 2);
    func_800291A0(0x59, 3);
    func_800291A0(0x5A, 3);
    func_800291A0(0x5B, 3);
    func_800291A0(0x5C, 2);
    func_800291A0(0x5D, 2);
    func_800291A0(0x5E, 3);
    func_800291A0(0x5F, 2);
    func_800291A0(0x60, 3);
    func_800291A0(0x61, 2);
    func_800291A0(0x62, 3);
    func_800291A0(0x2E, 5);
    func_800291A0(0x7F, (u8)(D_8010F536 | 0x80));

    D_800A65B8 = D_8010F534;

    func_80029124(0xBB, 1);
}

