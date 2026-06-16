#include "common.h"

/* func_800CEDFC:
 *   v1 = D_800B99F0 (u16, lhu)
 *   if ((u32)v1 < 0x14)  [sltiu, beqz]
 *       D_800D3430[v1]()   ; function-pointer table, sll v1,2 -> word index
 *   return (void)
 *
 * The frame (sw ra; addiu sp,-0x18) is allocated because of the indirect call.
 */
extern u16 D_800B99F0;
extern void (*D_800D3430[])(void);

void func_800CEDFC(void) {
    u16 idx = D_800B99F0;
    if (idx < 0x14) {
        D_800D3430[idx]();
    }
}

extern u16 D_800B99F6;
extern void (*D_800D3480[])(void);

void func_800CEE40(void) {
    if (D_800B99F6 < 2) {
        D_800D3480[D_800B99F6]();
    }
}

extern s16 D_800B9A00;
extern s32 D_80127084;
extern s32 D_80114E78;
extern void func_80029344(void);
extern void func_8001B324(void);
extern void func_8002AEF8(void);
extern void func_80029254(void);
extern void func_800CFBBC(void);
extern void func_80011DCC(void);
extern void func_80010AE0(s32);
extern void func_80011C10(void);
void func_800CEE84(void) {
    func_80029344();
    D_80127084 = 0;
    D_80114E78 = 0;
    if (D_800B9A00 != 0) {
        D_80127084 = 1;
    }
    func_8001B324();
    func_8002AEF8();
    func_80029254();
    func_800CFBBC();
    func_80011DCC();
    func_80010AE0(0x3E0);
    func_80011C10();
}

extern s32 func_800D0488(s32);
extern void func_80011A3C(void);

void func_800CEF04(void) {
    if (func_800D0488(1)) {
        func_80011A3C();
    }
}

extern void func_8001B324(void);
extern void func_80011A3C(void);

void func_800CEF34(void) {
    func_8001B324();
    func_80011A3C();
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800CEF5C);

extern void func_80011A3C(void);

void func_800CEFB0(void) {
    func_80011A3C();
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800CEFD0);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800CF104);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800CF238);

/* func_800CF370:
 *   jal func_8001A9F8(0)
 *   jal func_80011B7C(0xF)
 *   return (void)
 */
extern void func_8001A9F8(s32);
extern void func_80011B7C(s32);

void func_800CF370(void) {
    func_8001A9F8(0);
    func_80011B7C(0xF);
}

extern void func_80011A3C(void);

void func_800CF398(void) {
    func_80011A3C();
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800CF3B8);

extern s32 D_80114E78;
extern u8 D_800AF218;
extern s32 func_8001ABBC(s32 arg0, s32 arg1, u8 *arg2, s32 arg3, s32 arg4);
extern void func_80011C10(void);

void func_800CF47C(void) {
    if (D_80114E78 != 0) {
        if (func_8001ABBC(0, 0, &D_800AF218, 0, 0) == 0) {
            return;
        }
        D_80114E78 = 0;
    }
    func_80011C10();
}

extern u16 D_800B99FC;
extern void (*D_800D3490[])(void);

void func_800CF4D4(void) {
    D_800D3490[D_800B99FC]();
}

extern u8 D_800B9A11;
extern s32 D_80127084;
extern s16 D_801152BA;
extern void func_80014928(void);
extern void func_8001C0C8(void);
extern void func_80015310(void);
extern void func_8001B384(void);
extern void func_80011CFC(void);
extern void func_80011D54(s32 arg0);

void func_800CF510(void) {
    func_80014928();
    D_800B9A11 = 1;
    func_8001C0C8();
    func_80015310();
    func_8001B384();
    D_801152BA = 0;
    if (D_80127084 != 0) {
        func_80011CFC();
    } else {
        func_80011D54(3);
    }
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800CF584);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800CF5D4);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800CF628);

extern s32 D_80114E94;
extern s16 currentLocationId;
extern void func_800191A8(void);
extern s32 func_800CFE60(void);
extern void func_800CFDA4(void);
extern void func_80011CFC(void);

void func_800CF714(void) {
    func_800191A8();
    if (func_800CFE60() != 0) {
        func_800CFDA4();
        currentLocationId = D_80114E94;
        func_80011CFC();
    }
}

extern s32 func_80128218(void);
extern s32 func_800D0214(s32);
extern s32 D_80127084;
extern s32 D_80114E98;

void func_800CF764(void) {
    if (func_800D0214(func_80128218())) {
        D_80127084 = 0;
        D_80114E98 = 1;
    }
}

extern s32 D_80127084;
extern s32 D_80114E98;
extern void func_800191A8(void);
extern s32 func_8001AF04(void);
extern s32 func_800CFE60(void);
extern void func_800CFDA4(void);

void func_800CF7A4(void) {
    func_800191A8();
    if (func_8001AF04() == 2) {
        return;
    }
    if (func_800CFE60() == 0) {
        return;
    }
    func_800CFDA4();
    D_80127084 = 0;
    D_80114E98 = 1;
}

void func_800CF804(void) {
    D_80127084 = 1;
}

void func_800CF818(void) {
    D_80114E78 = 1;
}

extern s16 D_800B9A0E;
void func_800CF82C(void) {
    D_800B9A0E = 1;
}

void func_800CF840(void) {
    D_800B9A0E = 2;
}

extern u8 D_800AE6BF;
s32 func_800CF854(void) {
    return D_800AE6BF != 0;
}

extern s16 currentLocationId;
extern u16 D_80126B58;
extern s32 func_800CF8B4(void);

s32 func_800CF864(void) {
    if (currentLocationId == 0x3069) {
        return 1;
    }
    if (D_80126B58 == 0x1A) {
        return 1;
    }
    return func_800CF8B4();
}

extern u16 D_800B99F0;

s32 func_800CF8B4(void) {
    return D_800B99F0 == 9;
}

extern u16 D_800B99F0;

s32 func_800CF8CC(void) {
    return D_800B99F0 == 0xA;
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800CF8E4);

extern u8 D_800AE890;
extern void *D_80072C74;
extern int CdReadRequest(void *dst, void *src, int arg2, int arg3);
extern void func_80011A3C(void);

void func_800CF94C(void) {
    if (CdReadRequest(&D_800AE890, D_80072C74, 0, 0) != 0) {
        func_80011A3C();
    }
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800CF990);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800CFAD0);

extern u16 D_80114E70;

void func_800CFBBC(void) {
    D_80114E70 = 0;
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800CFBCC);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800CFBE8);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800CFBF8);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800CFC5C);

extern s32 D_800D34AC[];
extern void func_800191D4(s32 arg0);

void func_800CFD68(s32 arg0) {
    func_800191D4(D_800D34AC[arg0 & 0xFFFF0FFF] & 0xFFF);
}

extern s16 currentLocationId;
extern s32 D_800D34AC[];
extern void func_800191BC(s32 arg0);

void func_800CFDA4(void) {
    func_800191BC(D_800D34AC[currentLocationId & 0xFFFF0FFF] & 0xFFF);
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800CFDE8);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800CFE60);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D00E4);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D0214);

extern s32 D_800D375C;

void func_800D02C0(s32 arg0) {
    D_800D375C = arg0;
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D02D0);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D0488);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D0588);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D05E8);

extern void func_800D065C(void);
extern s32 D_8011529C;

void func_800D0630(void) {
    func_800D065C();
    D_8011529C = -1;
}

extern s32 D_801151F8;
extern s32 D_80126AE8;
extern s32 D_80127500;
extern s32 D_8012704C;
extern s32 D_801201F0;
extern s32 D_80127050;

void func_800D065C(void) {
    D_801151F8 = 0;
    D_80126AE8 = 0;
    D_80127500 = 0;
    D_8012704C = 0;
    D_801201F0 = 0;
    D_80127050 = 0;
}

extern s32 D_801151F8;
extern s32 D_80126AE8;
extern s32 D_80127500;
extern s32 D_8012704C;
extern s32 D_801201F0;
extern s32 D_80127050;

void func_800D0694(void) {
    D_801151F8 = 0;
    D_80126AE8 = 0;
    D_80127500 = 0;
    D_8012704C = 0;
    D_801201F0 = 0;
    D_80127050 = 0;
}

extern s32 D_801151F8;
extern s32 D_80127500;

void func_800D06CC(void) {
    D_801151F8 = 3;
    D_80127500 = 3;
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D06E8);

extern s32 resLoad_lastId;
extern void func_8002D4C8(s32 arg0, s32 arg1);

void func_800D0C48(u16 arg0) {
    func_8002D4C8(1, arg0);
    resLoad_lastId = 0;
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D0C74);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D0CA0);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D0CE0);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D0D7C);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D0E30);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D0EC4);

extern s16 D_80078EAC;
extern void func_800291A0(s32, s32);
extern void func_800291C8(s32, s32);

void func_800D0F0C(s32 arg0, s32 arg1) {
    func_800291A0(arg0, arg1 & 0xFF);
    func_800291C8((arg0 << 1) - 0x4A, D_80078EAC);
}

// ANALYSIS: a0 masked to u8, passed to func_800D0F8C. Result in callee-saved s0
// (live across 2nd call). If result != 0: call func_800D0FE0(result), return result.
// Else return 0. beqz s0 with v0 preset to 0 in delay slot; nonzero path is fall-through.
extern s32 func_800D0F8C(u8 arg0);
extern void func_800D0FE0(s32 arg0);

s32 func_800D0F4C(u8 arg0) {
    s32 v0 = func_800D0F8C(arg0);
    if (v0 != 0) {
        func_800D0FE0(v0);
        return v0;
    }
    return 0;
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D0F8C);

extern void func_800291A0(s32 arg0, s32 arg1);

void func_800D0FE0(s32 arg0) {
    func_800291A0(arg0, 0);
}

extern s32 func_800291DC(s32);

s16 func_800D1000(s32 arg0) {
    return func_800291DC(arg0 * 2 - 0x4A);
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D1028);

extern s32 D_8010EDE8[];

s32 func_800D1054(s32 arg0) {
    return D_8010EDE8[(arg0 & 0xFF) * 3];
}

// ANALYSIS: andi a0,0xff (u8 idx); index = idx*0xC; return lh at D_8010EDEC + idx*0xC.
// Array of 0xC-byte records, s16 field at offset 0.
extern s16 D_8010EDEC;

s16 func_800D1078(u8 arg0) {
    return *(s16 *)((u8 *)&D_8010EDEC + arg0 * 0xC);
}

// ANALYSIS: t = func_800291B4(); return (s16)func_800D10C8(t & 0xff);
// andi a0,v0,0xff lands in the jal delay slot (arg to func_800D10C8).
// sll/sra 16 => sign-extend the s16 return to s32.
extern s32 func_800291B4(void);
extern s32 func_800D10C8(s32);

s32 func_800D109C(void) {
    return (s16)func_800D10C8(func_800291B4() & 0xff);
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D10C8);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D10EC);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D11F0);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D128C);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D1658);

extern u16 D_80078E50;
u16 func_800D1714(void) {
    return D_80078E50;
}

extern s32 D_800AE6B0;
void func_800D1724(s32 arg0) {
    D_800AE6B0 = arg0;
}

extern s32 D_800AE6A8;

void func_800D1734(s32 arg0) {
    D_800AE6A8 = arg0;
}

extern s32 D_800AE6AC;

void func_800D1744(s32 arg0) {
    D_800AE6AC = arg0;
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D1754);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D17B8);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D185C);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D18DC);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D1938);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D1984);

extern s8 D_800B9A10;

s32 func_800D19DC(void) {
    D_800B9A10 = 1;
    return 1;
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D19F0);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D1B10);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D1B80);

extern void func_800D1BF8(void);

s32 DsMix(void) {
    func_800D1BF8();
    return 1;
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D1BF8);

/* func_800D1D24:
 *   v0 = D_80078E50 (u16)
 *   a0 = D_800B9A0A (u16, old value)
 *   D_800B9A11 = 1
 *   currentLocationId = v0
 *   D_800B9A0C = a0          (old D_800B9A0A)
 *   D_800B9A0A = v0 & 0xF000
 *   func_8001C0C8(); func_80015310(); func_80129258(); func_801378F0();
 */
extern u16 D_80078E50;
extern u16 D_800B9A0A;
extern u8  D_800B9A11;
extern s16 currentLocationId;
extern s16 D_800B9A0C;
extern void func_8001C0C8(void);
extern void func_80015310(void);
extern void func_80129258(void);
extern void func_801378F0(void);

void func_800D1D24(void) {
    u16 v0 = D_80078E50;
    u16 old = D_800B9A0A;
    D_800B9A11 = 1;
    currentLocationId = v0;
    D_800B9A0C = old;
    D_800B9A0A = v0 & 0xF000;
    func_8001C0C8();
    func_80015310();
    func_80129258();
    func_801378F0();
}

extern u16 D_80078E50;

s32 func_800D1D94(void) {
    return (s32)((D_80078E50 & 0xF000) << 16) >> 16;
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D1DB0);

void func_800D1E20(void) {
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D1E28);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D1EBC);

extern u16 D_80078EB4;
extern u16 D_80078EB8;
extern s32 D_80078E8C;
extern s32 D_8011DB14;
extern s32 D_8011DB1C;
extern s32 D_80128150;

void func_800D1F58(void) {
    D_8011DB14 = D_80078EB4;
    D_8011DB1C = D_80078EB8;
    D_80128150 = D_80078E8C;
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D1F90);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D1FC8);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D20C0);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D21C4);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D222C);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D2294);

typedef struct {
    /* 0x00 */ s32 f0;
    /* 0x04 */ s32 f4;
    /* 0x08 */ s32 f8;
    /* 0x0C */ s32 fC;
    /* 0x10 */ s32 f10;
    /* 0x14 */ s32 f14;
    /* 0x18 */ s32 f18;
} S800D22E4;

void func_800D22E4(S800D22E4 *p) {
    p->f4 += p->f10;
    p->f8 += p->f14;
    p->fC += p->f18;
}

// ANALYSIS: leaf-ish fn taking a struct* (a0=s3). Loads s32 at +0x2C, masks
// with 0x3FFFFFFF, extracts three signed bitfields via <<16>>19 / <<22>>19
// (signed /8-style scaled extracts), squares two of them, calls
// func_80047D3C(s1f^2 + s2f^2) -> r1, then ratan2(s0f,(s16)r1) -> r2 (stored
// negated at +0x12), then ratan2(s1f,s2f) -> r3 stored at +0x16, +0x1A=0.
// Risk: exact shift/extract idiom + mult/mflo ordering + the negate-in-delay-slot.

extern s32 func_80047D3C(s32 arg0);
extern s32 ratan2(s32 y, s32 x);

void func_800D2318(s32 *p) {
    s32 raw = p[0xB];                 /* *(s32*)((u8*)p + 0x2C) */
    u32 masked = (u32)raw & 0x3FFFFFFF;   /* u32 -> srl on the >> below (matches asm) */
    s32 s1f = (s32)(((masked >> 14) & 0xFFC0) << 16) >> 19;
    s32 s2f = (s32)(raw << 22) >> 19;
    s32 s0f = (s32)(((masked >> 4) & 0xFFC0) << 16) >> 19;
    s32 r1 = func_80047D3C(s1f * s1f + s2f * s2f);

    *(s16 *)((u8 *)p + 0x12) = -ratan2(s0f, (s16)r1);
    *(s16 *)((u8 *)p + 0x16) = ratan2(s1f, s2f);
    *(s16 *)((u8 *)p + 0x1A) = 0;
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D23D0);

void func_800D2460(void) {
}

extern void func_80016714(void *, s32);
extern u8 D_80115110[];
extern s32 D_8012751C;
extern s32 D_8011DB20;

void func_800D2468(void) {
    func_80016714(D_80115110, 0xC4);
    D_8012751C = 0;
    D_8011DB20 = 0;
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D24A0);

extern void (*D_8011DB24)(void);

void func_800D25FC(void) {
    D_8011DB24();
}

extern u8 D_800B9A13;
extern void func_8002D4C8(s32 arg0, s32 arg1);

void func_800D2624(void) {
    D_800B9A13 = 0;
    func_8002D4C8(0x15, 0);
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D2650);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D27DC);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D29F8);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D2CA8);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D2D10);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D2DAC);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D2DFC);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D2E20);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D2E6C);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D2EE8);

extern void (*D_800D39C4[])(void);

void func_800D2F0C(u8 *arg0) {
    D_800D39C4[arg0[0x15]]();
}

extern void func_800D33B8(void);
extern void func_800167B8(s32 arg0);

s32 func_800D2F48(u8 *arg0) {
    func_800D33B8();
    func_800167B8(0);
    arg0[0x15]++;
    return 0;
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D2F8C);

extern void (*D_800D39F0[])(void);

void func_800D2FB0(u8 *arg0) {
    D_800D39F0[arg0[0x15]]();
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D2FEC);

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D302C);

extern void func_800D1EBC(void);

void func_800D30A8(void) {
    func_800D1EBC();
}

extern void (*D_800D3A8C[])(void);

void func_800D30C8(void *arg0) {
    D_800D3A8C[*(u8 *)((u8 *)arg0 + 0x15)]();
}

/* func_800D3104: a0 is a struct pointer.
 *   lbu v0, 0x15(a0)        -> read u8 at +0x15
 *   addiu v1, zero, 0xA     -> 10
 *   sb v1, 0x19(a0)         -> store 10 at +0x19
 *   addiu v0, v0, 1         -> +1
 *   sb v0, 0x15(a0)         -> store back at +0x15
 *   return 0
 */
typedef struct {
    u8 pad15[0x15];
    u8 field_0x15;
    u8 pad16[0x3];
    u8 field_0x19;
} Struct800D3104;

s32 func_800D3104(Struct800D3104 *a0) {
    u8 v = a0->field_0x15;
    a0->field_0x19 = 0xA;
    a0->field_0x15 = v + 1;
    return 0;
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D3120);

extern u16 func_800167F0(s32 arg0);

s32 func_800D319C(void) {
    return func_800167F0(4) != 0;
}

extern void (*D_800D3920[])(void);

void func_800D31C0(u8 *arg0) {
    D_800D3920[arg0[0x15]]();
}

extern void (*D_800D3928[])(void);

void func_800D31FC(u8 *arg0) {
    D_800D3928[arg0[0x15]]();
}

// ANALYSIS: idx = *(u8*)(arg+0x214); fp = D_800D3A98[idx]; fp(arg).
// Function-pointer table dispatch; a0 (arg) preserved into the jalr.
extern void (*D_800D3A98[])();

void func_800D3238(void *arg0) {
    D_800D3A98[*(u8 *)((u8 *)arg0 + 0x214)](arg0);
}

extern s32 func_8013767C(s32);

void func_800D3274(u8 *arg0) {
    s32 w = *(s32 *)(arg0 + 0x198);
    if (w != 0) {
        *(s32 *)(arg0 + 0x198) = func_8013767C(w);
        *(u8 *)(arg0 + 0x214) = *(u8 *)(arg0 + 0x214) + 1;
    } else {
        *(u8 *)(arg0 + 0x214) = *(u8 *)(arg0 + 0x214) + 2;
    }
}

extern s32 func_801399F0(s32);
extern void func_80139914(s32);

void func_800D32D4(void *arg0) {
    if (func_801399F0(*(s32 *)((u8 *)arg0 + 0x198)) != 0) {
        func_80139914(*(s32 *)((u8 *)arg0 + 0x198));
        *(u8 *)((u8 *)arg0 + 0x214) += 1;
    }
}

extern void func_8016F0E4(void);

void func_800D3328(void) {
    func_8016F0E4();
}

extern void (*D_800D3AA4[])(void);

void func_800D3348(u8 *arg0) {
    D_800D3AA4[*(u8 *)(arg0 + 0x214)]();
}

void func_800D3384(u8 *arg0) {
    *(u8 *)(arg0 + 0x214) += 1;
}

extern void func_8016F0E4(void);

void func_800D3398(void) {
    func_8016F0E4();
}

INCLUDE_ASM("asm/resident/nonmatchings/resident", func_800D33B8);

extern u8 D_800D3AB0;
extern void func_8016EE40(u8 *arg0, s32 arg1);

void func_800D33E0(void) {
    func_8016EE40(&D_800D3AB0, 0x1000000);
}

